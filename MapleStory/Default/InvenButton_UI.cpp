#include "stdafx.h"
#include "InvenButton_UI.h"

#include "BmpMgr.h"
#include "KeyMgr.h"
#include "InvenMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "UIMgr.h"


CInvenButton_UI::CInvenButton_UI()
{

}

CInvenButton_UI::~CInvenButton_UI()
{
	Release();
}

void CInvenButton_UI::Initialize(void)
{
	m_sTag = "InvenButton_UI";

	m_tInfo.fX = 9999.f;
	m_tInfo.fY = 9999.f;

	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 12.f;
	m_tInfo.fTCY = 12.f;


	m_tInfo.fCCX = 26.f;
	m_tInfo.fCCY = 20.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)0.f;

}

int CInvenButton_UI::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;



	return OBJ_NOEVENT;
}
void CInvenButton_UI::Late_Update(void)
{

}


void CInvenButton_UI::Render(HDC hDC)
{
	Update_Rect();
}


void CInvenButton_UI::OnCollision(CObj* _pOther)
{
	if (!CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		return;

	if(m_iIndex == 0)
		((CInven_UI*)CUIMgr::Get_Instance()->Get_InvenUI())->SetChange(true);
	else if(m_iIndex == 1)
		((CInven_UI*)CUIMgr::Get_Instance()->Get_InvenUI())->SetChange(false);
}


void CInvenButton_UI::ColRender(HDC hDC)
{
	Rectangle(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tRect.right),
		int(m_tRect.bottom));
}

void CInvenButton_UI::Release(void)
{

}