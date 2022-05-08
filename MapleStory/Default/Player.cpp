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
	: m_eCurState(IDLE), m_ePreState(END)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerL.bmp", L"PlayerL");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerR.bmp", L"PlayerR");
	//Set_FrameKey(L"PlayerL");
	//m_tFrame.iFrameStart = 0;
	//m_tFrame.iFrameEnd = 3;
	//m_tFrame.iMotion = 0;
	//m_tFrame.dwSpeed = 1000.f;
	//m_tFrame.dwTime = GetTickCount();

	m_tInfo.fCX = 1000.f;
	m_tInfo.fCY = 1000.f;

	m_eCurState = IDLE;
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

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Test.bmp", L"Test");
	Set_FrameKey(L"Test");
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 1000.f;
	m_tFrame.dwTime = GetTickCount();
	m_eCurState = TEST;
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	// 연산을 진행
	
	switch (m_eCurState)
	{
	case CPlayer::IDLE:
		Key_Input();
		break;
	case CPlayer::WALK:
		Key_Input();
		break;
	case CPlayer::AIR:
		Key_Input();
		break;
	case CPlayer::ATTACK:
		Key_Input();
		break;
	case CPlayer::SKILL:
		Key_Input();
		break;
	case CPlayer::HIT:
		Key_Input();
		break;
	case CPlayer::BENDIDLE:
	case CPlayer::BENDWALK:
		break;
	case CPlayer::HANGIDLE:
	case CPlayer::HANGWALK:
		Hang_Input();
		break;
	case CPlayer::DEAD:
		Key_Input();
		break;
	}

	OffSet();
	// 모든 연산이 끝난 뒤에 최종적인 좌표를 완성
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	switch (m_eCurState)
	{
	case CPlayer::IDLE:
		Update_Gravity();
		break;
	case CPlayer::WALK:
		Update_Gravity();
		break;
	case CPlayer::AIR:
		Update_Gravity();
		break;
	case CPlayer::ATTACK:
		Update_Gravity();
		break;
	case CPlayer::SKILL:
		Update_Gravity();
		break;
	case CPlayer::HIT:
		Update_Gravity();
		break;
	case CPlayer::BENDIDLE:
	case CPlayer::BENDWALK:
		break;
	case CPlayer::HANGIDLE:
	case CPlayer::HANGWALK:
		Update_Hang();
		break;
	case CPlayer::DEAD:
		Update_Gravity();
		break;
	}

	Motion_Change();
	Move_Frame();
}

void CPlayer::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 									// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX),								// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top - 37 + iScrollY),
			int(m_tInfo.fCX),								// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY),
			hMemDC,											// 비트맵을 가지고 있는 DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,		// 비트맵 출력 시작 좌표, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,								// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));								// 제거하고자 하는 색상

}
void CPlayer::Release(void)
{
	
}


void CPlayer::SetCurState(STATE _eState, DIRECTION _eDir)
{
	if(_eDir == DIR_LEFT)
		m_pFrameKey = L"PlayerL";
	else
		m_pFrameKey = L"PlayerR";

	m_eCurState = _eState;
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

		SetCurState(AIR, m_eDir);
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
		{
			m_bOnAir = true;
		}
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
		SetCurState(IDLE, m_eDir);
		return;
	}

	m_tInfo.fX = m_pHangLine->Get_Info().tLPoint.fX;
	
	m_pDropLine = nullptr;
	m_bDrop = false;
	m_bJump = false;
	m_fValY = 2.f;
	if(m_eCurState != HANGWALK)
		SetCurState(HANGIDLE, m_eDir);
}

void CPlayer::Key_Input(void)
{
	float	fY = 0.f;

	// GetKeyState
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
		m_eDir = DIR_LEFT;
		SetCurState(WALK, m_eDir);
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		m_eDir = DIR_RIGHT;
		SetCurState(WALK, m_eDir);
	}
	else
	{
		if (m_eCurState != HANGIDLE && m_eCurState != HANGWALK)
			SetCurState(IDLE, m_eDir);
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

	if (CKeyMgr::Get_Instance()->Key_Down(VK_UP) || CKeyMgr::Get_Instance()->Key_Down(VK_DOWN))
	{
		SetCurState(HANGIDLE, m_eDir);
	}

}

void CPlayer::Hang_Input(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		m_tInfo.fY -= m_fSpeed;
		SetCurState(HANGWALK, m_eDir);
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
		SetCurState(HANGWALK, m_eDir);
	}
	else
		SetCurState(HANGIDLE, m_eDir);

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		SetCurState(IDLE, m_eDir);
		m_bJump = true;
		m_bOnAir = true;
	}
}


void CPlayer::OffSet(void)
{
	int		iOffSetX = WINCX >> 1;
	int		iOffSetY = WINCY >> 1;
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	int		iItvX = 30;
	int		iItvY = 20;

	if (iOffSetX - iItvX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (iOffSetX + iItvX < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

	if (iOffSetY - iItvY > m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

	if (iOffSetY + iItvY < m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);

}

void CPlayer::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 800.f;
			m_tFrame.dwTime = GetTickCount();
			break;

		case WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case AIR:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case SKILL:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case BENDIDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case HANGIDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 7;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case BENDWALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case HANGWALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 7;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
	}
}