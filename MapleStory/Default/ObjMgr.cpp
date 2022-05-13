#include "stdafx.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

#include "CollisionMgr.h"
#include "KeyMgr.h"

#include "BlueSnail.h"
#include "RedSnail.h"
#include "Mushroom.h"
#include "DeleteDarPeng.h"
#include "DeletePig.h"
#include "NightE.h"
#include "NightC.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
	: m_pPlayer(nullptr)
	, m_bColRender(false)
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

CObj* CObjMgr::Get_Target(OBJID eID, CObj* pObj)
{
	if (m_ObjList[eID].empty())
		return nullptr;

	CObj*		pTarget = nullptr;
	float		fDistance = 0.f;
	
	for (auto& iter : m_ObjList[eID])
	{
		if (iter->Get_Dead())
			continue;

		float	fWidth = abs(pObj->Get_Info().fX - iter->Get_Info().fX);
		float	fHeight = abs(pObj->Get_Info().fY - iter->Get_Info().fY);

		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if ((!pTarget) || (fDistance > fDiagonal))
		{
			pTarget = iter;
			fDistance = fDiagonal;
		}
	}
		
	return pTarget;
}

void CObjMgr::Add_Object(OBJID eID, CObj * pObj)
{
	if ((eID >= OBJ_END) || (nullptr == pObj))
		return;

	m_ObjList[eID].push_back(pObj);
}

int CObjMgr::Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down('P'))
	{
		if(m_bColRender)
			m_bColRender = false;
		else
			m_bColRender = true;
	}
		


	return 0;
}

void CObjMgr::Late_Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Late_Update();
	}


	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER], false);
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_BLOCK], m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_BLOCKME], m_ObjList[OBJ_PLAYER]);
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MAP], false);   // 플레이어 포탈
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_SKILL], false);   // 몬스터	플레이어스킬
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSKILL], false);   // 플레이어 몬스터 스킬
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_ITEM], false);   // 플레이어 아이템
}

void CObjMgr::Render(HDC hDC)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			if(m_bColRender) iter->ColRender(hDC);
			iter->Render(hDC);
		}
	}
}

void CObjMgr::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			Safe_Delete<CObj*>(iter);

		m_ObjList[i].clear();
	}
}

void CObjMgr::Delete_ID(OBJID eID)
{
	for (auto& iter : m_ObjList[eID])
		Safe_Delete(iter);

	m_ObjList[eID].clear();
}


void CObjMgr::MakeMonster(MONSTERID _eID, float _fX, float _fY)
{
	switch (_eID)
	{
	case MON_BLUESNAIL:
		Add_Object(OBJ_MONSTER, CAbstractFactory<CBlueSnail>::Create(_fX, _fY, "Monster"));
		break;
	case MON_REDSNAIL:
		Add_Object(OBJ_MONSTER, CAbstractFactory<CRedSnail>::Create(_fX, _fY, "Monster"));
		break;
	case MON_GREENMUSH:
		Add_Object(OBJ_MONSTER, CAbstractFactory<CMushroom>::Create(_fX, _fY, "Monster"));
		break;
	case MON_DELSNAIL:
		Add_Object(OBJ_MONSTER, CAbstractFactory<CDeleteDarPeng>::Create(_fX, _fY, "Monster"));
		break;
	case MON_DELPIG:
		Add_Object(OBJ_MONSTER, CAbstractFactory<CDeletePig>::Create(_fX, _fY, "Monster"));
		break;
	case MON_NIGHTE:
		Add_Object(OBJ_MONSTER, CAbstractFactory<CNightE>::Create(_fX, _fY, "Monster"));
		break;
	case MON_NIGHTC:
		Add_Object(OBJ_MONSTER, CAbstractFactory<CNightC>::Create(_fX, _fY, "Monster"));
		break;
	}
}
