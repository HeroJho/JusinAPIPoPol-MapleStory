#include "stdafx.h"
#include "UIMgr.h"

#include "ObjMgr.h"

#include "HpHp_UI.h"


CUIMgr* CUIMgr::m_pInstance = nullptr;
CUIMgr::CUIMgr()
	: m_pHpHpUI(nullptr)
	, m_pInven(nullptr)
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
	if (!m_pInven)
	{
		m_pInven = new CInven_UI;
		m_pInven->Initialize();
	}


	ChangePlayerHp(CObjMgr::Get_Instance()->Get_Player()->Get_Stat().iHp, CObjMgr::Get_Instance()->Get_Player()->Get_Stat().iMaxHp);
	ChangePlayerMp(CObjMgr::Get_Instance()->Get_Player()->Get_Stat().iMp, CObjMgr::Get_Instance()->Get_Player()->Get_Stat().iMaxMp);
	ChangePlayerExp(CObjMgr::Get_Instance()->Get_Player()->Get_Stat().iExp, CObjMgr::Get_Instance()->Get_Player()->Get_Stat().iMaxExp);

}

void CUIMgr::Update(void)
{
	m_pHpHpUI->Update();
	m_pInven->Update();
}

void CUIMgr::Render(HDC hDC)
{
	m_pHpHpUI->Render(hDC);
	m_pInven->Render(hDC);

	//m_pInven->ColRender(hDC);
}



void CUIMgr::ChangePlayerHp(int _iHp, int _iMaxHp)
{
	float fP = _iHp / (float)_iMaxHp;

	if (fP < 0.f)
		fP = 0.f;

	m_pHpHpUI->SetPH(fP);
}

void CUIMgr::ChangePlayerMp(int _iMp, int _iMaxMp)
{
	float fP = _iMp / (float)_iMaxMp;

	if (fP < 0.f)
		fP = 0.f;

	m_pHpHpUI->SetPM(fP);
}

void CUIMgr::ChangePlayerExp(int _iExp, int _iMaxExp)
{
	float fP = _iExp / (float)_iMaxExp;

	if (fP < 0.f)
		fP = 0.f;

	m_pHpHpUI->SetPE(fP);
}





void CUIMgr::Release(void)
{
	if (m_pHpHpUI != nullptr)
		Safe_Delete(m_pHpHpUI);
	if (m_pInven != nullptr)
		Safe_Delete(m_pInven);
}

