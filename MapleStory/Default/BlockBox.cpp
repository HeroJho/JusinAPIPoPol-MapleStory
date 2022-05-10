#include "stdafx.h"
#include "BlockBox.h"

#include "ScrollMgr.h"

CBlockBox::CBlockBox()
{
}

CBlockBox::~CBlockBox()
{
	Release();
}

void CBlockBox::Initialize(void)
{
	m_sTag = "Block";

	// 콜리젼 크기, 피봇 설정
	m_tInfo.fCCX = 50.f;
	m_tInfo.fCCY = 50.f;
	m_tColPivot.x = 0.f;
	m_tColPivot.y = 0.f;
	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 0.f;
	m_tInfo.fTCY = 0.f;

	m_fSpeed = 0.f;

	m_pOldLine = nullptr;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;
}

int CBlockBox::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;



	Update_Rect();

	return OBJ_NOEVENT;
}

void CBlockBox::Late_Update(void)
{
	// Update_Gravity();
}

void CBlockBox::Render(HDC hDC)
{

}

void CBlockBox::Release(void)
{

}

void CBlockBox::OnCollision(CObj* _pOther)
{

}