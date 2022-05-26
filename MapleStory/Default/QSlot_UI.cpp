#include "stdafx.h"
#include "QSlot_UI.h"

#include "BmpMgr.h"
#include "KeyMgr.h"
#include "InvenMgr.h"
#include "SlotMgr.h"


CQSlot_UI::CQSlot_UI()
{
}

CQSlot_UI::~CQSlot_UI()
{
	Release();
}

void CQSlot_UI::Initialize(void)
{
	m_sTag = "QSlot_UI";


	m_tInfo.fX = 1280.f - 192/2 - 2;
	m_tInfo.fY = 720.f - 64/2 - 12;

	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 192.f;
	m_tInfo.fTCY = 64.f;


	m_tInfo.fCCX = 0.f;
	m_tInfo.fCCY = 0.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)0.f;


	for (int i = 0; i < 12; ++i)
	{
		m_aSlot[i] = new CQSlotTemp_UI;
		m_aSlot[i]->Initialize();
		m_aSlot[i]->SetIndex(i);

		int x = i % 6;
		int y = i / 6;

		m_aSlot[i]->Set_Pos(m_tInfo.fX - 80 + (x * 32), m_tInfo.fY - 16 + (y * 32));
	}

}

int CQSlot_UI::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	for (int i = 0; i < 12; ++i)
	{
		m_aSlot[i]->SetInfo(CSlotMgr::Get_Instance()->GetSlotInfo()[i]->GetInfo());
	}


	Update_Rect();

	return OBJ_NOEVENT;
}

void CQSlot_UI::Late_Update(void)
{

}

void CQSlot_UI::Render(HDC hDC)
{

	HDC		hMemDCFrame = CBmpMgr::Get_Instance()->Find_Image(L"quickslot");

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

	for (int i = 0; i < 12; ++i)
	{
		m_aSlot[i]->Render(hDC);
		// m_aSlot[i]->ColRender(hDC);
	}
}

void CQSlot_UI::ColRender(HDC hDC)
{
	Rectangle(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tRect.right),
		int(m_tRect.bottom));
}

void CQSlot_UI::Release(void)
{
	for (int i = 0; i < 12; ++i)
		Safe_Delete(m_aSlot[i]);
}