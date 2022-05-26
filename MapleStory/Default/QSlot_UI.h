#pragma once
#include "Obj.h"
#include "QSlotTemp_UI.h"

class CQSlot_UI :
    public CObj
{
public:
	CQSlot_UI();
	virtual ~CQSlot_UI();

public:
	CQSlotTemp_UI** GetSlotUIList() { return m_aSlot; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual     void	ColRender(HDC hDC) override;


private:
	CQSlotTemp_UI* m_aSlot[12];
};

