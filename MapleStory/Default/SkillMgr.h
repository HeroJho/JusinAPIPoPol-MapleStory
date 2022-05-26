#pragma once

#include "Include.h"

class CSkillMgr
{
private:
	CSkillMgr();
	~CSkillMgr();


public:
	void		Initialize(void);
	int			Update(void);
	void		Release(void);

public:
	bool UseSkill(SKILLID _eID, TCHAR _cHoldKey = ' ');

	void UpSKill_1();
	void UpSKill_2();
	void UpSKill_3();
	void UpSKill_4();

public:
	float  Getf1() { return m_f1; }
	float  Getf2() { return m_f2; }
	float  Getf3() { return m_f3; }
	float  Getf4() { return m_f4; }

	int  GetSkillLevel1() { return m_iLevel_1; }
	int  GetSkillLevel2() { return m_iLevel_2; }
	int  GetSkillLevel3() { return m_iLevel_3; }
	int  GetSkillLevel4() { return m_iLevel_4; }

	void DecreaseVet()
	{
		--m_iVetCount;
		if (m_iVetCount < 0)
			m_iVetCount = 0;
	}
	void CreateVect();

private:
	SKILL m_sSkill_1;
	SKILL m_sSkill_2;
	SKILL m_sSkill_3;
	SKILL m_sSkill_4;

	int m_iLevel_1;
	int m_iLevel_2;
	int m_iLevel_3;
	int m_iLevel_4;

	float m_f1;
	float m_f2;
	float m_f3;
	float m_f4;

	int m_iVetCount;

#pragma region Ins
public:
	static		CSkillMgr* Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CSkillMgr;
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
	static CSkillMgr* m_pInstance;
#pragma endregion


};

