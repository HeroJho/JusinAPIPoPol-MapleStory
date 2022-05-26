#pragma once
#include "Obj.h"
class CMaya :
    public CObj
{
public:
	enum STATE { IDLE, MOVE, END };

public:
	CMaya();
	virtual ~CMaya();

public:
	void SetCurState(STATE _eState, DIRECTION _eDir);

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;


private:
	void Update_Idle();


	virtual void OnCollision(CObj* _pOther) override;


protected:
	void Motion_Change(void);

private:
	void ChooseRandStat();

private:
	STATE m_eCurState;
	STATE m_ePreState;

	float m_fOldTime;
	float m_fRandTime;

	bool m_bDecPlayer;

};

