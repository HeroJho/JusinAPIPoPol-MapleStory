#include "stdafx.h"
#include "Mouse.h"

#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "Item_UI.h"
#include "InvenMgr.h"
#include "SkillS_UI.h"
#include "SlotMgr.h"
#include "QSlotTemp_UI.h"
#include "SoundMgr.h"
#include "SkillMgr.h"
#include "Inven_UI.h"
#include "UIMgr.h"
#include "StatMgr.h"


CMouse::CMouse()
	: m_sInfo{}
{
}

CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize(void)
{
	m_sTag = "Mouse";

	Set_FrameKey(L"Cursor");
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = (DWORD)1000.f;
	m_tFrame.dwTime = (DWORD)GetTickCount64();

	m_tInfo.fCCX = 10.f;
	m_tInfo.fCCY = 10.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)0.f;
	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 32.f;
	m_tInfo.fTCY = 32.f;

}

int CMouse::Update(void)
{
	if (m_eState == HOLD && CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON) || CKeyMgr::Get_Instance()->Key_Pressing(VK_RBUTTON))
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_MOUSE);
		CSoundMgr::Get_Instance()->PlaySound(L"DragEnd.wav", SOUND_MOUSE, 1);

		m_tFrame.iMotion = 2;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON) || CKeyMgr::Get_Instance()->Key_Pressing(VK_RBUTTON))
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_MOUSE);
		CSoundMgr::Get_Instance()->PlaySound(L"BtMouseClick.wav", SOUND_MOUSE, 1);

		m_eState = PICK;
		m_tFrame.iMotion = 1;
	}




	POINT	pt{};

	GetCursorPos(&pt);	// 현재 마우스의 위치 좌표를 얻어오는 함수
	ScreenToClient(g_hWnd, &pt);	// 전체 스크린영역에서 생성한 클라이언트(창) 좌표로 변환

	m_tInfo.fX = (float)pt.x;
	m_tInfo.fY = (float)pt.y;

	Update_Rect();
	ShowCursor(false);		// 마우스 커서를 출력하지 않겠다.

	return OBJ_NOEVENT;
}

void CMouse::Late_Update(void)
{


}

