#include "stdafx.h"
#include "Inven_UI.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "InvenMgr.h"
#include "SoundMgr.h"


CInven_UI::CInven_UI()
	: m_bIsOpen(false)
	, m_bChange(false)
{
}


CInven_UI::~CInven_UI()
{
	Release();
}

void CInven_UI::Initialize(void)
{
	m_sTag = "InvenUI";


	m_fRePosX = 800.f;
	m_fRePosY = 300.f;

	m_tInfo.fX = 9999.f;
	m_tInfo.fY = 9999.f;

	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 172.f;
	m_tInfo.fTCY = 335.f;


	m_tInfo.fCCX = 172.f;
	m_tInfo.fCCY = 40.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)-165.f;

	m_bIsOpen = false;


	for (int i = 0; i < 2; ++i)
	{
		m_pInvenButton_UI[i] = new CInvenButton_UI();
		m_pInvenButton_UI[i]->Initialize();
		m_pInvenButton_UI[i]->SetIndex(i);

		int x = i % 4;
		int y = i / 4;

		m_pInvenButton_UI[i]->Set_Pos(m_tInfo.fX - 59, m_tInfo.fY - 102);
	}


	for (int i = 0; i < 24; ++i)
	{
		m_aItemUIList[i] = new CItem_UI;
		m_aItemUIList[i]->Initialize();
		m_aItemUIList[i]->SetIndex(i);

		int x = i % 4;
		int y = i / 4;

		m_aItemUIList[i]->Set_Pos(m_tInfo.fX - 59 + (x * 36), m_tInfo.fY - 102 + (y * 35));
	}
}

int CInven_UI::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (CKeyMgr::Get_Instance()->Key_Down('I'))
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

	for (int i = 0; i < 24; ++i)
		m_aItemUIList[i]->GetInfo().InvenID = 100;

	if (!m_bChange)
	{
		// 소모창
		for (auto& sInfo : CInvenMgr::Get_Instance()->Get_InvenList())
		{
			for (int i = 0; i < 24; ++i)
			{
				int x = i % 4;
				int y = i / 4;
				m_aItemUIList[i]->Set_Pos(m_tInfo.fX - 59 + (x * 36), m_tInfo.fY - 102 + (y * 35));

				if (m_aItemUIList[i]->GetIndex() == sInfo->GetInfo().InvenID)
				{
					m_aItemUIList[i]->SetInfo(sInfo->GetInfo());
				}
			}
		}
	}
	else
	{
		// 장비창
		for (auto& sInfo : CInvenMgr::Get_Instance()->Get_EquipList())
		{
			for (int i = 0; i < 24; ++i)
			{
				int x = i % 4;
				int y = i / 4;
				m_aItemUIList[i]->Set_Pos(m_tInfo.fX - 59 + (x * 36), m_tInfo.fY - 102 + (y * 35));

				if (m_aItemUIList[i]->GetIndex() == sInfo->GetInfo().InvenID)
				{
					m_aItemUIList[i]->SetInfo(sInfo->GetInfo());
				}
			}
		}
	}

	for (int i = 0; i < 2; ++i)
	{
		m_pInvenButton_UI[i]->Set_Pos(m_tInfo.fX - 65 + (i * 34), m_tInfo.fY - 132);
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CInven_UI::Late_Update(void)
{

}

void CInven_UI::Render(HDC hDC)
{
	HDC		hMemDCFrame = nullptr;

	if(m_bChange)
		hMemDCFrame = CBmpMgr::Get_Instance()->Find_Image(L"Inventory_Equip");
	else
		hMemDCFrame = CBmpMgr::Get_Instance()->Find_Image(L"Inventory_Consum");
	

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
		RGB(0, 255, 0));

	// 돈 랜더
	int size = to_string(CInvenMgr::Get_Instance()->Get_Money()).size();
	LOGFONT m_labelFontInfo{};
	m_labelFontInfo.lfHeight = 13;
	m_labelFontInfo.lfWidth = 5;
	m_labelFontInfo.lfCharSet = HANGEUL_CHARSET;
	HFONT textFont, oldFont;
	textFont = CreateFontIndirect(&m_labelFontInfo);
	oldFont = (HFONT)SelectObject(hDC, textFont);

	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(0, 0, 0));
	TCHAR lpOut[1024];
	wsprintf(lpOut, TEXT("%d"), CInvenMgr::Get_Instance()->Get_Money());
	TextOut(hDC, m_tTRect.left + 115 - (size * 5), m_tTRect.top + 267, lpOut, lstrlen(lpOut));

	SelectObject(hDC, oldFont);
	DeleteObject(textFont);

	for (int i = 0; i < 24; ++i)
	{
		m_aItemUIList[i]->Render(hDC);
		//m_aItemUIList[i]->ColRender(hDC);
	}

	for (int i = 0; i < 2; ++i)
	{
		m_pInvenButton_UI[i]->Render(hDC);
		//m_pInvenButton_UI[i]->ColRender(hDC);
	}
}

void CInven_UI::ColRender(HDC hDC)
{
	Rectangle(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tRect.right),
		int(m_tRect.bottom));
}

void CInven_UI::Release(void)
{
	for (int i = 0; i < 24; ++i)
		Safe_Delete(m_aItemUIList[i]);

	for (int i = 0; i < 2; ++i)
		Safe_Delete(m_pInvenButton_UI[i]);
}