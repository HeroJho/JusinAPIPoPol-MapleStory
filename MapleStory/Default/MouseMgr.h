#pragma once

#include "Obj.h"

class CMouseMgr
{
private:
	CMouseMgr();
	~CMouseMgr();


public:
	void		Initialize(void);
	void		Render(HDC hDC);
	int			Update(void);
	void		Late_Update(void);
	void		Release(void);

private:
	CObj* m_pMouse;

#pragma region Ins
public:
	static		CMouseMgr* Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CMouseMgr;
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
	static CMouseMgr* m_pInstance;
#pragma endregion

};

