#include "stdafx.h"
#include "ScrollMgr.h"

#include "SceneMgr.h"


CScrollMgr*	CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr()
	: m_pTarget(nullptr)
	, m_fScrollX(0.f)
	, m_fScrollY(0.f)
{
	
}

CScrollMgr::~CScrollMgr()
{
}


void CScrollMgr::Update()
{
	// target이 없다면 0, 0 고정
	if (!m_pTarget)
		return;

	m_fScrollX = -m_pTarget->Get_Info().fX + WINCX * 0.5f;
	m_fScrollY = -m_pTarget->Get_Info().fY + WINCY * 0.5f;


	int		iOffSetX = WINCX >> 1;
	int		iOffSetY = WINCY >> 1;

	// x, y축 고정
	CScene* pCurScene = CSceneMgr::Get_Instance()->Get_CurScene();
	if (pCurScene->Get_MapSize().left >= m_pTarget->Get_Info().fX - iOffSetX)
	{
		m_fScrollX = -pCurScene->Get_MapSize().left;
	}
	else if (pCurScene->Get_MapSize().right <= m_pTarget->Get_Info().fX + iOffSetX)
	{
		m_fScrollX = -pCurScene->Get_MapSize().right + WINCX;
	}
	if (pCurScene->Get_MapSize().top >= m_pTarget->Get_Info().fY - iOffSetY)
	{
		m_fScrollY = -pCurScene->Get_MapSize().top;
	}
	else if (pCurScene->Get_MapSize().bottom <= m_pTarget->Get_Info().fY + iOffSetY)
	{
		m_fScrollY = -pCurScene->Get_MapSize().bottom + WINCY;
	}



	//int		iItvX = 30;
	//int		iItvY = 20;
	//if (iOffSetX - iItvX > m_tInfo.fX + iScrollX)
	//	CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	//if (iOffSetX + iItvX < m_tInfo.fX + iScrollX)
	//	CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

	//if (iOffSetY - iItvY > m_tInfo.fY + iScrollY)
	//	CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

	//if (iOffSetY + iItvY < m_tInfo.fY + iScrollY)
	//	CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);
}
