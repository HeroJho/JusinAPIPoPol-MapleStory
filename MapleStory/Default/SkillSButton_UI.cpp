#include "stdafx.h"
#include "SkillSButton_UI.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "InvenMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "SkillMgr.h"


CSkillSButton_UI::CSkillSButton_UI()
{

}

CSkillSButton_UI::~CSkillSButton_UI()
{
	Release();
}

void CSkillSButton_UI::Initialize(void)
{
	m_sTag = "SkillSButton_UI";
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

int CSkillSButton_UI::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (!CStatMgr::Get_Instance()->GetSkillPoint())
		m_tFrame.iFrameStart = 2;

	return OBJ_NOEVENT;
}
void CSkillSButton_UI::Late_Update(void)
{

}


void CSkillSButton_UI::Render(HDC hDC)
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

	switch (m_iIndex)
	{
	case 0:
		if (CSkillMgr::Get_Instance()->GetSkillLevel1() == 5)
			m_tFrame.iFrameStart = 2;
		break;
	case 1:
		if (CSkillMgr::Get_Instance()->GetSkillLevel2() == 5)
			m_tFrame.iFrameStart = 2;
		break;
	case 2:
		if (CSkillMgr::Get_Instance()->GetSkillLevel3() == 5)
			m_tFrame.iFrameStart = 2;
		break;
	case 3:
		if (CSkillMgr::Get_Instance()->GetSkillLevel4() == 5)
			m_tFrame.iFrameStart = 2;
		break;
	}
	
}


void CSkillSButton_UI::OnCollision(CObj* _pOther)
{
	if (!CStatMgr::Get_Instance()->GetSkillPoint())
		return;


	switch (m_iIndex)
	{
	case 0:
		if (CSkillMgr::Get_Instance()->GetSkillLevel1() != 5)
			m_tFrame.iFrameStart = 1;
		break;
	case 1:
		if (CSkillMgr::Get_Instance()->GetSkillLevel2() != 5)
			m_tFrame.iFrameStart = 1;
		break;
	case 2:
		if (CSkillMgr::Get_Instance()->GetSkillLevel3() != 5)
			m_tFrame.iFrameStart = 1;
		break;
	case 3:
		if (CSkillMgr::Get_Instance()->GetSkillLevel4() != 5)
			m_tFrame.iFrameStart = 1;
		break;
	}


	if (!CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		return;

	if (_pOther->Get_Tag() == "Mouse")
	{
		switch (m_iIndex)
		{
		case 0:
			if (CSkillMgr::Get_Instance()->GetSkillLevel1() < 5)
				CStatMgr::Get_Instance()->Increase_Skill_1();
			break;
		case 1:
			if (CSkillMgr::Get_Instance()->GetSkillLevel2() < 5)
				CStatMgr::Get_Instance()->Increase_Skill_2();
			break;
		case 2:
			if (CSkillMgr::Get_Instance()->GetSkillLevel3() < 5)
				CStatMgr::Get_Instance()->Increase_Skill_3();
			break;
		case 3:
			if (CSkillMgr::Get_Instance()->GetSkillLevel4() < 5)
				CStatMgr::Get_Instance()->Increase_Skill_4();
			break;
		}
	}

}


void CSkillSButton_UI::ColRender(HDC hDC)
{
	Update_Rect();

	Rectangle(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tRect.right),
		int(m_tRect.bottom));
}

void CSkillSButton_UI::Release(void)
{

}