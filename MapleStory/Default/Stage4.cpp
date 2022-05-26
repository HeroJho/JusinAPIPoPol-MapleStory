#include "stdafx.h"
#include "Stage4.h"

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

CStage4::CStage4()
{
	m_tMapSize.left = 0.f;
	m_tMapSize.top = 0.f;
	m_tMapSize.right = 2790.f;
	m_tMapSize.bottom = 1200.f - 50.f;
}

CStage4::~CStage4()
{
	Release();
}

void CStage4::Initialize(void)
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

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/DeleteDarPeng/DeleteDarPengL.bmp", L"DeleteDarPengL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/DeleteDarPeng/DeleteDarPengR.bmp", L"DeleteDarPengR");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/DeletePig/DeletePigL.bmp", L"DeletePigL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/DeletePig/DeletePigR.bmp", L"DeletePigR");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/MesoBig.bmp", L"MesoBig");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Meso.bmp", L"Meso");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/RedPotion.bmp", L"RedPotion");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/BluePotion.bmp", L"BluePotion");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Equip.bmp", L"Equip");


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Scene4/4_Middle.bmp", L"4_Middle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Scene4/4_Back.bmp", L"4_Back");
	CLineMgr::Get_Instance()->Scene_4();	// 1. 맵 라인
	CSpawnMgr::Get_Instance()->Scene_4();   // 2. 맵 스폰
	MakeMap();								// 3. 맵 블락, 포탈

	// Player 생성
	if (!CObjMgr::Get_Instance()->Get_Player())
	{
		CObj* pPlayer = CAbstractFactory<CPlayer>::Create(1087.f, 781.f, "Player");
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pPlayer);
		CObjMgr::Get_Instance()->Set_Player(pPlayer);
	}
	else
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(1087.f, 781.f);

	// UI
	CUIMgr::Get_Instance()->Initialize();

	// 카메라 설정
	CScrollMgr::Get_Instance()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	CScrollMgr::Get_Instance()->Initialize();

	//CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	//CSoundMgr::Get_Instance()->PlaySound(L"Scene_3_4.wav", SOUND_BGM, 0.5);

}

void CStage4::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Update();
	CSpawnMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();
}

void CStage4::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage4::Render(HDC hDC)
{
	// 출력 순서
	RenderBackGround(hDC);

	CObjMgr::Get_Instance()->Render(hDC);
	CUIMgr::Get_Instance()->Render(hDC);
	// CLineMgr::Get_Instance()->Render(hDC);
}

void CStage4::Release(void)
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

void CStage4::RenderBackGround(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hBackMemDC = CBmpMgr::Get_Instance()->Find_Image(L"4_Back");
	GdiTransparentBlt(hDC,
		(iScrollX / 2),
		(iScrollY / 2) - 250.f,
		2790,
		1200,
		hBackMemDC,
		0,
		0,
		2790,
		1200,
		RGB(255, 0, 255));

	HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"4_Middle");
	GdiTransparentBlt(hDC,
		iScrollX,
		iScrollY,
		2790,
		1200,
		hGroundMemDC,
		0,
		0,
		2790,
		1200,
		RGB(255, 0, 255));
}

void CStage4::MakeMap()
{
	//// 포탈
	CObjMgr::Get_Instance()->Add_Object(OBJ_MAP, CAbstractFactory<CPortal>::Create(1087.f, 790.f, "Portal_4To3"));
	// 블락
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(0.f, 801.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(535.f, 790.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(21.f, 361.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(604.f, 356.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(651.f, 421.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(1417.f, 420.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(537.f, 861.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(811.f, 920.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(898.f, 982.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(2406.f, 588.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(1821.f, 592.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(2362.f, 352.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(2766.f, 354.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(1644.f, 234.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(2322.f, 232.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(2790.f, 984.f, "Block"));


	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCKME, CAbstractFactory<CBlockBox>::Create(537.f, 861.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCKME, CAbstractFactory<CBlockBox>::Create(811.f, 920.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCKME, CAbstractFactory<CBlockBox>::Create(898.f, 982.f, "Block"));
}
