#include "stdafx.h"
#include "MouseMgr.h"

#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "UIMgr.h"
#include "InvenMgr.h"
#include "AbstractFactory.h"
#include "Mouse.h"
#include "BmpMgr.h"

CMouseMgr* CMouseMgr::m_pInstance = nullptr;
CMouseMgr::CMouseMgr()
	: m_pMouse(nullptr)
{
}
CMouseMgr::~CMouseMgr()
{
	Release();
}

void CMouseMgr::Initialize(void)
{
	m_pMouse = CAbstractFactory<CMouse>::Create(390.f, 930.f, "Mouse");
}

void CMouseMgr::Render(HDC hDC)
{
	m_pMouse->Render(hDC);
}

int CMouseMgr::Update(void)
{
	m_pMouse->Update();
	return 0;
}

void CMouseMgr::Late_Update()
{
	// 付快胶 面倒贸府
	CCollisionMgr::Collision_RectEx(m_pMouse, CUIMgr::Get_Instance()->Get_InvenUI(), false);
	CCollisionMgr::Collision_RectEx(m_pMouse, CUIMgr::Get_Instance()->Get_SkillUI(), false);
	CCollisionMgr::Collision_RectEx(m_pMouse, CUIMgr::Get_Instance()->Get_StatUI(), false);
	CCollisionMgr::Collision_RectEx(m_pMouse, CUIMgr::Get_Instance()->Get_EquipUI(), false);
	CCollisionMgr::Collision_RectEx(m_pMouse, ((CCommunity_UI*)CUIMgr::Get_Instance()->Get_CommunityUI())->GetCommunityS(), false);
	CCollisionMgr::Collision_RectEx(m_pMouse, ((CDead_UI*)CUIMgr::Get_Instance()->Get_DeadUI())->GetCommunityS(), false);
	CCollisionMgr::CollisionInvenUI_RectEx(m_pMouse, ((CInven_UI*)CUIMgr::Get_Instance()->Get_InvenUI())->GetItemUIList(), false);
	CCollisionMgr::CollisionSkillUI_RectEx(m_pMouse, ((CSkill_UI*)CUIMgr::Get_Instance()->Get_SkillUI())->GetSkillUIList(), false);
	CCollisionMgr::CollisionSlotUI_RectEx(m_pMouse, ((CQSlot_UI*)CUIMgr::Get_Instance()->Get_SlotUI())->GetSlotUIList(), false);
	CCollisionMgr::CollisionShopUI_RectEx(m_pMouse, ((CShop_UI*)CUIMgr::Get_Instance()->Get_ShopUI())->GetShopUIList(), false);
	CCollisionMgr::CollisionStatUI_RectEx(m_pMouse, ((CStatUI*)CUIMgr::Get_Instance()->Get_StatUI())->GetStatUIList(), false);
	CCollisionMgr::CollisionSkillSButtonUI_RectEx(m_pMouse, ((CSkill_UI*)CUIMgr::Get_Instance()->Get_SkillUI())->GetSkillButtonUIList(), false);
	CCollisionMgr::CollisionInvenButtonUI_RectEx(m_pMouse, ((CInven_UI*)CUIMgr::Get_Instance()->Get_InvenUI())->GetInvenButton(), false);
	CCollisionMgr::CollisionEquipUI_RectEx(m_pMouse, ((CEquip_UI*)CUIMgr::Get_Instance()->Get_EquipUI())->GetEquipUIList(), false);
	CCollisionMgr::CollisionSoundUI_RectEx(m_pMouse, ((COption_UI*)CUIMgr::Get_Instance()->Get_OptionUI())->GetSoundButton(), false);

}

void CMouseMgr::Release(void)
{
	if (m_pMouse != nullptr)
		Safe_Delete(m_pMouse);
}
