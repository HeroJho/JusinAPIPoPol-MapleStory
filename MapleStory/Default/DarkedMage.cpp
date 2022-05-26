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
#include "UIMgr.h"
#include "Chang.h"
#include "SceneMgr.h"

CDarkedMage::CDarkedMage()
	: m_fOldTime(GetTickCount64())
	, m_fRandTime(0.f)
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
	m_tFrame.dwSpeed = 80.f;
	m_tFrame.dwTime = GetTickCount();


	// 콜리젼 크기, 피봇 설정
	m_tInfo.fCCX = 300.f;
	m_tInfo.fCCY = 350.f;
	m_tColPivot.x = 0.f;
	m_tColPivot.y = -35.f;
	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 800.f;
	m_tInfo.fTCY = 700.f;

	Set_Stat(10000, 100, 5);
	m_tStat.iMp = 0;
	CUIMgr::Get_Instance()->ShowBossHP(m_tStat.iHp, m_tStat.iMaxHp, m_tStat.iMp, m_tStat.iMaxMp);

	m_fSpeed = 1.f;

	m_bCanHit = true;
	m_pOldLine = nullptr;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;

	m_fDelayTime = 1200.f;
	m_fOldDelayTime = GetTickCount64();

	m_iSkill1_Count = 0;
	m_fSkill1_DelayTime = 1500.f;
	m_fSkill1_OldDelayTime = GetTickCount64();
	m_iSkill2_Count = 0;
	m_fSkill2_DelayTime = 2000.f;
	m_fSkill2_OldDelayTime = GetTickCount64();
	m_iSkill3_Count = 0;
	m_fSkill3_DelayTime = 400.f;
	m_fSkill3_OldDelayTime = GetTickCount64();
	m_iSkill4_Count = 0;
	m_fSkill4_DelayTime = 2000.f;
	m_fSkill4_OldDelayTime = GetTickCount64();

	m_eCurState = BOSS_STATE::IDLE;


	m_fDomi_DelayTime = 2000.f;
	m_fDomi_OldDelayTime = 0.f;
	m_bDomi = false;
}

int CDarkedMage::Update(void)
{
	if (!m_bCanHit)
		return OBJ_NOEVENT;

	if (m_bDomi && m_fDomi_OldDelayTime + m_fDomi_DelayTime < GetTickCount64())
	{
		CUIMgr::Get_Instance()->DomiOpen();
		m_bDomi = false;
		((CPlayer*)CObjMgr::Get_Instance()->Get_Player())->OnHit(9999999);
		return OBJ_NOEVENT;
	}

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
	if (!m_bCanHit)
		return;

	Skill_1_Temp();
	Skill_2_Temp();
	Skill_3_Temp();
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
		m_fRandTime = CEventMgr::Get_Instance()->GetRandomNum_Int(7000, 9000);
		BOSS_STATE eRandStat = BOSS_STATE(CEventMgr::Get_Instance()->GetRandomNum_Int(1, 4));

		switch (eRandStat)
		{
		case CDarkedMage::IDLE:
			SetCurState(eRandStat, DIR_LEFT);
			break;
		case CDarkedMage::SKILL_1:
			if (m_iSkill1_Count == 0)
			{
				CSoundMgr::Get_Instance()->StopSound(SOUND_NPC);
				CSoundMgr::Get_Instance()->PlaySound(L"BlackSkill_Use.wav", SOUND_NPC, 0.5);
				SetCurState(eRandStat, DIR_LEFT);
			}

			break;
		case CDarkedMage::SKILL_2:
			if (m_iSkill2_Count == 0)
			{
				CSoundMgr::Get_Instance()->StopSound(SOUND_NPC);
				CSoundMgr::Get_Instance()->PlaySound(L"BlackSkill_Use.wav", SOUND_NPC, 0.5);
				SetCurState(eRandStat, DIR_LEFT);
			}
			break;
		case CDarkedMage::SKILL_3:
			if (m_iSkill3_Count == 0)
			{
				CSoundMgr::Get_Instance()->StopSound(SOUND_NPC);
				CSoundMgr::Get_Instance()->PlaySound(L"BlackSkill_Use.wav", SOUND_NPC, 0.5);
				SetCurState(eRandStat, DIR_LEFT);
			}
			break;
		case CDarkedMage::SKILL_4:
			if (m_iSkill4_Count == 0)
			{
				CSoundMgr::Get_Instance()->StopSound(SOUND_NPC);
				CSoundMgr::Get_Instance()->PlaySound(L"BlackSkill_Use.wav", SOUND_NPC, 0.5);
				SetCurState(eRandStat, DIR_LEFT);
			}
			break;
		default:
			break;
		}

		m_fOldTime = GetTickCount64();
	}
}

