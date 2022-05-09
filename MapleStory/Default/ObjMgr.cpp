#include "stdafx.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

#include "CollisionMgr.h"

#include "Monster.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
	: m_pPlayer(nullptr)
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

	return 0;
}

void CObjMgr::Late_Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Late_Update();
	}

	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MAP], false);
}

void CObjMgr::Render(HDC hDC)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->ColRender(hDC);
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
	{
		CObj* pMonster = CAbstractFactory<CMonster>::Create(_fX, _fY, "Monster");
		pMonster->Set_Stat(50, 10);
		pMonster->Set_Speed(2.f);
		((CMonster*)pMonster)->Set_ID(MON_BLUESNAIL);
		Add_Object(OBJ_MONSTER, pMonster);
	}
		break;
	case MON_REDSNAIL:

		break;
	case MON_GREENMUSH:
		break;
	case MON_DELSNAIL:
		break;
	case MON_DELPIG:
		break;
	case MON_NIGHTE:
		break;
	case MON_NIGHTC:
		break;
	}
}
