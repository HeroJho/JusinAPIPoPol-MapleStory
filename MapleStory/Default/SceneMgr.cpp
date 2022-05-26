#include "stdafx.h"
#include "SceneMgr.h"

#include "ScrollMgr.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Stage4.h"
#include "Stage5.h"
#include "Stage6.h"
#include "Stage7.h"
#include "Stage_Catoon.h"
#include "Stage_Boss.h"
#include "Stage_End.h"
#include "BmpMgr.h"
#include "SoundMgr.h"
#include "EventMgr.h"

CSceneMgr*	CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_eCurScene(SC_END), m_ePreScene(SC_END)
	, m_bScene3First(true)
	, m_iAlpha(255)
	, m_bFade(false)
	, m_bWhiteIn(false)
	, m_fAlphaTime(10.f)
	, m_fOldAlphaTime(0.f)
	, m_pKey(nullptr)
{
	m_fBgmSound = 10;
	m_fEffectSound = 10;
}

CSceneMgr::~CSceneMgr()
{
	Release();
}


void CSceneMgr::Scene_Change(SCENEID eID)
{
	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{
		case SC_LOGO:
			m_pScene = new CLogo;
			break;
		case SC_MENU:
			m_pScene = new CMyMenu;
			break;
		case SC_EDIT:
			break;
		case SC_STAGE_1:
			m_pScene = new CStage1;
			break;
		case SC_STAGE_2:
			m_pScene = new CStage2;
			break;
		case SC_STAGE_3:
			m_pScene = new CStage3;
			break;
		case SC_STAGE_4:
			m_pScene = new CStage4;
			break;
		case SC_STAGE_5:
			m_pScene = new CStage5;
			break;
		case SC_STAGE_6:
			m_pScene = new CStage6;
			break;
		case SC_STAGE_7:
			m_pScene = new CStage7;
			break; 
		case SC_STAGE_COO:
			m_pScene = new CStage_Catoon;
			break;
		case SC_STAGE_BOSS:
			m_pScene = new CStage_Boss;
			break;
		case SC_ENDING:
			m_pScene = new CStage_End;
			break;
		}

	CBmpMgr::Get_Instance()->Release();
	Start_FadeIn();
	 m_pScene->Initialize();
	 m_ePreScene = m_eCurScene;
	}

}

void CSceneMgr::Start_FadeIn()
{
	m_iAlpha = 255;
	m_bFade = true;
	m_bFadeOut = false;
	m_pKey = L"Alpha";
}

void CSceneMgr::Start_FadeOut()
{
	m_iAlpha = 0;
	m_bFade = false;
	m_bFadeOut = true;
	m_pKey = L"Alpha";
}

void CSceneMgr::Start_WhiteIn()
{
	m_iAlpha = 0;
	m_bFade = false;
	m_bFadeOut = false;
	m_bWhiteIn = true;
	m_pKey = L"White";
}

void CSceneMgr::End_WhiteIn()
{
	m_iAlpha = 0;
	m_bFade = false;
	m_bFadeOut = false;
	m_bWhiteIn = false;
}

void CSceneMgr::Update(void)
{
	m_pScene->Update();

	if (m_bFade)
		Fade_Update();
	else if (m_bFadeOut)
		FadeOut_Update();
	else if (m_bWhiteIn)
		WhiteIn_Update();
}

void CSceneMgr::Late_Update(void)
{
	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);

	if (m_bFade || m_bFadeOut || m_bWhiteIn)
	{
		BLENDFUNCTION bf;
		HDC m_hAlpha = CBmpMgr::Get_Instance()->Find_Image(m_pKey);
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = m_iAlpha;
		bf.AlphaFormat = 0;

	
		GdiAlphaBlend(hDC,
			int(0),
			int(0),
			int(1280),
			int(720),
			m_hAlpha,
			0,
			0,
			int(1280),
			int(720),
			bf);
	}

}

void CSceneMgr::Release(void)
{
	Safe_Delete(m_pScene);
}


