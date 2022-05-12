#pragma once

#include "Include.h"

#include "LineMgr.h"
#include "Line.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	void		Set_Dir(DIRECTION eDir) { m_eDir = eDir; }
	void		Set_Dead() { m_bDead = true; }
	void		Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void		Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }
	void		Set_Tag(string _sTag) { m_sTag = _sTag; }
	void		Set_Speed(float _fSpeed) { m_fSpeed = _fSpeed; }

	void		Set_PosX(float _fX) { m_tInfo.fX += _fX; }
	void		Set_PosY(float _fY) { m_tInfo.fY += _fY; }

	void		Set_FrameKey(TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }

	void		Set_Stat(int _iMaxHp, int _iAt);

	bool		Get_Dead() { return m_bDead; }
	CObj* Get_Target() { return m_pTarget; }
	DIRECTION	Get_Dir() { return m_eDir; }
	bool		Get_CanHit() { return m_bCanHit; }

	float Get_ColPosX() { return m_tInfo.fCX; }
	float Get_ColPosY() { return m_tInfo.fCY; }

	const string Get_Tag() { return m_sTag; }

	STAT&		Get_Stat(void) { return m_tStat; }
	const INFO&		Get_Info(void) const { return m_tInfo; }
	const RECT&		Get_Rect(void) const { return m_tRect; }


public:
	virtual		void	Initialize(void)	PURE;
	virtual		int		Update(void)		PURE;
	virtual		void	Late_Update(void)	PURE;
	virtual		void	Render(HDC hDC)		PURE;
	virtual		void	Release(void)		PURE;

	virtual     void	ColRender(HDC hDC);

	virtual		void	OnCollision(CObj* _pOther) {};

public:
	virtual		void	OnHit(CObj* _pOther) {};

protected:
	void		Update_Rect(void);
	void		Move_Frame(void);
	void		Update_Gravity(bool _bItem = false);
	virtual void	OnePlayEnd(void) {};

protected:
	INFO		m_tInfo;
	STAT		m_tStat;
	RECT		m_tRect;
	RECT		m_tTRect;		// 텍스쳐 렉트
	FRAME		m_tFrame;

	float		m_fSpeed;
	float		m_fAngle;

	DIRECTION	m_eDir;
	bool		m_bDead;

	bool        m_bOnePlay;
	bool		m_bStayPlay;

	bool		m_bCanHit;

	CObj*		m_pTarget;
	TCHAR*		m_pFrameKey;

	POINT       m_tColPivot;
	string		m_sTag;

protected:
	bool					m_bJump;
	bool					m_bOnAir;		// 점프 상태 확인
	float					m_fJumpPower;	// 점프 힘
	float					m_fAirTime;	// 점프 중 진행 시간
	float					m_fValY;

	CLine*					m_pCurLine;
	CLine*					m_pOldLine;
	float					m_fLinefY;
};

