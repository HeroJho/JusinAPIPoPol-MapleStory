#include "stdafx.h"
#include "Obj.h"

#include "ScrollMgr.h"
#include "SceneMgr.h"

CObj::CObj()
	: m_fSpeed(0.f)
	, m_eDir(DIR_END)
	, m_bDead(false)
	, m_bOnePlay(false)
	, m_bStayPlay(false)
	, m_bCanHit(true)
	, m_fAngle(0.f)
	, m_pFrameKey(nullptr)
{
	ZeroMemory(&m_tStat, sizeof(STAT));
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tColPivot, sizeof(POINT));

	m_fJumpPower = 10.f;
}

CObj::~CObj()
{
}

void CObj::Set_Stat(int _iMaxHp, int _iAt)
{
	m_tStat.iHp = _iMaxHp;
	m_tStat.iMaxHp = _iMaxHp;
	m_tStat.iAt = _iAt;
	m_tStat.iExp = 0;
}

void CObj::Update_Rect(void)
{
	m_tRect.left   = LONG(m_tInfo.fCX - (m_tInfo.fCCX * 0.5f));
	m_tRect.top    = LONG(m_tInfo.fCY - (m_tInfo.fCCY * 0.5f));
 	m_tRect.right  = LONG(m_tInfo.fCX + (m_tInfo.fCCX * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.fCY + (m_tInfo.fCCY * 0.5f));

	m_tTRect.left	= LONG(m_tInfo.fX - (m_tInfo.fTCX * 0.5f));
	m_tTRect.top	= LONG(m_tInfo.fY - (m_tInfo.fTCY * 0.5f));
	m_tTRect.right	= LONG(m_tInfo.fX + (m_tInfo.fTCX * 0.5f));
	m_tTRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fTCY * 0.5f));

	// 콜라이더 위치
	m_tInfo.fCX = float(m_tInfo.fX + m_tColPivot.x);
	m_tInfo.fCY = float(m_tInfo.fY + m_tColPivot.y);

	// 맵 벗어낫는지
	CScene* pCurScene = CSceneMgr::Get_Instance()->Get_CurScene();
	RECT fRect = pCurScene->Get_MapSize();
	if (m_tRect.left < fRect.left)
		m_tInfo.fX += m_fSpeed;
	else if (m_tRect.right > fRect.right)
		m_tInfo.fX -= m_fSpeed;

}

void CObj::Update_Gravity(void)
{
	// 1. 라인을 얻어온다.
	float		LinefY = 0.f;

	CLine* m_pCurLine = m_pCurLine = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &LinefY);

	// 3. 공중 여부에 따라 중력 적용한다.
	if (m_bOnAir)
	{
		// m_fAirTime += 0.2f;

		m_fValY += 0.4f;

		// m_tInfo.fY -= m_fJumpPower * m_fAirTime - 1.f * m_fAirTime * m_fAirTime * 0.5f;
		m_tInfo.fY += m_fValY;
	}

	if (m_bJump)
	{
		m_tInfo.fY -= m_fJumpPower;
	}

	// 2. 공중인지 아닌지 판단한다.
	if (LinefY <= m_tInfo.fY)
	{	// 바닥일 때
		m_tInfo.fY = LinefY;
		m_bOnAir = false;
		m_fValY = 0.f;
	}
	else if (LinefY > m_tInfo.fY)
	{	// 공중일 때
		// 이전 라인이랑 같고,           대각선일때
		if (!(m_pOldLine == m_pCurLine && m_pCurLine->Get_Diagonal()))
			m_bOnAir = true;
	}

	if (!m_bOnAir)
	{
		m_tInfo.fY = LinefY;
		m_bJump = false;
	}

	m_pOldLine = m_pCurLine;
}

void CObj::Move_Frame(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		m_tFrame.iFrameStart++;

		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameStart = 0;

			if (m_bOnePlay)
			{
				OnePlayEnd();
				m_bOnePlay = false;
				m_bStayPlay = true;
			}
		}
			
	}

}

void CObj::ColRender(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	Rectangle(hDC, 									    
		int(m_tRect.left + iScrollX),					
		int(m_tRect.top + iScrollY),
		int(m_tRect.right + iScrollX),
		int(m_tRect.bottom + iScrollY));
}