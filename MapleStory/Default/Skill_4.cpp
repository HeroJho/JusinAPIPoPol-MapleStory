#include "stdafx.h"
#include "Skill_4.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"

CSkill_4::CSkill_4()
	: m_fDir(0.f)
{
}

CSkill_4::~CSkill_4()
{
	Release();
}

void CSkill_4::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/DarkedMage/Skill_4/Skill_4.bmp", L"Skill_4");
	Set_FrameKey(L"Skill_4");
	m_bOnePlay = true;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 60;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = (DWORD)70.f;
	m_tFrame.dwTime = (DWORD)GetTickCount64();


	// �ݸ��� ũ��, �Ǻ� ����
	m_tInfo.fCCX = 100.f;
	m_tInfo.fCCY = 600.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)-150.f;
	// �ؽ��� ũ�� ����
	m_tInfo.fTCX = 500.f;
	m_tInfo.fTCY = 900.f;

	Set_Stat(0, 0, 20);
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
	m_fSkillTime = 2500.f;
	m_fDeleteTime = 4500.f;
	m_fDir = 0.f;

}

int CSkill_4::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bCanHit)
	{
		if (m_fDir == 0.f)
			m_fDir = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX - m_tInfo.fX;
		if (0.f < m_fDir)
			m_tInfo.fX += 2.f;
		else if (0.f > m_fDir)
			m_tInfo.fX += -2.f;

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

void CSkill_4::Late_Update(void)
{
	if (!m_bStayPlay)
		Move_Frame();
}

void CSkill_4::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);


	GdiTransparentBlt(hDC, 									// ���� ����, ���������� �׸��� �׸� DC
		int(m_tTRect.left + iScrollX),					// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tTRect.top - 250 + iScrollY),
		int(m_tInfo.fTCX),								// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fTCY),
		hMemDC,											// ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fTCX,		// ��Ʈ�� ��� ���� ��ǥ, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fTCY,
		(int)m_tInfo.fTCX,								// ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fTCY,
		RGB(255, 0, 255));								// �����ϰ��� �ϴ� ����

}

void CSkill_4::Release(void)
{
}

void CSkill_4::OnCollision(CObj* _pOther)
{
	if (m_CanHitCount > m_CanHitMaxCount)
		return;
	if (!_pOther->Get_CanHit())
		return;

	if (!m_bCanHit)
		return;

	++m_CanHitCount;

	if (_pOther->Get_Tag() == "Player")
	{
		_pOther->OnHit(this);
	}

}

void CSkill_4::Motion_Change(void)
{

}