#include "stdafx.h"
#include "Line.h"
#include "ScrollMgr.h"


CLine::CLine()
	: m_tInfo()
{
}


CLine::CLine(LINEPOINT& tLeft, LINEPOINT& tRight)
	: m_tInfo(tLeft, tRight)
	, m_bIsDiagonal(false)
{

}

CLine::CLine(LINE tLine)
	: m_tInfo(tLine)
	, m_bIsDiagonal(false)
{

}

CLine::CLine(LINE tLine, bool _bIsDiagonal)
	: m_tInfo(tLine)
	, m_bIsDiagonal(_bIsDiagonal)
{
}

CLine::~CLine()
{
}

void CLine::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	MoveToEx(hDC, (int)m_tInfo.tLPoint.fX + iScrollX, (int)m_tInfo.tLPoint.fY + iScrollY, nullptr);
	LineTo(hDC, (int)m_tInfo.tRPoint.fX + iScrollX, (int)m_tInfo.tRPoint.fY + iScrollY);
}
