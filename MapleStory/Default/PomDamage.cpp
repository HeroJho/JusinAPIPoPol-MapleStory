#include "stdafx.h"
#include "PomDamage.h"

#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "InvenMgr.h"
#include "EventMgr.h"

CPomDamage::CPomDamage()
	: m_iStart(0)
	, m_iEnd(0)
	, m_fUpTime(0.f)
	, m_fOldUpTime(0.f)
{
}

CPomDamage::~CPomDamage()
{
	Release();
}

void CPomDamage::Init(int _iStart, int _iEnd, int _iDamageSkin)
{
	m_iStart = _iStart;
	m_iEnd = _iEnd;
	m_iCount = CEventMgr::Get_Instance()->GetRandomNum_Int(m_iStart, m_iEnd);
	m_sDamage = to_string(m_iCount);

	m_bJump = true;
	m_fJumpPower = 7.f;

	m_eDir = (DIRECTION)CEventMgr::Get_Instance()->GetRandomNum_Int(0,1);

	Update_Gravity();

	switch (_iDamageSkin)
	{
	case 1:
		m_pFrameKey = L"Damage";
		break;
	case 2:
		m_pFrameKey = L"Damage2";
		m_iDisX = 40;
		break;
	case 3:
		m_pFrameKey = L"Damage3";
		break;
	case 4:
		m_pFrameKey = L"Damage4";
		break;
	case 9:
		m_pFrameKey = L"Damaged";
		break;
	}
}

void CPomDamage::Initialize(void)
{
	Set_FrameKey(L"Damage");
	m_tFrame.iMotion = 0;
	m_iDisX = 28;
	// 콜리젼 크기, 피봇 설정
	m_tInfo.fCCX = 25.f;
	m_tInfo.fCCY = 25.f;
	m_tColPivot.x = 0.f;
	m_tColPivot.y = 0.f;
	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 50.f;
	m_tInfo.fTCY = 50.f;

	m_fSpeed = 0.f;

	m_pOldLine = nullptr;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;

	m_fOldUpTime = GetTickCount64();
	m_fUpTime = 1000.f;
}

int CPomDamage::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_eDir == DIR_LEFT)
		m_tInfo.fX -= 3.f;
	else
		m_tInfo.fX += 3.f;


	if (m_fOldUpTime + m_fUpTime < GetTickCount64())
	{
		m_bDead = true;
	}

	m_tInfo.fY -= 1.f;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CPomDamage::Late_Update(void)
{

	Update_Gravity(true);
	// Move_Frame();
}

void CPomDamage::Render(HDC hDC)
{
	int iShfX = 0;

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	if (m_pFrameKey != L"Damaged")
	{
		HDC		hMemCirlDC = CBmpMgr::Get_Instance()->Find_Image(L"Clri");

		GdiTransparentBlt(hDC,
			int(m_tTRect.left + iScrollX + iShfX - 25),
			int(m_tTRect.top + iScrollY - 25),
			70,
			70,
			hMemCirlDC,
			0,
			0,
			70,
			70,
			RGB(255, 0, 255));
	}


	for (int i = 0; i < m_sDamage.size(); ++i)
	{
		switch (m_sDamage[i])
		{
		case '0':
			m_tFrame.iFrameStart = 0;
			break;
		case '1':
			m_tFrame.iFrameStart = 1;
			break;
		case '2':
			m_tFrame.iFrameStart = 2;
			break;
		case '3':
			m_tFrame.iFrameStart = 3;
			break;
		case '4':
			m_tFrame.iFrameStart = 4;
			break;
		case '5':
			m_tFrame.iFrameStart = 5;
			break;
		case '6':
			m_tFrame.iFrameStart = 6;
			break;
		case '7':
			m_tFrame.iFrameStart = 7;
			break;
		case '8':
			m_tFrame.iFrameStart = 8;
			break;
		case '9':
			m_tFrame.iFrameStart = 9;
			break;
		}


		GdiTransparentBlt(hDC,
			int(m_tTRect.left + iScrollX + iShfX),
			int(m_tTRect.top + iScrollY),
			int(m_tInfo.fTCX),
			int(m_tInfo.fTCY),
			hMemDC,
			m_tFrame.iFrameStart * (int)m_tInfo.fTCX,
			m_tFrame.iMotion * (int)m_tInfo.fTCY,
			(int)m_tInfo.fTCX,
			(int)m_tInfo.fTCY,
			RGB(255, 0, 255));

		iShfX += m_iDisX;
		m_tFrame.iFrameStart++;
	}
}

void CPomDamage::Release(void)
{
}

