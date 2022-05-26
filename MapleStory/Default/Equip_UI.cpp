#include "stdafx.h"
#include "Equip_UI.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "InvenMgr.h"
#include "SoundMgr.h"
#include "StatMgr.h"


CEquip_UI::CEquip_UI()
	: m_bIsOpen(false)
{
}


CEquip_UI::~CEquip_UI()
{
	Release();
}

void CEquip_UI::Initialize(void)
{
	m_sTag = "EquipUI";


	m_fRePosX = 800.f;
	m_fRePosY = 300.f;

	m_tInfo.fX = 9999.f;
	m_tInfo.fY = 9999.f;

	// ≈ÿΩ∫√ƒ ≈©±‚ º≥¡§
	m_tInfo.fTCX = 184.f;
	m_tInfo.fTCY = 290.f;


	m_tInfo.fCCX = 172.f;
	m_tInfo.fCCY = 25.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)-140.f;

	m_bIsOpen = false;

	m_aEquipUIList[0] = new CEquipS_UI();
	m_aEquipUIList[0]->Initialize();
	m_aEquipUIList[0]->SetIndex(0);
	m_aEquipUIList[0]->Set_Pos(100.f, 100.f);

	m_aEquipUIList[1] = new CEquipS_UI();
	m_aEquipUIList[1]->Initialize();
	m_aEquipUIList[1]->SetIndex(1);
	m_aEquipUIList[1]->Set_Pos(100.f, 100.f);

	m_aEquipUIList[2] = new CEquipS_UI();
	m_aEquipUIList[2]->Initialize();
	m_aEquipUIList[2]->SetIndex(2);
	m_aEquipUIList[2]->Set_Pos(100.f, 100.f);

	m_aEquipUIList[3] = new CEquipS_UI();
	m_aEquipUIList[3]->Initialize();
	m_aEquipUIList[3]->SetIndex(3);
	m_aEquipUIList[3]->Set_Pos(100.f, 100.f);

	m_aEquipUIList[4] = new CEquipS_UI();
	m_aEquipUIList[4]->Initialize();
	m_aEquipUIList[4]->SetIndex(4);
	m_aEquipUIList[4]->Set_Pos(100.f, 100.f);

	m_aEquipUIList[5] = new CEquipS_UI();
	m_aEquipUIList[5]->Initialize();
	m_aEquipUIList[5]->SetIndex(5);
	m_aEquipUIList[5]->Set_Pos(100.f, 100.f);

	m_aEquipUIList[6] = new CEquipS_UI();
	m_aEquipUIList[6]->Initialize();
	m_aEquipUIList[6]->SetIndex(6);
	m_aEquipUIList[6]->Set_Pos(100.f, 100.f);

}

int CEquip_UI::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (CKeyMgr::Get_Instance()->Key_Down('U'))
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

	for (int i = 0; i < 7; ++i)
		m_aEquipUIList[i]->GetInfo().InvenID = 100;

	m_aEquipUIList[0]->Set_Pos(m_tInfo.fX - 33, m_tInfo.fY - 100); // ∏”∏Æ
	m_aEquipUIList[1]->Set_Pos(m_tInfo.fX + 33, m_tInfo.fY); // π´±‚
	m_aEquipUIList[2]->Set_Pos(m_tInfo.fX, m_tInfo.fY); // «— π˙ø 
	m_aEquipUIList[3]->Set_Pos(m_tInfo.fX, m_tInfo.fY + 65); // Ω≈πﬂ
	m_aEquipUIList[4]->Set_Pos(m_tInfo.fX + 66, m_tInfo.fY - 33); // ∞ﬂ¿Â
	m_aEquipUIList[5]->Set_Pos(m_tInfo.fX + 66, m_tInfo.fY); // ∏¡≈‰
	m_aEquipUIList[6]->Set_Pos(m_tInfo.fX - 66, m_tInfo.fY + 33); // ¿Â∞©

	m_aEquipUIList[0]->SetInfo(CStatMgr::Get_Instance()->Get_Het());		// ∏”∏Æ
	m_aEquipUIList[1]->SetInfo(CStatMgr::Get_Instance()->Get_Weapon());		// π´±‚
	m_aEquipUIList[2]->SetInfo(CStatMgr::Get_Instance()->Get_Shute());		// «— π˙ø 
	m_aEquipUIList[3]->SetInfo(CStatMgr::Get_Instance()->Get_Shose());		// Ω≈πﬂ
	m_aEquipUIList[4]->SetInfo(CStatMgr::Get_Instance()->Get_Gyenjong());	// ∞ﬂ¿Â
	m_aEquipUIList[5]->SetInfo(CStatMgr::Get_Instance()->Get_Cave());		// ∏¡≈‰
	m_aEquipUIList[6]->SetInfo(CStatMgr::Get_Instance()->Get_Glove());		// ¿Â∞©



	Update_Rect();

	return OBJ_NOEVENT;
}

void CEquip_UI::Late_Update(void)
{

}

void CEquip_UI::Render(HDC hDC)
{

	HDC		hMemDCFrame = CBmpMgr::Get_Instance()->Find_Image(L"EquipCon");


	// «¡∑π¿”
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


	for (int i = 0; i < 7; ++i)
	{
		m_aEquipUIList[i]->Render(hDC);
		// m_aEquipUIList[i]->ColRender(hDC);
	}

}

void CEquip_UI::ColRender(HDC hDC)
{
	Rectangle(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tRect.right),
		int(m_tRect.bottom));
}

void CEquip_UI::Release(void)
{
	for (int i = 0; i < 7; ++i)
		Safe_Delete(m_aEquipUIList[i]);
}