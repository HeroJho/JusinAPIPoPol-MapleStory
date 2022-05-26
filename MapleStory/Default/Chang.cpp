#include "stdafx.h"
#include "Chang.h"
#include "AbstractFactory.h"

#include "EventMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SpawnMgr.h"

#include "Skill.h"
#include "ObjMgr.h"
#include "MoneyBig.h"
#include "Player.h"
#include "DarkedMage.h"
#include "SoundMgr.h"

CChang::CChang()
	: m_fOldTime(GetTickCount64())
	, m_fRandTime(0.f)
{

}

CChang::~CChang()
{
	Release();
}

void CChang::Initialize(void)
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_MONE);
	CSoundMgr::Get_Instance()->PlaySound(L"BlackSkill_4.wav", SOUND_MONE, 1);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/DarkedMage/Skill_5/Skill_5.bmp", L"Skill_5");

	Set_FrameKey(L"Skill_5");
	SetCurState(REION, DIR_LEFT);
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 500.f;
	m_tFrame.dwTime = GetTickCount64();



	// 콜리젼 크기, 피봇 설정
	m_tInfo.fCCX = 50.f;
	m_tInfo.fCCY = 80.f;
	m_tColPivot.x = 0.f;
	m_tColPivot.y = -35.f;
	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 400.f;
	m_tInfo.fTCY = 400.f;

	Set_Stat(500, 0, 5);

	m_fSpeed = 1.f;

	m_bCanHit = true;
	m_pOldLine = nullptr;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;


	//m_fAttackRange = 170.f;
	m_fAttackTime = 3000.f;
	m_fOldAttackTime = GetTickCount64();

	m_fRegionTime = 1600.f;
	m_fOldRegionTime = GetTickCount64();

	m_fHitTime = 1000.f;
	m_fOldHitTime = GetTickCount64();

	m_fOldChaseTime = 0.f;
	m_fChaseTime = 5000.f;
	m_fOldDeadTime = 0.f;
	m_fDeadTime = 2500.f;
}

int CChang::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	switch (m_eCurState)
	{
	case REION:
		Update_Region();
		break;
	case IDLE:
		Update_Idle();
		break;
	case ATTACK:
		Update_Attack();
		break;
	case DEAD:
		Update_Dead();
		break;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CChang::Late_Update(void)
{
	//pdate_Gravity();

	Motion_Change();
	if (!m_bStayPlay)
	{
		Move_Frame();
	}
}

void CChang::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 									// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tTRect.left + iScrollX),					// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tTRect.top - 75 + iScrollY),
		int(m_tInfo.fTCX),								// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fTCY),
		hMemDC,											// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fTCX,		// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fTCY,
		(int)m_tInfo.fTCX,								// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fTCY,
		RGB(255, 0, 255));								// 제거하고자 하는 색상
}

void CChang::Release(void)
{

}

void CChang::SetCurState(STATEA _eState, DIRECTION _eDir)
{
	m_eDir = _eDir;
	m_eCurState = _eState;
}


void CChang::Update_Region()
{
	if (m_fOldRegionTime + m_fRegionTime < GetTickCount64())
	{
		SetCurState(IDLE, m_eDir);
		m_fOldAttackTime = GetTickCount64();
	}
}

void CChang::Update_Idle()
{
	float		fWidth = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX - m_tInfo.fX;
	float		fHeight = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY - m_tInfo.fY;

	float		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);
	float		fRadian = acosf(fWidth / fDiagonal);

	m_fAngle = fRadian * 180.f / PI;

	if (m_tInfo.fY < CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY)
		m_fAngle *= -1.f;


	m_tInfo.fX += m_fSpeed * cosf(m_fAngle * PI / 180.f);
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);

	if (m_eCurState != DEAD && !m_bCanHit && m_fOldHitTime + m_fHitTime < GetTickCount64())
	{
		m_bCanHit = true;
	}
}

void CChang::Update_Attack()
{
}

void CChang::Update_Dead()
{
	if (m_fOldDeadTime + m_fDeadTime < GetTickCount64())
	{
		m_bDead = true;
	}
}



void CChang::OnHit(CObj* _pOther)
{
	m_tStat.iHp -= _pOther->Get_Stat().iAt;
	if (m_tStat.iHp <= 0.f)
	{
		SetCurState(DEAD, m_eDir);
		m_fOldDeadTime = GetTickCount64();
		m_bCanHit = false;

		CSoundMgr::Get_Instance()->StopSound(SOUND_MONE5);
		CSoundMgr::Get_Instance()->PlaySound(L"ChangOut.wav", SOUND_MONE5, 1);
		return;
	}
}

void CChang::DropItem()
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CMoneyBig>::Create(m_tInfo.fX, m_tInfo.fY - 10.f, "Item"));
}


void CChang::OnCollision(CObj* _pOther)
{
	if (_pOther->Get_Tag() == "Player")
	{
		if (m_bCanHit)
		{
			if (((CPlayer*)CObjMgr::Get_Instance()->Get_Player())->GetCurState() == CPlayer::DEAD
				|| ((CPlayer*)CObjMgr::Get_Instance()->Get_Player())->GetHit())
				return;

			_pOther->OnHit(this);
			((CDarkedMage*)m_pTarget)->IncreaseMp(20);
			m_bCanHit = false;
			m_fOldHitTime = GetTickCount64();
		}

	}
}



void CChang::OnePlayEnd(void)
{

}

void CChang::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		m_bOnePlay = false;
		m_bStayPlay = false;
		switch (m_eCurState)
		{
		case REION:
			m_bOnePlay = true;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 16;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 80.f;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 80.f;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case DEAD:
			m_bOnePlay = true;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 22;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 80.f;
			m_tFrame.dwTime = GetTickCount64();
			break;
		}

		m_ePreState = m_eCurState;
	}
}
