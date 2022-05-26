#include "stdafx.h"
#include "NightC.h"
#include "AbstractFactory.h"

#include "EventMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SpawnMgr.h"

#include "Skill.h"
#include "ObjMgr.h"
#include "MoneyBig.h"
#include "Player.h"
#include "QuestMgr.h"

CNightC::CNightC()
	: m_fOldTime(GetTickCount64())
	, m_fRandTime(0.f)
{

}

CNightC::~CNightC()
{
	Release();
}

void CNightC::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/NightC/NightCL.bmp", L"NightCL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/NightC/NightCR.bmp", L"NightCR");
	Set_FrameKey(L"NightCL");
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 500.f;
	m_tFrame.dwTime = GetTickCount();


	m_fOldHitTime = 0.f;
	m_fHitTime = 1000.f;
	m_fOldChaseTime = 0.f;
	m_fChaseTime = 20000.f;
	m_fOldDeadTime = 0.f;
	m_fDeadTime = 2000.f;


	// 콜리젼 크기, 피봇 설정
	m_tInfo.fCCX = 50.f;
	m_tInfo.fCCY = 80.f;
	m_tColPivot.x = 0.f;
	m_tColPivot.y = -35.f;
	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 200.f;
	m_tInfo.fTCY = 200.f;

	Set_Stat(150, 0, 5);

	m_fSpeed = 1.f;

	m_bCanHit = true;
	m_pOldLine = nullptr;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;

	m_eCurState = IDLE;

	m_fAttackRange = 100.f;
	m_fAttackTime = 1100.f;
	m_fOldAttackTime = GetTickCount64();
}

int CNightC::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_eCurState != CHASE && m_eCurState != DEAD && m_eCurState != ATTACK)
		ChooseRandStat();

	switch (m_eCurState)
	{
	case CMonster::IDLE:
		Update_Idle();
		break;
	case CMonster::WALK:
		Update_Walk();
		break;
	case CMonster::CHASE:
		Update_Chase();
		break;
	case CMonster::HIT:
		Update_Hit();
		break;
	case CMonster::ATTACK:
		Update_Attack();
		break;
	case CMonster::DEAD:
		Update_Dead();
		break;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CNightC::Late_Update(void)
{
	Update_Gravity();

	Motion_Change();
	if (!m_bStayPlay)
	{
		Move_Frame();
	}
}

void CNightC::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 									// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tTRect.left + iScrollX),					// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tTRect.top - 60 + iScrollY),
		int(m_tInfo.fTCX),								// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fTCY),
		hMemDC,											// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fTCX,		// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fTCY,
		(int)m_tInfo.fTCX,								// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fTCY,
		RGB(255, 0, 255));								// 제거하고자 하는 색상
}

void CNightC::Release(void)
{

}

void CNightC::SetCurState(STATE _eState, DIRECTION _eDir)
{
	if (_eDir == DIR_LEFT)
		m_pFrameKey = L"NightCL";
	else
		m_pFrameKey = L"NightCR";

	m_eDir = _eDir;
	m_eCurState = _eState;
}


void CNightC::ChooseRandStat()
{
	if (m_fOldTime + m_fRandTime < GetTickCount64())
	{
		m_fRandTime = CEventMgr::Get_Instance()->GetRandomNum_Int(4000, 10000);
		STATE eRandStat = STATE(CEventMgr::Get_Instance()->GetRandomNum_Int(0, 1));
		DIRECTION eRandDir = DIRECTION(CEventMgr::Get_Instance()->GetRandomNum_Int(0, 1));

		SetCurState(eRandStat, eRandDir);

		m_fOldTime = GetTickCount64();
	}
}

void CNightC::Update_Idle()
{
}

void CNightC::Update_Walk()
{
	if (m_eDir == DIR_LEFT)
		m_tInfo.fX -= m_fSpeed;
	else if (m_eDir == DIR_RIGHT)
		m_tInfo.fX += m_fSpeed;
}

