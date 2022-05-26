#pragma once
#include "Obj.h"
#include "Bullet.h"
#include "Line.h"

class CPlayer
	: public CObj
{
public:
	enum STATE { IDLE, WALK, AIR, ATTACK, SKILL, HIT, BENDIDLE, HANGIDLE, BENDWALK, HANGWALK, DEAD, TEST, END };

public:
	CPlayer();
	virtual ~CPlayer();

public:
	void SetCurState(STATE _eState, DIRECTION _eDir);
	void SetStateSkill() { m_eCurState = SKILL;}
	void SetStateAttack() { m_eCurState = ATTACK;}
	bool DecreaseMp(int _iValue);
	void AddExp(int _iValue);
	void LevelUp();

	bool GetHit() { return m_bHit; }

	void IncreaseHp(int _iValue);
	void IncreaseMp(int _iValue);

	void SetHold() { m_bHold = true; }
	void ResetHold() { m_bHold = false; }

	STATE GetCurState() { return m_eCurState; }
	bool  IsHang() { return m_pHangLine; }

	float GetSpeed() { return m_fSpeed; }

	void ResetDead();

public:
	virtual void	Initialize(void)	override;
	virtual int		Update(void)		override;
	virtual	void	Late_Update(void)	override;
	virtual void	Render(HDC hDC)		override;
	virtual void	Release(void)		override;

	void	Update_Gravity(void);
	void	Update_Hang(void);

	virtual		void	OnCollision(CObj* _pOther)	override;

private:
	void		Key_Input(void);
	void		Hang_Input(void);
	void		Motion_Change(void);
	void		Hit_Update(void);
	void		Skill_Update(void);

public:
	virtual void	OnHit(CObj* _pOther) override;
	void	OnHit(int _iValue);
	virtual void    OnePlayEnd(void) override;

private:
	bool					m_bDrop;
	bool					m_bDoubleJump;
	DIRECTION				m_eDoubleDir;

	CLine* m_pDropLine;
	CLine* m_pHangLine;
	float					m_fDropY;

	float					m_fDropSpeed;
	bool					m_bHit;
	float					m_fOldHitTime;
	float					m_fHitTime;

	STATE					m_ePreState;
	STATE					m_eCurState;

	float					m_fOldSkillTime;
	float					m_fSkillTime;

	bool m_bHold;

	float					m_fOldHitAnimTime;
	float					m_fHitAnimTime;
	bool m_bHitAnim;

	float m_fRotAngle;
};
