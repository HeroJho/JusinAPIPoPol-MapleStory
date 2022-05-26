#pragma once

#include "Include.h"

class CQuestMgr
{
private:
	CQuestMgr();
	~CQuestMgr();

#pragma region Inst
public:
	static		CQuestMgr* Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CQuestMgr;
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
	static CQuestMgr* m_pInstance;
#pragma endregion


public:
	void		Initialize(void);
	void		Update(void);
	void		Release(void);


public:
	QUEST GetQuest() { return m_eCurState; }
	void SetQuest(QUEST _eState) { m_eCurState = _eState; }

	int Get_BlueNail() { return m_iBlueNail; }
	int Get_RedNail() { return m_iRedNail; }
	int Get_Green() { return m_iGreen; }
	int Get_MaxBlueNail() { return m_iMaxBlueNail; }
	int Get_MaxRedNail() { return m_iMaxRedNail; }
	int Get_MaxGreen() { return m_iMaxGreen; }

	int Get_DelNail() { return m_iDelNail; }
	int Get_DelPig() { return m_iDelPig; }
	int Get_MaxDelNail() { return m_iMaxDelNail; }
	int Get_MaxDelPig() { return m_iMaxDelPig; }



public:
	void HuntingMonster(MONSTERID _eID);
	void AcceptQuest();


private:
	QUEST m_eCurState;

	bool m_b5;
	bool m_b6;

private:
	int m_iBlueNail;
	int m_iMaxBlueNail;
	int m_iRedNail;
	int m_iMaxRedNail;
	int m_iGreen;
	int m_iMaxGreen;

	int m_iDelNail;
	int m_iMaxDelNail;
	int m_iDelPig;
	int m_iMaxDelPig;

	int m_iNightC;
	int m_iMaxNightC;

	int m_iNightE;
	int m_iMaxNightE;
};

