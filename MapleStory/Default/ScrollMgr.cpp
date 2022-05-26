#include "stdafx.h"
#include "ScrollMgr.h"

#include "SceneMgr.h"


CScrollMgr*	CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr()
	: m_pTarget(nullptr)
	, m_fScrollX(0.f)
	, m_fScrollY(0.f)
	, m_bMoveX(false)
	, m_bMoveY(false)
	, m_bShake(false)
	, m_bShakeTemp(0.f)
	, m_fShakeTime(0.f)
	, m_fShakeOldTime(0.f)
	, m_fShakeValue(0.f)
	, m_bShakeTurn(false)
{
	
}

CScrollMgr::~CScrollMgr()
{
}


void CScrollMgr::Initialize(void)
{
	// x, y�� ����

	if (!m_pTarget)
		return;

	m_fScrollX = -m_pTarget->Get_Info().fX + WINCX * 0.5f;
	m_fScrollY = -m_pTarget->Get_Info().fY + WINCY * 0.5f;

	int		iOffSetX = WINCX >> 1;
	int		iOffSetY = WINCY >> 1;
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
}

void CScrollMgr::Update(void)
{
	if (m_bShake)
		Shake();

	Nomal();
}


void CScrollMgr::StartShake(float _fShakeValue, float _fShakeSpeed, float _fTime , float _fATime)
{
	m_bShake = true;
	m_fShakeValue = _fShakeValue;
	
	m_bShakeTemp = 0.f;
	m_fShakeTime = _fTime;
	m_fShakeOldTime = GetTickCount64();

	m_fShakeSpeed = _fShakeSpeed;

	m_fATime = _fATime;
	m_fOldATime = GetTickCount64();
}

void CScrollMgr::Nomal()
{
	// target�� ���ٸ� 0, 0 ����
	if (!m_pTarget)
		return;

	//m_fScrollX = -m_pTarget->Get_Info().fX + WINCX * 0.5f;
	//m_fScrollY = -m_pTarget->Get_Info().fY + WINCY * 0.5f;


	int		iOffSetX = WINCX >> 1;
	int		iOffSetY = WINCY >> 1;
	int		iItvX = 200;
	int		iItvY = 100;
	if (iOffSetX - iItvX > m_pTarget->Get_Info().fX + m_fScrollX)
	{
		m_bMoveX = true;
	}
	else if (iOffSetX + iItvX < m_pTarget->Get_Info().fX + m_fScrollX)
	{
		m_bMoveX = true;
	}

	if (iOffSetY - iItvY > m_pTarget->Get_Info().fY + m_fScrollY)
	{
		m_bMoveY = true;
	}
	else if (iOffSetY + iItvY < m_pTarget->Get_Info().fY + m_fScrollY)
	{
		m_bMoveY = true;
	}

	if (m_bMoveX)
	{
		float disX = m_pTarget->Get_Info().fX + m_fScrollX - iOffSetX;

		if (disX > 3.f)
		{
			if (disX > 200.f)
				m_fScrollX += -6.f;
			else
				m_fScrollX += -3.f;
		}
		else if (disX < -3.f)
		{
			if (disX < -200.f)
				m_fScrollX += 6.f;
			else
				m_fScrollX += 3.f;
		}
		else
			m_bMoveX = false;
	}
	if (m_bMoveY)
	{
		float disY = m_pTarget->Get_Info().fY + m_fScrollY - iOffSetY;

		if (disY > 3.f)
		{
			if (disY > 200.f)
				m_fScrollY += -6.f;
			else
				m_fScrollY += -3.f;
		}
		else if (disY < -3.f)
		{
			if (disY < -200.f)
				m_fScrollY += 6.f;
			else
				m_fScrollY += 3.f;
		}
		else
			m_bMoveY = false;
	}


	CScene* pCurScene = CSceneMgr::Get_Instance()->Get_CurScene();
	if (pCurScene->Get_MapSize().left + m_fScrollX >= 0)
	{
		m_fScrollX = -pCurScene->Get_MapSize().left;
	}
	else if (pCurScene->Get_MapSize().right + m_fScrollX <= WINCX)
	{
		m_fScrollX = -pCurScene->Get_MapSize().right + WINCX;
	}
	if (pCurScene->Get_MapSize().top + m_fScrollY >= 0)
	{
		m_fScrollY = -pCurScene->Get_MapSize().top;
	}
	else if (pCurScene->Get_MapSize().bottom + m_fScrollY <= WINCY)
	{
		m_fScrollY = -pCurScene->Get_MapSize().bottom + WINCY;
	}

}

void CScrollMgr::Shake()
{
	if (m_fOldATime + m_fATime < GetTickCount64())
	{
		if (m_fShakeOldTime + m_fShakeTime < GetTickCount64())
		{
			m_bShake = false;
			return;
		}

		if (m_bShakeTemp > m_fShakeValue)
		{
			m_bShakeTurn = false;

		}
		else if (m_bShakeTemp < -m_fShakeValue)
		{
			m_bShakeTurn = true;
		}

		if (m_bShakeTurn)
		{
			m_bShakeTemp += m_fShakeSpeed;
			m_fScrollX += 10.f;
			m_fScrollY += 10.f;
		}
		else
		{
			m_bShakeTemp -= m_fShakeSpeed;
			m_fScrollX -= 10.f;
			m_fScrollY -= 10.f;
		}


	}
	else
		m_fShakeOldTime = GetTickCount64();



}

