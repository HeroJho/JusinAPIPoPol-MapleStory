#include "stdafx.h"
#include "Option_UI.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "InvenMgr.h"
#include "QuestMgr.h"
#include "SoundMgr.h"
#include "SceneMgr.h"


COption_UI::COption_UI()
	: m_bIsOpen(false)
{
}

COption_UI::~COption_UI()
{
	Release();
}



void COption_UI::Initialize(void)
{
	m_sTag = "OptionUI";


	m_tInfo.fX = 9999.f;
	m_tInfo.fY = 9999.f;

	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 200.f;
	m_tInfo.fTCY = 199.f;


	m_tInfo.fCCX = 276.f;
	m_tInfo.fCCY = 505.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)-135.f;

	m_bIsOpen = false;

	for (int i = 0; i < 11; ++i)
	{
		m_pSoundButton[i] = new CSoundButton;
		m_pSoundButton[i]->Initialize();
	}
	
	m_pSoundButton[0]->Set_Tag("BgmDownButton");
	m_pSoundButton[0]->SetColBox(15.f, 15.f);
	m_pSoundButton[1]->Set_Tag("BgmUpButton");
	m_pSoundButton[1]->SetColBox(15.f, 15.f);
	m_pSoundButton[2]->Set_Tag("EffectDownButton");
	m_pSoundButton[2]->SetColBox(15.f, 15.f);
	m_pSoundButton[3]->Set_Tag("EffectUpButton");
	m_pSoundButton[3]->SetColBox(15.f, 15.f);

	m_pSoundButton[4]->Set_Tag("DamageEffect_0");
	m_pSoundButton[4]->SetColBox(30.f, 20.f);
	m_pSoundButton[5]->Set_Tag("DamageEffect_1");
	m_pSoundButton[5]->SetColBox(30.f, 20.f);
	m_pSoundButton[6]->Set_Tag("DamageEffect_2");
	m_pSoundButton[6]->SetColBox(30.f, 20.f);

	m_pSoundButton[7]->Set_Tag("DamageSkin_0");
	m_pSoundButton[7]->SetColBox(30.f, 30.f);
	m_pSoundButton[8]->Set_Tag("DamageSkin_1");
	m_pSoundButton[8]->SetColBox(30.f, 30.f);
	m_pSoundButton[9]->Set_Tag("DamageSkin_2");
	m_pSoundButton[9]->SetColBox(30.f, 30.f);
	m_pSoundButton[10]->Set_Tag("DamageSkin_3");
	m_pSoundButton[10]->SetColBox(30.f, 30.f);
}

int COption_UI::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (CKeyMgr::Get_Instance()->Key_Down('O'))
	{
		if (!m_bIsOpen)
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_UI);
			CSoundMgr::Get_Instance()->PlaySound(L"MenuUp.wav", SOUND_UI, 1);

			m_tInfo.fX = 400.f;
			m_tInfo.fY = 300.f;
			m_bIsOpen = true;
		}
		else
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_UI);
			CSoundMgr::Get_Instance()->PlaySound(L"MenuDown.wav", SOUND_UI, 1);

			m_tInfo.fX = 9999.f;
			m_tInfo.fY = 9999.f;
			m_bIsOpen = false;
		}
	}

	Update_Rect();


	m_pSoundButton[0]->Set_Pos(m_tInfo.fX - 16, m_tInfo.fY - 45);
	m_pSoundButton[1]->Set_Pos(m_tInfo.fX + 16, m_tInfo.fY - 45);
	m_pSoundButton[2]->Set_Pos(m_tInfo.fX - 16, m_tInfo.fY - 20);
	m_pSoundButton[3]->Set_Pos(m_tInfo.fX + 16, m_tInfo.fY - 20);

	m_pSoundButton[4]->Set_Pos(m_tInfo.fX - 12, m_tInfo.fY + 10);
	m_pSoundButton[5]->Set_Pos(m_tInfo.fX + 28, m_tInfo.fY + 10);
	m_pSoundButton[6]->Set_Pos(m_tInfo.fX + 68, m_tInfo.fY + 10);

	m_pSoundButton[7]->Set_Pos(m_tInfo.fX - 70, m_tInfo.fY + 63);
	m_pSoundButton[8]->Set_Pos(m_tInfo.fX - 39, m_tInfo.fY + 63);
	m_pSoundButton[9]->Set_Pos(m_tInfo.fX - 7, m_tInfo.fY + 63);
	m_pSoundButton[10]->Set_Pos(m_tInfo.fX + 25, m_tInfo.fY + 63);

	return OBJ_NOEVENT;
}

