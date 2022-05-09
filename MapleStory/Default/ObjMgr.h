#pragma once

#include "Obj.h"

class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	CObj*		Get_Player() { return m_pPlayer; }
	void		Set_Player(CObj* _pPlayer) { m_pPlayer = _pPlayer; }
	CObj*		Get_Target(OBJID eID, CObj* pObj);

public:
	void		Add_Object(OBJID eID, CObj* pObj);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	void		Delete_ID(OBJID eID);

public:
	void MakeMonster(MONSTERID _eID, float _fX, float _fY);

private:
	list<CObj*>	m_ObjList[OBJ_END];
	CObj* m_pPlayer;

#pragma region Ins
public:
	static		CObjMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CObjMgr;
		}

		return m_pInstance;
	}

	static	void	Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CObjMgr*			m_pInstance;
#pragma endregion


};

