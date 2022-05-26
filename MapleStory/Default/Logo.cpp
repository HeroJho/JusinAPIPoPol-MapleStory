#include "stdafx.h"
#include "Logo.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"


CLogo::CLogo()
{
	m_tMapSize.left = (LONG)0.f;
	m_tMapSize.top = (LONG)0.f;
	m_tMapSize.right = (LONG)2238.f;
	m_tMapSize.bottom = (LONG)1597.f - 450.f;
}

CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize(void)
{
	m_iRGB = 255;
	m_bTurn = false;

	m_iCount = 0;
	m_fStartTime = 100.f;
	m_fOldStartTime = 0.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logo/Logo.bmp", L"Logo");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logo/Aing.bmp", L"Aing");

	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	CSoundMgr::Get_Instance()->PlaySound(L"Scene_7.wav", SOUND_BGM, 0.5);
}

void CLogo::Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE_1);
	}

	CObjMgr::Get_Instance()->Update();
}

void CLogo::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();

	Move_Frame();
}

void CLogo::Render(HDC hDC)
{
	// 출력 순서
	RenderBackGround(hDC);

	// CObjMgr::Get_Instance()->Render(hDC);

	if (m_iRGB >= 255)
		m_bTurn = false;
	else if (m_iRGB <= 0)
		m_bTurn = true;
	if (m_bTurn)
		++m_iRGB;
	else
		--m_iRGB;

	LOGFONT m_labelFontInfo{};
	m_labelFontInfo.lfHeight = 32;
	m_labelFontInfo.lfWidth = 18;
	m_labelFontInfo.lfCharSet = CHINESEBIG5_CHARSET;
	HFONT textFont, oldFont;
	textFont = CreateFontIndirect(&m_labelFontInfo);
	oldFont = (HFONT)SelectObject(hDC, textFont);

	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(m_iRGB, m_iRGB, m_iRGB));
	TCHAR lpOut[1024];
	wsprintf(lpOut, TEXT("Press any key to start..."));
	TextOut(hDC, 450, 450, lpOut, lstrlen(lpOut));
	wsprintf(lpOut, TEXT("Press any key to start..."));
	TextOut(hDC, 450 + 1, 450 + 1, lpOut, lstrlen(lpOut));
	wsprintf(lpOut, TEXT("Press any key to start..."));
	TextOut(hDC, 450 + 2, 450 + 2, lpOut, lstrlen(lpOut));

	SelectObject(hDC, oldFont);
	DeleteObject(textFont);
}

void CLogo::Release(void)
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

void CLogo::RenderBackGround(HDC hDC)
{
	HDC		hBackMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Logo");

	int iX = m_iCount % 5;
	int iY = m_iCount / 5;
	// 498 280
	GdiTransparentBlt(hDC,
		0,
		0,
		1280,
		720,
		hBackMemDC,
		iX * 498,
		iY * 280,
		498,
		280,
		RGB(255, 0, 255));

	//hBackMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Aing");
	//GdiTransparentBlt(hDC,
	//	265,
	//	55,
	//	521 / 5,
	//	447 / 5,
	//	hBackMemDC,
	//	0,
	//	0,
	//	521,
	//	447,
	//	RGB(255, 0, 255));
}

void CLogo::Move_Frame(void)
{
	if (m_fOldStartTime + m_fStartTime < GetTickCount64())
	{
		m_iCount++;

		m_fOldStartTime = (DWORD)GetTickCount64();

		if (m_iCount > 29)
		{
			m_iCount = 0;
		}
	}
}