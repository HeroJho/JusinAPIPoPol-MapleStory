#include "stdafx.h"
#include "Inven_UI.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "InvenMgr.h"


CInven_UI::CInven_UI()
	: m_bIsOpen(false)
{
}


CInven_UI::~CInven_UI()
{
	Release();
}

void CInven_UI::Initialize(void)
{
	m_sTag = "InvenUI";

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/HpMp.bmp", L"HpMp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/hp.bmp", L"hp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/mp.bmp", L"mp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/exp.bmp", L"exp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/expGage.bmp", L"expGage");
	// Set_FrameKey(L"HpMp");


	m_tInfo.fX = 9999.f;
	m_tInfo.fY = 9999.f;

	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 172.f;
	m_tInfo.fTCY = 335.f;


	m_tInfo.fCCX = 172.f;
	m_tInfo.fCCY = 25.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)-155.f;

	m_bIsOpen = false;
}

int CInven_UI::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (CKeyMgr::Get_Instance()->Key_Down('I'))
	{
		if (m_bIsOpen)
		{
			m_tInfo.fX = 800.f;
			m_tInfo.fY = 300.f;
			m_bIsOpen = false;
		}
		else
		{
			m_tInfo.fX = 9999.f;
			m_tInfo.fY = 9999.f;
			m_bIsOpen = true;
		}
	}

	// 인벤 랜더
	for (auto& sInfo : CInvenMgr::Get_Instance()->Get_InvenList())
	{
		int slot = sInfo->GetInfo().InvenID;
		int x = slot % 4;
		int y = slot / 4;

		sInfo->Set_Pos(m_tInfo.fX - 59 + (x * 36), m_tInfo.fY - 102 + (y * 35));
		sInfo->Update();
	}


	Update_Rect();

	return OBJ_NOEVENT;
}

void CInven_UI::Late_Update(void)
{

}

void CInven_UI::Render(HDC hDC)
{
	HDC		hMemDCFrame = CBmpMgr::Get_Instance()->Find_Image(L"Inventory_Consum");

	// 프레임
	GdiTransparentBlt(hDC,
		int(m_tTRect.left),
		int(m_tTRect.top),
		int(m_tInfo.fTCX),
		int(m_tInfo.fTCY),
		hMemDCFrame,
		0,
		0,
		(int)m_tInfo.fTCX,
		(int)m_tInfo.fTCY,
		RGB(0, 255, 0));

	int size = to_string(CInvenMgr::Get_Instance()->Get_Money()).size();
	LOGFONT m_labelFontInfo{};
	m_labelFontInfo.lfHeight = 13;
	m_labelFontInfo.lfWidth = 5;
	m_labelFontInfo.lfCharSet = HANGEUL_CHARSET;
	HFONT textFont, oldFont;
	textFont = CreateFontIndirect(&m_labelFontInfo);
	oldFont = (HFONT)SelectObject(hDC, textFont);

	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(0, 0, 0));
	TCHAR lpOut[1024];
	wsprintf(lpOut, TEXT("%d"), CInvenMgr::Get_Instance()->Get_Money());
	TextOut(hDC, m_tTRect.left + 115 - (size * 5), m_tTRect.top + 267, lpOut, lstrlen(lpOut));
	
	SelectObject(hDC, oldFont);
	DeleteObject(textFont);


	// 인벤 랜더
	for (auto& sInfo : CInvenMgr::Get_Instance()->Get_InvenList())
	{
		sInfo->Render(hDC);
	}
}

void CInven_UI::ColRender(HDC hDC)
{
	Rectangle(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tRect.right),
		int(m_tRect.bottom));
}

void CInven_UI::Release(void)
{

}