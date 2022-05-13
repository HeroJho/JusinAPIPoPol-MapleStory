#pragma once
#include "Monster.h"
class CNightE :
	public CMonster
{
public:
	CNightE();
	virtual ~CNightE();

public:
	void SetCurState(STATE _eState, DIRECTION _eDir);

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	virtual void	OnHit(CObj* _pOther) override;
	void DropItem();

private:
	void Update_Idle();
	void Update_Walk();
	void Update_Chase();
	void Update_Hit();
	void Update_Attack();
	void Update_Dead();

	virtual void OnCollision(CObj* _pOther) override;
	virtual void    OnePlayEnd(void) override;

protected:
	virtual void Motion_Change(void) override;

private:
	void ChooseRandStat();

private:
	float m_fOldTime;
	float m_fRandTime;

	float m_fOldHitTime;
	float m_fHitTime;

	float m_fOldChaseTime;
	float m_fChaseTime;

	float m_fOldDeadTime;
	float m_fDeadTime;

	float m_fAttackRange;
	float m_fAttackTime;
	float m_fOldAttackTime;
};

