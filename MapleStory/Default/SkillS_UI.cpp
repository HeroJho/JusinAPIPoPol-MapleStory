#include "stdafx.h"
#include "SkillS_UI.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "InvenMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "SkillMgr.h"


CSkillS_UI::CSkillS_UI()
	: m_sInfo{}
{

}

CSkillS_UI::~CSkillS_UI()
{
	Release();
}

void CSkillS_UI::Initialize(void)
{
	m_sTag = "Skill_UI";
	m_sInfo.InvenID = 101;
	m_sInfo.eID = IT_SKILL;

	m_tInfo.fX = 9999.f;
	m_tInfo.fY = 9999.f;

	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 32.f;
	m_tInfo.fTCY = 32.f;


	m_tInfo.fCCX = 32.f;
	m_tInfo.fCCY = 32.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)0.f;

}

int CSkillS_UI::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	return OBJ_NOEVENT;
}
void CSkillS_UI::Late_Update(void)
{

}


void CSkillS_UI::Render(HDC hDC)
{
	Update_Rect();


	LOGFONT m_labelFontInfo{};
	m_labelFontInfo.lfHeight = 12;
	m_labelFontInfo.lfWidth = 5;
	m_labelFontInfo.lfCharSet = HANGEUL_CHARSET;
	HFONT textFont, oldFont;
	textFont = CreateFontIndirect(&m_labelFontInfo);
	oldFont = (HFONT)SelectObject(hDC, textFont);

	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(0, 0, 0));
	TCHAR lpOut[1024];


	HDC		hMemDC = nullptr;

	if (m_sInfo.sTag == "Skill_1")
	{
		if(CSkillMgr::Get_Instance()->GetSkillLevel1() == 0)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Skill1_Cool");
		else
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Skill1_Icon");

		wsprintf(lpOut, TEXT("블레이드 퓨리"));
		TextOut(hDC, m_tTRect.left + 38, m_tTRect.top + 1, lpOut, lstrlen(lpOut));
		wsprintf(lpOut, TEXT("%d / 5"), CSkillMgr::Get_Instance()->GetSkillLevel1());
		TextOut(hDC, m_tTRect.left + 38, m_tTRect.top + 19, lpOut, lstrlen(lpOut));
	}
	else if (m_sInfo.sTag == "Skill_2")
	{
		if (CSkillMgr::Get_Instance()->GetSkillLevel2() == 0)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Skill2_Cool");
		else
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Skill2_Icon");

		wsprintf(lpOut, TEXT("팬텀 블로우"));
		TextOut(hDC, m_tTRect.left + 38, m_tTRect.top + 1, lpOut, lstrlen(lpOut));
		wsprintf(lpOut, TEXT("%d / 5"), CSkillMgr::Get_Instance()->GetSkillLevel2());
		TextOut(hDC, m_tTRect.left + 38, m_tTRect.top + 19, lpOut, lstrlen(lpOut));
	}
	else if (m_sInfo.sTag == "Skill_3")
	{
		if (CSkillMgr::Get_Instance()->GetSkillLevel3() == 0)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Skill3_Cool");
		else
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Skill3_Icon");

		wsprintf(lpOut, TEXT("카르마 퓨리"));
		TextOut(hDC, m_tTRect.left + 38, m_tTRect.top + 1, lpOut, lstrlen(lpOut));
		wsprintf(lpOut, TEXT("%d / 5"), CSkillMgr::Get_Instance()->GetSkillLevel3());
		TextOut(hDC, m_tTRect.left + 38, m_tTRect.top + 19, lpOut, lstrlen(lpOut));
	}
	else if (m_sInfo.sTag == "Skill_4")
	{
		if (CSkillMgr::Get_Instance()->GetSkillLevel4() == 0)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Skill4_Cool");
		else
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Skill4_Icon");

		wsprintf(lpOut, TEXT("블레이드 스톰"));
		TextOut(hDC, m_tTRect.left + 38, m_tTRect.top + 1, lpOut, lstrlen(lpOut));
		wsprintf(lpOut, TEXT("%d / 5"), CSkillMgr::Get_Instance()->GetSkillLevel4());
		TextOut(hDC, m_tTRect.left + 38, m_tTRect.top + 19, lpOut, lstrlen(lpOut));
	}


	SelectObject(hDC, oldFont);
	DeleteObject(textFont);


	if (!hMemDC)
		return;

	GdiTransparentBlt(hDC,
		int(m_tTRect.left),
		int(m_tTRect.top),
		int(m_tInfo.fTCX),
		int(m_tInfo.fTCY),
		hMemDC,
		0,
		0,
		(int)m_tInfo.fTCX,
		(int)m_tInfo.fTCY,
		RGB(255, 0, 255));

}


void CSkillS_UI::OnCollision(CObj* _pOther)
{

}


void CSkillS_UI::ColRender(HDC hDC)
{
	Update_Rect();

	Rectangle(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tRect.right),
		int(m_tRect.bottom));
}

void CSkillS_UI::Release(void)
{

}