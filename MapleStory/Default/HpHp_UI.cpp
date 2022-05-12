#include "stdafx.h"
#include "HpHp_UI.h"
#include "BmpMgr.h"


CHpHp_UI::CHpHp_UI()
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

	m_fPreP = 0.f;
}

int CHpHp_UI::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;



	if (m_fPreP < m_fP - 0.02f)
	{
		m_fPreP += 0.01f;
	}
	else if (m_fPreP > m_fP + 0.02f)
	{
		m_fPreP -= 0.01f;
	}
	else
	{
		m_fPreP = m_fP;
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
		0.f,
		0.f,
		(int)m_tInfo.fTCX,
		(int)m_tInfo.fTCY,
		RGB(255, 0, 255));
	// hp
	GdiTransparentBlt(hDC,
		int(m_tTRect.left + 24),
		int(m_tTRect.top + 28),
		142 * m_fPreP,
		13,
		hMemDCHp,
		0.f,
		0.f,
		142,
		13,
		RGB(255, 0, 255));
	// mp
	GdiTransparentBlt(hDC,
		int(m_tTRect.left + 24),
		int(m_tTRect.top + 44),
		142,
		13,
		hMemDCMp,
		0.f,
		0.f,
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
		0.f,
		0.f,
		1280,
		10,
		RGB(255, 0, 255));
	// expGage
	GdiTransparentBlt(hDC,
		15,
		int(m_tTRect.top + 65),
		1000,
		7,
		hMemDCExpGage,
		0.f,
		0.f,
		1264,
		7,
		RGB(255, 0, 255));

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


