#include "stdafx.h"
#include "Mouse.h"

#include "ScrollMgr.h"

CMouse::CMouse()
{
}

CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize(void)
{
	m_tInfo.fCCX = 20.f;
	m_tInfo.fCCY = 20.f;
}

int CMouse::Update(void)
{

	POINT	pt{};

	GetCursorPos(&pt);	// ���� ���콺�� ��ġ ��ǥ�� ������ �Լ�
	ScreenToClient(g_hWnd, &pt);	// ��ü ��ũ���������� ������ Ŭ���̾�Ʈ(â) ��ǥ�� ��ȯ

	m_tInfo.fX = (float)pt.x;
	m_tInfo.fY = (float)pt.y;
	
	Update_Rect();
	ShowCursor(false);		// ���콺 Ŀ���� ������� �ʰڴ�.

	return OBJ_NOEVENT;
}

void CMouse::Late_Update(void)
{
	

}

void CMouse::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	// TEST: ���콺 ��ǥ ǥ��
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	int iRealPosX = m_tInfo.fX - iScrollX;
	int iRealPosY = m_tInfo.fY - iScrollY;
	TCHAR lpOut[1024];
	wsprintf(lpOut, TEXT("lX: %d \nY: %d"), iRealPosX, iRealPosY);
	TextOut(hDC, 35, 15, lpOut, lstrlen(lpOut));
}

void CMouse::Release(void)
{
	
}
