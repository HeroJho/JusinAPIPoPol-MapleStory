#include "stdafx.h"
#include "Stage_Catoon.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
#include "EventMgr.h"


CStage_Catoon::CStage_Catoon()
{

}

CStage_Catoon::~CStage_Catoon()
{
	Release();
}

void CStage_Catoon::Initialize(void)
{
	m_iCount = 0;
	m_fStartTime = 60.f;
	m_fOldStartTime = 0.f;

	m_fChangTime = 2700.f;
	m_fOldChangTime = GetTickCount64();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logo/BossCatoon.bmp", L"BossCatoon");

	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	CSoundMgr::Get_Instance()->StopSound(SOUND_MONE2);
	CSoundMgr::Get_Instance()->PlaySound(L"BossApp.wav", SOUND_MONE2, 1);
}

void CStage_Catoon::Update(void)
{
	if(m_fOldChangTime + m_fChangTime < GetTickCount64())
		CEventMgr::Get_Instance()->AddSceneChangeEvent(SC_STAGE_BOSS);
	

	CObjMgr::Get_Instance()->Update();
}

void CStage_Catoon::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();

	Move_Frame();
}

void CStage_Catoon::Render(HDC hDC)
{
	// 출력 순서
	RenderBackGround(hDC);

	// CObjMgr::Get_Instance()->Render(hDC);
}

void CStage_Catoon::Release(void)
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

void CStage_Catoon::RenderBackGround(HDC hDC)
{
	HDC		hBackMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BossCatoon");

	int iX = m_iCount % 5;
	int iY = m_iCount / 5;
	// 800 450
	GdiTransparentBlt(hDC,
		0,
		0,
		1280,
		720,
		hBackMemDC,
		iX * 800,
		iY * 450,
		800,
		450,
		RGB(255, 0, 255));
}

void CStage_Catoon::Move_Frame(void)
{
	if (m_fOldStartTime + m_fStartTime < GetTickCount64())
	{
		m_iCount++;

		m_fOldStartTime = (DWORD)GetTickCount64();

		if (m_iCount > 33)
		{
			m_iCount = 33;
		}
	}
}