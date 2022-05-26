#pragma once
#include "Npc.h"

class CCutMgr
{
private:
	CCutMgr();
	~CCutMgr();

public:
	void StartCut_1();
	void StartCut_2();
	void StartCut_3();
	void StartCut_4();

public:
	void UpdateCut_1();
	void UpdateCut_2();
	void UpdateCut_3();
	void UpdateCut_4();

public:
	void SetNpc(CNpc* _pObj) { m_pNpc = _pObj; }

public:
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

private:
	bool m_bCut_1;
	bool m_bCut_2;
	bool m_bCut_3;
	bool m_bCut_4;
	bool m_bDomi;
	bool m_bMark;

	float m_fDomiTime;
	float m_fOldDomiTime;

	bool m_bWrite;
	float m_fWriteTime;
	float m_fOldWriteTime;

	float m_fNextMapTime;
	float m_fOldNextMapTime;

	float m_fNpcMarkTime;
	float m_fOldNpcMarkTime;

	CNpc* m_pNpc;

#pragma region Ins
public:
	static		CCutMgr* Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CCutMgr;
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
	static CCutMgr* m_pInstance;
#pragma endregion


};

