#include "stdafx.h"
#include "DamageGen.h"
#include "AbstractFactory.h"

#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "InvenMgr.h"
#include "Damge.h"
#include "PomDamage.h"
#include "Effect.h"
#include "EventMgr.h"
#include "SoundMgr.h"
#include "UIMgr.h"
#include "ScaleDamage.h"

CDamageGen::CDamageGen()
	: m_iHitCount(0)
	, m_iHitOldCount(0)
	, m_fHitTime(0.f)
	, m_fOldHitTime(0.f)
	, m_iStart(0)
	, m_iEnd(0)
	, m_fMeX(0.f)
	, m_fMeY(0.f)
	, m_fPivot(0.f)
	, m_fTempPivot(0.f)
	, m_fOlbTempPivot(0.f)
{
}

CDamageGen::~CDamageGen()
{
	Release();
}

void CDamageGen::Init(int _iHitCount, float _fHitTime, int _iStart, int _iEnd, float _fMeX, float _fMeY, float _fPivot, float _fTempPivot)
{
	m_iHitCount = _iHitCount;
	m_fHitTime = _fHitTime;
	m_iStart = _iStart;
	m_iEnd = _iEnd;
	m_fMeX = _fMeX;
	m_fMeY = _fMeY;
	m_fPivot = _fPivot;
	m_fTempPivot = _fTempPivot;
	m_fOldHitTime = 0.f;
}

void CDamageGen::Initialize(void)
{

	// 콜리젼 크기, 피봇 설정
	m_tInfo.fCCX = 25.f;
	m_tInfo.fCCY = 25.f;
	m_tColPivot.x = 0.f;
	m_tColPivot.y = -10.f;
	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 30.f;
	m_tInfo.fTCY = 30.f;

	m_fSpeed = 0.f;

	m_pOldLine = nullptr;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;

	m_fHitTime = GetTickCount64();
}

int CDamageGen::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_iHitOldCount > m_iHitCount)
	{
		m_bDead = true;
	}
	
	

	if (m_fOldHitTime + m_fHitTime < GetTickCount64())
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT1);
		CSoundMgr::Get_Instance()->PlaySound(L"Hit2.wav", SOUND_PEFFECT1, 1);

		int x = CEventMgr::Get_Instance()->GetRandomNum_Int(-10, 10);

		if (CUIMgr::Get_Instance()->Get_PomDamage() == 0)
		{
			CDamge* pDamage = (CDamge*)CAbstractFactory<CDamge>::Create(m_fMeX + x, m_fMeY - m_fPivot - m_fOlbTempPivot);
			pDamage->Init(m_iStart, m_iEnd, CUIMgr::Get_Instance()->Get_DamageSkin());
			CObjMgr::Get_Instance()->Add_Object(OBJ_SKILLE, pDamage);
		}
		else if (CUIMgr::Get_Instance()->Get_PomDamage() == 1)
		{
			CPomDamage*  pDamage = (CPomDamage*)CAbstractFactory<CPomDamage>::Create(m_fMeX + x, m_fMeY - m_fPivot - m_fOlbTempPivot);
			pDamage->Init(m_iStart, m_iEnd, CUIMgr::Get_Instance()->Get_DamageSkin());
			CObjMgr::Get_Instance()->Add_Object(OBJ_SKILLE, pDamage);
		}
		else if (CUIMgr::Get_Instance()->Get_PomDamage() == 2)
		{
			CScaleDamage* pDamage = (CScaleDamage*)CAbstractFactory<CScaleDamage>::Create(m_fMeX + x, m_fMeY - m_fPivot - m_fOlbTempPivot);
			pDamage->Init(m_iStart, m_iEnd, CUIMgr::Get_Instance()->Get_DamageSkin());
			CObjMgr::Get_Instance()->Add_Object(OBJ_SKILLE, pDamage);
		}



		x = CEventMgr::Get_Instance()->GetRandomNum_Int(-50, 50);
		int y = CEventMgr::Get_Instance()->GetRandomNum_Int(-50, 50);

		CEffect* pEffect = (CEffect*)CAbstractFactory<CEffect>::Create(m_fMeX + x, m_fMeY + y);
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, pEffect);


		++m_iHitOldCount;
		m_fOldHitTime = GetTickCount64();
		m_fOlbTempPivot += m_fTempPivot;
	}


	Update_Rect();

	return OBJ_NOEVENT;
}

void CDamageGen::Late_Update(void)
{

}

void CDamageGen::Render(HDC hDC)
{

}

void CDamageGen::Release(void)
{
}

