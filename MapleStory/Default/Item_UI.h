#pragma once
#include "Obj.h"

class CItem_UI :
    public CObj
{
public:
	CItem_UI();
	virtual ~CItem_UI();

public:
	void SetInfo(ITEM _sInfo) { m_sInfo = _sInfo; };
	ITEM& GetInfo() { return m_sInfo; }
	void Use_Item();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual void OnCollision(CObj* _pOther);
	virtual     void	ColRender(HDC hDC) override;

private:
	bool m_bIsOpen;
	ITEM m_sInfo;

};

