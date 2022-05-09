#include "stdafx.h"
#include "Stage2.h"
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
	// Bmp 로딩
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Scene2/2_Middle.bmp", L"2_Middle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Scene2/2_Back.bmp", L"2_Back");
	CLineMgr::Get_Instance()->Scene_2();

	// Obj 생성
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(2122.f, 1568.f);
	// 포탈
	CObjMgr::Get_Instance()->Add_Object(OBJ_MAP, CAbstractFactory<CPortal>::Create(2122.f, 1568.f, "Portal_2To1"));

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster>::Create(1200.f, 1000.f, "Monster"));

	// 카메라 설정
	CScrollMgr::Get_Instance()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
}

void CStage2::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Update();
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
	// CLineMgr::Get_Instance()->Render(hDC);
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