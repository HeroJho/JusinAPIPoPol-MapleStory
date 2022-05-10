#include "stdafx.h"
#include "Skill.h"

CSkill::CSkill()
{
}

CSkill::~CSkill()
{
    Release();
}

void CSkill::Initialize(void)
{
	// �ݸ��� ũ��, �Ǻ� ����
	m_tInfo.fCCX = 50.f;
	m_tInfo.fCCY = 50.f;
	m_tColPivot.x = -25.f;
	m_tColPivot.y = -25.f;
	// �ؽ��� ũ�� ����
	m_tInfo.fTCX = 0.f;
	m_tInfo.fTCY = 0.f;

	Set_Stat(0, 10);
	m_fSpeed = 0.f;

	m_bCanHit = false;
	m_CanHitCount = 0;
	m_CanHitMaxCount = 1;

	m_pOldLine = nullptr;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;

	m_fOldSkillTime = GetTickCount64();
	m_fSkillTime = 100.f;
	m_fDeleteTime = 140.f;
}

int CSkill::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX = m_pTarget->Get_Info().fX;
	m_tInfo.fY = m_pTarget->Get_Info().fY;

	if (m_pTarget->Get_Dir() == DIR_LEFT)
	{
		m_tColPivot.x = -25.f;
		m_tColPivot.y = -25.f;
	}
	else
	{
		m_tColPivot.x = 25.f;
		m_tColPivot.y = -25.f;
	}



	// ��Ʈ �ð�
	if (m_fOldSkillTime + m_fSkillTime < GetTickCount64() && !m_bJump)
	{
		m_bCanHit = true;
		m_bJump = true;
	}
	// �Ҹ� �ð�
	if (m_fOldSkillTime + m_fDeleteTime < GetTickCount64())
	{
		m_bDead = true;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CSkill::Late_Update(void)
{
}

void CSkill::Render(HDC hDC)
{
}

void CSkill::Release(void)
{
}

void CSkill::OnCollision(CObj* _pOther)
{
	if (!m_bCanHit)
		return;
	if (!_pOther->Get_CanHit())
		return;

	if (_pOther->Get_Tag() == "Monster")
	{
		_pOther->OnHit(this);
	}

	m_bCanHit = false;
}