void CDarkedMage::OnHit(CObj* _pOther)
{
	m_tStat.iHp -= _pOther->Get_Stat().iAt;
	CUIMgr::Get_Instance()->ChangeBossHp(m_tStat.iHp, m_tStat.iMaxHp);
	if (m_tStat.iHp <= 0.f)
	{
		m_bCanHit = false;

		CObjMgr::Get_Instance()->SetDead_ID(OBJ_MONSKILL);
		CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
		CSceneMgr::Get_Instance()->Start_FadeOut();

		return;
	}
}

void CDarkedMage::Idle_Update()
{
	m_fOldDelayTime = GetTickCount64();
}

void CDarkedMage::Skill_1_Update()
{
	// 시전 시간
	if (m_fOldDelayTime + m_fDelayTime < GetTickCount64())
	{
		m_iSkill1_Count = 2;
	}
	else
		m_fSkill1_OldDelayTime = GetTickCount64();
}
void CDarkedMage::Skill_2_Update()
{
	// 시전 시간
	if (m_fOldDelayTime + m_fDelayTime < GetTickCount64())
	{
		m_iSkill2_Count = 2;
	}
	else
		m_fSkill2_OldDelayTime = GetTickCount64();
}
void CDarkedMage::Skill_3_Update()
{
	// 시전 시간
	m_iSkill3_Count = 3;
	m_fSkill3_OldDelayTime = GetTickCount64();
}
void CDarkedMage::Skill_4_Update()
{
	// 시전 시간
	if (m_fOldDelayTime + m_fDelayTime < GetTickCount64())
	{
		m_iSkill4_Count = 1;
	}
	else
		m_fSkill4_OldDelayTime = GetTickCount64();
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

		m_fSkill1_OldDelayTime = GetTickCount64();

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

		m_fSkill2_OldDelayTime = GetTickCount64();

		--m_iSkill2_Count;
	}
}
void CDarkedMage::Skill_3_Temp()
{
	if (m_iSkill3_Count <= 0)
	{
		m_iSkill3_Count = 0;
		return;
	}

	if (m_fSkill3_OldDelayTime + m_fSkill3_DelayTime < GetTickCount64())
	{
		float fX = CEventMgr::Get_Instance()->GetRandomNum_Int(100.f, 1800.f);
		float fY = CEventMgr::Get_Instance()->GetRandomNum_Int(100.f, 500.f);

		CObj* pSkill = CAbstractFactory<CChang>::Create(fX, fY, "Monster");
		pSkill->Set_Target(this);

		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pSkill);

		m_fSkill3_OldDelayTime = GetTickCount64();

		--m_iSkill3_Count;
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

		m_fSkill4_OldDelayTime = GetTickCount64();

		--m_iSkill4_Count;
	}
}


void CDarkedMage::OnCollision(CObj* _pOther)
{

}


void CDarkedMage::IncreaseMp(int _iValue)
{
	if (m_bDomi)
		return;

	m_tStat.iMp += _iValue;
	if (m_tStat.iMaxMp < m_tStat.iMp)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_SYSTEM);
		CSoundMgr::Get_Instance()->PlaySound(L"Finish.wav", SOUND_SYSTEM, 1);

		m_tStat.iMp = 0;
		CUIMgr::Get_Instance()->DomiClose();
		m_bDomi = true;
		m_fDomi_OldDelayTime = GetTickCount64();
	}
		
	CUIMgr::Get_Instance()->ChangeBossMp(m_tStat.iMp, m_tStat.iMaxMp);
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
			m_tFrame.dwSpeed = 80.f;
			m_tFrame.dwTime = GetTickCount();
			break;
		case SKILL_1:
			m_bOnePlay = true;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 36;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 80;
			m_tFrame.dwTime = GetTickCount();
			break;
		case SKILL_2:
			m_bOnePlay = true;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 38;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 80.f;
			m_tFrame.dwTime = GetTickCount();
			break;
		case SKILL_3:
			m_bOnePlay = true;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 37;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 80.f;
			m_tFrame.dwTime = GetTickCount();
			break;
		case SKILL_4:
			m_bOnePlay = true;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 35;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 80.f;
			m_tFrame.dwTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
	}
}