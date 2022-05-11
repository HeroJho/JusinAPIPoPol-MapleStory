#pragma once
#include "Skill.h"
class CSkill_2 :
    public CSkill
{
public:
	CSkill_2();
	~CSkill_2();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	virtual void OnCollision(CObj* _pOther) override;

private:
	void		Motion_Change(void);

};

