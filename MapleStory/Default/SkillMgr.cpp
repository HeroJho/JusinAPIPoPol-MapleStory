#include "stdafx.h"
#include "SkillMgr.h"
#include "AbstractFactory.h"

#include "ObjMgr.h"

#include "BladeFury.h"
#include "KarmaFury.h"
#include "PhantomBlow.h"
#include "BladeStorm.h"
#include "Player.h"


CSkillMgr* CSkillMgr::m_pInstance = nullptr;
CSkillMgr::CSkillMgr()
	: m_sSkill_1{}
	, m_sSkill_2{}
	, m_sSkill_3{}
	, m_sSkill_4{}
{
}

CSkillMgr::~CSkillMgr()
{
	Release();
}

void CSkillMgr::Initialize(void)
{
	m_sSkill_1.Init(SK_SKILL1, 50, 10, 500.f);
	m_sSkill_2.Init(SK_SKILL2, 10, 0, 500.f);
	m_sSkill_3.Init(SK_SKILL3, 10, 12, 6000.f);
	m_sSkill_4.Init(SK_SKILL4, 10, 24, 15000.f);
}

int CSkillMgr::Update(void)
{
	if (!m_sSkill_1.m_bCanUse)
	{
		if (m_sSkill_1.m_fOldCoolDown + m_sSkill_1.m_fCoolDown < GetTickCount64())
		{
			m_sSkill_1.m_bCanUse = true;
		}
	}
	if (!m_sSkill_2.m_bCanUse)
	{
		if (m_sSkill_2.m_fOldCoolDown + m_sSkill_2.m_fCoolDown < GetTickCount64())
		{
			m_sSkill_2.m_bCanUse = true;
		}
	}
	if (!m_sSkill_3.m_bCanUse)
	{
		if (m_sSkill_3.m_fOldCoolDown + m_sSkill_3.m_fCoolDown < GetTickCount64())
		{
			m_sSkill_3.m_bCanUse = true;
		}
	}
	if (!m_sSkill_4.m_bCanUse)
	{
		if (m_sSkill_4.m_fOldCoolDown + m_sSkill_4.m_fCoolDown < GetTickCount64())
		{
			m_sSkill_4.m_bCanUse = true;
		}
	}

	return 0;
}

void CSkillMgr::Release(void)
{
}

bool CSkillMgr::UseSkill(SKILLID _eID)
{
	CPlayer* pP = (CPlayer*)(CObjMgr::Get_Instance()->Get_Player());

	switch (_eID)
	{
	case SK_SKILL1:
	{
		if (!m_sSkill_1.m_bCanUse)
			return false;

		if (!pP->DecreaseMp(0))
			return false;

		CObj* pSkill = CAbstractFactory<CBladeFury>::Create(pP->Get_Info().fX, pP->Get_Info().fY, "Skill");
		pSkill->Set_Target(pP);
		((CSkill*)pSkill)->Set_SkillInfo(m_sSkill_1.iAt, m_sSkill_1.iMonCount);
		CObjMgr::Get_Instance()->Add_Object(OBJ_SKILL, pSkill);
		
		m_sSkill_1.m_bCanUse = false;
		m_sSkill_1.m_fOldCoolDown = (float)GetTickCount64();
	}
		break;
	case SK_SKILL2:
	{
		if (!m_sSkill_2.m_bCanUse)
			return false;

		if (!pP->DecreaseMp(10))
			return false;

		CObj* pSkill = CAbstractFactory<CPhantomBlow>::Create(pP->Get_Info().fX, pP->Get_Info().fY, "Skill");
		pSkill->Set_Target(pP);
		((CSkill*)pSkill)->Set_SkillInfo(m_sSkill_2.iAt, m_sSkill_2.iMonCount);
		CObjMgr::Get_Instance()->Add_Object(OBJ_SKILL, pSkill);

		pP->Get_Stat().iMp -= 10;


		m_sSkill_2.m_bCanUse = false;
		m_sSkill_2.m_fOldCoolDown = (float)GetTickCount64();
	}
		break;
	case SK_SKILL3:
	{
		if (!m_sSkill_3.m_bCanUse)
			return false;

		if (!pP->DecreaseMp(40))
			return false;

		CObj* pSkill = CAbstractFactory<CBladeStorm>::Create(pP->Get_Info().fX, pP->Get_Info().fY, "Skill");
		pSkill->Set_Target(pP);
		((CBladeStorm*)pSkill)->Set_SkillInfo(m_sSkill_3.iAt, m_sSkill_3.iMonCount);
		((CBladeStorm*)pSkill)->SetHoldKey('A');
		CObjMgr::Get_Instance()->Add_Object(OBJ_SKILL, pSkill);

		m_sSkill_3.m_bCanUse = false;
		m_sSkill_3.m_fOldCoolDown = (float)GetTickCount64();
	}
		break;
	case SK_SKILL4:
	{
		if (!m_sSkill_4.m_bCanUse)
			return false;

		if (!pP->DecreaseMp(40))
			return false;

		CObj* pSkill = CAbstractFactory<CKarmaFury>::Create(pP->Get_Info().fX, pP->Get_Info().fY, "Skill");
		pSkill->Set_Target(pP);
		((CSkill*)pSkill)->Set_SkillInfo(m_sSkill_4.iAt, m_sSkill_4.iMonCount);
		CObjMgr::Get_Instance()->Add_Object(OBJ_SKILL, pSkill);

		m_sSkill_4.m_bCanUse = false;
		m_sSkill_4.m_fOldCoolDown = (float)GetTickCount64();
	}
		break;
	}

	return true;
}
