#include "stdafx.h"
#include "LevelUp.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "UIMgr.h"


CLevelUp::CLevelUp()
{
}

CLevelUp::~CLevelUp()
{
	Release();
}

void CLevelUp::Initialize(void)
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_ITEM);
	CSoundMgr::Get_Instance()->PlaySound(L"LevelUp.wav", SOUND_ITEM, 1);


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/LevelUp/LevelUp.bmp", L"LevelUp");
	Set_FrameKey(L"LevelUp");
	m_bOnePlay = true;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 20;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 80.f;
	m_tFrame.dwTime = GetTickCount64();


	// 콜리젼 크기, 피봇 설정
	m_tInfo.fCCX = 1200.f;
	m_tInfo.fCCY = 1200.f;
	m_tColPivot.x = 0.f;
	m_tColPivot.y = -200.f;
	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 1000.f;
	m_tInfo.fTCY = 1000.f;

	Set_Stat(0, 0, 50);
	m_fSpeed = 0.f;

	m_bCanHit = true;
	m_CanHitCount = 0;
	m_CanHitMaxCount = 15;

	m_pOldLine = nullptr;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;

	m_fOldSkillTime = GetTickCount64();
	m_fSkillTime = 700.f;
	m_fDeleteTime = 2000.f;

}

int CLevelUp::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX = m_pTarget->Get_Info().fX;
	m_tInfo.fY = m_pTarget->Get_Info().fY;


	// 히트 시간
	if (m_fOldSkillTime + m_fSkillTime < GetTickCount64() && !m_bJump)
	{
		m_bCanHit = false;
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

void CLevelUp::Late_Update(void)
{
	if (!m_bStayPlay)
		Move_Frame();
}

void CLevelUp::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);


	GdiTransparentBlt(hDC, 									// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tTRect.left + iScrollX),					// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tTRect.top - 230 + iScrollY),
		int(m_tInfo.fTCX),								// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fTCY),
		hMemDC,											// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fTCX,		// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fTCY,
		(int)m_tInfo.fTCX,								// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fTCY,
		RGB(255, 0, 255));								// 제거하고자 하는 색상

}

void CLevelUp::Release(void)
{
}

void CLevelUp::OnCollision(CObj* _pOther)
{
	if (m_bCanHit)
		return;
	if (m_CanHitCount > m_CanHitMaxCount)
		return;
	if (!_pOther->Get_CanHit())
		return;

	if (!m_pFirst)
		m_pFirst = _pOther;
	else if (m_pFirst == _pOther)
	{
		m_pFirst = nullptr;
		m_bCanHit = true;
		return;
	}

	++m_CanHitCount;

	if (_pOther->Get_Tag() == "Monster")
	{
		_pOther->OnHit(this);
		CUIMgr::Get_Instance()->MakeDamge(12, 120.f, 99999999, 99999999, _pOther->Get_Info().fX, _pOther->Get_Info().fY, 120.f, 40.f);
	}
}

void CLevelUp::Motion_Change(void)
{

}
