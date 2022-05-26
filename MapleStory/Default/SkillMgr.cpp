#include "stdafx.h"
#include "SkillMgr.h"
#include "AbstractFactory.h"

#include "ObjMgr.h"

#include "BladeFury.h"
#include "KarmaFury.h"
#include "PhantomBlow.h"
#include "BladeStorm.h"
#include "Player.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "StatMgr.h"
#include "Vet.h"


CSkillMgr* CSkillMgr::m_pInstance = nullptr;
CSkillMgr::CSkillMgr()
	: m_sSkill_1{}
	, m_sSkill_2{}
	, m_sSkill_3{}
	, m_sSkill_4{}
	, m_iLevel_1(0)
	, m_iLevel_2(0)
	, m_iLevel_3(0)
	, m_iLevel_4(0)

{
}

CSkillMgr::~CSkillMgr()
{
	Release();
}

void CSkillMgr::Initialize(void)
{
	m_iLevel_1 = 0;
	m_iLevel_2 = 0;
	m_iLevel_3 = 0;
	m_iLevel_4 = 0;

	m_sSkill_1.Init(SK_SKILL1, 0, 0, 0.f);
	m_sSkill_2.Init(SK_SKILL2, 10, 0, 500.f);
	m_sSkill_3.Init(SK_SKILL3, 10, 24, 6000.f);
	m_sSkill_4.Init(SK_SKILL4, 10, 12, 15000.f);

	m_f1 = 1.f;
	m_f2 = 1.f;
	m_f3 = 1.f;
	m_f4 = 1.f;

	m_iVetCount = 0;
}

int CSkillMgr::Update(void)
{
	if (!m_sSkill_1.m_bCanUse)
	{
		if (m_sSkill_1.m_fOldCoolDown + m_sSkill_1.m_fCoolDown < GetTickCount64())
		{
			m_sSkill_1.m_bCanUse = true;
			m_f1 = 1.f;
		}
		else
		{
			m_f1 = (GetTickCount64() - m_sSkill_1.m_fOldCoolDown )/(m_sSkill_1.m_fCoolDown);
		}
	}
	if (!m_sSkill_2.m_bCanUse)
	{
		if (m_sSkill_2.m_fOldCoolDown + m_sSkill_2.m_fCoolDown < GetTickCount64())
		{
			m_sSkill_2.m_bCanUse = true;
			m_f2 = 1.f;
		}
		else
		{
			m_f2 = (GetTickCount64() - m_sSkill_2.m_fOldCoolDown) / (m_sSkill_2.m_fCoolDown);
		}
	}
	if (!m_sSkill_3.m_bCanUse)
	{
		if (m_sSkill_3.m_fOldCoolDown + m_sSkill_3.m_fCoolDown < GetTickCount64())
		{
			m_sSkill_3.m_bCanUse = true;
			m_f3 = 1.f;
		}
		else
		{
			m_f3 = (GetTickCount64() - m_sSkill_3.m_fOldCoolDown) / (m_sSkill_3.m_fCoolDown);
		}
	}
	if (!m_sSkill_4.m_bCanUse)
	{
		if (m_sSkill_4.m_fOldCoolDown + m_sSkill_4.m_fCoolDown < GetTickCount64())
		{
			m_sSkill_4.m_bCanUse = true;
			m_f4 = 1.f;
		}
		else
		{
			m_f4 = (GetTickCount64() - m_sSkill_4.m_fOldCoolDown) / (m_sSkill_4.m_fCoolDown);
		}
	}

	return 0;
}

void CSkillMgr::Release(void)
{
}

