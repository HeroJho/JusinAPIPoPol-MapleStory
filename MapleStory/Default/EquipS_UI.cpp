#include "stdafx.h"
#include "EquipS_UI.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "InvenMgr.h"
#include "ObjMgr.h"
#include "Player.h"


CEquipS_UI::CEquipS_UI()
	: m_sInfo{}
{
}

CEquipS_UI::~CEquipS_UI()
{
	Release();
}

void CEquipS_UI::Initialize(void)
{
	m_sTag = "EquipS_UI";
	m_sInfo.InvenID = 100;


	m_tInfo.fX = 9999.f;
	m_tInfo.fY = 9999.f;

	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 30.f;
	m_tInfo.fTCY = 30.f;


	m_tInfo.fCCX = 30.f;
	m_tInfo.fCCY = 30.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)0.f;

}

int CEquipS_UI::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;



	return OBJ_NOEVENT;
}

void CEquipS_UI::Late_Update(void)
{

}

void CEquipS_UI::Render(HDC hDC)
{
	Update_Rect();

	if (m_sInfo.InvenID == 100)
		return;

	HDC		hMemDC = nullptr;
	if (m_sInfo.sTag == "Weapon")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Equip");
		m_tInfo.fTCX = 40.f;
		m_tInfo.fTCY = 40.f;
		m_tFrame.iFrameStart = 0;
	}
	else if (m_sInfo.sTag == "Shute")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Equip");
		m_tInfo.fTCX = 40.f;
		m_tInfo.fTCY = 40.f;
		m_tFrame.iFrameStart = 1;
	}
	else if (m_sInfo.sTag == "Shose")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Equip");
		m_tInfo.fTCX = 40.f;
		m_tInfo.fTCY = 40.f;
		m_tFrame.iFrameStart = 2;
	}
	else if (m_sInfo.sTag == "Gyenjong")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Equip");
		m_tInfo.fTCX = 40.f;
		m_tInfo.fTCY = 40.f;
		m_tFrame.iFrameStart = 3;
	}
	else if (m_sInfo.sTag == "Cave")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Equip");
		m_tInfo.fTCX = 40.f;
		m_tInfo.fTCY = 40.f;
		m_tFrame.iFrameStart = 5;
	}
	else if (m_sInfo.sTag == "Het")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Equip");
		m_tInfo.fTCX = 40.f;
		m_tInfo.fTCY = 40.f;
		m_tFrame.iFrameStart = 6;
	}
	else if (m_sInfo.sTag == "Glove")
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Equip");
		m_tInfo.fTCX = 40.f;
		m_tInfo.fTCY = 40.f;
		m_tFrame.iFrameStart = 7;
	}

	if (!hMemDC)
		return;

	GdiTransparentBlt(hDC,
		int(m_tTRect.left),
		int(m_tTRect.top),
		int(m_tInfo.fTCX),
		int(m_tInfo.fTCY),
		hMemDC,
		int(m_tFrame.iFrameStart * m_tInfo.fTCX),
		0,
		(int)m_tInfo.fTCX,
		(int)m_tInfo.fTCY,
		RGB(255, 0, 255));

}


void CEquipS_UI::OnCollision(CObj* _pOther)
{
	if (m_sInfo.InvenID == 100)
		return;

	if (_pOther->Get_Tag() == "Mouse")
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
		{
			// TODO : 아이템 해제
			CInvenMgr::Get_Instance()->Add_Item(m_sInfo);
			m_sInfo.InvenID = 100;

			if (m_sInfo.sTag == "Weapon")
			{
				CStatMgr::Get_Instance()->Remove_Weapon();
			}
			else if (m_sInfo.sTag == "Shute")
			{
				CStatMgr::Get_Instance()->Remove_Shute();
			}
			else if (m_sInfo.sTag == "Shose")
			{
				CStatMgr::Get_Instance()->Remove_Shose();
			}
			else if (m_sInfo.sTag == "Gyenjong")
			{
				CStatMgr::Get_Instance()->Remove_Gyenjong();
			}
			else if (m_sInfo.sTag == "Cave")
			{
				CStatMgr::Get_Instance()->Remove_Cave();
			}
			else if (m_sInfo.sTag == "Het")
			{
				CStatMgr::Get_Instance()->Remove_Het();
			}
			else if (m_sInfo.sTag == "Glove")
			{
				CStatMgr::Get_Instance()->Remove_Glove();
			}

		}
	}
}


void CEquipS_UI::ColRender(HDC hDC)
{

	Update_Rect();

	Rectangle(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tRect.right),
		int(m_tRect.bottom));
}


void CEquipS_UI::Release(void)
{

}