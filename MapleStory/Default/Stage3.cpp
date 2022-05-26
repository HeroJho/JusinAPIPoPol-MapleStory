#include "stdafx.h"
#include "Stage3.h"
#include "AbstractFactory.h"

#include "SceneMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "ScrollMgr.h"
#include "SpawnMgr.h"
#include "UIMgr.h"

#include "Mouse.h"
#include "Player.h"
#include "Monster.h"
#include "Portal.h"
#include "DarkedMage.h"
#include "HpHp_UI.h"

#include "Money.h"
#include "MoneyBig.h"
#include "RedPosion.h"
#include "BluePosion.h"
#include "Npc.h"
#include "Maya.h"
#include "BlockBox.h"
#include "CutMgr.h"
#include "SoundMgr.h"

CStage3::CStage3()
{
	m_tMapSize.left = (LONG)0.f;
	m_tMapSize.top = (LONG)0.f;
	m_tMapSize.right = (LONG)3548.f;
	m_tMapSize.bottom = (LONG)1166.f - 250.f;
}

CStage3::~CStage3()
{
	Release();
}

void CStage3::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerL.bmp", L"PlayerL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerR.bmp", L"PlayerR");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerPainL.bmp", L"PlayerPainL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerPainR.bmp", L"PlayerPainR");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerPainPL.bmp", L"PlayerPainPL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerPainPR.bmp", L"PlayerPainPR");


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Scene3/3_Middle.bmp", L"3_Middle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Scene3/3_Back.bmp", L"3_Back");


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/MesoBig.bmp", L"MesoBig");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Meso.bmp", L"Meso");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/RedPotion.bmp", L"RedPotion");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/BluePotion.bmp", L"BluePotion");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Equip.bmp", L"Equip");



	CLineMgr::Get_Instance()->Scene_3();

	MakeMap();

	// 카메라 설정
	CScrollMgr::Get_Instance()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	CScrollMgr::Get_Instance()->Initialize();

	if (CSceneMgr::Get_Instance()->Get_Scene3First())
	{
		CUIMgr::Get_Instance()->DomiOpen();
		CSceneMgr::Get_Instance()->Set_Scene3First();
	}


	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	CSoundMgr::Get_Instance()->PlaySound(L"Scene_3_4.wav", SOUND_BGM, 0.5);

	CUIMgr::Get_Instance()->Initialize();
}

void CStage3::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();
}

void CStage3::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage3::Render(HDC hDC)
{
	// 출력 순서
	RenderBackGround(hDC);

	CObjMgr::Get_Instance()->Render(hDC);
	// CLineMgr::Get_Instance()->Render(hDC);
	CUIMgr::Get_Instance()->Render(hDC);
}

void CStage3::Release(void)
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

void CStage3::RenderBackGround(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hBackMemDC = CBmpMgr::Get_Instance()->Find_Image(L"3_Back");
	GdiTransparentBlt(hDC,
		(iScrollX / 2),
		(iScrollY / 2),
		3548,
		1166,
		hBackMemDC,
		0,
		0,
		3548,
		1166,
		RGB(255, 0, 255));

	HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"3_Middle");
	GdiTransparentBlt(hDC,
		iScrollX,
		iScrollY,
		3548,
		1166,
		hGroundMemDC,
		0,
		0,
		3548,
		1166,
		RGB(255, 0, 255));
}

void CStage3::MakeMap()
{
	// Player 생성
	if (!CObjMgr::Get_Instance()->Get_Player())
	{
		CObj* pPlayer = CAbstractFactory<CPlayer>::Create(390.f, 100.f, "Player");
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pPlayer);
		CObjMgr::Get_Instance()->Set_Player(pPlayer);
	}
	else
	{
		if (CSceneMgr::Get_Instance()->Get_Scene3First())
			CObjMgr::Get_Instance()->Get_Player()->Set_Pos(1273.f, 419.f);
		else
			CObjMgr::Get_Instance()->Get_Player()->Set_Pos(1830.f, 425.f);
	}



	// 블락
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(1039, 401.f, "Block"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockBox>::Create(1628, 401.f, "Block"));

	// NPC
	CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CNpc>::Create(1365.f, 426.f, "Jang"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CMaya>::Create(2013.f, 753.f, "Maya"));

	//CUIMgr::Get_Instance()->Initialize();

	// 포탈
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MAP, CAbstractFactory<CPortal>::Create(390.f, 930.f, "Portal_1To2"));
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MAP, CAbstractFactory<CPortal>::Create(537.f, 928.f, "Portal_1ToBoss"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MAP, CAbstractFactory<CPortal>::Create(1830.f, 425.f, "Portal_3To4"));

}