void CMouse::Render(HDC hDC)
{
	HDC		hMemItemDC = nullptr;
	int xC = 0;
	int yC = 0;
	int iItemKey = 0;
	if (m_sInfo.InvenID != 100)
	{
		if (m_sInfo.sTag == "RedPosion")
		{
			hMemItemDC = CBmpMgr::Get_Instance()->Find_Image(L"RedPotion");
			iItemKey = 0;
		}
		else if (m_sInfo.sTag == "BluePosion")
		{
			hMemItemDC = CBmpMgr::Get_Instance()->Find_Image(L"BluePotion");
			iItemKey = 0;
		}
		else if (m_sInfo.sTag == "Weapon")
		{
			hMemItemDC = CBmpMgr::Get_Instance()->Find_Image(L"Equip");
			iItemKey = 0;
			xC = 10;
			yC = 10;
		}
		else if (m_sInfo.sTag == "Shute")
		{
			hMemItemDC = CBmpMgr::Get_Instance()->Find_Image(L"Equip");
			iItemKey = 1;
			xC = 10;
			yC = 10;
		}
		else if (m_sInfo.sTag == "Shose")
		{
			hMemItemDC = CBmpMgr::Get_Instance()->Find_Image(L"Equip");
			iItemKey = 2;
			xC = 10;
			yC = 10;
		}
		else if (m_sInfo.sTag == "Gyenjong")
		{
			hMemItemDC = CBmpMgr::Get_Instance()->Find_Image(L"Equip");
			iItemKey = 3;
			xC = 10;
			yC = 10;
		}
		else if (m_sInfo.sTag == "Cave")
		{
			hMemItemDC = CBmpMgr::Get_Instance()->Find_Image(L"Equip");
			iItemKey = 5;
			xC = 10;
			yC = 10;
		}
		else if (m_sInfo.sTag == "Het")
		{
			hMemItemDC = CBmpMgr::Get_Instance()->Find_Image(L"Equip");
			iItemKey = 6;
			xC = 10;
			yC = 10;
		}
		else if (m_sInfo.sTag == "Glove")
		{
			hMemItemDC = CBmpMgr::Get_Instance()->Find_Image(L"Equip");
			iItemKey = 7;
			xC = 10;
			yC = 10;
		}
		else if (m_sInfo.sTag == "Skill_1")
		{
			hMemItemDC = CBmpMgr::Get_Instance()->Find_Image(L"Skill1_Icon");
			iItemKey = 0;
			xC = 2;
			yC = 2;
		}
		else if (m_sInfo.sTag == "Skill_2")
		{
			hMemItemDC = CBmpMgr::Get_Instance()->Find_Image(L"Skill2_Icon");
			iItemKey = 0;
			xC = 2;
			yC = 2;
		}
		else if (m_sInfo.sTag == "Skill_3")
		{
			hMemItemDC = CBmpMgr::Get_Instance()->Find_Image(L"Skill3_Icon");
			iItemKey = 0;
			xC = 2;
			yC = 2;
		}
		else if (m_sInfo.sTag == "Skill_4")
		{
			hMemItemDC = CBmpMgr::Get_Instance()->Find_Image(L"Skill4_Icon");
			iItemKey = 0;
			xC = 2;
			yC = 2;
		}

	}


	if (hMemItemDC)
	{
		GdiTransparentBlt(hDC,
			int(m_tTRect.left),
			int(m_tTRect.top),
			int(30) + xC,
			int(30) + yC,
			hMemItemDC,
			iItemKey * ((int)30 + xC),
			0,
			(int)30 + xC,
			(int)30 + yC,
			RGB(255, 0, 255));
	}


	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tInfo.fTCX),
		int(m_tInfo.fTCY),
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tInfo.fTCX,
		m_tFrame.iMotion * (int)m_tInfo.fTCY,
		(int)m_tInfo.fTCX,
		(int)m_tInfo.fTCY,
		RGB(255, 0, 255));



	//// TEST: 마우스 좌표 표시
	//int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//int iRealPosX = int(m_tInfo.fX - iScrollX);
	//int iRealPosY = int(m_tInfo.fY - iScrollY);
	//TCHAR lpOut[1024];
	//wsprintf(lpOut, TEXT("lX: %d \nY: %d"), iRealPosX, iRealPosY);
	//TextOut(hDC, 35, 15, lpOut, lstrlen(lpOut));


	if (!(m_eState == HOLD && CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON) || CKeyMgr::Get_Instance()->Key_Pressing(VK_RBUTTON)))
	{
		if (m_eState != HOLD)
			m_sInfo.InvenID = 100;
		m_eState = IDLE;
		m_tFrame.iMotion = 0;
		m_sInfo.SlotIdex = 99;
	}
}

void CMouse::Release(void)
{

}

