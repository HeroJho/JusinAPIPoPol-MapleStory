#pragma once
#include "Obj.h"
#include "Player.h"

class CVet :
    public CObj
{
public:
	enum STATE { IDLE, CHASE, ATTACK, END };

public:
	CVet();
	virtual ~CVet();

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

private:
	void Update_Idle();
	void Update_Chase();
	void Update_Attack();

	virtual void OnCollision(CObj* _pOther) override;
	virtual void    OnePlayEnd(void) override;


protected:
	void Motion_Change(void);

private:
	STATE m_eCurState;
	STATE m_ePreState;

	CPlayer* m_pTarget;
	CObj* m_pMonster;
	CObj* m_pDestMon;
	float m_fMonX;
	float m_fMonY;

	float m_fTickCount;
	float m_fOldTickCount;

	float m_fAttackCount;
	float m_fOldAttackCount;

	int m_iHitCount;
};