void CSceneMgr::IncreaseBgmSound()
{
	++m_fBgmSound;
	if (m_fBgmSound > 10)
		m_fBgmSound = 10;

	switch (m_eCurScene)
	{
	case SC_LOGO:
		break;
	case SC_STAGE_1:
		CSoundMgr::Get_Instance()->PlaySound(L"Scene_1.wav", SOUND_BGM, 0.5);
		break;
	case SC_STAGE_2:
		CSoundMgr::Get_Instance()->PlaySound(L"Scene_2.wav", SOUND_BGM, 0.5);
		break;
	case SC_STAGE_3:
	case SC_STAGE_4:
		CSoundMgr::Get_Instance()->PlaySound(L"Scene_3_4.wav", SOUND_BGM, 0.5);
		break;
	case SC_STAGE_5:
	case SC_STAGE_6:
		CSoundMgr::Get_Instance()->PlaySound(L"Scene_5_6.wav", SOUND_BGM, 0.5);
		break;
	case SC_STAGE_7:
		CSoundMgr::Get_Instance()->PlaySound(L"Scene_7.wav", SOUND_BGM, 0.5);
		break;
	case SC_STAGE_BOSS:
		CSoundMgr::Get_Instance()->PlaySound(L"Scene_Boss.wav", SOUND_BGM, 0.5);
		break;
	}
}
void CSceneMgr::DecreaseBgmSound()
{
	--m_fBgmSound;
	if (m_fBgmSound < 0)
		m_fBgmSound = 0;

	switch (m_eCurScene)
	{
	case SC_LOGO:
		break;
	case SC_STAGE_1:
		CSoundMgr::Get_Instance()->PlaySound(L"Scene_1.wav", SOUND_BGM, 0.5);
		break;
	case SC_STAGE_2:
		CSoundMgr::Get_Instance()->PlaySound(L"Scene_2.wav", SOUND_BGM, 0.5);
		break;
	case SC_STAGE_3:
	case SC_STAGE_4:
		CSoundMgr::Get_Instance()->PlaySound(L"Scene_3_4.wav", SOUND_BGM, 0.5);
		break;
	case SC_STAGE_5:
	case SC_STAGE_6:
		CSoundMgr::Get_Instance()->PlaySound(L"Scene_5_6.wav", SOUND_BGM, 0.5);
		break;
	case SC_STAGE_7:
		CSoundMgr::Get_Instance()->PlaySound(L"Scene_7.wav", SOUND_BGM, 0.5);
		break;
	case SC_STAGE_BOSS:
		CSoundMgr::Get_Instance()->PlaySound(L"Scene_Boss.wav", SOUND_BGM, 0.5);
		break;
	}
}
void CSceneMgr::IncreaseEffectSound()
{
	++m_fEffectSound;
	if (m_fEffectSound > 10)
		m_fEffectSound = 10;

	switch (m_eCurScene)
	{
	case SC_LOGO:
		break;
	case SC_STAGE_1:
		CSoundMgr::Get_Instance()->PlaySound(L"Scene_1.wav", SOUND_BGM, 0.5);
		break;
	case SC_STAGE_2:
		CSoundMgr::Get_Instance()->PlaySound(L"Scene_2.wav", SOUND_BGM, 0.5);
		break;
	case SC_STAGE_3:
	case SC_STAGE_4:
		CSoundMgr::Get_Instance()->PlaySound(L"Scene_3_4.wav", SOUND_BGM, 0.5);
		break;
	case SC_STAGE_5:
	case SC_STAGE_6:
		CSoundMgr::Get_Instance()->PlaySound(L"Scene_5_6.wav", SOUND_BGM, 0.5);
		break;
	case SC_STAGE_7:
		CSoundMgr::Get_Instance()->PlaySound(L"Scene_7.wav", SOUND_BGM, 0.5);
		break;
	case SC_STAGE_BOSS:
		CSoundMgr::Get_Instance()->PlaySound(L"Scene_Boss.wav", SOUND_BGM, 0.5);
		break;
	}
}
void CSceneMgr::DecreaseEffectSound()
{
	--m_fEffectSound;
	if (m_fEffectSound < 0)
		m_fEffectSound = 0;

	switch (m_eCurScene)
	{
	case SC_LOGO:
		break;
	case SC_STAGE_1:
		CSoundMgr::Get_Instance()->PlaySound(L"Scene_1.wav", SOUND_BGM, 0.5);
		break;
	case SC_STAGE_2:
		CSoundMgr::Get_Instance()->PlaySound(L"Scene_2.wav", SOUND_BGM, 0.5);
		break;
	case SC_STAGE_3:
	case SC_STAGE_4:
		CSoundMgr::Get_Instance()->PlaySound(L"Scene_3_4.wav", SOUND_BGM, 0.5);
		break;
	case SC_STAGE_5:
	case SC_STAGE_6:
		CSoundMgr::Get_Instance()->PlaySound(L"Scene_5_6.wav", SOUND_BGM, 0.5);
		break;
	case SC_STAGE_7:
		CSoundMgr::Get_Instance()->PlaySound(L"Scene_7.wav", SOUND_BGM, 0.5);
		break;
	case SC_STAGE_BOSS:
		CSoundMgr::Get_Instance()->PlaySound(L"Scene_Boss.wav", SOUND_BGM, 0.5);
		break;
	}
}

void CSceneMgr::Fade_Update()
{
	if (m_fOldAlphaTime + m_fAlphaTime < GetTickCount64())
	{
		m_iAlpha -= 10;

		if (m_iAlpha < 0)
		{
			m_iAlpha = 0;
			m_bFade = false;
		}

		m_fOldAlphaTime = GetTickCount64();
	}
}

void CSceneMgr::FadeOut_Update()
{
	if (m_fOldAlphaTime + m_fAlphaTime < GetTickCount64())
	{
		m_iAlpha += 2;

		if (m_iAlpha > 255)
		{
			m_iAlpha = 255;
			m_bFade = false;
			m_bFadeOut = true; // 깜한 화면 유지
			CEventMgr::Get_Instance()->AddSceneChangeEvent(SC_ENDING);
		}

		m_fOldAlphaTime = GetTickCount64();
	}
}

void CSceneMgr::WhiteIn_Update()
{
	if (m_fOldAlphaTime + m_fAlphaTime < GetTickCount64())
	{
		m_iAlpha += 7;

		if (m_iAlpha > 255)
		{
			m_iAlpha = 255;
			m_bFade = false;
			m_bWhiteIn = true;
		}

		m_fOldAlphaTime = GetTickCount64();
	}
}
