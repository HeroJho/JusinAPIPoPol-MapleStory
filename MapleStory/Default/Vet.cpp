#include "stdafx.h"
#include "Vet.h"
#include "EventMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

#include "Money.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "Player.h"
#include "UIMgr.h"
#include "QuestMgr.h"
#include "SkillMgr.h"

CVet::CVet()
	: m_pMonster(nullptr)
	, m_pDestMon(nullptr)
{

}

CVet::~CVet()
{
	Release();
}

void CVet::Initialize(void)
{
	m_pTarget = (CPlayer*)CObjMgr::Get_Instance()->Get_Player();
	CObj::m_pTarget = (CPlayer*)CObjMgr::Get_Instance()->Get_Player();
	Set_FrameKey(L"VetL");
	SetCurState(IDLE, DIR_LEFT);
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 1000.f;
	m_tFrame.dwTime = GetTickCount64();

	// 콜리젼 크기, 피봇 설정
	m_tInfo.fCCX = 25.f;
	m_tInfo.fCCY = 25.f;
	m_tColPivot.x = 0.f;
	m_tColPivot.y = -10.f;
	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 50.f;
	m_tInfo.fTCY = 40.f;

	Set_Stat(0, 0, 15);
	m_bCanHit = false;

	m_bJump = false;
	m_fSpeed = 0.4f;
	m_fJumpPower = 6.5f;

	m_pOldLine = nullptr;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;

	m_fTickCount = 100.f;
	m_fOldTickCount = 0.f;

	m_fAttackCount = 6000.f;
	m_fOldAttackCount = GetTickCount64();

	m_fMonX = 0.f;
	m_fMonY = 0.f;

	m_iHitCount = 0;
}

int CVet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (4 < m_iHitCount)
	{
		CSkillMgr::Get_Instance()->DecreaseVet();
		return OBJ_DEAD;
	}


	m_pMonster = CObjMgr::Get_Instance()->Get_RandomTarget(OBJ_MONSTER);
	if (m_pMonster == nullptr && m_eCurState != CHASE)
	{
		SetCurState(IDLE, m_eDir);
		m_bCanHit = false;
	}
	if ((m_fOldAttackCount + m_fAttackCount < GetTickCount64()))
	{
		if(m_pMonster)
			SetCurState(ATTACK, m_eDir);

		m_fOldAttackCount = GetTickCount64();
	}

	switch (m_eCurState)
	{
	case IDLE:
		Update_Idle();
		break;
	case CHASE:
		Update_Chase();
		break;
	case ATTACK:
		Update_Attack();
		break;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CVet::Late_Update(void)
{
	// Update_Gravity();

	if (!m_bStayPlay)
	{
		Motion_Change();
		Move_Frame();
	}
}

void CVet::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		int(m_tTRect.left + iScrollX),
		int(m_tTRect.top - 22 + iScrollY),
		int(m_tInfo.fTCX),
		int(m_tInfo.fTCY),
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tInfo.fTCX,
		m_tFrame.iMotion * (int)m_tInfo.fTCY,
		(int)m_tInfo.fTCX,
		(int)m_tInfo.fTCY,
		RGB(255, 0, 255));

}

void CVet::Release(void)
{

}

void CVet::OnHit(CObj* _pOther)
{

}

void CVet::SetCurState(STATE _eState, DIRECTION _eDir)
{
	if (_eDir == DIR_LEFT)
		m_pFrameKey = L"VetL";
	else
		m_pFrameKey = L"VetR";

	m_eDir = _eDir;
	m_eCurState = _eState;
}


