#include "stdafx.h"
#include "UIMgr.h"

#include "ObjMgr.h"

#include "HpHp_UI.h"


CUIMgr* CUIMgr::m_pInstance = nullptr;
CUIMgr::CUIMgr()
	: m_pHpHpUI(nullptr)
{

}

CUIMgr::~CUIMgr()
{
	Release();
}

void CUIMgr::Initialize(void)
{
	if (!m_pHpHpUI)
	{
		m_pHpHpUI = new CHpHp_UI;
		m_pHpHpUI->Initialize();
	}
	ChangePlayerHp(CObjMgr::Get_Instance()->Get_Player()->Get_Stat().iHp, CObjMgr::Get_Instance()->Get_Player()->Get_Stat().iMaxHp);

}

void CUIMgr::Update(void)
{
	m_pHpHpUI->Update();
}

void CUIMgr::Render(HDC hDC)
{
	m_pHpHpUI->Render(hDC);
}

void CUIMgr::Release(void)
{
	if (m_pHpHpUI != nullptr)
		Safe_Delete(m_pHpHpUI);
}

void CUIMgr::ChangePlayerHp(int _iHp, int _iMaxHp)
{
	float fP = _iHp / (float)_iMaxHp;

	if (fP < 0.f)
		fP = 0.f;

	m_pHpHpUI->SetP(fP);

}
