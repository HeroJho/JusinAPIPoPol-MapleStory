#include "stdafx.h"
#include "StatUI.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "InvenMgr.h"
#include "QuestMgr.h"
#include "StatMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"


CStatUI::CStatUI()
	: m_bIsOpen(false)
{
}

CStatUI::~CStatUI()
{
	Release();
}



void CStatUI::Initialize(void)
{
	m_sTag = "StatUI";

	m_fRePosX = 500.f;
	m_fRePosY = 600.f;

	m_tInfo.fX = 9999.f;
	m_tInfo.fY = 9999.f;

	// ÅØ½ºÃÄ Å©±â ¼³Á¤
	m_tInfo.fTCX = 212.f;
	m_tInfo.fTCY = 318.f;


	m_tInfo.fCCX = 190.f;
	m_tInfo.fCCY = 40.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)-145.f;

	m_bIsOpen = false;


	for (int i = 0; i < 4; ++i)
	{
		m_aStatUIList[i] = new CStatS_UI;
		m_aStatUIList[i]->Initialize();
		m_aStatUIList[i]->SetIndex(i);

		m_aStatUIList[i]->Set_Pos(m_tInfo.fX + 87, m_tInfo.fY + 55 + (i * 18));
	}
}

int CStatUI::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	if (CKeyMgr::Get_Instance()->Key_Down('J'))
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


	for (int i = 0; i < 4; ++i)
	{
		m_aStatUIList[i]->Set_Pos(m_tInfo.fX + 87, m_tInfo.fY + 55 + (i * 18));
		m_aStatUIList[i]->Update();
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CStatUI::Late_Update(void)
{

}

void CStatUI::Render(HDC hDC)
{

	HDC		hMemDCFrame = CBmpMgr::Get_Instance()->Find_Image(L"stat");

	// ÇÁ·¹ÀÓ
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
	m_labelFontInfo.lfWidth = 6;
	m_labelFontInfo.lfCharSet = HANGEUL_CHARSET;
	HFONT textFont, oldFont;
	textFont = CreateFontIndirect(&m_labelFontInfo);
	oldFont = (HFONT)SelectObject(hDC, textFont);

	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(0, 0, 0));



	TCHAR lpOut[1024];

	wsprintf(lpOut, TEXT("¹è²Å¹ú··ÀÌ"));
	TextOut(hDC, m_tTRect.left + 72, m_tTRect.top + 30, lpOut, lstrlen(lpOut));
	wsprintf(lpOut, TEXT("µà¾ó ºí·¹ÀÌµå"));
	TextOut(hDC, m_tTRect.left + 72, m_tTRect.top + 48, lpOut, lstrlen(lpOut));
	wsprintf(lpOut, TEXT("¹ú··ÀÌ¿Í ¾ÆÀÌµé"));
	TextOut(hDC, m_tTRect.left + 72, m_tTRect.top + 67, lpOut, lstrlen(lpOut));
	wsprintf(lpOut, TEXT("-5"));
	TextOut(hDC, m_tTRect.left + 72, m_tTRect.top + 84, lpOut, lstrlen(lpOut));

	int iATStart = CStatMgr::Get_Instance()->Get_PlayerAT();
	int iATEnd = iATStart + (iATStart/2);
	wsprintf(lpOut, TEXT("%d ~ %d"), iATStart * 1423, iATEnd * 1423);
	TextOut(hDC, m_tTRect.left + 72, m_tTRect.top + 103, lpOut, lstrlen(lpOut));

	iATStart = CObjMgr::Get_Instance()->Get_Player()->Get_Stat().iMp;
	iATEnd = CStatMgr::Get_Instance()->Get_PlayerMaxMP();
	wsprintf(lpOut, TEXT("%d / %d"), iATStart, iATEnd);
	TextOut(hDC, m_tTRect.left + 72, m_tTRect.top + 121, lpOut, lstrlen(lpOut));

	iATStart = CObjMgr::Get_Instance()->Get_Player()->Get_Stat().iHp;
	iATEnd = CStatMgr::Get_Instance()->Get_PlayerMaxHP();
	wsprintf(lpOut, TEXT("%d / %d"), iATStart, iATEnd);
	TextOut(hDC, m_tTRect.left + 72, m_tTRect.top + 139, lpOut, lstrlen(lpOut));


	wsprintf(lpOut, TEXT("%d"), CStatMgr::Get_Instance()->GetStatPoint());
	TextOut(hDC, m_tTRect.left + 72, m_tTRect.top + 180, lpOut, lstrlen(lpOut));


	int iPlusSTR = CStatMgr::Get_Instance()->Get_PlusSTR();
	int iSTR = CStatMgr::Get_Instance()->GetPlayerState().iSTR;
	int iTotalSTR = iSTR + iPlusSTR;
	wsprintf(lpOut, TEXT("%d (%d+%d)"), iTotalSTR, iSTR, iPlusSTR);
	TextOut(hDC, m_tTRect.left + 72, m_tTRect.top + 208, lpOut, lstrlen(lpOut));

	iPlusSTR = CStatMgr::Get_Instance()->Get_PlusDEX();
	iSTR = CStatMgr::Get_Instance()->GetPlayerState().iDEX;
	iTotalSTR = iSTR + iPlusSTR;
	wsprintf(lpOut, TEXT("%d (%d+%d)"), iTotalSTR, iSTR, iPlusSTR);
	TextOut(hDC, m_tTRect.left + 72, m_tTRect.top + 226, lpOut, lstrlen(lpOut));

	iPlusSTR = CStatMgr::Get_Instance()->Get_PlusINT();
	iSTR = CStatMgr::Get_Instance()->GetPlayerState().iINT;
	iTotalSTR = iSTR + iPlusSTR;
	wsprintf(lpOut, TEXT("%d (%d+%d)"), iTotalSTR, iSTR, iPlusSTR);
	TextOut(hDC, m_tTRect.left + 72, m_tTRect.top + 244, lpOut, lstrlen(lpOut));

	iPlusSTR = CStatMgr::Get_Instance()->Get_PlusLUK();
	iSTR = CStatMgr::Get_Instance()->GetPlayerState().iLUK;
	iTotalSTR = iSTR + iPlusSTR;
	wsprintf(lpOut, TEXT("%d (%d+%d)"), iTotalSTR, iSTR, iPlusSTR);
	TextOut(hDC, m_tTRect.left + 72, m_tTRect.top + 262, lpOut, lstrlen(lpOut));


	SelectObject(hDC, oldFont);
	DeleteObject(textFont);


	for (int i = 0; i < 4; ++i)
	{
		m_aStatUIList[i]->Render(hDC);
	}

}


void CStatUI::ColRender(HDC hDC)
{
	Rectangle(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tRect.right),
		int(m_tRect.bottom));
}

void CStatUI::Release(void)
{
	for (int i = 0; i < 4; ++i)
		Safe_Delete(m_aStatUIList[i]);
}