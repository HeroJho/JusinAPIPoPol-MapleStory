#include "stdafx.h"
#include "ShopS_UI.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "InvenMgr.h"
#include "ObjMgr.h"
#include "Player.h"


CShopS_UI::CShopS_UI()
	: m_sInfo{}
{

}

CShopS_UI::~CShopS_UI()
{
	Release();
}

void CShopS_UI::Initialize(void)
{
	m_tFrame.iFrameStart = 0;

	m_sTag = "Shop_UI";
	m_sInfo.InvenID = 101;
	m_sInfo.eID = IT_SKILL;

	m_tInfo.fX = 9999.f;
	m_tInfo.fY = 9999.f;

	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 30.f;
	m_tInfo.fTCY = 30.f;


	m_tInfo.fCCX = 30.f;
	m_tInfo.fCCY = 30.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)0.f;

}

int CShopS_UI::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	return OBJ_NOEVENT;
}
void CShopS_UI::Late_Update(void)
{

}


void CShopS_UI::Render(HDC hDC)
{
	Update_Rect();

	LOGFONT m_labelFontInfo{};
	m_labelFontInfo.lfHeight = 12;
	m_labelFontInfo.lfWidth = 5;
	m_labelFontInfo.lfCharSet = HANGEUL_CHARSET;
	HFONT textFont, oldFont;
	textFont = CreateFontIndirect(&m_labelFontInfo);
	oldFont = (HFONT)SelectObject(hDC, textFont);

	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(0, 0, 0));
	TCHAR lpOut[1024];


	HDC		hMemDC = nullptr;

	if (m_sInfo.sTag == "RedPosion")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"RedPotion");
		wsprintf(lpOut, TEXT("빨간 포션"));
		TextOut(hDC, m_tTRect.left + 37, m_tTRect.top + 2, lpOut, lstrlen(lpOut));

		wsprintf(lpOut, TEXT("%d 메소"), m_sInfo.InvenID);
		TextOut(hDC, m_tTRect.left + 55, m_tTRect.top + 20, lpOut, lstrlen(lpOut));
	}
	else if (m_sInfo.sTag == "BluePosion")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BluePotion");
		wsprintf(lpOut, TEXT("파란 포션"));
		TextOut(hDC, m_tTRect.left + 37, m_tTRect.top + 2, lpOut, lstrlen(lpOut));

		wsprintf(lpOut, TEXT("%d 메소"), m_sInfo.InvenID);
		TextOut(hDC, m_tTRect.left + 55, m_tTRect.top + 20, lpOut, lstrlen(lpOut));
	}
	else if (m_sInfo.sTag == "Weapon")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Equip");
		wsprintf(lpOut, TEXT("반짝반짝 무기"));
		TextOut(hDC, m_tTRect.left + 41, m_tTRect.top + 7, lpOut, lstrlen(lpOut));
		m_tFrame.iFrameStart = 0;

		wsprintf(lpOut, TEXT("%d 메소"), m_sInfo.InvenID);
		TextOut(hDC, m_tTRect.left + 60, m_tTRect.top + 25, lpOut, lstrlen(lpOut));
	}
	else if (m_sInfo.sTag == "Shute")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Equip");
		wsprintf(lpOut, TEXT("한 벌옷"));
		TextOut(hDC, m_tTRect.left + 41, m_tTRect.top + 7, lpOut, lstrlen(lpOut));
		m_tFrame.iFrameStart = 1;

		wsprintf(lpOut, TEXT("%d 메소"), m_sInfo.InvenID);
		TextOut(hDC, m_tTRect.left + 60, m_tTRect.top + 25, lpOut, lstrlen(lpOut));
	}
	else if (m_sInfo.sTag == "Shose")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Equip");
		wsprintf(lpOut, TEXT("신발"));
		TextOut(hDC, m_tTRect.left + 41, m_tTRect.top + 7, lpOut, lstrlen(lpOut));
		m_tFrame.iFrameStart = 2;

		wsprintf(lpOut, TEXT("%d 메소"), m_sInfo.InvenID);
		TextOut(hDC, m_tTRect.left + 60, m_tTRect.top + 25, lpOut, lstrlen(lpOut));
	}
	else if (m_sInfo.sTag == "Gyenjong")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Equip");
		wsprintf(lpOut, TEXT("견장"));
		TextOut(hDC, m_tTRect.left + 41, m_tTRect.top + 7, lpOut, lstrlen(lpOut));
		m_tFrame.iFrameStart = 3;

		wsprintf(lpOut, TEXT("%d 메소"), m_sInfo.InvenID);
		TextOut(hDC, m_tTRect.left + 60, m_tTRect.top + 25, lpOut, lstrlen(lpOut));
	}
	else if (m_sInfo.sTag == "Cave")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Equip");
		wsprintf(lpOut, TEXT("망토"));
		TextOut(hDC, m_tTRect.left + 41, m_tTRect.top + 7, lpOut, lstrlen(lpOut));
		m_tFrame.iFrameStart = 5;

		wsprintf(lpOut, TEXT("%d 메소"), m_sInfo.InvenID);
		TextOut(hDC, m_tTRect.left + 60, m_tTRect.top + 25, lpOut, lstrlen(lpOut));
	}
	else if (m_sInfo.sTag == "Het")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Equip");
		wsprintf(lpOut, TEXT("모자"));
		TextOut(hDC, m_tTRect.left + 41, m_tTRect.top + 7, lpOut, lstrlen(lpOut));
		m_tFrame.iFrameStart = 6;

		wsprintf(lpOut, TEXT("%d 메소"), m_sInfo.InvenID);
		TextOut(hDC, m_tTRect.left + 60, m_tTRect.top + 25, lpOut, lstrlen(lpOut));
	}
	else if (m_sInfo.sTag == "Glove")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Equip");
		wsprintf(lpOut, TEXT("장갑"));
		TextOut(hDC, m_tTRect.left + 41, m_tTRect.top + 7, lpOut, lstrlen(lpOut));
		m_tFrame.iFrameStart = 7;

		wsprintf(lpOut, TEXT("%d 메소"), m_sInfo.InvenID);
		TextOut(hDC, m_tTRect.left + 60, m_tTRect.top + 25, lpOut, lstrlen(lpOut));
	}



	SelectObject(hDC, oldFont);
	DeleteObject(textFont);


	if (!hMemDC)
		return;

	if (m_sInfo.eID == IT_CONSUM)
	{
		m_tInfo.fTCX = 30.f;
		m_tInfo.fTCY = 30.f;

		GdiTransparentBlt(hDC,
			int(m_tTRect.left),
			int(m_tTRect.top),
			int(m_tInfo.fTCX),
			int(m_tInfo.fTCY),
			hMemDC,
			0,
			0,
			(int)m_tInfo.fTCX,
			(int)m_tInfo.fTCY,
			RGB(255, 0, 255));
	}
	else if (m_sInfo.eID == IT_EQUIT)
	{
		m_tInfo.fTCX = 40.f;
		m_tInfo.fTCY = 40.f;

		GdiTransparentBlt(hDC,
			int(m_tTRect.left),
			int(m_tTRect.top),
			int(m_tInfo.fTCX),
			int(m_tInfo.fTCY),
			hMemDC,
			int(m_tFrame.iFrameStart * m_tInfo.fTCX),
			0,
			(int)m_tInfo.fTCX,
			(int)m_tInfo.fTCY,
			RGB(255, 0, 255));
	}


}


void CShopS_UI::OnCollision(CObj* _pOther)
{
	if (!CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		return;

	if (_pOther->Get_Tag() == "Mouse")
	{
		if(CInvenMgr::Get_Instance()->Des_Money(m_sInfo.InvenID))
			CInvenMgr::Get_Instance()->Add_Item(m_sInfo);
	}

}


void CShopS_UI::ColRender(HDC hDC)
{
	Update_Rect();

	Rectangle(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tRect.right),
		int(m_tRect.bottom));
}

void CShopS_UI::Release(void)
{

}