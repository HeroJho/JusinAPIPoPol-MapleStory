#pragma once
#include "Obj.h"

#include "SkillS_UI.h"
#include "SkillSButton_UI.h"

class CSkill_UI
	: public CObj
{
public:
	CSkill_UI();
	virtual ~CSkill_UI();

public:
	CSkillS_UI** GetSkillUIList() { return m_aSkillUIList; }
	CSkillSButton_UI** GetSkillButtonUIList() { return m_aSkillButtonUIList; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual     void	ColRender(HDC hDC) override;

private:
	CSkillS_UI* m_aSkillUIList[4];
	CSkillSButton_UI* m_aSkillButtonUIList[4];
	bool m_bIsOpen;

	float m_fRePosX;
	float m_fRePosY;

};