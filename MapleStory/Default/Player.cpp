#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "Shield.h"
#include "ScrewBullet.h"
#include "GuideBullet.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Test.bmp", L"Test");
	Set_FrameKey(L"Test");

	m_tInfo.fCX = 36.f;
	m_tInfo.fCY = 64.f;

	m_eState = IDLE;
	m_fSpeed = 3.f;
	m_fJumpPower = 10.f;

	m_pOldLine = nullptr;
	m_pDropLine = nullptr;
	m_pHangLine = nullptr;
	m_bDrop = false;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;
	m_fDropY = 0.f;
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	// 연산을 진행
	
	switch (m_eState)
	{
	case CPlayer::IDLE:
		Key_Input();
		break;
	case CPlayer::MOVE:
		Key_Input();
		break;
	case CPlayer::SKILL:
		Key_Input();
		break;
	case CPlayer::BEND:
		Key_Input();
		break;
	case CPlayer::HANG:
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		{
			m_tInfo.fY -= m_fSpeed;
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		{
			m_tInfo.fY += m_fSpeed;
		}

		if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
		{
			m_eState = IDLE;
			m_bJump = true;
			m_bOnAir = true;
		}

		break;
	default:
		break;
	}



	// 모든 연산이 끝난 뒤에 최종적인 좌표를 완성
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	switch (m_eState)
	{
	case CPlayer::IDLE:
		Update_Gravity();
		break;
	case CPlayer::MOVE:
		Update_Gravity();
		break;
	case CPlayer::SKILL:
		Update_Gravity();
		break;
	case CPlayer::BEND:
		Update_Gravity();
		break;
	case CPlayer::HANG:
		Update_Hang();
		break;
	}
}

void CPlayer::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	
	/*BitBlt(hDC,							// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top), 
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY), 
		hMemDC,							// 비트맵을 가지고 있는 DC
		0,								// 7, 8인자 : 비트맵을 출력할 시작 좌표, X,Y
		0, 
		SRCCOPY);*/						// 출력효과, 그대로 복사 출력

	

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top - m_tInfo.fCY / 2.f),
			int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY),
			hMemDC,							// 비트맵을 가지고 있는 DC
			0,								// 비트맵 출력 시작 좌표, X,Y
			0,
			(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));			// 제거하고자 하는 색상
				
}
void CPlayer::Release(void)
{
	
}


void CPlayer::Update_Gravity(void)
{
	// 1. 라인을 얻어온다.
	float		LinefY = 0.f;

	CLine* m_pCurLine = nullptr;

	if (m_bDrop && !m_pDropLine)
	{
		m_pCurLine = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &LinefY, m_bDrop);
		m_pDropLine = m_pCurLine;
		m_fDropY = LinefY;
	}
	else if (!m_pDropLine)
	{
		m_pCurLine = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &LinefY, m_bDrop);
		m_fDropY = LinefY;
	}
	if (!m_pCurLine)
		m_pCurLine = m_pDropLine;

	// 3. 공중 여부에 따라 중력 적용한다.
	if (m_bOnAir)
	{
		// m_fAirTime += 0.2f;

		m_fValY += 0.4f;

		// m_tInfo.fY -= m_fJumpPower * m_fAirTime - 1.f * m_fAirTime * m_fAirTime * 0.5f;
		m_tInfo.fY += m_fValY;
	}


	if (m_bJump)
	{
		m_tInfo.fY -= m_fJumpPower;
	}

	// 2. 공중인지 아닌지 판단한다.
	if (m_fDropY <= m_tInfo.fY)
	{	// 바닥일 때
		m_tInfo.fY = m_fDropY;
		m_bOnAir = false;
		m_bDrop = false;
		m_pDropLine = nullptr;
		m_fValY = 0.f;
	}
	else if (m_fDropY > m_tInfo.fY)
	{	// 공중일 때
		// 이전 라인이랑 같고,           대각선일때
		if (!(m_pOldLine == m_pCurLine && m_pCurLine->Get_Diagonal()))
			m_bOnAir = true;
	}

	if (!m_bOnAir)
	{
		m_tInfo.fY = m_fDropY;
		m_pDropLine = nullptr;
		m_bDrop = false;
		m_bJump = false;
		m_fValY = 0.f;
	}

	m_pOldLine = m_pCurLine;
}

void CPlayer::Update_Hang(void)
{
	float fLineY = 0.f;
	m_pHangLine = CLineMgr::Get_Instance()->Collision_HangLine(m_tInfo.fX, m_tInfo.fY, &fLineY);

	if (!m_pHangLine)
	{
		m_eState = IDLE;
		return;
	}

	m_tInfo.fX = m_pHangLine->Get_Info().tLPoint.fX;
	
	m_pDropLine = nullptr;
	m_bDrop = false;
	m_bJump = false;
	m_fValY = 0.f;
}

void CPlayer::Key_Input(void)
{
	float	fY = 0.f;

	// GetKeyState
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		{
			m_bDrop = true;
			m_bOnAir = true;
		}
		else
		{
			m_bJump = true;
			m_bOnAir = true;
		}
	}



	if (CKeyMgr::Get_Instance()->Key_Down(VK_UP))
	{
		m_eState = HANG;
	}
	else if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN))
	{
		m_eState = HANG;
	}

}


void CPlayer::OffSet(void)
{
	int		iOffSetX = WINCX >> 1;
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iItv = 300;


	if (iOffSetX - iItv > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (iOffSetX + iItv < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);
}
