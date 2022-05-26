#include "stdafx.h"
#include "Community_UI.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "InvenMgr.h"
#include "QuestMgr.h"


CCommunity_UI::CCommunity_UI()
	: m_bIsOpen(false)
{
}

CCommunity_UI::~CCommunity_UI()
{
	Release();
}



void CCommunity_UI::Initialize(void)
{
	m_sTag = "CommunityUI";


	m_tInfo.fX = 9999.f;
	m_tInfo.fY = 9999.f;

	// �ؽ��� ũ�� ����
	m_tInfo.fTCX = 519.f;
	m_tInfo.fTCY = 190.f;


	m_tInfo.fCCX = 276.f;
	m_tInfo.fCCY = 505.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)-135.f;

	m_bIsOpen = false;


	m_pNextButton = new CCommunityS_UI;
	m_pNextButton->Initialize();

	m_pNextButton->Set_Pos(m_tInfo.fX + 210, m_tInfo.fY + 45);
}

int CCommunity_UI::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	if (m_bIsOpen)
	{
		m_tInfo.fX = 650.f;
		m_tInfo.fY = 300.f;
	}
	else
	{
		m_tInfo.fX = 9999.f;
		m_tInfo.fY = 9999.f;
	}


	m_pNextButton->Set_Pos(m_tInfo.fX + 210, m_tInfo.fY + 45);



	Update_Rect();

	return OBJ_NOEVENT;
}

void CCommunity_UI::Late_Update(void)
{

}

void CCommunity_UI::Render(HDC hDC)
{

	HDC		hMemDCFrame = CBmpMgr::Get_Instance()->Find_Image(L"Community");

	// ������
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
	m_labelFontInfo.lfHeight = 13;
	m_labelFontInfo.lfWidth = 7;
	m_labelFontInfo.lfCharSet = HANGEUL_CHARSET;
	HFONT textFont, oldFont;
	textFont = CreateFontIndirect(&m_labelFontInfo);
	oldFont = (HFONT)SelectObject(hDC, textFont);

	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(0, 0, 0));


	switch (CQuestMgr::Get_Instance()->GetQuest())
	{
	case Stay1:
		QuestTalk_1(hDC);
		break;
	case Q1:
		QuestQ_1(hDC);
		break;
	case CQ1:
		QuestCQ_1(hDC);
		break;
	case Stay2:
		QuestTalk_2(hDC);
		break;
	case Q2:
		QuestQ_2(hDC);
		break;
	case CQ2:
		QuestCQ_2(hDC);
		break;
	case Stay3:
		QuestTalk_3(hDC);
		break;
	case Q3:
		QuestQ_3(hDC);
		break;
	}


	SelectObject(hDC, oldFont);
	DeleteObject(textFont);




	m_pNextButton->Render(hDC);
	// m_pNextButton->ColRender(hDC);

}

void CCommunity_UI::QuestTalk_1(HDC hDC)
{
	TCHAR lpOut[1024];
	SetTextColor(hDC, RGB(255, 255, 255));
	wsprintf(lpOut, TEXT("��� ����"));
	TextOut(hDC, m_tTRect.left + 48, m_tTRect.top + 121, lpOut, lstrlen(lpOut));

	SetTextColor(hDC, RGB(0, 0, 0));
	wsprintf(lpOut, TEXT("���̰�, ���Ͱ� ���� �þ�� ����..."));
	TextOut(hDC, m_tTRect.left + 160, m_tTRect.top + 30, lpOut, lstrlen(lpOut));
	wsprintf(lpOut, TEXT("���õ� ��Ź�Լ�."));
	TextOut(hDC, m_tTRect.left + 160, m_tTRect.top + 50, lpOut, lstrlen(lpOut));
}
void CCommunity_UI::QuestQ_1(HDC hDC)
{
	TCHAR lpOut[1024];
	SetTextColor(hDC, RGB(255, 255, 255));
	wsprintf(lpOut, TEXT("��� ����"));
	TextOut(hDC, m_tTRect.left + 48, m_tTRect.top + 121, lpOut, lstrlen(lpOut));

	SetTextColor(hDC, RGB(0, 0, 0));
	wsprintf(lpOut, TEXT("���� �� ���� �ֳ�?"));
	TextOut(hDC, m_tTRect.left + 160, m_tTRect.top + 30, lpOut, lstrlen(lpOut));
}
void CCommunity_UI::QuestCQ_1(HDC hDC)
{
	TCHAR lpOut[1024];
	SetTextColor(hDC, RGB(255, 255, 255));
	wsprintf(lpOut, TEXT("��� ����"));
	TextOut(hDC, m_tTRect.left + 48, m_tTRect.top + 121, lpOut, lstrlen(lpOut));

	SetTextColor(hDC, RGB(0, 0, 0));
	wsprintf(lpOut, TEXT("���ٳ�! ������!"));
	TextOut(hDC, m_tTRect.left + 160, m_tTRect.top + 30, lpOut, lstrlen(lpOut));
}

