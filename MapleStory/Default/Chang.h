#pragma once
#include "Monster.h"
class CChang :
    public CMonster
{
public:
	enum STATEA {REION, IDLE, DEAD, END};
public:
	CChang();
	virtual ~CChang();

public:
	void SetCurState(STATEA _eState, DIRECTION _eDir);

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
	void Update_Region();
	void Update_Idle();
	void Update_Attack();
	void Update_Dead();

	virtual void OnCollision(CObj* _pOther) override;
	virtual void    OnePlayEnd(void) override;

protected:
	virtual void Motion_Change(void) override;

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

	float m_fRegionTime;
	float m_fOldRegionTime;

	STATEA m_eCurState;
	STATEA m_ePreState;
};

