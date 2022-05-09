#pragma once
#include "Obj.h"
class CMonster : public CObj
{
public:
	CMonster();
	virtual ~CMonster();

public:
	void Set_ID(MONSTERID _eID);

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	MONSTERID m_eID;
};

