#include "stdafx.h"
#include "Stage5.h"
#include "AbstractFactory.h"

#include "SceneMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "ScrollMgr.h"
#include "SpawnMgr.h"
#include "UIMgr.h"

#include "Player.h"
#include "Monster.h"
#include "Portal.h"
#include "BlockBox.h"
#include "Mouse.h"
#include "SoundMgr.h"

CStage5::CStage5()
{
	m_tMapSize.left = 0.f;
	m_tMapSize.top = 0.f;
	m_tMapSize.right = 1420.f;
	m_tMapSize.bottom = 1220.f - 50.f;
}

CStage5::~CStage5()
{
	Release();
}

void CStage5::Initialize(void)
{
	CSpawnMgr::Get_Instance()->Initialize();

	// Bmp 로딩
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerL.bmp", L"PlayerL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerR.bmp", L"PlayerR");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerPainL.bmp", L"PlayerPainL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerPainR.bmp", L"PlayerPainR");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerPainPL.bmp", L"PlayerPainPL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerPainPR.bmp", L"PlayerPainPR");


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Scene5/5_Middle.bmp", L"5_Middle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Scene5/5_Back.bmp", L"5_Back");


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/MesoBig.bmp", L"MesoBig");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Meso.bmp", L"Meso");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/RedPotion.bmp", L"RedPotion");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/BluePotion.bmp", L"BluePotion");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Equip.bmp", L"Equip");


	CLineMgr::Get_Instance()->Scene_5();	// 1. 맵 라인
	CSpawnMgr::Get_Instance()->Scene_5();   // 2. 맵 스폰
	MakeMap();								// 3. 맵 블락, 포탈

	// Player 생성
	if (!CObjMgr::Get_Instance()->Get_Player())
	{
		CObj* pPlayer = CAbstractFactory<CPlayer>::Create(1087.f, 781.f, "Player");
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pPlayer);
		CObjMgr::Get_Instance()->Set_Player(pPlayer);
	}
	else
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(70.f, 1029.f);

	// UI
	CUIMgr::Get_Instance()->Initialize();

	// 카메라 설정
	CScrollMgr::Get_Instance()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	CScrollMgr::Get_Instance()->Initialize();

	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	CSoundMgr::Get_Instance()->PlaySound(L"Scene_5_6.wav", SOUND_BGM, 0.5);
}

void CStage5::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Update();
	CSpawnMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();
}

void CStage5::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage5::Render(HDC hDC)
{
	// 출력 순서
	RenderBackGround(hDC);

	CObjMgr::Get_Instance()->Render(hDC);
	CUIMgr::Get_Instance()->Render(hDC);
	// CLineMgr::Get_Instance()->Render(hDC);
}

void CStage5::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_MONSTER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_NPC);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_MAP);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BLOCK);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BLOCKME);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_SKILL);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_MONSKILL);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_ITEM);
}

void CStage5::RenderBackGround(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hBackMemDC = CBmpMgr::Get_Instance()->Find_Image(L"5_Back");
	GdiTransparentBlt(hDC,
		(iScrollX / 2),
		(iScrollY / 2) - 100.f,
		1420,
		1220,
		hBackMemDC,
		0,
		0,
		1420,
		1220,
		RGB(255, 0, 255));

	HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"5_Middle");
	GdiTransparentBlt(hDC,
		iScrollX,
		iScrollY,
		1420,
		1220,
		hGroundMemDC,
		0,
		0,
		1420,
		1220,
		RGB(255, 0, 255));
}

void CStage5::MakeMap()
{
	//// 포탈
	CObjMgr::Get_Instance()->Add_Object(OBJ_MAP, CAbstractFactory<CPortal>::Create(70.f, 1029.f, "Portal_5To3"));

	// 블락
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(-5.f, 1035.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(1430.f, 1035.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(857.f, 735.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(1431.f, 735.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(-5.f, 744.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(719.f, 744.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(854.f, 496.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(1429.f, 496.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(-5.f, 435.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(834.f, 435.f, "Block"));
}