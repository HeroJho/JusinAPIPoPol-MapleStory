#include "stdafx.h"
#include "BladeFury.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"

CBladeFury::CBladeFury()
{
}

CBladeFury::~CBladeFury()
{
	Release();
}

void CBladeFury::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/BladeFury/BladeFury.bmp", L"BladeFury");
	Set_FrameKey(L"BladeFury");
	m_bOnePlay = true;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 13;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 50.f;
	m_tFrame.dwTime = GetTickCount64();


	// �ݸ��� ũ��, �Ǻ� ����
	m_tInfo.fCCX = 500.f;
	m_tInfo.fCCY = 250.f;
	m_tColPivot.x = 0.f;
	m_tColPivot.y = -30.f;
	// �ؽ��� ũ�� ����
	m_tInfo.fTCX = 800.f;
	m_tInfo.fTCY = 400.f;

	Set_Stat(0, 20);
	m_fSpeed = 0.f;

	m_bCanHit = false;
	m_CanHitCount = 0;
	m_CanHitMaxCount = 12;

	m_pOldLine = nullptr;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;

	m_fOldSkillTime = GetTickCount64();
	m_fSkillTime = 100.f;
	m_fDeleteTime = 800.f;

}

int CBladeFury::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX = m_pTarget->Get_Info().fX;
	m_tInfo.fY = m_pTarget->Get_Info().fY;


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

void CBladeFury::Late_Update(void)
{
	if (!m_bStayPlay)
		Move_Frame();
}

void CBladeFury::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 									// ���� ����, ���������� �׸��� �׸� DC
		int(m_tTRect.left + iScrollX),					// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tTRect.top - 37 + iScrollY),
		int(m_tInfo.fTCX),								// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fTCY),
		hMemDC,											// ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fTCX,		// ��Ʈ�� ��� ���� ��ǥ, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fTCY,
		(int)m_tInfo.fTCX,								// ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fTCY,
		RGB(255, 0, 255));								// �����ϰ��� �ϴ� ����

}

void CBladeFury::Release(void)
{
}

void CBladeFury::OnCollision(CObj* _pOther)
{
	if (m_bCanHit)
		return;
	if (m_CanHitCount > m_CanHitMaxCount)
		return;
	if (!_pOther->Get_CanHit())
		return;

	if (!m_pFirst)
		m_pFirst = _pOther;
	else if(m_pFirst == _pOther)
	{
		m_pFirst = nullptr;
		m_bCanHit = true;
		return;
	}

	++m_CanHitCount;

	if (_pOther->Get_Tag() == "Monster")
	{
		_pOther->OnHit(this);
	}
}

void CBladeFury::Motion_Change(void)
{
	
}
