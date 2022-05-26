#include "stdafx.h"
#include "Item_Info.h"
#include "Player.h"
#include "ObjMgr.h"
#include "SoundMgr.h"




CItem_Info::CItem_Info()
{
}

CItem_Info::~CItem_Info()
{
}

void CItem_Info::Use_Item()
{
	if (m_sInfo.sTag == "RedPosion")
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_ITEM);
		CSoundMgr::Get_Instance()->PlaySound(L"PosionUse.wav", SOUND_ITEM, 1);
		((CPlayer*)CObjMgr::Get_Instance()->Get_Player())->IncreaseHp(40);
	}
	else if (m_sInfo.sTag == "BluePosion")
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_ITEM);
		CSoundMgr::Get_Instance()->PlaySound(L"PosionUse.wav", SOUND_ITEM, 1);
		((CPlayer*)CObjMgr::Get_Instance()->Get_Player())->IncreaseMp(50);
	}
}