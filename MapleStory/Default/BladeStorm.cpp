#include "stdafx.h"
#include "BladeStorm.h"
#include "AbstractFactory.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"

#include "BladeStormF.h"

CBladeStorm::CBladeStorm()
{
}

CBladeStorm::~CBladeStorm()
{
	Release();
}

void CBladeStorm::Initialize(void)
{
	CObj* pSkill = CAbstractFactory<CBladeStormF>::Create(m_tInfo.fCX, m_tInfo.fCY, "Skill");
	pSkill->Set_Target(this);
	((CBladeStormF*)pSkill)->SetHoldKey('A');
	CObjMgr::Get_Instance()->Add_Object(OBJ_SKILL, pSkill);


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/BladeStorm/BladeStormL.bmp", L"BladeStormL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/BladeStorm/BladeStormR.bmp", L"BladeStormR");
	Set_FrameKey(L"BladeStormL");
	m_bOnePlay = false;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 10;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 50.f;
	m_tFrame.dwTime = GetTickCount64();


	// 콜리젼 크기, 피봇 설정
	m_tInfo.fCCX = 500.f;
	m_tInfo.fCCY = 250.f;
	m_tColPivot.x = 0.f;
	m_tColPivot.y = -30.f;
	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 1000.f;
	m_tInfo.fTCY = 500.f;

	Set_Stat(0, 1);
	m_fSpeed = 0.f;

	m_bCanHit = false;
	m_CanHitCount = 0;
	m_CanHitMaxCount = 10.f;

	m_pOldLine = nullptr;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;

	m_fOldSkillTime = GetTickCount64();
	m_fSkillTime = 100.f;
	m_fDeleteTime = 5000.f;

	m_fHitTime = 500.f;
	m_fOldHitTime = GetTickCount64();

}

int CBladeStorm::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	if (!(CKeyMgr::Get_Instance()->Key_Pressing(m_cHoldKey)))
	{
		m_bDead = true;
	}

	if (m_fOldHitTime + m_fHitTime < GetTickCount64())
	{
		m_CanHitCount = 0;
		m_bCanHit = false;
		m_fOldHitTime = GetTickCount64();
	}


	m_tInfo.fX = m_pTarget->Get_Info().fX;
	m_tInfo.fY = m_pTarget->Get_Info().fY;


	if (m_pTarget->Get_Dir() == DIR_LEFT)
	{
		m_tColPivot.x = -300.f;
		m_tColPivot.y = -70.f;
		SetFrameDir(DIR_LEFT);
	}
	else
	{
		m_tColPivot.x = 300.f;
		m_tColPivot.y = -70.f;
		SetFrameDir(DIR_RIGHT);
	}


	//// 히트 시간
	//if (m_fOldSkillTime + m_fSkillTime < GetTickCount64() && !m_bJump)
	//{
	//	// m_bCanHit = true;
	//	m_bJump = true;
	//}
	// 소멸 시간
	if (m_fOldSkillTime + m_fDeleteTime < GetTickCount64())
	{
		m_bDead = true;
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CBladeStorm::Late_Update(void)
{
	if (!m_bStayPlay)
		Move_Frame();
}

void CBladeStorm::Render(HDC hDC)
{

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	int left = 0;
	if (m_pTarget->Get_Dir() == DIR_LEFT)
	{
		left = m_tTRect.left + iScrollX - 220;
	}
	else
	{
		left = m_tTRect.left + iScrollX + 220;
	}

	GdiTransparentBlt(hDC, 									// 복사 받을, 최종적으로 그림을 그릴 DC
		left,					// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tTRect.top - 80 + iScrollY),
		int(m_tInfo.fTCX),								// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fTCY),
		hMemDC,											// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fTCX,		// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fTCY,
		(int)m_tInfo.fTCX,								// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fTCY,
		RGB(255, 0, 255));								// 제거하고자 하는 색상
}

void CBladeStorm::Release(void)
{
}

void CBladeStorm::OnCollision(CObj* _pOther)
{
	if (m_bCanHit)
		return;
	if (m_CanHitCount > m_CanHitMaxCount)
		return;
	if (!_pOther->Get_CanHit())
		return;

	if (!m_pFirst)
		m_pFirst = _pOther;
	else if (m_pFirst == _pOther)
	{
		m_pFirst = nullptr;
		m_bCanHit = true;
		return;
	}

	++m_CanHitCount;

	if (_pOther->Get_Tag() == "Monster")
	{
		_pOther->OnHit(this);
	}
}


void CBladeStorm::SetFrameDir(DIRECTION _eDir)
{
	if (_eDir == DIR_LEFT)
		m_pFrameKey = L"BladeStormL";
	else
		m_pFrameKey = L"BladeStormR";

	m_eDir = _eDir;
}

void CBladeStorm::Motion_Change(void)
{

}