void CVet::Update_Idle()
{
	// 일정 범위 떨어지면 초기화
	float fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	float fY = m_pTarget->Get_Info().fY - m_tInfo.fY;
	if (400.f < fX || -400.f > fX || 200.f < fY || -200.f > fY)
	{
		int iRX = CEventMgr::Get_Instance()->GetRandomNum_Int(-30, 30);
		m_tInfo.fX = m_pTarget->Get_Info().fX + iRX;
		m_tInfo.fY = m_pTarget->Get_Info().fY;
		SetCurState(IDLE, m_eDir);
	}


	if (m_fOldTickCount + m_fTickCount < GetTickCount64())
	{
		m_fSpeed = CEventMgr::Get_Instance()->GetRandomNum_float(1.f, 3.f);
		m_fAngle = CEventMgr::Get_Instance()->GetRandomNum_float(-20.f, 20.f);

		if (CEventMgr::Get_Instance()->GetRandomNum_Int(0, 1))
			m_fAngle += 180.f;


		m_fTickCount = CEventMgr::Get_Instance()->GetRandomNum_float(600.f, 800.f);
		m_fOldTickCount = GetTickCount64();
	}

	float fDirX = m_fSpeed * 1.2f * cosf(m_fAngle * PI / 180.f);
	if (fDirX < 0)
		m_eDir = DIR_LEFT;
	else
		m_eDir = DIR_RIGHT;
	SetCurState(IDLE, m_eDir);

	m_tInfo.fX += fDirX;
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);

	if (70.f < fX || -70.f > fX || 90.f < fY || 0.f > fY)
	{
		SetCurState(CHASE, m_eDir);
	}
}

void CVet::Update_Chase()
{
	// 일정 범위 떨어지면 초기화
	float fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	float fY = m_pTarget->Get_Info().fY - m_tInfo.fY;
	if (400.f < fX || -400.f > fX || 200.f < fY || -200.f > fY)
	{
		int iRX = CEventMgr::Get_Instance()->GetRandomNum_Int(-30, 30);
		m_tInfo.fX = m_pTarget->Get_Info().fX + iRX;
		m_tInfo.fY = m_pTarget->Get_Info().fY;
		SetCurState(IDLE, m_eDir);
	}


	float		fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
	float		fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;
	fHeight += 20;
	float		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);
	float		fRadian = acosf(fWidth / fDiagonal);

	m_fAngle = fRadian * 180.f / PI;

	if (m_tInfo.fY < m_pTarget->Get_Info().fY - 20)
		m_fAngle *= -1.f;

	m_tInfo.fX += 2.5f * cosf(m_fAngle * PI / 180.f);
	m_tInfo.fY -= 2.5f * sinf(m_fAngle * PI / 180.f);

	if (0 < fWidth)
		m_eDir = DIR_RIGHT;
	else
		m_eDir = DIR_LEFT;
	SetCurState(CHASE, m_eDir);

	if (100 > fWidth && -100 < fWidth && 100 > fHeight && 10 < fHeight)
	{
		SetCurState(IDLE, m_eDir);
		return;
	}
}

void CVet::Update_Attack()
{
	if (!m_bCanHit)
	{
		if (m_pMonster != nullptr)
		{
			m_fMonX = m_pMonster->Get_Info().fX;
			m_fMonY = m_pMonster->Get_Info().fY;
			m_pDestMon = m_pMonster;
			m_bCanHit = true;
		}
		else
		{
			SetCurState(IDLE, m_eDir);
			m_bCanHit = false;
		}
	}
		

	float		fWidth =	m_fMonX - m_tInfo.fX;
	float		fHeight =   m_fMonY - m_tInfo.fY;
	// fHeight += 20;
	float		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);
	float		fRadian = acosf(fWidth / fDiagonal);

	m_fAngle = fRadian * 180.f / PI;

	if (m_tInfo.fY < m_fMonY)
		m_fAngle *= -1.f;

	m_tInfo.fX += 10.f * cosf(m_fAngle * PI / 180.f);
	m_tInfo.fY -= 10.f * sinf(m_fAngle * PI / 180.f);

	if (fDiagonal < 10)
	{
		SetCurState(ATTACK, m_eDir);
		m_bCanHit = false;
	}

}

void CVet::OnCollision(CObj* _pOther)
{
	if (!_pOther->Get_CanHit())
		return;

	if (_pOther->Get_Tag() == "Monster")
	{
		if (_pOther == m_pDestMon)
		{
			++m_iHitCount;
			m_bCanHit = false;
			_pOther->OnHit(this);
			CUIMgr::Get_Instance()->MakeDamge(1, 1.f, m_tStat.iAt * m_tStat.iAt * 500, m_tStat.iAt * m_tStat.iAt * 600, _pOther->Get_Info().fX, _pOther->Get_Info().fY, 120.f, 35.f);
		}
	}
}

void CVet::OnePlayEnd(void)
{
	m_tFrame.iFrameStart = 2;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iMotion = 1;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
}

void CVet::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case CHASE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount64();
			break;
		}

		m_ePreState = m_eCurState;
	}
}