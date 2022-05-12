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

	GetCursorPos(&pt);	// 현재 마우스의 위치 좌표를 얻어오는 함수
	ScreenToClient(g_hWnd, &pt);	// 전체 스크린영역에서 생성한 클라이언트(창) 좌표로 변환

	m_tInfo.fX = (float)pt.x;
	m_tInfo.fY = (float)pt.y;
	
	Update_Rect();
	ShowCursor(false);		// 마우스 커서를 출력하지 않겠다.

	return OBJ_NOEVENT;
}

void CMouse::Late_Update(void)
{
	

}

void CMouse::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	// TEST: 마우스 좌표 표시
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
