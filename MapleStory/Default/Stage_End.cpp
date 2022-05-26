#include "stdafx.h"
#include "Stage_End.h"
#include "AbstractFactory.h"

#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
#include "EventMgr.h"
#include "Dance.h"
#include "Dance2.h"
#include "Clear.h"


CStage_End::CStage_End()
{

}

CStage_End::~CStage_End()
{
	Release();
}

void CStage_End::Initialize(void)
{
	m_iCount = 0;
	m_fStartTime = 300.f;
	m_fOldStartTime = GetTickCount64();

	m_fChangTime = 3000.f;
	m_fOldChangTime = GetTickCount64();

	m_fWhiteTime = 8000.f;
	m_fOldWhiteTime = GetTickCount64();
	m_bWhite = false;

	m_fWhiteEndTime = 10000.f;
	m_fOldWhiteEndTime = GetTickCount64();
	m_bWhiteEnd = false;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/White.bmp", L"White");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logo/EggBreak.bmp", L"EggBreak");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Dance2L.bmp", L"Dance2L");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Dance2R.bmp", L"Dance2R");

	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);


	m_bEggEnd1 = false;
	m_bEggEnd2 = false;
	m_bEggEnd3 = false;
	m_bEggEnd4 = false;
	m_fEggTime1 = 3000.f;
	m_fEggTime2 = 4500.f;
	m_fEggTime3 = 6000.f;
	m_fEggTime4 = 7000.f;

	m_fOldEggTime = GetTickCount64();
}

void CStage_End::Update(void)
{
	CObjMgr::Get_Instance()->Update();

	if (!m_bWhite && m_fOldWhiteTime + m_fWhiteTime < GetTickCount64())
	{
		CSceneMgr::Get_Instance()->Start_WhiteIn();
		m_bWhite = true;
	}

	if (!m_bWhiteEnd && m_fOldWhiteEndTime + m_fWhiteEndTime < GetTickCount64())
	{
		CSceneMgr::Get_Instance()->End_WhiteIn();
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CDance>::Create(650.f, 400.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CDance2>::Create(650.f, 400.f, DIR_LEFT));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CDance2>::Create(650.f, 400.f, DIR_RIGHT));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CClear>::Create(690.f, 200.f));

		CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
		CSoundMgr::Get_Instance()->PlaySound(L"EndSound.wav", SOUND_BGM, 1);
		m_bWhiteEnd = true;
	}


	if (!m_bEggEnd1 && m_fOldEggTime + m_fEggTime1 < GetTickCount64())
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT2);
		CSoundMgr::Get_Instance()->PlaySound(L"Cresh.wav", SOUND_PEFFECT2, 1);
		m_bEggEnd1 = true;
	}
	else if (!m_bEggEnd2 && m_fOldEggTime + m_fEggTime2 < GetTickCount64())
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT2);
		CSoundMgr::Get_Instance()->PlaySound(L"Cresh.wav", SOUND_PEFFECT2, 1);
		m_bEggEnd2 = true;
	}
	else if (!m_bEggEnd3 && m_fOldEggTime + m_fEggTime3 < GetTickCount64())
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT2);
		CSoundMgr::Get_Instance()->PlaySound(L"Cresh.wav", SOUND_PEFFECT2, 1);
		m_bEggEnd3 = true;
	}
	else if (!m_bEggEnd4 && m_fOldEggTime + m_fEggTime4 < GetTickCount64())
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT2);
		CSoundMgr::Get_Instance()->PlaySound(L"Cresh.wav", SOUND_PEFFECT2, 1);
		m_bEggEnd4 = true;
	}


}

void CStage_End::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();

	if (m_fOldChangTime + m_fChangTime < GetTickCount64())
	{
		Move_Frame();
	}
}

void CStage_End::Render(HDC hDC)
{
	// 출력 순서
	if (m_fOldChangTime + m_fChangTime < GetTickCount64())
	{
		RenderBackGround(hDC);
	}

	CObjMgr::Get_Instance()->Render(hDC);
}

void CStage_End::Release(void)
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

void CStage_End::RenderBackGround(HDC hDC)
{
	HDC		hBackMemDC = nullptr;

	if (!m_bWhiteEnd)
	{
		hBackMemDC = CBmpMgr::Get_Instance()->Find_Image(L"EggBreak");

		// 800 450
		GdiTransparentBlt(hDC,
			0,
			0,
			1280,
			720,
			hBackMemDC,
			m_iCount * 1024,
			0,
			1024,
			768,
			RGB(255, 0, 255));
	}
	else
	{
		hBackMemDC = CBmpMgr::Get_Instance()->Find_Image(L"White");

		// 800 450
		GdiTransparentBlt(hDC,
			0,
			0,
			1280,
			720,
			hBackMemDC,
			0,
			0,
			1280,
			720,
			RGB(255, 0, 255));
	}

}

void CStage_End::Move_Frame(void)
{
	if (m_fOldStartTime + m_fStartTime < GetTickCount64())
	{
		m_iCount++;

		m_fOldStartTime = (DWORD)GetTickCount64();

		if (m_iCount > 16)
		{
			m_iCount = 16;
		}
	}
}