#include "stdafx.h"
#include "CommunityS_UI.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "InvenMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "UIMgr.h"
#include "QuestMgr.h"


CCommunityS_UI::CCommunityS_UI()
	: m_sInfo{}
{

}

CCommunityS_UI::~CCommunityS_UI()
{
	Release();
}

void CCommunityS_UI::Initialize(void)
{
	m_tInfo.fX = 9999.f;
	m_tInfo.fY = 9999.f;

	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 30.f;
	m_tInfo.fTCY = 30.f;

	m_tInfo.fCCX = 40.f;
	m_tInfo.fCCY = 20.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)0.f;
}

int CCommunityS_UI::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	return OBJ_NOEVENT;
}
void CCommunityS_UI::Late_Update(void)
{

}


void CCommunityS_UI::Render(HDC hDC)
{
	Update_Rect();
}


void CCommunityS_UI::OnCollision(CObj* _pOther)
{
	if (!CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		return;

	if (m_sTag == "DeadButton")
	{
		((CPlayer*)CObjMgr::Get_Instance()->Get_Player())->ResetDead();
		CUIMgr::Get_Instance()->CloseDead();
		return;
	}

	if (_pOther->Get_Tag() == "Mouse")
	{
		CQuestMgr::Get_Instance()->AcceptQuest();
		CUIMgr::Get_Instance()->CloseCommunity();
	}

}


void CCommunityS_UI::ColRender(HDC hDC)
{
	Update_Rect();

	Rectangle(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tRect.right),
		int(m_tRect.bottom));
}

void CCommunityS_UI::Release(void)
{

}