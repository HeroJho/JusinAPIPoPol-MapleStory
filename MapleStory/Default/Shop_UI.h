#pragma once
#include "Obj.h"

#include "ShopS_UI.h"

class CShop_UI :
    public CObj
{
public:
	CShop_UI();
	virtual ~CShop_UI();

public:
	CShopS_UI** GetShopUIList() { return m_aShopUIList; }
	void Open() { m_bIsOpen = true; };
	void Close() { m_bIsOpen = false; };

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual     void	ColRender(HDC hDC) override;

private:
	CShopS_UI* m_aShopUIList[9];
	bool m_bIsOpen;

};

