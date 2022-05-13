#pragma once

#include "Include.h"

struct SpawnInfo
{
	RECT rect;
	MONSTERID Id;

	void Init(MONSTERID _Id, LONG _Left, LONG _Right, LONG _Bottom)
	{
		Id = _Id;
		rect.left = _Left;
		rect.right = _Right;
		rect.bottom = _Bottom;
	}

};

class CSpawnMgr
{
private:
	CSpawnMgr();
	~CSpawnMgr();
#pragma region ins
public:
	static		CSpawnMgr* Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CSpawnMgr;
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
	static CSpawnMgr* m_pInstance;
#pragma endregion

public:
	void DecreaseCount() { --m_iMonsterCount; }

public:
	void		Initialize(void);
	void		Update(void);
	void		Release(void);

public:
	void Scene_2();
	void Scene_4();

private:
	list<SpawnInfo> m_lRects;

	int m_iMaxMonsterCount;
	int m_iMonsterCount;
	int m_iLineCount;

	float m_fGenTime;
	float m_fOldGenTime;
};

