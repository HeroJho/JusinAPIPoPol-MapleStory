#include "stdafx.h"
#include "Shop_UI.h"

#include "BmpMgr.h"
#include "KeyMgr.h"
#include "InvenMgr.h"


CShop_UI::CShop_UI()
	: m_bIsOpen(false)
{
}


CShop_UI::~CShop_UI()
{
	Release();
}

void CShop_UI::Initialize(void)
{
	m_sTag = "ShopUI";


	m_tInfo.fX = 9999.f;
	m_tInfo.fY = 9999.f;

	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 276.f;
	m_tInfo.fTCY = 505.f;


	m_tInfo.fCCX = 276.f;
	m_tInfo.fCCY = 505.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)-135.f;

	m_bIsOpen = false;


	for (int i = 0; i < 9; ++i)
	{
		m_aShopUIList[i] = new CShopS_UI;
		m_aShopUIList[i]->Initialize();
		m_aShopUIList[i]->SetIndex(i);


		m_aShopUIList[i]->Set_Pos(m_tInfo.fX - 59, m_tInfo.fY - 37 + (i * 40));
	}

	ITEM sInfo{};
	sInfo.eID = IT_CONSUM;
	sInfo.sTag = "BluePosion";
	sInfo.InvenID = 50;
	sInfo.iCount = 1;
	m_aShopUIList[0]->SetInfo(sInfo);
	sInfo.eID = IT_CONSUM;
	sInfo.sTag = "RedPosion";
	sInfo.InvenID = 80;
	sInfo.iCount = 1;
	m_aShopUIList[1]->SetInfo(sInfo);


	sInfo.eID = IT_EQUIT;
	sInfo.sTag = "Weapon";
	sInfo.InvenID = 80;
	sInfo.iCount = 1;
	sInfo.iAt = 50;
	sInfo.iHp = 0;
	sInfo.iMp = 0;
	sInfo.iLUK = 10;
	sInfo.iINT = 10;
	sInfo.iSTR = 10;
	sInfo.iDEX = 10;
	m_aShopUIList[2]->SetInfo(sInfo);

	sInfo.eID = IT_EQUIT;
	sInfo.sTag = "Shute";
	sInfo.InvenID = 80;
	sInfo.iCount = 1;
	sInfo.iAt = 0;
	sInfo.iHp = 200;
	sInfo.iMp = 0;
	sInfo.iLUK = 0;
	sInfo.iINT = 0;
	sInfo.iSTR = 0;
	sInfo.iDEX = 0;
	m_aShopUIList[3]->SetInfo(sInfo);

	sInfo.eID = IT_EQUIT;
	sInfo.sTag = "Shose";
	sInfo.InvenID = 80;
	sInfo.iCount = 1;
	sInfo.iSpeed = 2;
	sInfo.iAt = 0;
	sInfo.iHp = 10;
	sInfo.iMp = 0;
	sInfo.iLUK = 20;
	sInfo.iINT = 5;
	sInfo.iSTR = 5;
	sInfo.iDEX = 5;
	m_aShopUIList[4]->SetInfo(sInfo);

	sInfo.eID = IT_EQUIT;
	sInfo.sTag = "Gyenjong";
	sInfo.InvenID = 80;
	sInfo.iCount = 1;
	sInfo.iAt = 5;
	sInfo.iHp = 10;
	sInfo.iMp = 0;
	sInfo.iLUK = 10;
	sInfo.iINT = 5;
	sInfo.iSTR = 5;
	sInfo.iDEX = 5;
	m_aShopUIList[5]->SetInfo(sInfo);

	sInfo.eID = IT_EQUIT;
	sInfo.sTag = "Cave";
	sInfo.InvenID = 80;
	sInfo.iCount = 1;
	sInfo.iAt = 0;
	sInfo.iHp = 10;
	sInfo.iMp = 200;
	sInfo.iLUK = 10;
	sInfo.iINT = 5;
	sInfo.iSTR = 5;
	sInfo.iDEX = 5;
	m_aShopUIList[6]->SetInfo(sInfo);

	sInfo.eID = IT_EQUIT;
	sInfo.sTag = "Het";
	sInfo.InvenID = 80;
	sInfo.iCount = 1;
	sInfo.iAt = 0;
	sInfo.iHp = 50;
	sInfo.iMp = 0;
	sInfo.iLUK = 20;
	sInfo.iINT = 5;
	sInfo.iSTR = 5;
	sInfo.iDEX = 5;
	m_aShopUIList[7]->SetInfo(sInfo);

	sInfo.eID = IT_EQUIT;
	sInfo.sTag = "Glove";
	sInfo.InvenID = 80;
	sInfo.iCount = 1;
	sInfo.iAt = 20;
	sInfo.iHp = 0;
	sInfo.iMp = 0;
	sInfo.iLUK = 20;
	sInfo.iINT = 5;
	sInfo.iSTR = 5;
	sInfo.iDEX = 5;
	m_aShopUIList[8]->SetInfo(sInfo);

}

int CShop_UI::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	if (m_bIsOpen)
	{
		m_tInfo.fX = 400.f;
		m_tInfo.fY = 300.f;
	}
	else
	{
		m_tInfo.fX = 9999.f;
		m_tInfo.fY = 9999.f;
	}



	// 인벤

	for (int i = 0; i < 9; ++i)
	{
		m_aShopUIList[i]->Set_Pos(m_tInfo.fX - 110, m_tInfo.fY - 113 + (i * 42));
	}


	Update_Rect();

	return OBJ_NOEVENT;
}

void CShop_UI::Late_Update(void)
{

}

void CShop_UI::Render(HDC hDC)
{

	HDC		hMemDCFrame = CBmpMgr::Get_Instance()->Find_Image(L"store");

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


	for (int i = 0; i < 9; ++i)
	{
		m_aShopUIList[i]->Render(hDC);
		//m_aShopUIList[i]->ColRender(hDC);
	}
}

void CShop_UI::ColRender(HDC hDC)
{
	Rectangle(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tRect.right),
		int(m_tRect.bottom));
}

void CShop_UI::Release(void)
{
	for (int i = 0; i < 9; ++i)
		Safe_Delete(m_aShopUIList[i]);
}