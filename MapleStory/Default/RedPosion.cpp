#include "stdafx.h"
#include "RedPosion.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "InvenMgr.h"
#include "SoundMgr.h"

CRedPosion::CRedPosion()
{
}

CRedPosion::~CRedPosion()
{
	Release();
}

void CRedPosion::Initialize(void)
{
	m_sItemTag = "RedPosion";
	m_eID = IT_CONSUM;

	Set_FrameKey(L"RedPotion");
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 1000.f;
	m_tFrame.dwTime = GetTickCount64();


	// 콜리젼 크기, 피봇 설정
	m_tInfo.fCCX = 25.f;
	m_tInfo.fCCY = 25.f;
	m_tColPivot.x = 0.f;
	m_tColPivot.y = -10.f;
	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 30.f;
	m_tInfo.fTCY = 30.f;

	m_fSpeed = 0.f;

	m_pOldLine = nullptr;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;

	m_bEat = false;

	m_fUpTime = 500.f;
	m_fOldUpTime = 0.f;

	m_iMove = 0.f;
	m_bUpDown = false;
}

int CRedPosion::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;



	Update_Rect();

	return OBJ_NOEVENT;
}

void CRedPosion::Late_Update(void)
{

	if (m_bEat)
	{
		if (m_fOldUpTime + m_fUpTime < GetTickCount64())
			Set_Dead();
		m_tInfo.fY -= 7.5f;

		float fPx = m_pTarget->Get_Info().fX - m_tInfo.fX;
		if (fPx < -5.f)
			m_tInfo.fX -= 3.f;
		else if (fPx > 5.f)
			m_tInfo.fX += 3.f;

		Update_Gravity(true);
	}
	else
	{
		if (6.f < m_iMove)
			m_bUpDown = false;
		else if (0.f > m_iMove)
			m_bUpDown = true;

		if (m_bUpDown)
			m_iMove += 0.2f;
		else
			m_iMove -= 0.2f;

		Update_Gravity();
	}

	Move_Frame();
}

void CRedPosion::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 									// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tTRect.left + iScrollX),					// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tTRect.top - 15 + m_iMove + iScrollY),
		int(m_tInfo.fTCX),								// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fTCY),
		hMemDC,											// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fTCX,		// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fTCY,
		(int)m_tInfo.fTCX,								// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fTCY,
		RGB(255, 0, 255));								// 제거하고자 하는 색상
}

void CRedPosion::Release(void)
{
}



void CRedPosion::OnHit(CObj* _pOther)
{
	if (m_bEat)
		return;

	CSoundMgr::Get_Instance()->StopSound(SOUND_ITEM);
	CSoundMgr::Get_Instance()->PlaySound(L"PickUpItem.wav", SOUND_ITEM, 1);

	ITEM sInfo = CInvenMgr::Get_Instance()->MakeItemInfo(this);
	CInvenMgr::Get_Instance()->Add_Item(sInfo);

	m_pTarget = _pOther;
	m_bEat = true;
	m_fOldUpTime = GetTickCount64();
}

void CRedPosion::OnCollision(CObj* _pOther)
{

}

