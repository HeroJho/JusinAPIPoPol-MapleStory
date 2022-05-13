#pragma once

#include "HpHp_UI.h"
#include "Inven_UI.h"

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
	CObj* Get_InvenUI() { return m_pInven; }


public:
	void		Initialize(void);
	void		Update(void);
	void		Render(HDC hDC);
	void		Release(void);

public:
	void ChangePlayerHp(int _iHp, int _iMaxHp);
	void ChangePlayerMp(int _iMp, int _iMaxMp);
	void ChangePlayerExp(int _iExp, int _iMaxExp);


private:
	CHpHp_UI* m_pHpHpUI;
	CInven_UI* m_pInven;

};

