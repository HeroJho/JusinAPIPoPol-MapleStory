#include "stdafx.h"
#include "Item.h"

CItem::CItem()
{
}

CItem::~CItem()
{
	Release();
}

void CItem::Initialize(void)
{
}

int CItem::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;



	Update_Rect();

	return OBJ_NOEVENT;
}

void CItem::Late_Update(void)
{
}

void CItem::Render(HDC hDC)
{
}

void CItem::Release(void)
{
}
