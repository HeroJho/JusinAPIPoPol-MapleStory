#pragma once
#include "Skill.h"
class CEffect :
    public CSkill
{
public:
	CEffect();
	~CEffect();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

