#include "stdafx.h"
#include "CollisionMgr.h"
#include "QSlotTemp_UI.h"


CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}


void CCollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT		rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))
			{
				Dest->Set_Dead();
				Sour->Set_Dead();
			}
		}
	}
}
// 고정되어 있는 물체  // 움직이는 물체		
void CCollisionMgr::Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Sour, bool _bPush)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			float	fX = 0.f, fY = 0.f;

			if (Check_Rect(Dest, Sour, &fX, &fY))
			{
				Dest->OnCollision(Sour);
				Sour->OnCollision(Dest);

				// 상하 충돌
				if (fX > fY)
				{
					// 상 충돌
					if (Dest->Get_Info().fCY > Sour->Get_Info().fCY)
					{
						if (_bPush)Sour->Set_PosY(-fY);
					}
					// 하 충돌
					else
					{
						if (_bPush)Sour->Set_PosY(fY);
					}
				}
				// 좌우 충돌
				else
				{
					// 좌 충돌
					if (Dest->Get_Info().fCX > Sour->Get_Info().fCX)
					{
						if (_bPush)Sour->Set_PosX(-fX);
					}
					// 우 충돌
					else
					{
						if (_bPush)Sour->Set_PosX(fX);
					}
				}

			}
		}
	}
}

void CCollisionMgr::Collision_RectEx(CObj* _Dest, CObj* _Sour, bool _bPush)
{

	float	fX = 0.f, fY = 0.f;

	if (Check_Rect(_Dest, _Sour, &fX, &fY))
	{
		_Dest->OnCollision(_Sour);
		_Sour->OnCollision(_Dest);

		// 상하 충돌
		if (fX > fY)
		{
			// 상 충돌
			if (_Dest->Get_Info().fCY > _Sour->Get_Info().fCY)
			{
				if (_bPush)_Sour->Set_PosY(-fY);
			}
			// 하 충돌
			else
			{
				if (_bPush)_Sour->Set_PosY(fY);
			}
		}
		// 좌우 충돌
		else
		{
			// 좌 충돌
			if (_Dest->Get_Info().fCX > _Sour->Get_Info().fCX)
			{
				if (_bPush)_Sour->Set_PosX(-fX);
			}
			// 우 충돌
			else
			{
				if (_bPush)_Sour->Set_PosX(fX);
			}
		}
	}
}


