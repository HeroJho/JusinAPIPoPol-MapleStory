#pragma once

#include "Obj.h"
#include "Item_UI.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static bool		Check_Sphere(CObj* pDest, CObj* pSour);
	static bool		Check_Rect(CObj* pDest, CObj* pSour, float *pX, float* pY);
	static void		Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour);
	static void		Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Sour, bool _bPush = true);
	static void		Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour);
	static void     Collision_RectEx(CObj* _Dest, CObj* _Sour, bool _bPush = true);
	static void     Collision_RectEx(CObj* _Dest, list<CItem_UI*> _Sour, bool _bPush = true);
};

