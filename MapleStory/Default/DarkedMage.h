#pragma once
#include "Monster.h"
class CDarkedMage :
	public CMonster
{
	enum BOSS_STATE {IDLE, SKILL_1, SKILL_2, SKILL_3, SKILL_4};

public:
	CDarkedMage();
	virtual ~CDarkedMage();

public:
	void SetCurState(BOSS_STATE _eState, DIRECTION _eDir);

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	virtual void	OnHit(CObj* _pOther) override;

private:
	void Idle_Update();
	void Skill_1_Update();
	void Skill_2_Update();
	void Skill_3_Update();
	void Skill_4_Update();

	void Skill_1_Temp();
	void Skill_2_Temp();

	virtual void OnCollision(CObj* _pOther) override;
	virtual void    OnePlayEnd(void) override;

protected:
	virtual void Motion_Change(void) override;

private:
	void ChooseRandStat();

private:
	float m_fOldTime;
	float m_fRandTime;

	BOSS_STATE m_eCurState;
	BOSS_STATE m_ePreState;

	bool m_fTest = false;

	float m_fDelayTime;
	float m_fOldDelayTime;

	int   m_iSkill1_Count;
	float m_fSkill1_DelayTime;
	float m_fSkill1_OldDelayTime;
	int   m_iSkill2_Count;
	float m_fSkill2_DelayTime;
	float m_fSkill2_OldDelayTime;
};

