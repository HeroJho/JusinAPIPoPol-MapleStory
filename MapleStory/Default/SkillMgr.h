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
	bool UseSkill(SKILLID _eID);

private:
	SKILL m_sSkill_1;
	SKILL m_sSkill_2;
	SKILL m_sSkill_3;
	SKILL m_sSkill_4;

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

