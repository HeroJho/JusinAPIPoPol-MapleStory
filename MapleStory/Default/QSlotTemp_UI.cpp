#include "stdafx.h"
#include "QSlotTemp_UI.h"

#include "BmpMgr.h"
#include "KeyMgr.h"
#include "InvenMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "Mouse.h"
#include "SkillMgr.h"


CQSlotTemp_UI::CQSlotTemp_UI()
	: m_sInfo{}
	, m_iIndex(0)
{

}

CQSlotTemp_UI::~CQSlotTemp_UI()
{
	Release();
}

void CQSlotTemp_UI::Initialize(void)
{
	m_sTag = "Slot_UI";
	m_sInfo.InvenID = 100;


	m_tInfo.fX = 9999.f;
	m_tInfo.fY = 9999.f;

	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 30.f;
	m_tInfo.fTCY = 30.f;


	m_tInfo.fCCX = 30.f;
	m_tInfo.fCCY = 30.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)0.f;

}

int CQSlotTemp_UI::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;



	return OBJ_NOEVENT;
}

void CQSlotTemp_UI::Late_Update(void)
{

}

void CQSlotTemp_UI::Render(HDC hDC)
{
	Update_Rect();

	if (m_sInfo.InvenID == 100)
		return;

	HDC		hMemDC = nullptr;
	HDC		hMemCoolDC = nullptr;
	if (m_sInfo.sTag == "RedPosion")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"RedPotion");
		m_tInfo.fTCX = 30.f;
		m_tInfo.fTCY = 30.f;
	}
	else if (m_sInfo.sTag == "BluePosion")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BluePotion");
		m_tInfo.fTCX = 30.f;
		m_tInfo.fTCY = 30.f;
	}
	else if (m_sInfo.sTag == "Skill_1")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Skill1_Cool");
		hMemCoolDC = CBmpMgr::Get_Instance()->Find_Image(L"Skill1_Icon");
		m_tInfo.fTCX = 32.f;
		m_tInfo.fTCY = 32.f;
	}
	else if (m_sInfo.sTag == "Skill_2")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Skill2_Cool");
		hMemCoolDC = CBmpMgr::Get_Instance()->Find_Image(L"Skill2_Icon");
		m_tInfo.fTCX = 32.f;
		m_tInfo.fTCY = 32.f;
	}
	else if (m_sInfo.sTag == "Skill_3")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Skill3_Cool");
		hMemCoolDC = CBmpMgr::Get_Instance()->Find_Image(L"Skill3_Icon");
		m_tInfo.fTCX = 32.f;
		m_tInfo.fTCY = 32.f;
	}
	else if (m_sInfo.sTag == "Skill_4")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Skill4_Cool");
		hMemCoolDC = CBmpMgr::Get_Instance()->Find_Image(L"Skill4_Icon");
		m_tInfo.fTCX = 32.f;
		m_tInfo.fTCY = 32.f;
	}



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


	if (m_sInfo.eID == IT_CONSUM)
	{
		LOGFONT m_labelFontInfo{};
		m_labelFontInfo.lfHeight = 14;
		m_labelFontInfo.lfWidth = 7;
		m_labelFontInfo.lfCharSet = TURKISH_CHARSET;
		HFONT textFont, oldFont;
		textFont = CreateFontIndirect(&m_labelFontInfo);
		oldFont = (HFONT)SelectObject(hDC, textFont);

		SetBkMode(hDC, TRANSPARENT);
		TCHAR lpOut[1024];
		SetTextColor(hDC, RGB(0, 0, 0));
		wsprintf(lpOut, TEXT("%d"), m_sInfo.iCount);
		TextOut(hDC, m_tTRect.left, m_tTRect.top + 17, lpOut, lstrlen(lpOut));
		SetTextColor(hDC, RGB(0, 0, 0));
		wsprintf(lpOut, TEXT("%d"), m_sInfo.iCount);
		TextOut(hDC, m_tTRect.left + 2, m_tTRect.top + 19, lpOut, lstrlen(lpOut));

		SetTextColor(hDC, RGB(255, 255, 255));
		wsprintf(lpOut, TEXT("%d"), m_sInfo.iCount);
		TextOut(hDC, m_tTRect.left + 1, m_tTRect.top + 18, lpOut, lstrlen(lpOut));

		SelectObject(hDC, oldFont);
		DeleteObject(textFont);
	}
	else if (m_sInfo.eID == IT_SKILL)
	{
		float fI = 1.f;
		if (m_sInfo.sTag == "Skill_1")
			fI = CSkillMgr::Get_Instance()->Getf1();
		else if (m_sInfo.sTag == "Skill_2")
			fI = CSkillMgr::Get_Instance()->Getf2();
		else if (m_sInfo.sTag == "Skill_3")
			fI = CSkillMgr::Get_Instance()->Getf3();
		else if (m_sInfo.sTag == "Skill_4")
			fI = CSkillMgr::Get_Instance()->Getf4();


		GdiTransparentBlt(hDC,
			int(m_tTRect.left),
			int(m_tTRect.top),
			int(m_tInfo.fTCX),
			int(m_tInfo.fTCY) * fI,
			hMemCoolDC,
			0,
			0,
			(int)m_tInfo.fTCX,
			(int)m_tInfo.fTCY * fI,
			RGB(255, 0, 255));
	}

}


void CQSlotTemp_UI::OnCollision(CObj* _pOther)
{
	if (m_sInfo.InvenID == 100)
		return;

	//if (_pOther->Get_Tag() == "Mouse")
	//{
	//	ITEM i = ((CMouse*)_pOther)->GetInfo();
	//	m_sInfo = i;
	//}
}


void CQSlotTemp_UI::ColRender(HDC hDC)
{
	Update_Rect();

	Rectangle(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tRect.right),
		int(m_tRect.bottom));
}


void CQSlotTemp_UI::Release(void)
{

}