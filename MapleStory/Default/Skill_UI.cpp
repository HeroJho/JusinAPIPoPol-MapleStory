#include "stdafx.h"
#include "Skill_UI.h"

#include "BmpMgr.h"
#include "KeyMgr.h"
#include "InvenMgr.h"
#include "SoundMgr.h"
#include "StatMgr.h"


CSkill_UI::CSkill_UI()
	: m_bIsOpen(false)
{
}


CSkill_UI::~CSkill_UI()
{
	Release();
}

void CSkill_UI::Initialize(void)
{
	m_sTag = "SkillUI";

	m_fRePosX = 200.f;
	m_fRePosY = 300.f;


	m_tInfo.fX = 9999.f;
	m_tInfo.fY = 9999.f;

	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 174.f;
	m_tInfo.fTCY = 300.f;


	m_tInfo.fCCX = 172.f;
	m_tInfo.fCCY = 40.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)-135.f;

	m_bIsOpen = false;


	for (int i = 0; i < 4; ++i)
	{
		m_aSkillUIList[i] = new CSkillS_UI;
		m_aSkillUIList[i]->Initialize();
		m_aSkillUIList[i]->SetIndex(i);


		m_aSkillUIList[i]->Set_Pos(m_tInfo.fX - 59, m_tInfo.fY - 37 + (i * 40));
	}
	m_aSkillUIList[0]->GetInfo().sTag = "Skill_1";
	m_aSkillUIList[1]->GetInfo().sTag = "Skill_2";
	m_aSkillUIList[2]->GetInfo().sTag = "Skill_3";
	m_aSkillUIList[3]->GetInfo().sTag = "Skill_4";


	for (int i = 0; i < 4; ++i)
	{
		m_aSkillButtonUIList[i] = new CSkillSButton_UI;
		m_aSkillButtonUIList[i]->Initialize();
		m_aSkillButtonUIList[i]->SetIndex(i);

		m_aSkillButtonUIList[i]->Set_Pos(m_tInfo.fX + 87, m_tInfo.fY + 55 + (i * 18));
	}
}

int CSkill_UI::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (CKeyMgr::Get_Instance()->Key_Down('K'))
	{
		if (!m_bIsOpen)
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_UI);
			CSoundMgr::Get_Instance()->PlaySound(L"MenuUp.wav", SOUND_UI, 1);

			m_tInfo.fX = m_fRePosX;
			m_tInfo.fY = m_fRePosY;

			m_bIsOpen = true;
		}
		else
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_UI);
			CSoundMgr::Get_Instance()->PlaySound(L"MenuDown.wav", SOUND_UI, 1);

			m_fRePosX = m_tInfo.fX;
			m_fRePosY = m_tInfo.fY;

			m_tInfo.fX = 9999.f;
			m_tInfo.fY = 9999.f;
			m_bIsOpen = false;
		}
	}


	// 인벤

	for (int i = 0; i < 4; ++i)
	{
		m_aSkillUIList[i]->Set_Pos(m_tInfo.fX - 59, m_tInfo.fY - 37 + (i * 40));
	}

	for (int i = 0; i < 4; ++i)
	{
		m_aSkillButtonUIList[i]->Set_Pos(m_tInfo.fX + 55, m_tInfo.fY - 29 + (i * 40));
		m_aSkillButtonUIList[i]->Update();
	}


	Update_Rect();

	return OBJ_NOEVENT;
}

void CSkill_UI::Late_Update(void)
{

}

void CSkill_UI::Render(HDC hDC)
{

	HDC		hMemDCFrame = CBmpMgr::Get_Instance()->Find_Image(L"SkillInven");
	HDC		hMemDCCoFrame = CBmpMgr::Get_Instance()->Find_Image(L"Skill_content");

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
		RGB(0, 255, 0));

	GdiTransparentBlt(hDC,
		int(m_tTRect.left) + 10,
		int(m_tTRect.top) + 95,
		140,
		155,
		hMemDCCoFrame,
		0,
		0,
		140,
		155,
		RGB(0, 255, 0));


	for (int i = 0; i < 4; ++i)
	{
		m_aSkillUIList[i]->Render(hDC);
		//m_aItemUIList[i]->ColRender(hDC);
	}

	for (int i = 0; i < 4; ++i)
	{
		m_aSkillButtonUIList[i]->Render(hDC);
	}


	LOGFONT m_labelFontInfo{};
	m_labelFontInfo.lfHeight = 13;
	m_labelFontInfo.lfWidth = 6;
	m_labelFontInfo.lfCharSet = HANGEUL_CHARSET;
	HFONT textFont, oldFont;
	textFont = CreateFontIndirect(&m_labelFontInfo);
	oldFont = (HFONT)SelectObject(hDC, textFont);

	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(0, 0, 0));

	TCHAR lpOut[1024];
	wsprintf(lpOut, TEXT("%d"), CStatMgr::Get_Instance()->GetSkillPoint());
	TextOut(hDC, m_tTRect.left + 145, m_tTRect.top + 256, lpOut, lstrlen(lpOut));

	SelectObject(hDC, oldFont);
	DeleteObject(textFont);
}

void CSkill_UI::ColRender(HDC hDC)
{
	Rectangle(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tRect.right),
		int(m_tRect.bottom));
}

void CSkill_UI::Release(void)
{
	for (int i = 0; i < 4; ++i)
		Safe_Delete(m_aSkillUIList[i]);
	for (int i = 0; i < 4; ++i)
		Safe_Delete(m_aSkillButtonUIList[i]);
}