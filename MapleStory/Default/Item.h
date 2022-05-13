#pragma once
#include "Obj.h"
class CItem :
    public CObj
{
public:
	CItem();
	~CItem();

public:
	string Get_ItemTag() { return m_sItemTag; }
	ITEMID Get_ItemId() { return m_eID; }

public:
	virtual		void	Initialize(void)	override;
	virtual		int		Update(void)		override;
	virtual		void	Late_Update(void)	override;
	virtual		void	Render(HDC hDC)		override;
	virtual		void	Release(void)		override;


protected:
	string	 m_sItemTag;
	ITEMID   m_eID;
};

