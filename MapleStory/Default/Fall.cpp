#include "stdafx.h"
#include "Fall.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "UIMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"


CFall::CFall()
{
}

CFall::~CFall()
{
	Release();
}

void CFall::Initialize(void)
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"Tombstone.wav", SOUND_PEFFECT, 1);


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/fall.bmp", L"fall");
	Set_FrameKey(L"fall");
	m_bOnePlay = true;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 19;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 40.f;
	m_tFrame.dwTime = GetTickCount64();


	// 콜리젼 크기, 피봇 설정
	m_tInfo.fCCX = 100.f;
	m_tInfo.fCCY = 50.f;
	m_tColPivot.x = 0.f;
	m_tColPivot.y = -200.f;
	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 100.f;
	m_tInfo.fTCY = 50.f;

	Set_Stat(0, 0, 50);
	m_fSpeed = 0.f;

	//m_bCanHit = true;
	//m_CanHitCount = 0;
	//m_CanHitMaxCount = 15;

	m_pOldLine = nullptr;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;

	m_fOldSkillTime = GetTickCount64();
	//m_fSkillTime = 700.f;
	m_fDeleteTime = 2000.f;

}

int CFall::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	//m_tInfo.fX = m_pTarget->Get_Info().fX;
	//m_tInfo.fY = m_pTarget->Get_Info().fY;


	//// 히트 시간
	//if (m_fOldSkillTime + m_fSkillTime < GetTickCount64() && !m_bJump)
	//{
	//	m_bCanHit = false;
	//	m_bJump = true;
	//}




	// 소멸 시간
	if (((CPlayer*)CObjMgr::Get_Instance()->Get_Player())->GetCurState() != CPlayer::DEAD)
	{
		m_bDead = true;
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CFall::Late_Update(void)
{
	// Update_Gravity();

	
	if (CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY > m_tInfo.fY)
	{
		m_fValY += 0.5f;
		m_tInfo.fY += m_fValY;
	}
	else
		m_tInfo.fY = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY;



	if (!m_bStayPlay)
		Move_Frame();
}

void CFall::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);


	GdiTransparentBlt(hDC, 									// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tTRect.left + iScrollX),					// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tTRect.top -25 + iScrollY),
		int(m_tInfo.fTCX),								// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fTCY),
		hMemDC,											// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fTCX,		// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fTCY,
		(int)m_tInfo.fTCX,								// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fTCY,
		RGB(255, 0, 255));								// 제거하고자 하는 색상

}

void CFall::Release(void)
{
}

void CFall::OnCollision(CObj* _pOther)
{
	//if (m_bCanHit)
	//	return;
	//if (m_CanHitCount > m_CanHitMaxCount)
	//	return;
	//if (!_pOther->Get_CanHit())
	//	return;

	//if (!m_pFirst)
	//	m_pFirst = _pOther;
	//else if (m_pFirst == _pOther)
	//{
	//	m_pFirst = nullptr;
	//	m_bCanHit = true;
	//	return;
	//}

	//++m_CanHitCount;

	//if (_pOther->Get_Tag() == "Monster")
	//{
	//	_pOther->OnHit(this);
	//	CUIMgr::Get_Instance()->MakeDamge(12, 120.f, 99999999, 99999999, _pOther->Get_Info().fX, _pOther->Get_Info().fY, 120.f, 40.f);
	//}
}

void CFall::Motion_Change(void)
{

}