bool CSkillMgr::UseSkill(SKILLID _eID , TCHAR _cHoldKey)
{
	CPlayer* pP = (CPlayer*)(CObjMgr::Get_Instance()->Get_Player());

	switch (_eID)
	{
	case SK_SKILL1:
	{
		if (!m_sSkill_1.m_bCanUse)
			return false;

		if (!pP->DecreaseMp(5))
			return false;

		CObj* pSkill = CAbstractFactory<CBladeFury>::Create(pP->Get_Info().fX, pP->Get_Info().fY, "Skill");
		pSkill->Set_Target(pP);
		((CSkill*)pSkill)->Set_SkillInfo(m_sSkill_1.iAt + CStatMgr::Get_Instance()->Get_PlayerAT(), m_sSkill_1.iMonCount);
		CObjMgr::Get_Instance()->Add_Object(OBJ_SKILL, pSkill);

		CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"Skill_1.wav", SOUND_PEFFECT, 1);
		
		pP->SetStateSkill();
		m_sSkill_1.m_bCanUse = false;
		m_sSkill_1.m_fOldCoolDown = (float)GetTickCount64();

		CreateVect();
	}
	break;
	case SK_SKILL2:
	{
		if (!m_sSkill_2.m_bCanUse)
			return false;

		if (!pP->DecreaseMp(5))
			return false;

		CObj* pSkill = CAbstractFactory<CPhantomBlow>::Create(pP->Get_Info().fX, pP->Get_Info().fY, "Skill");
		pSkill->Set_Target(pP);
		((CSkill*)pSkill)->Set_SkillInfo(m_sSkill_2.iAt + CStatMgr::Get_Instance()->Get_PlayerAT(), m_sSkill_2.iMonCount);
		CObjMgr::Get_Instance()->Add_Object(OBJ_SKILL, pSkill);

		CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"Skill_2.wav", SOUND_PEFFECT, 1);

		pP->SetStateAttack();
		m_sSkill_2.m_bCanUse = false;
		m_sSkill_2.m_fOldCoolDown = (float)GetTickCount64();

		CreateVect();
	}
	break;
	case SK_SKILL3:
	{
		if (!m_sSkill_3.m_bCanUse)
			return false;

		if (!pP->DecreaseMp(10))
			return false;

		CObj* pSkill = CAbstractFactory<CKarmaFury>::Create(pP->Get_Info().fX, pP->Get_Info().fY, "Skill");
		pSkill->Set_Target(pP);
		((CSkill*)pSkill)->Set_SkillInfo(m_sSkill_4.iAt + CStatMgr::Get_Instance()->Get_PlayerAT(), m_sSkill_4.iMonCount);
		CObjMgr::Get_Instance()->Add_Object(OBJ_SKILL, pSkill);

		CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"Skill_3.wav", SOUND_PEFFECT, 1);

		pP->SetStateSkill();
		m_sSkill_3.m_bCanUse = false;
		m_sSkill_3.m_fOldCoolDown = (float)GetTickCount64();

		CreateVect();
	}
	break;
	case SK_SKILL4:
	{
		if (!m_sSkill_4.m_bCanUse)
			return false;

		if (!pP->DecreaseMp(10))
			return false;
		CObj* pSkill = CAbstractFactory<CBladeStorm>::Create(pP->Get_Info().fX, pP->Get_Info().fY, "Skill");
		pSkill->Set_Target(pP);
		((CBladeStorm*)pSkill)->Set_SkillInfo(m_sSkill_4.iAt + CStatMgr::Get_Instance()->Get_PlayerAT(), m_sSkill_4.iMonCount);
		((CBladeStorm*)pSkill)->SetHoldKey(_cHoldKey);
		CObjMgr::Get_Instance()->Add_Object(OBJ_SKILL, pSkill);

		pP->SetStateAttack();
		m_sSkill_4.m_bCanUse = false;
		m_sSkill_4.m_fOldCoolDown = (float)GetTickCount64();

		CreateVect();
	}
	break;
	}

	return true;
}

void CSkillMgr::UpSKill_1()
{
	++m_iLevel_1;
	if (5 < m_iLevel_1)
		m_iLevel_1 = 5;

	switch (m_iLevel_1)
	{
	case 1:
		m_sSkill_1.Change(10, 6, 500.f);
		break;
	case 2:
		m_sSkill_1.Change(15, 8, 500.f);
		break;
	case 3:
		m_sSkill_1.Change(15, 12, 500.f);
		break;
	case 4:
		m_sSkill_1.Change(15, 14, 500.f);
		break;
	case 5:
		m_sSkill_1.Change(20, 16, 500.f);
		break;
	}
}

void CSkillMgr::UpSKill_2()
{
	++m_iLevel_2;
	if (5 < m_iLevel_2)
		m_iLevel_2 = 5;

	switch (m_iLevel_2)
	{
	case 1:
		m_sSkill_2.Change(20, 0, 1000.f);
		break;
	case 2:
		m_sSkill_2.Change(25, 0, 900.f);
		break;
	case 3:
		m_sSkill_2.Change(28, 0, 800.f);
		break;
	case 4:
		m_sSkill_2.Change(30, 0, 600.f);
		break;
	case 5:
		m_sSkill_2.Change(35, 0, 500.f);
		break;
	}
}

void CSkillMgr::UpSKill_3()
{
	++m_iLevel_3;
	if (5 < m_iLevel_3)
		m_iLevel_3 = 5;

	switch (m_iLevel_3)
	{
	case 1:
		m_sSkill_3.Change(50, 28, 10000.f);
		break;
	case 2:
		m_sSkill_3.Change(55, 28, 9000.f);
		break;
	case 3:
		m_sSkill_3.Change(60, 28, 8000.f);
		break;
	case 4:
		m_sSkill_3.Change(65, 28, 7000.f);
		break;
	case 5:
		m_sSkill_3.Change(70, 28, 6000.f);
		break;
	}
}

void CSkillMgr::UpSKill_4()
{
	++m_iLevel_4;
	if (5 < m_iLevel_4)
		m_iLevel_4 = 5;

	switch (m_iLevel_4)
	{
	case 1:
		m_sSkill_4.Change(1, 16, 15000.f);
		break;
	case 2:
		m_sSkill_4.Change(1, 16, 14000.f);
		break;
	case 3:
		m_sSkill_4.Change(28, 16, 14000.f);
		break;
	case 4:
		m_sSkill_4.Change(30, 16, 12000.f);
		break;
	case 5:
		m_sSkill_4.Change(35, 16, 10000.f);
		break;
	}
}

void CSkillMgr::CreateVect()
{
	if (6 < m_iVetCount)
		return;

	++m_iVetCount;
	CObjMgr::Get_Instance()->Add_Object(OBJ_VET, CAbstractFactory<CVet>::Create(CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX, CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY - 10.f, "Vet"));
}
