#include "stdafx.h"
#include "Stage7.h"
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
#include "Chang.h"
#include "SoundMgr.h"
#include "BossPotal.h"

CStage7::CStage7()
{
	m_tMapSize.left = 0.f;
	m_tMapSize.top = 0.f;
	m_tMapSize.right = 1823.f;
	m_tMapSize.bottom = 777.f - 50.f;
}

CStage7::~CStage7()
{
	Release();
}

void CStage7::Initialize(void)
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_NPC);
	CSoundMgr::Get_Instance()->PlaySound(L"DarkTalk_3.wav", SOUND_NPC, 1);

	CSpawnMgr::Get_Instance()->Initialize();

	// TEST
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerL.bmp", L"PlayerL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerR.bmp", L"PlayerR");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerPainL.bmp", L"PlayerPainL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerPainR.bmp", L"PlayerPainR");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerPainPL.bmp", L"PlayerPainPL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerPainPR.bmp", L"PlayerPainPR");


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Scene1/1_Middle.bmp", L"1_Middle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Scene1/1_Back.bmp", L"1_Back");


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/MesoBig.bmp", L"MesoBig");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Meso.bmp", L"Meso");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/RedPotion.bmp", L"RedPotion");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/BluePotion.bmp", L"BluePotion");


	// Bmp 로딩
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Scene7/7_Middle.bmp", L"7_Middle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Scene7/7_Back.bmp", L"7_Back");
	CLineMgr::Get_Instance()->Scene_7();	// 1. 맵 라인
	MakeMap();								// 3. 맵 블락, 포탈

	// Player 생성
	if (!CObjMgr::Get_Instance()->Get_Player())
	{
		CObj* pPlayer = CAbstractFactory<CPlayer>::Create(500.f, 500.f, "Player");
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pPlayer);
		CObjMgr::Get_Instance()->Set_Player(pPlayer);
	}
	else
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(203.f, 585.f);


	// UI
	CUIMgr::Get_Instance()->Initialize();

	// 카메라 설정
	CScrollMgr::Get_Instance()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	CScrollMgr::Get_Instance()->Initialize();

	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	CSoundMgr::Get_Instance()->PlaySound(L"Scene_7.wav", SOUND_BGM, 0.4);
}

void CStage7::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Update();
	CSpawnMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();
}

void CStage7::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage7::Render(HDC hDC)
{
	// 출력 순서
	RenderBackGround(hDC);

	CObjMgr::Get_Instance()->Render(hDC);
	CUIMgr::Get_Instance()->Render(hDC);
	// CLineMgr::Get_Instance()->Render(hDC);
}

void CStage7::Release(void)
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

void CStage7::RenderBackGround(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hBackMemDC = CBmpMgr::Get_Instance()->Find_Image(L"7_Back");
	GdiTransparentBlt(hDC,
		(iScrollX / 2) + 100.f,
		(iScrollY / 2) ,
		1823,
		777,
		hBackMemDC,
		0,
		0,
		1823,
		777,
		RGB(255, 0, 255));

	HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"7_Middle");
	GdiTransparentBlt(hDC,
		iScrollX,
		iScrollY,
		1823,
		777,
		hGroundMemDC,
		0,
		0,
		1823,
		777,
		RGB(255, 0, 255));
}

void CStage7::MakeMap()
{
	//// 포탈
	CObjMgr::Get_Instance()->Add_Object(OBJ_MAP, CAbstractFactory<CPortal>::Create(203.f, 585.f, "Portal_7To6"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MAP, CAbstractFactory<CBossPotal>::Create(1496.f, 585.f, "Portal_7ToBoss"));

}