void CNightC::Update_Chase()
{
	if (!m_pTarget)
	{
		SetCurState(IDLE, m_eDir);
		return;
	}

	if (m_fOldChaseTime + m_fChaseTime < GetTickCount64())
	{
		SetCurState(IDLE, m_eDir);
		return;
	}


	float fChaseDir = m_pTarget->Get_Info().fX - m_tInfo.fX;

	if (10.f < fChaseDir)
	{
		SetCurState(CHASE, DIR_RIGHT);
		m_tInfo.fX += m_fSpeed + 1.f;
	}
	else if (-10.f > fChaseDir)
	{
		SetCurState(CHASE, DIR_LEFT);
		m_tInfo.fX -= m_fSpeed + 1.f;
	}
	else
	{
		SetCurState(IDLE, m_eDir);
	}

	// 공격 범위
	float dis = abs(m_pTarget->Get_Info().fCX - m_tInfo.fX);
	if (m_fAttackRange > dis)
	{
		SetCurState(ATTACK, m_eDir);
		m_fOldAttackTime = GetTickCount64();

		CObj* pSkill = CAbstractFactory<CSkill>::Create(m_tInfo.fCX, m_tInfo.fCY, "Skill");
		pSkill->Set_Target(this);
		((CSkill*)pSkill)->Set_ColSet(80.f, 120.f, 60.f, -35.f, 1100.f, 500.f);

		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSKILL, pSkill);
	}
}

void CNightC::Update_Hit()
{
	if (m_fOldHitTime + m_fHitTime < GetTickCount64())
	{
		SetCurState(CHASE, m_eDir);
		m_fOldChaseTime = GetTickCount64();
	}
}

void CNightC::Update_Attack()
{
	if (m_fOldAttackTime + m_fAttackTime < GetTickCount64())
	{
		SetCurState(CHASE, m_eDir);
	}
}

void CNightC::Update_Dead()
{
	if (m_fOldDeadTime + m_fDeadTime < GetTickCount64())
	{
		m_bDead = true;
	}
}

void CNightC::OnHit(CObj* _pOther)
{
	m_tStat.iHp -= _pOther->Get_Stat().iAt;
	if (m_tStat.iHp <= 0.f)
	{
		SetCurState(DEAD, m_eDir);
		m_fOldDeadTime = GetTickCount64();
		m_bCanHit = false;
		CSpawnMgr::Get_Instance()->DecreaseCount();
		DropItem();
		((CPlayer*)CObjMgr::Get_Instance()->Get_Player())->AddExp(10);
		CQuestMgr::Get_Instance()->HuntingMonster(MON_NIGHTC);
		return;
	}

	m_fOldHitTime = GetTickCount64();

	DIRECTION eDir = _pOther->Get_Target()->Get_Dir();
	m_pTarget = _pOther->Get_Target();
	if (eDir == DIR_LEFT)
	{
		SetCurState(HIT, DIR_RIGHT);
		m_tInfo.fX -= 12.f;
	}
	else
	{
		SetCurState(HIT, DIR_LEFT);
		m_tInfo.fX += 12.f;
	}
}

void CNightC::DropItem()
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CMoneyBig>::Create(m_tInfo.fX, m_tInfo.fY - 10.f, "Item"));
}

void CNightC::OnCollision(CObj* _pOther)
{
	if (_pOther->Get_Tag() == "Player")
	{
		if (m_bCanHit)
			_pOther->OnHit(this);
	}
	else if (_pOther->Get_Tag() == "Block")
	{
		if (m_eDir == DIR_LEFT)
			SetCurState(m_eCurState, DIR_RIGHT);
		else if (m_eDir == DIR_RIGHT)
			SetCurState(m_eCurState, DIR_LEFT);
	}
}



void CNightC::OnePlayEnd(void)
{

}

void CNightC::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		m_bOnePlay = false;
		m_bStayPlay = false;
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 500.f;
			m_tFrame.dwTime = GetTickCount();
			break;

		case WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 150.f;
			m_tFrame.dwTime = GetTickCount();
			break;

		case CHASE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 150.f;
			m_tFrame.dwTime = GetTickCount();
			break;

		case HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 5;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case ATTACK:
			m_bOnePlay = true;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case DEAD:
			m_bOnePlay = true;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
	}
}
