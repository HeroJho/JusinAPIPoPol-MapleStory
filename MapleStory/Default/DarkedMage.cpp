#include "stdafx.h"
#include "DarkedMage.h"
#include "AbstractFactory.h"

#include "EventMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SpawnMgr.h"

#include "Skill.h"
#include "ObjMgr.h"
#include "DarkChain.h"
#include "Skill_2.h"
#include "Skill_4.h"

CDarkedMage::CDarkedMage()
	: m_fOldTime((float)GetTickCount64())
	, m_fRandTime(0.f)
	, m_eCurState(BOSS_STATE::IDLE)
	, m_ePreState(BOSS_STATE::IDLE)
	, m_fDelayTime(0.f)
	, m_fOldDelayTime(0.f)
	, m_fSkill1_DelayTime(0.f)
	, m_fSkill1_OldDelayTime(0.f)
	, m_fSkill2_DelayTime(0.f)
	, m_fSkill2_OldDelayTime(0.f)
	, m_fSkill4_DelayTime(0.f)
	, m_fSkill4_OldDelayTime(0.f)
	, m_iSkill1_Count(0)
	, m_iSkill2_Count(0)
	, m_iSkill4_Count(0)
{

}

CDarkedMage::~CDarkedMage()
{
	Release();
}

void CDarkedMage::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/DarkedMage/DarkedMage.bmp", L"DarkedMage");
	Set_FrameKey(L"DarkedMage");
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 11;
	m_tFrame.iMotion = 4;
	m_tFrame.dwSpeed = (DWORD)80.f;
	m_tFrame.dwTime = (DWORD)GetTickCount64();


	// 콜리젼 크기, 피봇 설정
	m_tInfo.fCCX = 100.f;
	m_tInfo.fCCY = 100.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)-35.f;
	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 800.f;
	m_tInfo.fTCY = 700.f;

	Set_Stat(150, 0, 5);

	m_fSpeed = 1.f;

	m_bCanHit = true;
	m_pOldLine = nullptr;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;

	m_fDelayTime = 1200.f;
	m_fOldDelayTime = (float)GetTickCount64();

	m_iSkill1_Count = 0;
	m_fSkill1_DelayTime = 1500.f;
	m_fSkill1_OldDelayTime = (float)GetTickCount64();
	m_iSkill2_Count = 0;
	m_fSkill2_DelayTime = 2000.f;
	m_fSkill2_OldDelayTime = (float)GetTickCount64();
	m_iSkill4_Count = 0;
	m_fSkill4_DelayTime = 2000.f;
	m_fSkill4_OldDelayTime = (float)GetTickCount64();

	m_eCurState = BOSS_STATE::IDLE;
}

