#pragma once

#include "Include.h"

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	RECT Get_MapSize(void) { return m_tMapSize; };

public:
	virtual void	Initialize(void) PURE;
	virtual void	Update(void) PURE;
	virtual void	Late_Update(void) PURE;
	virtual void	Render(HDC hDC) PURE;
	virtual void	Release(void) PURE;

protected:
	RECT			m_tMapSize;

};

