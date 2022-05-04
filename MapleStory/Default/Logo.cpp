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

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		0 + 400,							// 2,3 ���� :  ������� ��ġ X, Y
		0 + 250,
		36,									// 4,5 ���� : ������� ����, ���� ����
		64,
		hMemDC,								// ��Ʈ���� ������ �ִ� DC
		0,									// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		36,									// ������ ��Ʈ���� ����, ���� ����
		64,
		RGB(255, 0, 255));					// �����ϰ��� �ϴ� ����

}

void CLogo::Release(void)
{
	
}
