#pragma once

#include "HpHp_UI.h"

class CUIMgr
{
private:
	CUIMgr();
	~CUIMgr();

#pragma region Ins
public:
	static		CUIMgr* Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CUIMgr;
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
	static CUIMgr* m_pInstance;
#pragma endregion


public:
	void		Initialize(void);
	void		Update(void);
	void		Render(HDC hDC);
	void		Release(void);

public:
	void ChangePlayerHp(int _iHp, int _iMaxHp);


private:
	CHpHp_UI* m_pHpHpUI;


};

