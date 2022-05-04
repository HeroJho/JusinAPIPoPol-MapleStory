#include "stdafx.h"
#include "Logo.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"


CLogo::CLogo()
{
}

CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logo/Logo.bmp", L"Logo");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Test.bmp", L"Test");
}

void CLogo::Update(void)
{
	
}

void CLogo::Late_Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);

		return;
	}
}

void CLogo::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Logo");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Test");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		0 + 400,							// 2,3 인자 :  복사받을 위치 X, Y
		0 + 250,
		36,									// 4,5 인자 : 복사받을 가로, 세로 길이
		64,
		hMemDC,								// 비트맵을 가지고 있는 DC
		0,									// 비트맵 출력 시작 좌표, X,Y
		0,
		36,									// 복사할 비트맵의 가로, 세로 길이
		64,
		RGB(255, 0, 255));					// 제거하고자 하는 색상

}

void CLogo::Release(void)
{
	
}
