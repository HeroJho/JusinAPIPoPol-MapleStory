#pragma once
#include "Obj.h"

#include "Quest.h"

class CNpc :
    public CObj
{
public:
	enum STATE { IDLE, MOVE, END };

public:
	CNpc();
	virtual ~CNpc();

public:
	void SetCurState(STATE _eState, DIRECTION _eDir);
	void SetMark() { m_bMark = true; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	
private:
	void Update_Idle();
	void Update_Walk();



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
	CQuest* m_pQ;

	bool m_bMark;
};

