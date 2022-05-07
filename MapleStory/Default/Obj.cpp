#include "stdafx.h"
#include "Obj.h"

CObj::CObj()
	: m_fSpeed(0.f)
	, m_eDir(DIR_END)
	, m_bDead(false)
	, m_fAngle(0.f)
	, m_pFrameKey(nullptr)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));

	m_fJumpPower = 10.f;
}

CObj::~CObj()
{
}

void CObj::Update_Rect(void)
{
	m_tRect.left   = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top    = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
 	m_tRect.right  = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}

void CObj::Update_Gravity(void)
{
	// 1. ������ ���´�.
	float		LinefY = 0.f;

	CLine* m_pCurLine = m_pCurLine = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &LinefY);

	// 3. ���� ���ο� ���� �߷� �����Ѵ�.
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

	// 2. �������� �ƴ��� �Ǵ��Ѵ�.
	if (LinefY <= m_tInfo.fY)
	{	// �ٴ��� ��
		m_tInfo.fY = LinefY;
		m_bOnAir = false;
		m_fValY = 0.f;
	}
	else if (LinefY > m_tInfo.fY)
	{	// ������ ��
		// ���� �����̶� ����,           �밢���϶�
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
			m_tFrame.iFrameStart = 0;
	}

}
