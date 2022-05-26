#pragma once

#include "Player.h"
#include "Pet.h"

class CStatMgr
{
private:
	CStatMgr();
	~CStatMgr();

public:
	PLAYERSTATE GetPlayerState() { return m_tPlayerState; }

	bool AddStatPoint(int _iValue) 
	{ 
		m_iStatPoint += _iValue;
		if (0 > m_iStatPoint)
		{
			m_iStatPoint = 0;
			return false;
		}
		return true;
	}
	int GetStatPoint() { return m_iStatPoint; }

	bool AddSkillPoint(int _iValue)
	{
		m_iSkillPoint += _iValue;
		if (0 > m_iSkillPoint)
		{
			m_iSkillPoint = 0;
			return false;
		}
		return true;
	}
	int GetSkillPoint() { return m_iSkillPoint; }

	int Get_PlayerLevel() { return m_pPlayer->Get_Stat().iLevel; }

	int Get_PlayerAT();
	int Get_TotalAT();
	int Get_PlayerMaxHP();
	int Get_PlayerMaxMP();
	float Get_PlayerMaxSP();


	int Get_PlusMaxHP() { return m_iPlusHP; }
	int Get_PlusMaxMP() { return m_iPlusMP; }

	int Get_PlusAT();
	int Get_PlusMaxHp();
	int Get_PlusMaxMp();
	int Get_PlusSTR();
	int Get_PlusDEX();
	int Get_PlusINT();
	int Get_PlusLUK();

	void Increase_STR();
	void Increase_DEX();
	void Increase_INT();
	void Increase_LUK();

	void Increase_Skill_1();
	void Increase_Skill_2();
	void Increase_Skill_3();
	void Increase_Skill_4();

public:
	void Set_Weapon(ITEM _tInfo);
	void Set_Shute(ITEM _tInfo);
	void Set_Shose(ITEM _tInfo);
	void Set_Gyenjong(ITEM _tInfo);
	void Set_Cave(ITEM _tInfo);
	void Set_Het(ITEM _tInfo);
	void Set_Glove(ITEM _tInfo);

	ITEM	Get_Weapon()	   { return m_tWeapon; }
	ITEM	Get_Shute()		   { return m_tShute; }
	ITEM	Get_Shose()		   { return m_tShose; }
	ITEM	Get_Gyenjong()	   { return m_tGyenjong; }
	ITEM	Get_Cave()		   { return m_tCave; }
	ITEM	Get_Het()		   { return m_tHet; }
	ITEM	Get_Glove()		   { return m_tGlove; }

	void Remove_Weapon();
	void Remove_Shute();
	void Remove_Shose();
	void Remove_Gyenjong();
	void Remove_Cave(); 
	void Remove_Het();		
	void Remove_Glove();	


public:
	void		Initialize(void);
	int			Update(void);
	void		Release(void);

private:
	CPlayer* m_pPlayer;
	PLAYERSTATE m_tPlayerState;

	int m_iPlusAT;
	int m_iPlusHP;
	int m_iPlusMP;
	float m_iPlusSP;

	int m_iPlusSTR;
	int m_iPlusDEX;
	int m_iPlusINT;
	int m_iPlusLUK;

	int m_iStatPoint;
	int m_iSkillPoint;


	ITEM m_tWeapon;
	ITEM m_tShute;
	ITEM m_tShose;
	ITEM m_tGyenjong;
	ITEM m_tCave;
	ITEM m_tHet;
	ITEM m_tGlove;

#pragma region Ins
public:
	static		CStatMgr* Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CStatMgr;
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
	static CStatMgr* m_pInstance;
#pragma endregion


};

