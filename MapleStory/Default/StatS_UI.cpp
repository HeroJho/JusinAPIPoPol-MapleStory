#include "stdafx.h"
#include "StatS_UI.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "InvenMgr.h"
#include "ObjMgr.h"
#include "Player.h"


CStatS_UI::CStatS_UI()
{

}

CStatS_UI::~CStatS_UI()
{
	Release();
}

void CStatS_UI::Initialize(void)
{
	m_sTag = "Shop_UI";
	m_tFrame.iFrameStart = 0;

	m_tInfo.fX = 9999.f;
	m_tInfo.fY = 9999.f;

	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 12.f;
	m_tInfo.fTCY = 12.f;


	m_tInfo.fCCX = 12.f;
	m_tInfo.fCCY = 12.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)0.f;

}

int CStatS_UI::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (!CStatMgr::Get_Instance()->GetStatPoint())
		m_tFrame.iFrameStart = 2;

	return OBJ_NOEVENT;
}
void CStatS_UI::Late_Update(void)
{

}


void CStatS_UI::Render(HDC hDC)
{
	Update_Rect();

	
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"StatButton");;

	if (!hMemDC)
		return;

	GdiTransparentBlt(hDC,
		int(m_tTRect.left),
		int(m_tTRect.top),
		int(m_tInfo.fTCX),
		int(m_tInfo.fTCY),
		hMemDC,
		0,
		(int)m_tFrame.iFrameStart * m_tInfo.fTCX,
		(int)m_tInfo.fTCX,
		(int)m_tInfo.fTCY,
		RGB(255, 0, 255));

	m_tFrame.iFrameStart = 0;
}


void CStatS_UI::OnCollision(CObj* _pOther)
{
	if (!CStatMgr::Get_Instance()->GetStatPoint())
		return;

	m_tFrame.iFrameStart = 1;

	if (!CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		return;

	if (_pOther->Get_Tag() == "Mouse")
	{
		switch (m_iIndex)
		{
		case 0:
			CStatMgr::Get_Instance()->Increase_STR();
			break;
		case 1:
			CStatMgr::Get_Instance()->Increase_DEX();
			break;
		case 2:
			CStatMgr::Get_Instance()->Increase_INT();
			break;
		case 3:
			CStatMgr::Get_Instance()->Increase_LUK();
			break;
		}
	}

}


void CStatS_UI::ColRender(HDC hDC)
{
	Update_Rect();

	Rectangle(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tRect.right),
		int(m_tRect.bottom));
}

void CStatS_UI::Release(void)
{

}