void CCollisionMgr::CollisionInvenUI_RectEx(CObj* _Dest, CItem_UI** _Sour, bool _bPush)
{

	for (int i = 0; i < 24; ++i)
	{
		float	fX = 0.f, fY = 0.f;

		if (Check_Rect(_Dest, _Sour[i], &fX, &fY))
		{
			_Dest->OnCollision(_Sour[i]);
			_Sour[i]->OnCollision(_Dest);

			// 상하 충돌
			if (fX > fY)
			{
				// 상 충돌
				if (_Dest->Get_Info().fCY > _Sour[i]->Get_Info().fCY)
				{
					if (_bPush)_Sour[i]->Set_PosY(-fY);
				}
				// 하 충돌
				else
				{
					if (_bPush)_Sour[i]->Set_PosY(fY);
				}
			}
			// 좌우 충돌
			else
			{
				// 좌 충돌
				if (_Dest->Get_Info().fCX > _Sour[i]->Get_Info().fCX)
				{
					if (_bPush)_Sour[i]->Set_PosX(-fX);
				}
				// 우 충돌
				else
				{
					if (_bPush)_Sour[i]->Set_PosX(fX);
				}
			}
		}

	}

}
void CCollisionMgr::CollisionSkillUI_RectEx(CObj* _Dest, CSkillS_UI** _Sour, bool _bPush)
{

	for (int i = 0; i < 4; ++i)
	{
		float	fX = 0.f, fY = 0.f;

		if (Check_Rect(_Dest, _Sour[i], &fX, &fY))
		{
			_Dest->OnCollision(_Sour[i]);
			_Sour[i]->OnCollision(_Dest);

			// 상하 충돌
			if (fX > fY)
			{
				// 상 충돌
				if (_Dest->Get_Info().fCY > _Sour[i]->Get_Info().fCY)
				{
					if (_bPush)_Sour[i]->Set_PosY(-fY);
				}
				// 하 충돌
				else
				{
					if (_bPush)_Sour[i]->Set_PosY(fY);
				}
			}
			// 좌우 충돌
			else
			{
				// 좌 충돌
				if (_Dest->Get_Info().fCX > _Sour[i]->Get_Info().fCX)
				{
					if (_bPush)_Sour[i]->Set_PosX(-fX);
				}
				// 우 충돌
				else
				{
					if (_bPush)_Sour[i]->Set_PosX(fX);
				}
			}

		}


	}
}
void CCollisionMgr::CollisionSlotUI_RectEx(CObj* _Dest, CQSlotTemp_UI** _Sour, bool _bPush)
{

	for (int i = 0; i < 12; ++i)
	{
		float	fX = 0.f, fY = 0.f;

		if (Check_Rect(_Dest, _Sour[i], &fX, &fY))
		{
			_Dest->OnCollision(_Sour[i]);
			_Sour[i]->OnCollision(_Dest);

			// 상하 충돌
			if (fX > fY)
			{
				// 상 충돌
				if (_Dest->Get_Info().fCY > _Sour[i]->Get_Info().fCY)
				{
					if (_bPush)_Sour[i]->Set_PosY(-fY);
				}
				// 하 충돌
				else
				{
					if (_bPush)_Sour[i]->Set_PosY(fY);
				}
			}
			// 좌우 충돌
			else
			{
				// 좌 충돌
				if (_Dest->Get_Info().fCX > _Sour[i]->Get_Info().fCX)
				{
					if (_bPush)_Sour[i]->Set_PosX(-fX);
				}
				// 우 충돌
				else
				{
					if (_bPush)_Sour[i]->Set_PosX(fX);
				}
			}

		}


	}
}
void CCollisionMgr::CollisionShopUI_RectEx(CObj* _Dest, CShopS_UI** _Sour, bool _bPush)
{

	for (int i = 0; i < 9; ++i)
	{
		float	fX = 0.f, fY = 0.f;

		if (Check_Rect(_Dest, _Sour[i], &fX, &fY))
		{
			_Dest->OnCollision(_Sour[i]);
			_Sour[i]->OnCollision(_Dest);

			// 상하 충돌
			if (fX > fY)
			{
				// 상 충돌
				if (_Dest->Get_Info().fCY > _Sour[i]->Get_Info().fCY)
				{
					if (_bPush)_Sour[i]->Set_PosY(-fY);
				}
				// 하 충돌
				else
				{
					if (_bPush)_Sour[i]->Set_PosY(fY);
				}
			}
			// 좌우 충돌
			else
			{
				// 좌 충돌
				if (_Dest->Get_Info().fCX > _Sour[i]->Get_Info().fCX)
				{
					if (_bPush)_Sour[i]->Set_PosX(-fX);
				}
				// 우 충돌
				else
				{
					if (_bPush)_Sour[i]->Set_PosX(fX);
				}
			}

		}


	}
}
void CCollisionMgr::CollisionStatUI_RectEx(CObj* _Dest, CStatS_UI** _Sour, bool _bPush)
{

	for (int i = 0; i < 4; ++i)
	{
		float	fX = 0.f, fY = 0.f;

		if (Check_Rect(_Dest, _Sour[i], &fX, &fY))
		{
			_Dest->OnCollision(_Sour[i]);
			_Sour[i]->OnCollision(_Dest);

			// 상하 충돌
			if (fX > fY)
			{
				// 상 충돌
				if (_Dest->Get_Info().fCY > _Sour[i]->Get_Info().fCY)
				{
					if (_bPush)_Sour[i]->Set_PosY(-fY);
				}
				// 하 충돌
				else
				{
					if (_bPush)_Sour[i]->Set_PosY(fY);
				}
			}
			// 좌우 충돌
			else
			{
				// 좌 충돌
				if (_Dest->Get_Info().fCX > _Sour[i]->Get_Info().fCX)
				{
					if (_bPush)_Sour[i]->Set_PosX(-fX);
				}
				// 우 충돌
				else
				{
					if (_bPush)_Sour[i]->Set_PosX(fX);
				}
			}

		}


	}
}
void CCollisionMgr::CollisionSkillSButtonUI_RectEx(CObj* _Dest, CSkillSButton_UI** _Sour, bool _bPush)
{

	for (int i = 0; i < 4; ++i)
	{
		float	fX = 0.f, fY = 0.f;

		if (Check_Rect(_Dest, _Sour[i], &fX, &fY))
		{
			_Dest->OnCollision(_Sour[i]);
			_Sour[i]->OnCollision(_Dest);

			// 상하 충돌
			if (fX > fY)
			{
				// 상 충돌
				if (_Dest->Get_Info().fCY > _Sour[i]->Get_Info().fCY)
				{
					if (_bPush)_Sour[i]->Set_PosY(-fY);
				}
				// 하 충돌
				else
				{
					if (_bPush)_Sour[i]->Set_PosY(fY);
				}
			}
			// 좌우 충돌
			else
			{
				// 좌 충돌
				if (_Dest->Get_Info().fCX > _Sour[i]->Get_Info().fCX)
				{
					if (_bPush)_Sour[i]->Set_PosX(-fX);
				}
				// 우 충돌
				else
				{
					if (_bPush)_Sour[i]->Set_PosX(fX);
				}
			}

		}


	}
}
void CCollisionMgr::CollisionInvenButtonUI_RectEx(CObj* _Dest, CInvenButton_UI** _Sour, bool _bPush)
{

	for (int i = 0; i < 2; ++i)
	{
		float	fX = 0.f, fY = 0.f;

		if (Check_Rect(_Dest, _Sour[i], &fX, &fY))
		{
			_Dest->OnCollision(_Sour[i]);
			_Sour[i]->OnCollision(_Dest);

			// 상하 충돌
			if (fX > fY)
			{
				// 상 충돌
				if (_Dest->Get_Info().fCY > _Sour[i]->Get_Info().fCY)
				{
					if (_bPush)_Sour[i]->Set_PosY(-fY);
				}
				// 하 충돌
				else
				{
					if (_bPush)_Sour[i]->Set_PosY(fY);
				}
			}
			// 좌우 충돌
			else
			{
				// 좌 충돌
				if (_Dest->Get_Info().fCX > _Sour[i]->Get_Info().fCX)
				{
					if (_bPush)_Sour[i]->Set_PosX(-fX);
				}
				// 우 충돌
				else
				{
					if (_bPush)_Sour[i]->Set_PosX(fX);
				}
			}

		}


	}
}
void CCollisionMgr::CollisionEquipUI_RectEx(CObj* _Dest, CEquipS_UI** _Sour, bool _bPush)
{

	for (int i = 0; i < 7; ++i)
	{
		float	fX = 0.f, fY = 0.f;

		if (Check_Rect(_Dest, _Sour[i], &fX, &fY))
		{
			_Dest->OnCollision(_Sour[i]);
			_Sour[i]->OnCollision(_Dest);

			// 상하 충돌
			if (fX > fY)
			{
				// 상 충돌
				if (_Dest->Get_Info().fCY > _Sour[i]->Get_Info().fCY)
				{
					if (_bPush)_Sour[i]->Set_PosY(-fY);
				}
				// 하 충돌
				else
				{
					if (_bPush)_Sour[i]->Set_PosY(fY);
				}
			}
			// 좌우 충돌
			else
			{
				// 좌 충돌
				if (_Dest->Get_Info().fCX > _Sour[i]->Get_Info().fCX)
				{
					if (_bPush)_Sour[i]->Set_PosX(-fX);
				}
				// 우 충돌
				else
				{
					if (_bPush)_Sour[i]->Set_PosX(fX);
				}
			}

		}


	}
}
void CCollisionMgr::CollisionSoundUI_RectEx(CObj* _Dest, CSoundButton** _Sour, bool _bPush)
{

	for (int i = 0; i < 11; ++i)
	{
		float	fX = 0.f, fY = 0.f;

		if (Check_Rect(_Dest, _Sour[i], &fX, &fY))
		{
			_Dest->OnCollision(_Sour[i]);
			_Sour[i]->OnCollision(_Dest);

			// 상하 충돌
			if (fX > fY)
			{
				// 상 충돌
				if (_Dest->Get_Info().fCY > _Sour[i]->Get_Info().fCY)
				{
					if (_bPush)_Sour[i]->Set_PosY(-fY);
				}
				// 하 충돌
				else
				{
					if (_bPush)_Sour[i]->Set_PosY(fY);
				}
			}
			// 좌우 충돌
			else
			{
				// 좌 충돌
				if (_Dest->Get_Info().fCX > _Sour[i]->Get_Info().fCX)
				{
					if (_bPush)_Sour[i]->Set_PosX(-fX);
				}
				// 우 충돌
				else
				{
					if (_bPush)_Sour[i]->Set_PosX(fX);
				}
			}

		}


	}
}


bool CCollisionMgr::Check_Rect(CObj* pDest, CObj* pSour, float* pX, float* pY)
{
	float		fWidth = abs(pDest->Get_Info().fCX - pSour->Get_Info().fCX);
	float		fHeight = abs(pDest->Get_Info().fCY - pSour->Get_Info().fCY);

	float		fCX = (pDest->Get_Info().fCCX + pSour->Get_Info().fCCX) * 0.5f;
	float		fCY = (pDest->Get_Info().fCCY + pSour->Get_Info().fCCY) * 0.5f;

	if ((fCX > fWidth) && (fCY > fHeight))
	{
		*pX = fCX - fWidth;
		*pY = fCY - fHeight;

		return true;
	}

	return false;
}

bool CCollisionMgr::Check_Sphere(CObj* pDest, CObj* pSour)
{

	// abs : 절대값을 구해주는 함수
	float	fWidth = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float	fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	// sqrt : 루트를 씌워주는 함수
	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (pDest->Get_Info().fCCX + pSour->Get_Info().fCCX) * 0.5f;

	return fRadius > fDiagonal;
}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour)
{

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (Check_Sphere(Dest, Sour))
			{
				Dest->Set_Dead();
				Sour->Set_Dead();
			}
		}
	}
}
