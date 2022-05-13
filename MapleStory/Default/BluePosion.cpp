#include "stdafx.h"
#include "BluePosion.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "InvenMgr.h"

CBluePosion::CBluePosion()
	: m_bEat(false)
	, m_bUpDown(false)
	, m_fOldUpTime(0.f)
	, m_fUpTime(0.f)
	, m_iMove(0)
{
}

CBluePosion::~CBluePosion()
{
	Release();
}

void CBluePosion::Initialize(void)
{
	m_sItemTag = "BluePosion";
	m_eID = IT_CONSUM;

	Set_FrameKey(L"BluePotion");
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = (DWORD)1000.f;
	m_tFrame.dwTime = (DWORD)GetTickCount64();


	// �ݸ��� ũ��, �Ǻ� ����
	m_tInfo.fCCX = 25.f;
	m_tInfo.fCCY = 25.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)-10.f;
	// �ؽ��� ũ�� ����
	m_tInfo.fTCX = 30.f;
	m_tInfo.fTCY = 30.f;

	m_fSpeed = 0.f;

	m_pOldLine = nullptr;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;

	m_bEat = false;

	m_fUpTime = 500.f;
	m_fOldUpTime = 0.f;

	m_iMove = 0.f;
	m_bUpDown = false;
}

int CBluePosion::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;



	Update_Rect();

	return OBJ_NOEVENT;
}

void CBluePosion::Late_Update(void)
{

	if (m_bEat)
	{
		if (m_fOldUpTime + m_fUpTime < GetTickCount64())
			Set_Dead();
		m_tInfo.fY -= 7.5f;

		float fPx = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX - m_tInfo.fX;
		if (fPx < -5.f)
			m_tInfo.fX -= 3.f;
		else if (fPx > 5.f)
			m_tInfo.fX += 3.f;

		Update_Gravity(true);
	}
	else
	{
		if (6.f < m_iMove)
			m_bUpDown = false;
		else if (0.f > m_iMove)
			m_bUpDown = true;

		if (m_bUpDown)
			m_iMove += 0.2f;
		else
			m_iMove -= 0.2f;

		Update_Gravity();
	}

	Move_Frame();
}

void CBluePosion::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 									// ���� ����, ���������� �׸��� �׸� DC
		int(m_tTRect.left + iScrollX),					// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tTRect.top - 15 + m_iMove + iScrollY),
		int(m_tInfo.fTCX),								// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fTCY),
		hMemDC,											// ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fTCX,		// ��Ʈ�� ��� ���� ��ǥ, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fTCY,
		(int)m_tInfo.fTCX,								// ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fTCY,
		RGB(255, 0, 255));								// �����ϰ��� �ϴ� ����
}

void CBluePosion::Release(void)
{
}



void CBluePosion::OnHit(CObj* _pOther)
{
	if (m_bEat)
		return;

	ITEM sInfo = CInvenMgr::Get_Instance()->MakeItemInfo(this);
	CInvenMgr::Get_Instance()->Add_Item(sInfo);

	m_bEat = true;
	m_fOldUpTime = (float)GetTickCount64();
}

void CBluePosion::OnCollision(CObj* _pOther)
{

}