void COption_UI::Late_Update(void)
{

}

void COption_UI::Render(HDC hDC)
{

	HDC		hMemDCFrame = CBmpMgr::Get_Instance()->Find_Image(L"Option");

	// 프레임
	GdiTransparentBlt(hDC,
		int(m_tTRect.left),
		int(m_tTRect.top),
		int(m_tInfo.fTCX),
		int(m_tInfo.fTCY),
		hMemDCFrame,
		0,
		0,
		(int)m_tInfo.fTCX,
		(int)m_tInfo.fTCY,
		RGB(255, 0, 255));


	LOGFONT m_labelFontInfo{};
	m_labelFontInfo.lfHeight = 18;
	m_labelFontInfo.lfWidth = 8;
	m_labelFontInfo.lfCharSet = HANGEUL_CHARSET;
	m_labelFontInfo.lfWeight = FW_BOLD;
	HFONT textFont, oldFont;
	textFont = CreateFontIndirect(&m_labelFontInfo);
	oldFont = (HFONT)SelectObject(hDC, textFont);

	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(255, 255, 255));
	TCHAR lpOut[1024];

	int iVol = int(CSceneMgr::Get_Instance()->GetBgmSound() * 10);
	wsprintf(lpOut, TEXT("%d"), iVol);
	if (iVol == 10)
	{
		TextOut(hDC, m_tTRect.left + 88, m_tTRect.top + 45, lpOut, lstrlen(lpOut));
		TextOut(hDC, m_tTRect.left + 88 + 1, m_tTRect.top + 45 + 1, lpOut, lstrlen(lpOut));
	}
	else
	{
		TextOut(hDC, m_tTRect.left + 93, m_tTRect.top + 45, lpOut, lstrlen(lpOut));
		TextOut(hDC, m_tTRect.left + 93 + 1, m_tTRect.top + 45 + 1, lpOut, lstrlen(lpOut));
	}

	iVol = int(CSceneMgr::Get_Instance()->GetEffectSound() * 10);
	wsprintf(lpOut, TEXT("%d"), iVol);
	if (iVol == 10)
	{
		TextOut(hDC, m_tTRect.left + 88, m_tTRect.top + 72, lpOut, lstrlen(lpOut));
		TextOut(hDC, m_tTRect.left + 88 + 1, m_tTRect.top + 72 + 1, lpOut, lstrlen(lpOut));
	}
	else
	{
		TextOut(hDC, m_tTRect.left + 93, m_tTRect.top + 72, lpOut, lstrlen(lpOut));
		TextOut(hDC, m_tTRect.left + 93 + 1, m_tTRect.top + 72 + 1, lpOut, lstrlen(lpOut));
	}
		

	SelectObject(hDC, oldFont);
	DeleteObject(textFont);


	for (int i = 0; i < 11; ++i)
	{
		m_pSoundButton[i]->Render(hDC);
		// m_pSoundButton[i]->ColRender(hDC);
	}

}


void COption_UI::ColRender(HDC hDC)
{
	Rectangle(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tRect.right),
		int(m_tRect.bottom));
}

void COption_UI::Release(void)
{
	for(int i = 0; i < 11; ++i)
		Safe_Delete(m_pSoundButton[i]);
}