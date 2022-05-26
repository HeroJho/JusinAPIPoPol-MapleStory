#pragma once

#include "Include.h"

class CEventMgr
{
private:
	CEventMgr();
	~CEventMgr();

#pragma region Ins
public:
	static		CEventMgr* Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CEventMgr;
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
	static CEventMgr* m_pInstance;
#pragma endregion

public:
	void ExeEvent();

public:
	void AddSceneChangeEvent(SCENEID _eId);


public:
	int GetRandomNum_Int(int iLeft, int iRight);
	float GetRandomNum_float(float iLeft, float iRight);

private:
	SCENEID m_eID;
};

