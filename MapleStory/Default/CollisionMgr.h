#pragma once

#include "Obj.h"
#include "Item_UI.h"
#include "SkillS_UI.h"
#include "QSlotTemp_UI.h"
#include "ShopS_UI.h"
#include "StatS_UI.h"
#include "SkillSButton_UI.h"
#include "InvenButton_UI.h"
#include "EquipS_UI.h"
#include "SoundButton.h"

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
	static void     CollisionInvenUI_RectEx(CObj* _Dest, CItem_UI** _Sour, bool _bPush = true);
	static void     CollisionSkillUI_RectEx(CObj* _Dest, CSkillS_UI** _Sour, bool _bPush = true);
	static void     CollisionSlotUI_RectEx(CObj* _Dest, CQSlotTemp_UI** _Sour, bool _bPush = true);
	static void     CollisionShopUI_RectEx(CObj* _Dest, CShopS_UI** _Sour, bool _bPush = true);
	static void     CollisionStatUI_RectEx(CObj* _Dest, CStatS_UI** _Sour, bool _bPush = true);
	static void     CollisionSkillSButtonUI_RectEx(CObj* _Dest, CSkillSButton_UI** _Sour, bool _bPush = true);
	static void     CollisionInvenButtonUI_RectEx(CObj* _Dest, CInvenButton_UI** _Sour, bool _bPush = true);
	static void     CollisionEquipUI_RectEx(CObj* _Dest, CEquipS_UI** _Sour, bool _bPush = true);
	static void     CollisionSoundUI_RectEx(CObj* _Dest, CSoundButton** _Sour, bool _bPush = true);
};

