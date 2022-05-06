#pragma once

#include "Include.h"

class CLine
{
public:
	CLine();
	CLine(LINE tLine);
	CLine(LINE tLine, bool _bIsDiagonal);
	CLine(LINEPOINT& tLeft, LINEPOINT& tRight);
	~CLine();

public:
	const LINE& Get_Info(void) const { return m_tInfo; }
	bool	Get_Diagonal() { return m_bIsDiagonal; }

public:
	void	Render(HDC hDC);

private:
	LINE		m_tInfo;
	bool		m_bIsDiagonal;
};

