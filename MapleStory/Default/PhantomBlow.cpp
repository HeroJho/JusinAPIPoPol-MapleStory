#include "stdafx.h"
#include "PhantomBlow.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"


CPhantomBlow::CPhantomBlow()
{
}

CPhantomBlow::~CPhantomBlow()
{
	Release();
}

void CPhantomBlow::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/PhantomBlow/PhantomBlowL.bmp", L"PhantomBlowL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/PhantomBlow/PhantomBlowR.bmp", L"PhantomBlowR");
	Set_FrameKey(L"PhantomBlowL");
	m_bOnePlay = true;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 9;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = (DWORD)50.f;
	m_tFrame.dwTime = (DWORD)GetTickCount64();


	// 콜리젼 크기, 피봇 설정
	m_tInfo.fCCX = 300.f;
	m_tInfo.fCCY = 100.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)- 30.f;
	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 600.f;
	m_tInfo.fTCY = 300.f;

	Set_Stat(0, 10, 30);
	m_fSpeed = 0.f;

	m_bCanHit = false;
	m_CanHitCount = 0;
	m_CanHitMaxCount = 0;

	m_pOldLine = nullptr;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;

	m_fOldSkillTime = (float)GetTickCount64();
	m_fSkillTime = 100.f;
	m_fDeleteTime = 600.f;

}

int CPhantomBlow::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX = m_pTarget->Get_Info().fX;
	m_tInfo.fY = m_pTarget->Get_Info().fY;


	if (m_pTarget->Get_Dir() == DIR_LEFT)
	{
		m_tColPivot.x = (LONG) - 70.f;
		m_tColPivot.y = (LONG)-25.f;
		SetFrameDir(DIR_LEFT);
	}
	else
	{
		m_tColPivot.x = (LONG)70.f;
		m_tColPivot.y = (LONG)-25.f;
		SetFrameDir(DIR_RIGHT);
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

void CPhantomBlow::Late_Update(void)
{
	if (!m_bStayPlay)
		Move_Frame();
}

void CPhantomBlow::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	int left = 0;
	if (m_pTarget->Get_Dir() == DIR_LEFT)
	{
		left = m_tTRect.left + iScrollX - 50;
	}
	else
	{
		left = m_tTRect.left + iScrollX + 50;
	}


	GdiTransparentBlt(hDC, 								// 복사 받을, 최종적으로 그림을 그릴 DC
		left,											// 2,3 인자 :  복사받을 위치 X, Y
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

void CPhantomBlow::Release(void)
{
}

void CPhantomBlow::OnCollision(CObj* _pOther)
{
	if (m_CanHitCount > m_CanHitMaxCount)
		return;
	if (!_pOther->Get_CanHit())
		return;

	++m_CanHitCount;

	if (_pOther->Get_Tag() == "Monster")
	{
		_pOther->OnHit(this);
	}
}

void CPhantomBlow::SetFrameDir(DIRECTION _eDir)
{
	if (_eDir == DIR_LEFT)
		m_pFrameKey = L"PhantomBlowL";
	else
		m_pFrameKey = L"PhantomBlowR";

	m_eDir = _eDir;
}


void CPhantomBlow::Motion_Change(void)
{

}
