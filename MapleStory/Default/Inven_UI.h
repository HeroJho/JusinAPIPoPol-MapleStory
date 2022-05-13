#pragma once
#include "Obj.h"

class CInven_UI :
    public CObj
{
public:
	CInven_UI();
	virtual ~CInven_UI();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual     void	ColRender(HDC hDC) override;

private:
	bool m_bIsOpen;

};

