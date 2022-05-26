#pragma once
#include "Obj.h"
class CDamageGen :
    public CObj
{
public:
	CDamageGen();
	~CDamageGen();

public:
	void Init(int _iHitCount, float _fHitTime, int _iStart, int _iEnd, float _fMeX, float _fMeY, float _fPivot, float _fTempPivot);


public:
	virtual		void	Initialize(void)	override;
	virtual		int		Update(void)		override;
	virtual		void	Late_Update(void)	override;
	virtual		void	Render(HDC hDC)		override;
	virtual		void	Release(void)		override;


private:
	int m_iHitCount;
	int m_iHitOldCount;
	float m_fHitTime;
	float m_fOldHitTime;
	int m_iStart;
	int m_iEnd;
	float m_fMeX;
	float m_fMeY;
	float m_fPivot;


	float m_fOlbTempPivot;
	float m_fTempPivot;
};

