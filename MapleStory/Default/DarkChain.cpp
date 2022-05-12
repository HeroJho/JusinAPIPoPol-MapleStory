#include "stdafx.h"
#include "DarkChain.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"

CDarkChain::CDarkChain()
{
}

CDarkChain::~CDarkChain()
{
	Release();
}

void CDarkChain::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/DarkedMage/Skill_1/Skill_1.bmp", L"Skill_1");
	Set_FrameKey(L"Skill_1");
	m_bOnePlay = true;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 25;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 90.f;
	m_tFrame.dwTime = GetTickCount64();


	// 콜리젼 크기, 피봇 설정
	m_tInfo.fCCX = 200.f;
	m_tInfo.fCCY = 800.f;
	m_tColPivot.x = 0.f;
	m_tColPivot.y = -30.f;
	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 1200.f;
	m_tInfo.fTCY = 1800.f;

	Set_Stat(0, 20);
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
	m_fSkillTime = 1000.f;
	m_fDeleteTime = 2200.f;

}

int CDarkChain::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

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

void CDarkChain::Late_Update(void)
{
	if (!m_bStayPlay)
		Move_Frame();
}

void CDarkChain::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);


	GdiTransparentBlt(hDC, 									// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tTRect.left + iScrollX),					// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tTRect.top - 37 + iScrollY),
		int(m_tInfo.fTCX),								// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fTCY),
		hMemDC,											// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fTCX,		// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fTCY,
		(int)m_tInfo.fTCX,								// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fTCY,
		RGB(255, 0, 255));								// 제거하고자 하는 색상

}

void CDarkChain::Release(void)
{
}

void CDarkChain::OnCollision(CObj* _pOther)
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

void CDarkChain::Motion_Change(void)
{

}
