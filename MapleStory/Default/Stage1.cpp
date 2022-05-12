#include "stdafx.h"
#include "Stage1.h"
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
	// 2스테 갓다가 보방가면 요게 제대로 작동이 안되는것 같음.
	// 이상한건 Stage2의 스폰매니저 업데이트 주석해도 잘 됨.
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/DarkedMage/DarkedMage.bmp", L"DarkedMage");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/DarkedMage/Skill_1/Skill_1.bmp", L"Skill_1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/DarkedMage/Skill_2/Skill_2.bmp", L"Skill_2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/DarkedMage/Skill_4/Skill_4.bmp", L"Skill_4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/MesoBig.bmp", L"MesoBig");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Meso.bmp", L"Meso");


	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CMoney>::Create(600, 400, "Item"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CMoneyBig>::Create(650, 400, "Item"));

	// Bmp 로딩
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Scene1/1_Middle.bmp", L"1_Middle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Scene1/1_Back.bmp", L"1_Back");
	CLineMgr::Get_Instance()->Scene_1();

	// Player 생성
	if (!CObjMgr::Get_Instance()->Get_Player())
	{
		CObj* pPlayer = CAbstractFactory<CPlayer>::Create(390.f, 930.f, "Player");
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pPlayer);
		CObjMgr::Get_Instance()->Set_Player(pPlayer);
	}
	else
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(390.f, 930.f);
	

	// UI
	CUIMgr::Get_Instance()->Initialize();

	// 마우스
	CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CMouse>::Create(390.f, 930.f, "Mouse"));

	// 포탈
	CObjMgr::Get_Instance()->Add_Object(OBJ_MAP, CAbstractFactory<CPortal>::Create(390.f, 930.f, "Portal_1To2"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MAP, CAbstractFactory<CPortal>::Create(537.f, 928.f, "Portal_1ToBoss"));

	// 카메라 설정
	CScrollMgr::Get_Instance()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	CScrollMgr::Get_Instance()->Initialize();
}

void CStage1::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();
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
	// CLineMgr::Get_Instance()->Render(hDC);
	CUIMgr::Get_Instance()->Render(hDC);
}

void CStage1::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_MONSTER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_NPC);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_MAP);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BLOCK);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_SKILL);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_MONSKILL);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_ITEM);
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