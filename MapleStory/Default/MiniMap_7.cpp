#include "stdafx.h"
#include "MiniMap_7.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "InvenMgr.h"
#include "QuestMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"


CMiniMap_7::CMiniMap_7()
	: m_bIsOpen(false)
{
}

CMiniMap_7::~CMiniMap_7()
{
	Release();
}


void CMiniMap_7::Initialize(void)
{
	m_sTag = "MiniMap_2";


	m_tInfo.fX = 9999.f;
	m_tInfo.fY = 9999.f;

	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 224.f;
	m_tInfo.fTCY = 205.f;


	m_tInfo.fCCX = 0.f;
	m_tInfo.fCCY = 0.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)0.f;

	m_tInfo.fX = m_tInfo.fTCX * 0.5f;
	m_tInfo.fY = m_tInfo.fTCY * 0.5f;
	m_bIsOpen = true;
}

int CMiniMap_7::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (CKeyMgr::Get_Instance()->Key_Down('N'))
	{
		if (!m_bIsOpen)
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_UI);
			CSoundMgr::Get_Instance()->PlaySound(L"MenuUp.wav", SOUND_UI, 1);

			m_tInfo.fX = m_tInfo.fTCX * 0.5f;
			m_tInfo.fY = m_tInfo.fTCY * 0.5f;
			m_bIsOpen = true;
		}
		else
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_UI);
			CSoundMgr::Get_Instance()->PlaySound(L"MenuDown.wav", SOUND_UI, 1);

			m_tInfo.fX = 9999.f;
			m_tInfo.fY = 9999.f;
			m_bIsOpen = false;
		}
	}


	Update_Rect();

	return OBJ_NOEVENT;
}

void CMiniMap_7::Late_Update(void)
{

}

void CMiniMap_7::Render(HDC hDC)
{

	HDC		hMemDCFrame = CBmpMgr::Get_Instance()->Find_Image(L"MiniMap_7");

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
		RGB(255, 0, 255));


	hMemDCFrame = CBmpMgr::Get_Instance()->Find_Image(L"MiniPlayer");
	float fMapX = CSceneMgr::Get_Instance()->Get_CurScene()->Get_MapSize().right;
	float fMapY = CSceneMgr::Get_Instance()->Get_CurScene()->Get_MapSize().bottom;
	float fDisX = fMapX / 170;
	float fDisY = fMapY / 102;
	INFO pPlayerPos = CObjMgr::Get_Instance()->Get_Player()->Get_Info();


	GdiTransparentBlt(hDC,
		int(m_tTRect.left + pPlayerPos.fX / fDisX) + 20,
		int(m_tTRect.top + pPlayerPos.fY / fDisY) + 85,
		10,
		10,
		hMemDCFrame,
		0,
		0,
		10,
		10,
		RGB(255, 0, 255));
}


void CMiniMap_7::ColRender(HDC hDC)
{
	Rectangle(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tRect.right),
		int(m_tRect.bottom));
}

void CMiniMap_7::Release(void)
{
}