#include "stdafx.h"
#include "Stage2.h"
#include "AbstractFactory.h"

#include "SceneMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "ScrollMgr.h"
#include "SpawnMgr.h"

#include "Player.h"
#include "Monster.h"
#include "Portal.h"
#include "BlockBox.h"

CStage2::CStage2()
{
	m_tMapSize.left = 0.f;
	m_tMapSize.top = 0.f;
	m_tMapSize.right = 2238.f;
	m_tMapSize.bottom = 2035.f - 300.f;
}

CStage2::~CStage2()
{
	Release();
}

void CStage2::Initialize(void)
{
	CSpawnMgr::Get_Instance()->Initialize();

	// Bmp 로딩
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Scene2/2_Middle.bmp", L"2_Middle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Scene2/2_Back.bmp", L"2_Back");
	CLineMgr::Get_Instance()->Scene_2();	// 1. 맵 라인
	CSpawnMgr::Get_Instance()->Scene_2();   // 2. 맵 스폰
	MakeMap();								// 3. 맵 블락, 포탈


	// Player 생성
	if (!CObjMgr::Get_Instance()->Get_Player())
	{
		CObj* pPlayer = CAbstractFactory<CPlayer>::Create(2122.f, 1568.f, "Player");
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pPlayer);
		CObjMgr::Get_Instance()->Set_Player(pPlayer);
	}
	else
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(2122.f, 1568.f);


	// 카메라 설정
	CScrollMgr::Get_Instance()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
}

void CStage2::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Update();
	CSpawnMgr::Get_Instance()->Update();
}

void CStage2::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage2::Render(HDC hDC)
{
	// 출력 순서
	RenderBackGround(hDC);

	CObjMgr::Get_Instance()->Render(hDC);
	//CLineMgr::Get_Instance()->Render(hDC);
}

void CStage2::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_MONSTER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_NPC);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_MAP);
}

void CStage2::RenderBackGround(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hBackMemDC = CBmpMgr::Get_Instance()->Find_Image(L"2_Back");
	GdiTransparentBlt(hDC,
		(iScrollX / 2),
		(iScrollY / 2) - 300.f,
		2238,
		2035,
		hBackMemDC,
		0,
		0,
		2238,
		2035,
		RGB(255, 0, 255));

	HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"2_Middle");
	GdiTransparentBlt(hDC,
		iScrollX,
		iScrollY,
		2238,
		2035,
		hGroundMemDC,
		0,
		0,
		2238,
		2035,
		RGB(255, 0, 255));
}

void CStage2::MakeMap()
{
	// 포탈
	CObjMgr::Get_Instance()->Add_Object(OBJ_MAP, CAbstractFactory<CPortal>::Create(2122.f, 1568.f, "Portal_2To1"));
	// 블락
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(1857.f, 1241.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(2222.f, 1547.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(1685.f, 761.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(553.f, 765.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(460.f, 1004.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(367.f, 1248.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(11.f, 1545.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(1771.f, 1007.f, "Block"));
}
