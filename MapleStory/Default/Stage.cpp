#include "stdafx.h"
#include "Stage.h"
#include "AbstractFactory.h"

#include "SceneMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "ScrollMgr.h"

#include "Player.h"
#include "Monster.h"

CStage::CStage()
{
}

CStage::~CStage()
{
	Release();
}

void CStage::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Henesys/Henesys_1.bmp", L"Henesys_1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Henesys/Henesys_2.bmp", L"Henesys_2");
	CLineMgr::Get_Instance()->Initialize();
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(400.f, 600.f));
	// CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster>::Create());
}

void CStage::Update(void)
{
	CObjMgr::Get_Instance()->Update();
}

void CStage::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hBackMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Henesys_1");
	GdiTransparentBlt(hDC,
		(iScrollX/2),
		(iScrollY/2),
		5830,
		1600,
		hBackMemDC,
		0,
		0,
		5830,
		1600,
		RGB(255, 0, 255));

	HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Henesys_2");
	GdiTransparentBlt(hDC, 					
		iScrollX,							
		iScrollY,
		5830,								
		1600,
		hGroundMemDC,						
		0,									
		0,
		5830,								
		1600,
		RGB(255, 0, 255));



	CObjMgr::Get_Instance()->Render(hDC);
	CLineMgr::Get_Instance()->Render(hDC);
}

void CStage::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
}