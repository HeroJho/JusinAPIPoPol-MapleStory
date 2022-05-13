#include "stdafx.h"
#include "Stage_Boss.h"
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
#include "DarkedMage.h"

#include "SpawnMgr.h"

CStage_Boss::CStage_Boss()
{
	m_tMapSize.left = 0.f;
	m_tMapSize.top = 0.f;
	m_tMapSize.right = 1980.f;
	m_tMapSize.bottom = 800.f;
}

CStage_Boss::~CStage_Boss()
{
	Release();
}

void CStage_Boss::Initialize(void)
{
	// Bmp 로딩
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/SceneBoss/Boss_Back.bmp", L"Boss_Back");
	CLineMgr::Get_Instance()->Scene_Boss();
	CSpawnMgr::Get_Instance()->Initialize();


	// Player 생성
	if (!CObjMgr::Get_Instance()->Get_Player())
	{
		CObj* pPlayer = CAbstractFactory<CPlayer>::Create(1000.f, 500.f, "Player");
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pPlayer);
		CObjMgr::Get_Instance()->Set_Player(pPlayer);
	}
	else
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(1000.f, 500.f);


	CObj* pBoss = CAbstractFactory<CDarkedMage>::Create(996, 383, "Monster");
	pBoss->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pBoss);


	CObjMgr::Get_Instance()->Add_Object(OBJ_MAP, CAbstractFactory<CPortal>::Create(177.f, 685.f, "Portal_BossTo1"));


	// 카메라 설정
	CScrollMgr::Get_Instance()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	CScrollMgr::Get_Instance()->Initialize();
}

void CStage_Boss::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Update();
}

void CStage_Boss::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage_Boss::Render(HDC hDC)
{
	// 출력 순서
	RenderBackGround(hDC);

	CObjMgr::Get_Instance()->Render(hDC);
	CLineMgr::Get_Instance()->Render(hDC);
}

void CStage_Boss::Release(void)
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

void CStage_Boss::RenderBackGround(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Boss_Back");
	GdiTransparentBlt(hDC,
		iScrollX,
		iScrollY,
		1980,
		800,
		hGroundMemDC,
		0,
		0,
		1980,
		800,
		RGB(255, 0, 255));
}