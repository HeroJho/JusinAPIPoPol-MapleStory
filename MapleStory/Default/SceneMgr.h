#pragma once

#include "Logo.h"
#include "MyMenu.h"

class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

public:
	CScene* Get_CurScene(void) { return m_pScene; }
	void		Scene_Change(SCENEID eID);

public:
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

#pragma region Ins
public:
	static		CSceneMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CSceneMgr;
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
	static CSceneMgr*		m_pInstance;
#pragma	endregion

private:
	CScene*					m_pScene;

	SCENEID					m_eCurScene;
	SCENEID					m_ePreScene;

};

