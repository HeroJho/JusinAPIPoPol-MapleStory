#include "stdafx.h"
#include "Skill.h"

CSkill::CSkill()
	: m_pFirst(nullptr)
	, m_CanHitCount(0)
	, m_CanHitMaxCount(0)
	, m_fDeleteTime(0.f)
	, m_fFixPivotX(0.f)
	, m_fFixPivotY(0.f)
	, m_fOldSkillTime(0.f)
	, m_fSkillTime(0.f)
{
}

CSkill::~CSkill()
{
    Release();
}

void CSkill::Set_ColSet(float _fCX, float _fCY, float _fPvX, float _fPvY, float _fDeleteTime, float _fSkillTime)
{
	// 콜리젼 크기, 피봇 설정
	m_tInfo.fCCX = _fCX;
	m_tInfo.fCCY = _fCY;
	m_tColPivot.x = (LONG)_fPvX;
	m_tColPivot.y = (LONG)_fPvY;

	m_fFixPivotX = _fPvX;
	m_fFixPivotY = _fPvY;

	m_fDeleteTime = _fDeleteTime;
	m_fSkillTime = _fSkillTime;
}

void CSkill::Set_SkillInfo(int _iAt, int _iMonsCount)
{
	m_tStat.iAt = _iAt;
	m_CanHitMaxCount = _iMonsCount;
}

void CSkill::Initialize(void)
{
	// 콜리젼 크기, 피봇 설정
	m_tInfo.fCCX = 50.f;
	m_tInfo.fCCY = 50.f;
	m_tColPivot.x = (LONG)-25.f;
	m_tColPivot.y = (LONG)-25.f;
	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 0.f;
	m_tInfo.fTCY = 0.f;

	Set_Stat(0, 0, 10);
	m_fSpeed = 0.f;

	m_bCanHit = false;
	m_CanHitCount = 0;
	m_CanHitMaxCount = 1;

	m_pOldLine = nullptr;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;

	m_fOldSkillTime = (float)GetTickCount64();
	m_fSkillTime = 100.f;
	m_fDeleteTime = 140.f;

	m_fFixPivotX = 25.f;
	m_fFixPivotY = -25.f;
}

int CSkill::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX = m_pTarget->Get_Info().fX;
	m_tInfo.fY = m_pTarget->Get_Info().fY;

	if (m_pTarget->Get_Dir() == DIR_LEFT)
	{
		m_tColPivot.x = (LONG)-m_fFixPivotX;
		m_tColPivot.y = (LONG)m_fFixPivotY;
	}
	else
	{
		m_tColPivot.x = (LONG)m_fFixPivotX;
		m_tColPivot.y = (LONG)m_fFixPivotY;
	}



	// 히트 시간
	if (m_fOldSkillTime + m_fSkillTime < GetTickCount64() && !m_bJump)
	{
		m_bCanHit = true;
		m_bJump = true;
	}
	// 소멸 시간
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

	if (_pOther->Get_Tag() == "Player")
	{
		_pOther->OnHit(this);
	}

	m_bCanHit = false;
}