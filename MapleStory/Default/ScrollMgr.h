#pragma once

#include "Include.h"
#include "Obj.h"

class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	void		Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }

	float		Get_ScrollX(void) { return m_fScrollX; }
	float		Get_ScrollY(void) { return m_fScrollY; }


public:
	void		Update();


#pragma region Ins
public:
	static		CScrollMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CScrollMgr;
		}

		return m_pInstance;
	}

	static	void	Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CScrollMgr*		m_pInstance;
#pragma endregion


private:
	CObj*					m_pTarget;
	float					m_fScrollX;
	float					m_fScrollY;
};

