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

	//m_tInfo.fX = 100.f;
	//m_tInfo.fY = 300.f;

	m_tInfo.fCX = 36.f;
	m_tInfo.fCY = 64.f;

	m_fSpeed = 3.f;

	m_fDiagonal = 100.f;

	m_fValY = 0.f;
	m_bJump = false;
	m_bOnAir = false;
	m_fJumpPower = 10.f;
	m_fAirTime = 0.f;
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	// ������ ����
	Key_Input();
	// Jumping();
	// OffSet();

	// ��� ������ ���� �ڿ� �������� ��ǥ�� �ϼ�
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	// 1. ������ ���´�.
	float		LinefY = 0.f;
	bool		bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &LinefY);

	// 3. ���� ���ο� ���� �߷� �����Ѵ�.
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

	// 2. �������� �ƴ��� �Ǵ��Ѵ�.
	if (LinefY <= m_tInfo.fY)
	{	// �ٴ��� ��
		m_tInfo.fY = LinefY;
		m_bOnAir = false;
		//m_fAirTime = 0.f;
		m_fValY = 0.f;
	}
	else if (LinefY > m_tInfo.fY)
	{	// ������ ��
		m_bOnAir = true;
	}

	if(!m_bOnAir)
	{
		m_tInfo.fY = LinefY;
		m_bJump = false;
	}

}

void CPlayer::Jumping(void)
{
	//float		fY = 0.f;

	//bool		bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);

	//if (m_bOnAir)
	//{
	//	m_tInfo.fY -= m_fJumpPower * m_fJumpTime - 9.8f * m_fJumpTime * m_fJumpTime * 0.5f;
	//	m_fJumpTime += 0.2f;

	//	if (bLineCol && (fY < m_tInfo.fY))
	//	{
	//		m_bOnAir = false;
	//		m_fJumpTime = 0.f;
	//		m_tInfo.fY = fY;
	//	}
	//}
	//else if (bLineCol)
	//{
	//	m_tInfo.fY = fY;
	//}
}


void CPlayer::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	
	/*BitBlt(hDC,							// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left + iScrollX),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top), 
		int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY), 
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		0,								// 7, 8���� : ��Ʈ���� ����� ���� ��ǥ, X,Y
		0, 
		SRCCOPY);*/						// ���ȿ��, �״�� ���� ���

	

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
			int(m_tRect.left + iScrollX),	// 2,3 ���� :  ������� ��ġ X, Y
			int(m_tRect.top - m_tInfo.fCY / 2.f),
			int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
			int(m_tInfo.fCY),
			hMemDC,							// ��Ʈ���� ������ �ִ� DC
			0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			0,
			(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));			// �����ϰ��� �ϴ� ����
				
}
void CPlayer::Release(void)
{
	
}

void CPlayer::Key_Input(void)
{
	float	fY = 0.f;

	// GetKeyState
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		m_bJump = true;
		m_bOnAir = true;
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
