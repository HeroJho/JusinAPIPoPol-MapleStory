#include "stdafx.h"
#include "Dead_UI.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "InvenMgr.h"
#include "QuestMgr.h"


CDead_UI::CDead_UI()
	: m_bIsOpen(false)
{
}

CDead_UI::~CDead_UI()
{
	Release();
}



void CDead_UI::Initialize(void)
{
	m_sTag = "DeadUI";


	m_tInfo.fX = 9999.f;
	m_tInfo.fY = 9999.f;

	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 277.f;
	m_tInfo.fTCY = 120.f;


	m_tInfo.fCCX = 277.f;
	m_tInfo.fCCY = 120.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)-135.f;

	m_bIsOpen = false;


	m_pNextButton = new CCommunityS_UI;
	m_pNextButton->Initialize();
	m_pNextButton->Set_Tag("DeadButton");

	m_pNextButton->Set_Pos(m_tInfo.fX + 210, m_tInfo.fY + 45);
}

int CDead_UI::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	if (m_bIsOpen)
	{
		m_tInfo.fX = 640.f;
		m_tInfo.fY = 300.f;
	}
	else
	{
		m_tInfo.fX = 9999.f;
		m_tInfo.fY = 9999.f;
	}


	m_pNextButton->Set_Pos(m_tInfo.fX + 105, m_tInfo.fY + 37);

	Update_Rect();

	return OBJ_NOEVENT;
}

void CDead_UI::Late_Update(void)
{

}

void CDead_UI::Render(HDC hDC)
{
	HDC		hMemDCFrame = CBmpMgr::Get_Instance()->Find_Image(L"Dead_UI");

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


	

	m_pNextButton->Render(hDC);
	//m_pNextButton->ColRender(hDC);

}


void CDead_UI::ColRender(HDC hDC)
{
	Rectangle(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tRect.right),
		int(m_tRect.bottom));
}

void CDead_UI::Release(void)
{
	Safe_Delete(m_pNextButton);
}