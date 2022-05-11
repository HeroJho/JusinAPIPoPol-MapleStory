#include "stdafx.h"
#include "Stage1.h"
#include "AbstractFactory.h"

#include "SceneMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "ScrollMgr.h"

#include "Player.h"
#include "Monster.h"
#include "Portal.h"

CStage1::CStage1()
{
	m_tMapSize.left = 0.f;
	m_tMapSize.top = 0.f;
	m_tMapSize.right = 2238.f;
	m_tMapSize.bottom = 1597.f - 300.f;
}

CStage1::~CStage1()
{
	Release();
}

void CStage1::Initialize(void)
{

	// Bmp 로딩
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Scene1/1_Middle.bmp", L"1_Middle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Scene1/1_Back.bmp", L"1_Back");
	CLineMgr::Get_Instance()->Scene_1();

	// Player 생성
	if (!CObjMgr::Get_Instance()->Get_Player())
	{
		CObj* pPlayer = CAbstractFactory<CPlayer>::Create(1000.f, 500.f, "Player");
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pPlayer);
		CObjMgr::Get_Instance()->Set_Player(pPlayer);
	}
	else
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(390.f, 930.f);
	

	// 포탈
	CObjMgr::Get_Instance()->Add_Object(OBJ_MAP, CAbstractFactory<CPortal>::Create(390.f, 930.f, "Portal_1To2"));

	// 카메라 설정
	CScrollMgr::Get_Instance()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	CScrollMgr::Get_Instance()->Initialize();
}

void CStage1::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Update();
}

void CStage1::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage1::Render(HDC hDC)
{
	// 출력 순서
	RenderBackGround(hDC);

	CObjMgr::Get_Instance()->Render(hDC);
	CLineMgr::Get_Instance()->Render(hDC);
}

void CStage1::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_MONSTER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_NPC);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_MAP);
}

void CStage1::RenderBackGround(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hBackMemDC = CBmpMgr::Get_Instance()->Find_Image(L"1_Back");
	GdiTransparentBlt(hDC,
		(iScrollX / 2),
		(iScrollY / 2) - 300.f,
		3730,
		1597,
		hBackMemDC,
		0,
		0,
		3730,
		1597,
		RGB(255, 0, 255));

	HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"1_Middle");
	GdiTransparentBlt(hDC,
		iScrollX,
		iScrollY,
		3663,
		1597,
		hGroundMemDC,
		0,
		0,
		3663,
		1597,
		RGB(255, 0, 255));
}