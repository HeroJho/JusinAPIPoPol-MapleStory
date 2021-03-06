#pragma once
#include "Skill.h"
class CBladeStorm :
	public CSkill
{
public:
	CBladeStorm();
	~CBladeStorm();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	virtual void OnCollision(CObj* _pOther) override;
	void SetFrameDir(DIRECTION _eDir);
	void SetHoldKey(TCHAR _cHoldKey);

private:
	void		Motion_Change(void);

private:
	TCHAR m_cHoldKey;
	
	float	m_fHitTime;
	float	m_fOldHitTime;

};
