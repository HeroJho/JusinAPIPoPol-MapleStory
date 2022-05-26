#pragma once

#include "Include.h"
#include "Obj.h"

class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();


#pragma region Ins
public:
	static		CScrollMgr* Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CScrollMgr;
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
	static CScrollMgr* m_pInstance;
#pragma endregion


public:
	void		Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }

	float		Get_ScrollX(void) { return m_fScrollX; }
	float		Get_ScrollY(void) { return m_fScrollY; }

	void		StartShake(float _fShakeValue, float _fShakeSpeed, float _fTime ,float _fATime = 0.f);

public:
	void Nomal();
	void Shake();

public:
	void		Initialize(void);
	void		Update(void);




private:
	CObj*					m_pTarget;
	float					m_fScrollX;
	float					m_fScrollY;

	bool					m_bMoveX;
	bool					m_bMoveY;

	bool					m_bShake;
	bool					m_bShakeTurn;
	float					m_bShakeTemp;
	float					m_fShakeValue;
	float					m_fShakeTime;
	float					m_fShakeOldTime;
	float					m_fShakeSpeed;

	float					m_fATime;
	float					m_fOldATime;
};