void CMouse::OnCollision(CObj* _pOther)
{

	if (!CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
	{
		if (m_sInfo.InvenID == 100)
			return;

		if (_pOther->Get_Tag() == "Item_UI")
		{
			if(!((CInven_UI*)CUIMgr::Get_Instance()->Get_InvenUI())->GetChange())
				CInvenMgr::Get_Instance()->ChangeSlot(m_sInfo.InvenID, ((CItem_UI*)_pOther)->GetIndex());
			else if(((CInven_UI*)CUIMgr::Get_Instance()->Get_InvenUI())->GetChange())
				CInvenMgr::Get_Instance()->ChangeEquipSlot(m_sInfo.InvenID, ((CItem_UI*)_pOther)->GetIndex());
		}
		else if (_pOther->Get_Tag() == "Slot_UI")
		{
			if (!((CInven_UI*)CUIMgr::Get_Instance()->Get_InvenUI())->GetChange() || m_sInfo.eID == IT_SKILL)
				CSlotMgr::Get_Instance()->SetSlotInfo(m_sInfo, ((CQSlotTemp_UI*)_pOther)->GetIndex());
		}
		else if (_pOther->Get_Tag() == "EquipS_UI")
		{
			if (((CInven_UI*)CUIMgr::Get_Instance()->Get_InvenUI())->GetChange())
				SetItem(_pOther);
		}
			
	}


	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
	{
		if (m_sInfo.InvenID != 100)
			return;

		if (_pOther->Get_Tag() == "InvenUI")
		{
			m_eState = HOLD;
			_pOther->Set_Pos(m_tInfo.fX, m_tInfo.fY + 155);
		}
		else if (_pOther->Get_Tag() == "SkillUI")
		{
			m_eState = HOLD;
			_pOther->Set_Pos(m_tInfo.fX, m_tInfo.fY + 145);
		}
		else if (_pOther->Get_Tag() == "StatUI")
		{
			m_eState = HOLD;
			_pOther->Set_Pos(m_tInfo.fX, m_tInfo.fY + 145);
		}
		else if (_pOther->Get_Tag() == "EquipUI")
		{
			m_eState = HOLD;
			_pOther->Set_Pos(m_tInfo.fX, m_tInfo.fY + 145);
		}
		else if (_pOther->Get_Tag() == "Item_UI")
		{
			if (((CItem_UI*)_pOther)->GetInfo().eID == IT_CONSUM || ((CItem_UI*)_pOther)->GetInfo().eID == IT_EQUIT)
			{
				m_eState = HOLD;
				m_sInfo = ((CItem_UI*)_pOther)->GetInfo();
			}
		}
		else if (_pOther->Get_Tag() == "Skill_UI")
		{
			if (((CSkillS_UI*)_pOther)->GetInfo().sTag == "Skill_1"
				|| ((CSkillS_UI*)_pOther)->GetInfo().sTag == "Skill_2"
				|| ((CSkillS_UI*)_pOther)->GetInfo().sTag == "Skill_3"
				|| ((CSkillS_UI*)_pOther)->GetInfo().sTag == "Skill_4")
			{
				if (((CSkillS_UI*)_pOther)->GetInfo().sTag == "Skill_1" && CSkillMgr::Get_Instance()->GetSkillLevel1() == 0)
					return;
				else if (((CSkillS_UI*)_pOther)->GetInfo().sTag == "Skill_2" && CSkillMgr::Get_Instance()->GetSkillLevel2() == 0)
					return;
				else if (((CSkillS_UI*)_pOther)->GetInfo().sTag == "Skill_3" && CSkillMgr::Get_Instance()->GetSkillLevel3() == 0)
					return;
				else if (((CSkillS_UI*)_pOther)->GetInfo().sTag == "Skill_4" && CSkillMgr::Get_Instance()->GetSkillLevel4() == 0)
					return;

				m_eState = HOLD;
				m_sInfo = ((CSkillS_UI*)_pOther)->GetInfo();
			}
		}
		else if (_pOther->Get_Tag() == "Slot_UI")
		{
			m_eState = HOLD;
			m_sInfo = ((CQSlotTemp_UI*)_pOther)->GetInfo();
			m_sInfo.SlotIdex = ((CQSlotTemp_UI*)_pOther)->GetIndex();
		}

	}

}

void CMouse::SetItem(CObj* _pOther)
{
	int iIndex = ((CEquipS_UI*)_pOther)->GetIndex();
	switch (iIndex)
	{
	case 0:
		CStatMgr::Get_Instance()->Set_Het(m_sInfo);
		break;
	case 1:
		CStatMgr::Get_Instance()->Set_Weapon(m_sInfo);
		break;
	case 2:
		CStatMgr::Get_Instance()->Set_Shute(m_sInfo);
		break;
	case 3:
		CStatMgr::Get_Instance()->Set_Shose(m_sInfo);
		break;
	case 4:
		CStatMgr::Get_Instance()->Set_Gyenjong(m_sInfo);
		break;
	case 5:
		CStatMgr::Get_Instance()->Set_Cave(m_sInfo);
		break;
	case 6:
		CStatMgr::Get_Instance()->Set_Glove(m_sInfo);
		break;
	}
	
}
