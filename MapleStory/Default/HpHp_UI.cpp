#include "stdafx.h"
#include "HpHp_UI.h"
#include "BmpMgr.h"
#include "StatMgr.h"


CHpHp_UI::CHpHp_UI()
	: m_fPH(0.f)
	, m_fPrePH(0.f)
	, m_fPM(0.f)
	, m_fPrePM(0.f)
	, m_fPE(0.f)
	, m_fPrePE(0.f)
{
}


CHpHp_UI::~CHpHp_UI()
{
	Release();
}

void CHpHp_UI::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/HpMp.bmp", L"HpMp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/hp.bmp", L"hp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/mp.bmp", L"mp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/exp.bmp", L"exp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/expGage.bmp", L"expGage");
	// Set_FrameKey(L"HpMp");


	m_tInfo.fX = 640.f;
	m_tInfo.fY = 680.f;

	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 172.f;
	m_tInfo.fTCY = 66.f;


	m_tInfo.fCCX = 0.f;
	m_tInfo.fCCY = 0.f;

}

int CHpHp_UI::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	if (m_fPrePH < m_fPH - 0.02f)
	{
		m_fPrePH += 0.005f;
	}
	else if (m_fPrePH > m_fPH + 0.02f)
	{
		m_fPrePH -= 0.005f;
	}
	else
	{
		m_fPrePH = m_fPH;
	}

	if (m_fPrePM < m_fPM - 0.02f)
	{
		m_fPrePM += 0.005f;
	}
	else if (m_fPrePM > m_fPM + 0.02f)
	{
		m_fPrePM -= 0.005f;
	}
	else
	{
		m_fPrePM = m_fPM;
	}

	if (m_fPrePE < m_fPE - 0.02f)
	{
		m_fPrePE += 0.005f;
	}
	else if (m_fPrePE > m_fPE + 0.02f)
	{
		m_fPrePE -= 0.005f;
	}
	else
	{
		m_fPrePE = m_fPE;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CHpHp_UI::Late_Update(void)
{

}

void CHpHp_UI::Render(HDC hDC)
{
	HDC		hMemDCFrame = CBmpMgr::Get_Instance()->Find_Image(L"HpMp");
	HDC		hMemDCHp = CBmpMgr::Get_Instance()->Find_Image(L"hp");
	HDC		hMemDCMp = CBmpMgr::Get_Instance()->Find_Image(L"mp");
	HDC		hMemDCExp = CBmpMgr::Get_Instance()->Find_Image(L"exp");
	HDC		hMemDCExpGage = CBmpMgr::Get_Instance()->Find_Image(L"expGage");

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
	// hp
	GdiTransparentBlt(hDC,
		int(m_tTRect.left + 24),
		int(m_tTRect.top + 28),
		int(142 * m_fPrePH),
		13,
		hMemDCHp,
		0,
		0,
		142,
		13,
		RGB(255, 0, 255));
	// mp
	GdiTransparentBlt(hDC,
		int(m_tTRect.left + 24),
		int(m_tTRect.top + 44),
		int(142 * m_fPrePM),
		13,
		hMemDCMp,
		0,
		0,
		142,
		13,
		RGB(255, 0, 255));
	// exp
	GdiTransparentBlt(hDC,
		0,
		int(m_tTRect.top + 63),
		1280,
		10,
		hMemDCExp,
		0,
		0,
		1280,
		10,
		RGB(255, 0, 255));
	// expGage
	GdiTransparentBlt(hDC,
		15,
		int(m_tTRect.top + 65),
		int(1265 * m_fPrePE),
		7,
		hMemDCExpGage,
		0,
		0,
		1264,
		7,
		RGB(255, 0, 255));


	LOGFONT m_labelFontInfo{};
	m_labelFontInfo.lfHeight = 12;
	m_labelFontInfo.lfWidth = 6;
	m_labelFontInfo.lfCharSet = HANGEUL_CHARSET;
	HFONT textFont, oldFont;
	textFont = CreateFontIndirect(&m_labelFontInfo);
	oldFont = (HFONT)SelectObject(hDC, textFont);

	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(255, 255, 255));
	TCHAR lpOut[1024];
	wsprintf(lpOut, TEXT("배꼽벌렁이"));
	TextOut(hDC, m_tTRect.left + 62, m_tTRect.top + 6, lpOut, lstrlen(lpOut));

	SelectObject(hDC, oldFont);
	DeleteObject(textFont);


	m_labelFontInfo.lfHeight = 12;
	m_labelFontInfo.lfWidth = 6;
	m_labelFontInfo.lfWeight = FW_BOLD;
	m_labelFontInfo.lfCharSet = HANGEUL_CHARSET;
	textFont = CreateFontIndirect(&m_labelFontInfo);
	oldFont = (HFONT)SelectObject(hDC, textFont);

	SetBkMode(hDC, TRANSPARENT);

	int iLevel = CStatMgr::Get_Instance()->Get_PlayerLevel();
	SetTextColor(hDC, RGB(0, 0, 0));
	wsprintf(lpOut, TEXT("Lv. %d"), iLevel);
	TextOut(hDC, m_tTRect.left + 11, m_tTRect.top + 7, lpOut, lstrlen(lpOut));

	SetTextColor(hDC, RGB(255, 212, 0));
	wsprintf(lpOut, TEXT("Lv. %d"), iLevel);
	TextOut(hDC, m_tTRect.left + 10, m_tTRect.top + 6, lpOut, lstrlen(lpOut));
	wsprintf(lpOut, TEXT("Lv. %d"), iLevel);
	TextOut(hDC, m_tTRect.left + 9, m_tTRect.top + 5, lpOut, lstrlen(lpOut));


	SelectObject(hDC, oldFont);
	DeleteObject(textFont);


}

void CHpHp_UI::ColRender(HDC hDC)
{
	Rectangle(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tRect.right),
		int(m_tRect.bottom));
}

void CHpHp_UI::Release(void)
{

}