void CCommunity_UI::QuestTalk_2(HDC hDC)
{
	TCHAR lpOut[1024];
	SetTextColor(hDC, RGB(255, 255, 255));
	wsprintf(lpOut, TEXT("��� ����"));
	TextOut(hDC, m_tTRect.left + 48, m_tTRect.top + 121, lpOut, lstrlen(lpOut));

	SetTextColor(hDC, RGB(0, 0, 0));
	wsprintf(lpOut, TEXT("����... ��׽ý���..."));
	TextOut(hDC, m_tTRect.left + 160, m_tTRect.top + 30, lpOut, lstrlen(lpOut));
	wsprintf(lpOut, TEXT("���� �������� ���� Ʋ�����ٳ�. �ڳװ� �������ְԳ�!"));
	TextOut(hDC, m_tTRect.left + 160, m_tTRect.top + 50, lpOut, lstrlen(lpOut));
	wsprintf(lpOut, TEXT("���� �����翡�� ������,"));
	TextOut(hDC, m_tTRect.left + 160, m_tTRect.top + 80, lpOut, lstrlen(lpOut));
	wsprintf(lpOut, TEXT("���� �������� ���͵��� ó���ؾ� �Ѵٳ�!"));
	TextOut(hDC, m_tTRect.left + 160, m_tTRect.top + 110, lpOut, lstrlen(lpOut));

}
void CCommunity_UI::QuestQ_2(HDC hDC)
{
	TCHAR lpOut[1024];
	SetTextColor(hDC, RGB(255, 255, 255));
	wsprintf(lpOut, TEXT("��� ����"));
	TextOut(hDC, m_tTRect.left + 48, m_tTRect.top + 121, lpOut, lstrlen(lpOut));

	SetTextColor(hDC, RGB(0, 0, 0));
	wsprintf(lpOut, TEXT("����..."));
	TextOut(hDC, m_tTRect.left + 160, m_tTRect.top + 30, lpOut, lstrlen(lpOut));
}

void CCommunity_UI::QuestCQ_2(HDC hDC)
{
	TCHAR lpOut[1024];
	SetTextColor(hDC, RGB(255, 255, 255));
	wsprintf(lpOut, TEXT("��� ����"));
	TextOut(hDC, m_tTRect.left + 48, m_tTRect.top + 121, lpOut, lstrlen(lpOut));

	SetTextColor(hDC, RGB(0, 0, 0));
	wsprintf(lpOut, TEXT("��谡 ��ȭ�Ƴ�! ���� ������ �� ���� �ɼ�."));
	TextOut(hDC, m_tTRect.left + 160, m_tTRect.top + 30, lpOut, lstrlen(lpOut));
}

void CCommunity_UI::QuestTalk_3(HDC hDC)
{
	TCHAR lpOut[1024];
	SetTextColor(hDC, RGB(255, 255, 255));
	wsprintf(lpOut, TEXT("��� ����"));
	TextOut(hDC, m_tTRect.left + 48, m_tTRect.top + 121, lpOut, lstrlen(lpOut));

	SetTextColor(hDC, RGB(0, 0, 0));
	wsprintf(lpOut, TEXT("���� ���� �����縦 ������ �ְԳ�!"));
	TextOut(hDC, m_tTRect.left + 160, m_tTRect.top + 30, lpOut, lstrlen(lpOut));
	wsprintf(lpOut, TEXT("�ε� ������ ���ƿ���..."));
	TextOut(hDC, m_tTRect.left + 160, m_tTRect.top + 60, lpOut, lstrlen(lpOut));
}

void CCommunity_UI::QuestQ_3(HDC hDC)
{
	TCHAR lpOut[1024];
	SetTextColor(hDC, RGB(255, 255, 255));
	wsprintf(lpOut, TEXT("��� ����"));
	TextOut(hDC, m_tTRect.left + 48, m_tTRect.top + 121, lpOut, lstrlen(lpOut));

	wsprintf(lpOut, TEXT("�ε� ������ ���ƿ���..."));
	TextOut(hDC, m_tTRect.left + 160, m_tTRect.top + 30, lpOut, lstrlen(lpOut));
}


void CCommunity_UI::ColRender(HDC hDC)
{
	Rectangle(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tRect.right),
		int(m_tRect.bottom));
}

void CCommunity_UI::Release(void)
{
	Safe_Delete(m_pNextButton);
}