int CDarkedMage::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_eCurState == BOSS_STATE::IDLE)
		ChooseRandStat();

	switch (m_eCurState)
	{
	case BOSS_STATE::IDLE:
		Idle_Update();
		break;
	case BOSS_STATE::SKILL_1:
		Skill_1_Update();
		break;
	case BOSS_STATE::SKILL_2:
		Skill_2_Update();
		break;
	case BOSS_STATE::SKILL_3:
		Skill_3_Update();
		break;
	case BOSS_STATE::SKILL_4:
		Skill_4_Update();
		break;
	
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CDarkedMage::Late_Update(void)
{
	Skill_1_Temp();
	Skill_2_Temp();
	Skill_4_Temp();

	Motion_Change();
	if (!m_bStayPlay)
	{
		Move_Frame();
	}
}

void CDarkedMage::Render(HDC hDC)
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

void CDarkedMage::Release(void)
{

}

void CDarkedMage::SetCurState(BOSS_STATE _eState, DIRECTION _eDir)
{
	m_pFrameKey = L"DarkedMage";

	// m_eDir = _eDir;
	m_eCurState = _eState;
}


void CDarkedMage::ChooseRandStat()
{
	if (m_fOldTime + m_fRandTime < GetTickCount64())
	{
		m_fRandTime = (float)CEventMgr::Get_Instance()->GetRandomNum_Int(4000, 5500);
		BOSS_STATE eRandStat = BOSS_STATE(CEventMgr::Get_Instance()->GetRandomNum_Int(1, 4));

		switch (eRandStat)
		{
		case CDarkedMage::IDLE:
			SetCurState(eRandStat, DIR_LEFT);
			break;
		case CDarkedMage::SKILL_1:
			if (m_iSkill1_Count == 0)
				SetCurState(eRandStat, DIR_LEFT);
			break;
		case CDarkedMage::SKILL_2:
			if (m_iSkill2_Count == 0)
				SetCurState(eRandStat, DIR_LEFT);
			break;
		case CDarkedMage::SKILL_3:
			break;
		case CDarkedMage::SKILL_4:
			if (m_iSkill4_Count == 0)
				SetCurState(eRandStat, DIR_LEFT);
			break;
		default:
			break;
		}

		m_fOldTime = (float)GetTickCount64();
	}
}

void CDarkedMage::OnHit(CObj* _pOther)
{
	m_tStat.iHp -= _pOther->Get_Stat().iAt;
	if (m_tStat.iHp <= 0.f)
	{
		m_bCanHit = false;
		return;
	}
}

void CDarkedMage::Idle_Update()
{
	m_fOldDelayTime = (float)GetTickCount64();
}

void CDarkedMage::Skill_1_Update()
{
	// 시전 시간
	if (m_fOldDelayTime + m_fDelayTime < GetTickCount64())
	{
		m_iSkill1_Count = 2;
	}
	else
		m_fSkill1_OldDelayTime = (float)GetTickCount64();
}

void CDarkedMage::Skill_2_Update()
{
	// 시전 시간
	if (m_fOldDelayTime + m_fDelayTime < GetTickCount64())
	{
		m_iSkill2_Count = 2;
	}
	else
		m_fSkill2_OldDelayTime = (float)GetTickCount64();
}

void CDarkedMage::Skill_3_Update()
{
}

void CDarkedMage::Skill_4_Update()
{
	// 시전 시간
	if (m_fOldDelayTime + m_fDelayTime < GetTickCount64())
	{
		m_iSkill4_Count = 1;
	}
	else
		m_fSkill4_OldDelayTime = (float)GetTickCount64();
}

void CDarkedMage::Skill_1_Temp()
{
	if (m_iSkill1_Count <= 0)
	{
		m_iSkill1_Count = 0;
		return;
	}
		

	if (m_fSkill1_OldDelayTime + m_fSkill1_DelayTime < GetTickCount64())
	{
		CObj* pSkill = CAbstractFactory<CDarkChain>::Create(m_pTarget->Get_Info().fX, 600.f, "Skill");
		pSkill->Set_Target(this);

		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSKILL, pSkill);

		m_fSkill1_OldDelayTime = (float)GetTickCount64();

		--m_iSkill1_Count;
	}
}
void CDarkedMage::Skill_2_Temp()
{
	if (m_iSkill2_Count <= 0)
	{
		m_iSkill2_Count = 0;
		return;
	}


	if (m_fSkill2_OldDelayTime + m_fSkill2_DelayTime < GetTickCount64())
	{
		CObj* pSkill = CAbstractFactory<CSkill_2>::Create(m_pTarget->Get_Info().fX, 600.f, "Skill");
		pSkill->Set_Target(this);

		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSKILL, pSkill);

		m_fSkill2_OldDelayTime = (float)GetTickCount64();

		--m_iSkill2_Count;
	}
}

void CDarkedMage::Skill_4_Temp()
{
	if (m_iSkill4_Count <= 0)
	{
		m_iSkill4_Count = 0;
		return;
	}


	if (m_fSkill4_OldDelayTime + m_fSkill4_DelayTime < GetTickCount64())
	{
		CObj* pSkill = CAbstractFactory<CSkill_4>::Create(m_pTarget->Get_Info().fX, 600.f, "Skill");
		pSkill->Set_Target(this);

		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSKILL, pSkill);

		m_fSkill4_OldDelayTime = (float)GetTickCount64();

		--m_iSkill4_Count;
	}
}


void CDarkedMage::OnCollision(CObj* _pOther)
{

}



void CDarkedMage::OnePlayEnd(void)
{
	SetCurState(IDLE, DIR_LEFT);
}

void CDarkedMage::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		m_bOnePlay = false;
		m_bStayPlay = false;
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = (DWORD)80.f;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;
		case SKILL_1:
			m_bOnePlay = true;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 36;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = (DWORD)80;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;
		case SKILL_2:
			m_bOnePlay = true;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 38;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = (DWORD)80.f;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;
		case SKILL_3:
			m_bOnePlay = true;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 37;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = (DWORD)80.f;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;
		case SKILL_4:
			m_bOnePlay = true;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 35;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = (DWORD)80.f;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;
		}

		m_ePreState = m_eCurState;
	}
}