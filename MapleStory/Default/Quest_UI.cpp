#include "stdafx.h"
#include "Quest_UI.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "InvenMgr.h"
#include "QuestMgr.h"


CQuest_UI::CQuest_UI()
	: m_bIsOpen(false)
{
}

CQuest_UI::~CQuest_UI()
{
	Release();
}



void CQuest_UI::Initialize(void)
{
	m_sTag = "CommunityUI";


	m_tInfo.fX = 0.f;
	m_tInfo.fY = 350.f;

	// ÅØ½ºÃÄ Å©±â ¼³Á¤
	m_tInfo.fTCX = 200.f;
	m_tInfo.fTCY = 199.f;


	m_tInfo.fCCX = 0.f;
	m_tInfo.fCCY = 0.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)0.f;

	m_bIsOpen = false;
}

int CQuest_UI::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	if (CQuestMgr::Get_Instance()->GetQuest() == Q1 || CQuestMgr::Get_Instance()->GetQuest() == Q2
		|| CQuestMgr::Get_Instance()->GetQuest() == CQ1 || CQuestMgr::Get_Instance()->GetQuest() == CQ2
		|| CQuestMgr::Get_Instance()->GetQuest() == Q3)
	{
		m_tInfo.fX = 110.f;
		m_tInfo.fY = 310.f;
	}
	else
	{
		m_tInfo.fX = 9999.f;
		m_tInfo.fY = 9999.f;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CQuest_UI::Late_Update(void)
{

}

void CQuest_UI::Render(HDC hDC)
{

	HDC		hMemDCFrame = CBmpMgr::Get_Instance()->Find_Image(L"QuestUI");

	// ÇÁ·¹ÀÓ
	GdiTransparentBlt(hDC,
		int(m_tTRect.left),
		int(m_tTRect.top),
		int(m_tInfo.fTCX),
		int(m_tInfo.fTCY) - 70,
		hMemDCFrame,
		0,
		0,
		(int)m_tInfo.fTCX,
		(int)m_tInfo.fTCY,
		RGB(255, 0, 255));


	LOGFONT m_labelFontInfo{};
	m_labelFontInfo.lfHeight = 16;
	m_labelFontInfo.lfWidth = 8;
	m_labelFontInfo.lfCharSet = TURKISH_CHARSET;
	HFONT textFont, oldFont;
	textFont = CreateFontIndirect(&m_labelFontInfo);
	oldFont = (HFONT)SelectObject(hDC, textFont);

	SetBkMode(hDC, TRANSPARENT);
	SetBkColor(hDC, RGB(0, 0, 0));
	SetTextColor(hDC, RGB(255, 255, 255));


	switch (CQuestMgr::Get_Instance()->GetQuest())
	{
	case Q1:
	case CQ1:
		QuestQ_1(hDC);
		break;
	case Q2:
	case CQ2:
		QuestQ_2(hDC);
		break;
	case Q3:
		QuestQ_3(hDC);
		break;
	}


	SelectObject(hDC, oldFont);
	DeleteObject(textFont);
}

void CQuest_UI::QuestQ_1(HDC hDC)
{
	TCHAR lpOut[1024];

	if(CQuestMgr::Get_Instance()->Get_BlueNail() == CQuestMgr::Get_Instance()->Get_MaxBlueNail())
		SetTextColor(hDC, RGB(0, 255, 0));
	else
		SetTextColor(hDC, RGB(255, 255, 255));
	wsprintf(lpOut, TEXT("ÆÄ¶õ ´ÞÆØÀÌ: %d / %d"), CQuestMgr::Get_Instance()->Get_BlueNail(), CQuestMgr::Get_Instance()->Get_MaxBlueNail());
	TextOut(hDC, m_tInfo.fX - 80, m_tInfo.fY - 50, lpOut, lstrlen(lpOut));
	wsprintf(lpOut, TEXT("ÆÄ¶õ ´ÞÆØÀÌ: %d / %d"), CQuestMgr::Get_Instance()->Get_BlueNail(), CQuestMgr::Get_Instance()->Get_MaxBlueNail());
	TextOut(hDC, m_tInfo.fX - 80 - 1, m_tInfo.fY - 50 - 1, lpOut, lstrlen(lpOut));

	if (CQuestMgr::Get_Instance()->Get_RedNail() == CQuestMgr::Get_Instance()->Get_MaxRedNail())
		SetTextColor(hDC, RGB(0, 255, 0));
	else
		SetTextColor(hDC, RGB(255, 255, 255));
	wsprintf(lpOut, TEXT("»¡°£ ´ÞÆØÀÌ: %d / %d"), CQuestMgr::Get_Instance()->Get_RedNail(), CQuestMgr::Get_Instance()->Get_MaxRedNail());
	TextOut(hDC, m_tInfo.fX - 80, m_tInfo.fY - 30, lpOut, lstrlen(lpOut));
	wsprintf(lpOut, TEXT("»¡°£ ´ÞÆØÀÌ: %d / %d"), CQuestMgr::Get_Instance()->Get_RedNail(), CQuestMgr::Get_Instance()->Get_MaxRedNail());
	TextOut(hDC, m_tInfo.fX - 80 - 1, m_tInfo.fY - 30 - 1, lpOut, lstrlen(lpOut));

	if (CQuestMgr::Get_Instance()->Get_Green() == CQuestMgr::Get_Instance()->Get_MaxGreen())
		SetTextColor(hDC, RGB(0, 255, 0));
	else
		SetTextColor(hDC, RGB(255, 255, 255));
	wsprintf(lpOut, TEXT("ÃÊ·Ï ¹ö¼¸  : %d / %d"), CQuestMgr::Get_Instance()->Get_Green(), CQuestMgr::Get_Instance()->Get_MaxGreen());
	TextOut(hDC, m_tInfo.fX - 80, m_tInfo.fY - 10, lpOut, lstrlen(lpOut));
	wsprintf(lpOut, TEXT("ÃÊ·Ï ¹ö¼¸  : %d / %d"), CQuestMgr::Get_Instance()->Get_Green(), CQuestMgr::Get_Instance()->Get_MaxGreen());
	TextOut(hDC, m_tInfo.fX - 80 - 1, m_tInfo.fY - 10 - 1, lpOut, lstrlen(lpOut));

	SetTextColor(hDC, RGB(255, 255, 255));
}
void CQuest_UI::QuestQ_2(HDC hDC)
{
	TCHAR lpOut[1024];

	if (CQuestMgr::Get_Instance()->Get_DelNail() == CQuestMgr::Get_Instance()->Get_MaxDelNail())
		SetTextColor(hDC, RGB(0, 255, 0));
	else
		SetTextColor(hDC, RGB(255, 255, 255));
	wsprintf(lpOut, TEXT("ÈäÆøÇØÁø ´ÞÆØÀÌ: %d / %d"), CQuestMgr::Get_Instance()->Get_DelNail(), CQuestMgr::Get_Instance()->Get_MaxDelNail());
	TextOut(hDC, m_tInfo.fX - 80, m_tInfo.fY - 50, lpOut, lstrlen(lpOut));
	wsprintf(lpOut, TEXT("ÈäÆøÇØÁø ´ÞÆØÀÌ: %d / %d"), CQuestMgr::Get_Instance()->Get_DelNail(), CQuestMgr::Get_Instance()->Get_MaxDelNail());
	TextOut(hDC, m_tInfo.fX - 80 - 1, m_tInfo.fY - 50 - 1, lpOut, lstrlen(lpOut));


	if (CQuestMgr::Get_Instance()->Get_DelPig() == CQuestMgr::Get_Instance()->Get_MaxDelPig())
		SetTextColor(hDC, RGB(0, 255, 0));
	else
		SetTextColor(hDC, RGB(255, 255, 255));
	wsprintf(lpOut, TEXT("ÈäÆøÇØÁø µÅÁö: %d / %d"), CQuestMgr::Get_Instance()->Get_DelPig(), CQuestMgr::Get_Instance()->Get_MaxDelPig());
	TextOut(hDC, m_tInfo.fX - 80, m_tInfo.fY - 30, lpOut, lstrlen(lpOut));
	wsprintf(lpOut, TEXT("ÈäÆøÇØÁø µÅÁö: %d / %d"), CQuestMgr::Get_Instance()->Get_DelPig(), CQuestMgr::Get_Instance()->Get_MaxDelPig());
	TextOut(hDC, m_tInfo.fX - 80 - 1, m_tInfo.fY - 30 - 1, lpOut, lstrlen(lpOut));

	SetTextColor(hDC, RGB(255, 255, 255));
}

void CQuest_UI::QuestQ_3(HDC hDC)
{
	TCHAR lpOut[1024];

	SetTextColor(hDC, RGB(255, 0, 0));

	wsprintf(lpOut, TEXT("°ËÀº ¸¶¹ý»ç °ÝÆÄ"));
	TextOut(hDC, m_tInfo.fX - 80, m_tInfo.fY - 30, lpOut, lstrlen(lpOut));
	wsprintf(lpOut, TEXT("°ËÀº ¸¶¹ý»ç °ÝÆÄ"));
	TextOut(hDC, m_tInfo.fX - 80 - 1, m_tInfo.fY - 30 - 1, lpOut, lstrlen(lpOut));

	SetTextColor(hDC, RGB(255, 255, 255));
}



void CQuest_UI::ColRender(HDC hDC)
{
	Rectangle(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tRect.right),
		int(m_tRect.bottom));
}

void CQuest_UI::Release(void)
{

}