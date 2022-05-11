#pragma once
#include "Obj.h"
class CSkill :
    public CObj
{
public:
    CSkill();
    virtual ~CSkill();

public:
	void		Set_ColSet(float _fCX, float _fCY, float _fPvX, float _fPvY, float _fDeleteTime, float _fSkillTime);

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	virtual void OnCollision(CObj* _pOther) override;

protected:
	float					m_fOldSkillTime;
	float					m_fSkillTime;
	float					m_fDeleteTime;

	int						m_CanHitCount;
	int						m_CanHitMaxCount;

	float					m_fFixPivotX;
	float					m_fFixPivotY;
};

