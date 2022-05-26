#include "stdafx.h"
#include "MiniMap_1.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "InvenMgr.h"
#include "QuestMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"


CMiniMap_1::CMiniMap_1()
	: m_bIsOpen(false)
{
}

CMiniMap_1::~CMiniMap_1()
{
	Release();
}


void CMiniMap_1::Initialize(void)
{
	m_sTag = "MiniMap_1";


	m_tInfo.fX = 9999.f;
	m_tInfo.fY = 9999.f;

	// �ؽ��� ũ�� ����
	m_tInfo.fTCX = 159.f;
	m_tInfo.fTCY = 153.f;


	m_tInfo.fCCX = 0.f;
	m_tInfo.fCCY = 0.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)0.f;

	m_tInfo.fX = m_tInfo.fTCX * 0.5f;
	m_tInfo.fY = m_tInfo.fTCY * 0.5f;
	m_bIsOpen = true;
}

int CMiniMap_1::Update(void)
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

void CMiniMap_1::Late_Update(void)
{

}

void CMiniMap_1::Render(HDC hDC)
{

	HDC		hMemDCFrame = CBmpMgr::Get_Instance()->Find_Image(L"MiniMap_1");

	// ������
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
	float fDisX = fMapX / 139;
	float fDisY = fMapY / 79;
	INFO pPlayerPos = CObjMgr::Get_Instance()->Get_Player()->Get_Info();


	GdiTransparentBlt(hDC,
		int(m_tTRect.left + pPlayerPos.fX / fDisX) + 6,
		int(m_tTRect.top + pPlayerPos.fY / fDisY) + 50,
		10,
		10,
		hMemDCFrame,
		0,
		0,
		10,
		10,
		RGB(255, 0, 255));
}


void CMiniMap_1::ColRender(HDC hDC)
{
	Rectangle(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tRect.right),
		int(m_tRect.bottom));
}

void CMiniMap_1::Release(void)
{
}