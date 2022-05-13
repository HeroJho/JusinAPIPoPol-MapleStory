#include "stdafx.h"
#include "MouseMgr.h"

#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "UIMgr.h"
#include "InvenMgr.h"
#include "AbstractFactory.h"
#include "Mouse.h"

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
	CCollisionMgr::Collision_RectEx(m_pMouse, CUIMgr::Get_Instance()->Get_InvenUI(), false);
	CCollisionMgr::Collision_RectEx(m_pMouse, CInvenMgr::Get_Instance()->Get_InvenList(), false);
}

void CMouseMgr::Release(void)
{
	if (m_pMouse != nullptr)
		Safe_Delete(m_pMouse);
}
