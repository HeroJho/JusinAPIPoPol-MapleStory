#pragma once

#include "Obj.h"
#include "Player.h"

class CPet :
    public CObj
{
public:
	enum STATE {IDLE, CHASE ,JUMP, HANG, END};

public:
	CPet();
	virtual ~CPet();

public:
	void SetCurState(STATE _eState, DIRECTION _eDir);

	void SetPlayerPos();

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
	void Update_Jump();
	void Update_Hang();

	virtual void OnCollision(CObj* _pOther) override;
	virtual void    OnePlayEnd(void) override;


protected:
	void Motion_Change(void);

private:
	STATE m_eCurState;
	STATE m_ePreState;

	CPlayer* m_pTarget;

	float m_fVelX;
	float m_fStopRange;
	float m_fJumpPower;
};

