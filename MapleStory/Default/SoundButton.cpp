#include "stdafx.h"
#include "SoundButton.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "InvenMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "UIMgr.h"
#include "QuestMgr.h"
#include "SceneMgr.h"


CSoundButton::CSoundButton()
{

}

CSoundButton::~CSoundButton()
{
	Release();
}

void CSoundButton::Initialize(void)
{
	m_tInfo.fX = 9999.f;
	m_tInfo.fY = 9999.f;

	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 0.f;
	m_tInfo.fTCY = 0.f;

	m_tInfo.fCCX = 15.f;
	m_tInfo.fCCY = 15.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)0.f;
}

int CSoundButton::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	return OBJ_NOEVENT;
}
void CSoundButton::Late_Update(void)
{

}


void CSoundButton::Render(HDC hDC)
{
	Update_Rect();
}


void CSoundButton::OnCollision(CObj* _pOther)
{
	if (!CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		return;

	if (m_sTag == "BgmUpButton")
		CSceneMgr::Get_Instance()->IncreaseBgmSound();
	else if (m_sTag == "BgmDownButton")
		CSceneMgr::Get_Instance()->DecreaseBgmSound();
	else if (m_sTag == "EffectUpButton")
		CSceneMgr::Get_Instance()->IncreaseEffectSound();
	else if (m_sTag == "EffectDownButton")
		CSceneMgr::Get_Instance()->DecreaseEffectSound();

	else if (m_sTag == "DamageEffect_0")
		CUIMgr::Get_Instance()->Set_PomDamage(0);
	else if (m_sTag == "DamageEffect_1")
		CUIMgr::Get_Instance()->Set_PomDamage(1);
	else if (m_sTag == "DamageEffect_2")
		CUIMgr::Get_Instance()->Set_PomDamage(2);

	else if (m_sTag == "DamageSkin_0")
		CUIMgr::Get_Instance()->Set_DamageSkin(1);
	else if (m_sTag == "DamageSkin_1")
		CUIMgr::Get_Instance()->Set_DamageSkin(2);
	else if (m_sTag == "DamageSkin_2")
		CUIMgr::Get_Instance()->Set_DamageSkin(3);
	else if (m_sTag == "DamageSkin_3")
		CUIMgr::Get_Instance()->Set_DamageSkin(4);
}


void CSoundButton::ColRender(HDC hDC)
{
	Update_Rect();

	Rectangle(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tRect.right),
		int(m_tRect.bottom));
}

void CSoundButton::Release(void)
{

}


void CSoundButton::SetColBox(float fX, float fY)
{
	m_tInfo.fCCX = fX;
	m_tInfo.fCCY = fY;
}