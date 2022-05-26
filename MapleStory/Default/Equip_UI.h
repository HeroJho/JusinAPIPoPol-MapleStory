#pragma once
#include "Obj.h"
#include "EquipS_UI.h"

class CEquip_UI :
    public CObj
{
public:
	CEquip_UI();
	virtual ~CEquip_UI();

public:
	CEquipS_UI** GetEquipUIList() { return m_aEquipUIList; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual     void	ColRender(HDC hDC) override;


private:
	CEquipS_UI* m_aEquipUIList[7];
	bool m_bIsOpen;

	float m_fRePosX;
	float m_fRePosY;
};

