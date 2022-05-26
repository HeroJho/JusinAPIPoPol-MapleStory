#include "stdafx.h"
#include "Boss_UI.h"
#include "BmpMgr.h"


CBoss_UI::CBoss_UI()
	: m_fPH(0.f)
	, m_fPrePH(0.f)
	, m_fPM(0.f)
	, m_fPrePM(0.f)
{
}


CBoss_UI::~CBoss_UI()
{
	Release();
}

void CBoss_UI::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/boss_Hp.bmp", L"boss_Hp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/bossHpGage.bmp", L"bossHpGage");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/bossMpGage.bmp", L"bossMpGage");
	// Set_FrameKey(L"HpMp");


	m_tInfo.fX = 640.f;
	m_tInfo.fY = 680.f;

	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 801.f;
	m_tInfo.fTCY = 40.f;


	m_tInfo.fCCX = 0.f;
	m_tInfo.fCCY = 0.f;

}

int CBoss_UI::Update(void)
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

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBoss_UI::Late_Update(void)
{

}

void CBoss_UI::Render(HDC hDC)
{
	HDC		hMemDCFrame = CBmpMgr::Get_Instance()->Find_Image(L"boss_Hp");
	HDC		hMemDCHp = CBmpMgr::Get_Instance()->Find_Image(L"bossHpGage");
	HDC		hMemDCMp = CBmpMgr::Get_Instance()->Find_Image(L"bossMpGage");


	// 프레임
	GdiTransparentBlt(hDC,
		240,
		25,
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
		240 + 39,
		25 + 22,
		int(759) * m_fPrePH,
		16,
		hMemDCHp,
		0,
		0,
		759,
		16,
		RGB(255, 0, 255));
	// mp
	GdiTransparentBlt(hDC,
		240 + 40,
		25 + 4,
		int(754) * m_fPrePM,
		12,
		hMemDCMp,
		0,
		0,
		754,
		12,
		RGB(255, 0, 255));

}

void CBoss_UI::ColRender(HDC hDC)
{
	Rectangle(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tRect.right),
		int(m_tRect.bottom));
}

void CBoss_UI::Release(void)
{

}

