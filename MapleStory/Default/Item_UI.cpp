#include "stdafx.h"
#include "Item_UI.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "InvenMgr.h"
#include "ObjMgr.h"
#include "Player.h"


CItem_UI::CItem_UI()
	: m_bIsOpen(false)
	, m_sInfo{}
{
}

CItem_UI::~CItem_UI()
{
	Release();
}

void CItem_UI::Initialize(void)
{
	m_sTag = "Item_UI";
	m_sInfo.InvenID = 100;


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

int CItem_UI::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;



	return OBJ_NOEVENT;
}

void CItem_UI::Late_Update(void)
{

}

void CItem_UI::Render(HDC hDC)
{
	Update_Rect();

	if (m_sInfo.InvenID == 100)
		return;

	HDC		hMemDC = nullptr;
	if (m_sInfo.sTag == "RedPosion")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"RedPotion");
		m_tInfo.fTCX = 30.f;
		m_tInfo.fTCY = 30.f;
		m_tFrame.iFrameStart = 0;
	}
	else if (m_sInfo.sTag == "BluePosion")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BluePotion");
		m_tInfo.fTCX = 30.f;
		m_tInfo.fTCY = 30.f;
		m_tFrame.iFrameStart = 0;
	}
	else if (m_sInfo.sTag == "Weapon")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Equip");
		m_tInfo.fTCX = 40.f;
		m_tInfo.fTCY = 40.f;
		m_tFrame.iFrameStart = 0;
	}
	else if (m_sInfo.sTag == "Shute")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Equip");
		m_tInfo.fTCX = 40.f;
		m_tInfo.fTCY = 40.f;
		m_tFrame.iFrameStart = 1;
	}
	else if (m_sInfo.sTag == "Shose")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Equip");
		m_tInfo.fTCX = 40.f;
		m_tInfo.fTCY = 40.f;
		m_tFrame.iFrameStart = 2;
	}
	else if (m_sInfo.sTag == "Gyenjong")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Equip");
		m_tInfo.fTCX = 40.f;
		m_tInfo.fTCY = 40.f;
		m_tFrame.iFrameStart = 3;
	}
	else if (m_sInfo.sTag == "Cave")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Equip");
		m_tInfo.fTCX = 40.f;
		m_tInfo.fTCY = 40.f;
		m_tFrame.iFrameStart = 5;
	}
	else if (m_sInfo.sTag == "Het")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Equip");
		m_tInfo.fTCX = 40.f;
		m_tInfo.fTCY = 40.f;
		m_tFrame.iFrameStart = 6;
	}
	else if (m_sInfo.sTag == "Glove")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Equip");
		m_tInfo.fTCX = 40.f;
		m_tInfo.fTCY = 40.f;
		m_tFrame.iFrameStart = 7;
	}

	if (!hMemDC)
		return;
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


	if (m_sInfo.eID == IT_CONSUM)
	{
		LOGFONT m_labelFontInfo{};
		m_labelFontInfo.lfHeight = 14;
		m_labelFontInfo.lfWidth = 7;
		m_labelFontInfo.lfCharSet = TURKISH_CHARSET;
		HFONT textFont, oldFont;
		textFont = CreateFontIndirect(&m_labelFontInfo);
		oldFont = (HFONT)SelectObject(hDC, textFont);

		TCHAR lpOut[1024];
		SetBkMode(hDC, TRANSPARENT);
		SetTextColor(hDC, RGB(0, 0, 0));
		wsprintf(lpOut, TEXT("%d"), m_sInfo.iCount);
		TextOut(hDC, m_tTRect.left, m_tTRect.top + 17, lpOut, lstrlen(lpOut));
		SetTextColor(hDC, RGB(0, 0, 0));
		wsprintf(lpOut, TEXT("%d"), m_sInfo.iCount);
		TextOut(hDC, m_tTRect.left + 2, m_tTRect.top + 19, lpOut, lstrlen(lpOut));

		SetTextColor(hDC, RGB(255, 255, 255));
		wsprintf(lpOut, TEXT("%d"), m_sInfo.iCount);
		TextOut(hDC, m_tTRect.left + 1, m_tTRect.top + 18, lpOut, lstrlen(lpOut));

		SelectObject(hDC, oldFont);
		DeleteObject(textFont);
	}


}


void CItem_UI::OnCollision(CObj* _pOther)
{
	if (m_sInfo.InvenID == 100)
		return;

	if (_pOther->Get_Tag() == "Mouse")
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
		{
			CInvenMgr::Get_Instance()->Use_Item(m_sInfo.InvenID);
		}
	}
}


void CItem_UI::ColRender(HDC hDC)
{

	Update_Rect();

	Rectangle(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tRect.right),
		int(m_tRect.bottom));
}


void CItem_UI::Release(void)
{

}