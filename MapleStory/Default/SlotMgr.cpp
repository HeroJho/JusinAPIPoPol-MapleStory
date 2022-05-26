#include "stdafx.h"
#include "SlotMgr.h"
#include "InvenMgr.h"
#include "SkillMgr.h"


CSlotMgr* CSlotMgr::m_pInstance = nullptr;
CSlotMgr::CSlotMgr()
	: m_aSlotInfo{}
{
}

CSlotMgr::~CSlotMgr()
{
	Release();
}

void CSlotMgr::Initialize(void)
{
	for (int i = 0; i < 12; ++i)
		m_aSlotInfo[i] = new CSlotTemp;
}

int CSlotMgr::Update(void)
{
	for (int i = 0; i < 12; ++i)
	{
		if (m_aSlotInfo[i]->GetInfo().InvenID != 100 && m_aSlotInfo[i]->GetInfo().InvenID != 101)
		{
			ITEM itemInfo = CInvenMgr::Get_Instance()->FInd_Info(m_aSlotInfo[i]->GetInfo().InvenID);
			m_aSlotInfo[i]->SetInfo(itemInfo);
		}
	}

	return 0;
}

void CSlotMgr::Release(void)
{
	for (int i = 0; i < 12; ++i)
		Safe_Delete(m_aSlotInfo[i]);
}

void CSlotMgr::SetSlotInfo(ITEM _eInfo, int _iIndex)
{
	ITEM temp = m_aSlotInfo[_iIndex]->GetInfo();
	m_aSlotInfo[_iIndex]->SetInfo(_eInfo);

	if (_eInfo.SlotIdex == 99)
		return;

	m_aSlotInfo[_eInfo.SlotIdex]->SetInfo(temp);

}

void CSlotMgr::ChangeSlot(int _iLeftId, int _iRightId)
{
	ITEM temp = m_aSlotInfo[_iLeftId]->GetInfo();
	m_aSlotInfo[_iLeftId]->SetInfo(m_aSlotInfo[_iRightId]->GetInfo());
	m_aSlotInfo[_iRightId]->SetInfo(temp);
}

void CSlotMgr::UseA()
{
	if (m_aSlotInfo[0]->GetInfo().InvenID == 100)
		return;

	// 스킬이냐 아니냐
	if (m_aSlotInfo[0]->GetInfo().eID == IT_SKILL)
	{
		if (m_aSlotInfo[0]->GetInfo().sTag == "Skill_1")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL1);
		else if (m_aSlotInfo[0]->GetInfo().sTag == "Skill_2")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL2);
		else if (m_aSlotInfo[0]->GetInfo().sTag == "Skill_3")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL3);
		else if (m_aSlotInfo[0]->GetInfo().sTag == "Skill_4")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL4, 'A');
	}
	else if(m_aSlotInfo[0]->GetInfo().eID == IT_CONSUM)
	{
		CInvenMgr::Get_Instance()->Use_Item(m_aSlotInfo[0]->GetInfo().InvenID);
	}
}

void CSlotMgr::UseS()
{
	if (m_aSlotInfo[1]->GetInfo().InvenID == 100)
		return;

	// 스킬이냐 아니냐
	if (m_aSlotInfo[1]->GetInfo().eID == IT_SKILL)
	{
		if (m_aSlotInfo[1]->GetInfo().sTag == "Skill_1")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL1);
		else if (m_aSlotInfo[1]->GetInfo().sTag == "Skill_2")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL2);
		else if (m_aSlotInfo[1]->GetInfo().sTag == "Skill_3")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL3);
		else if (m_aSlotInfo[1]->GetInfo().sTag == "Skill_4")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL4, 'S');
	}
	else if (m_aSlotInfo[1]->GetInfo().eID == IT_CONSUM)
	{
		CInvenMgr::Get_Instance()->Use_Item(m_aSlotInfo[1]->GetInfo().InvenID);
	}
}

void CSlotMgr::UseD()
{
	if (m_aSlotInfo[2]->GetInfo().InvenID == 100)
		return;

	// 스킬이냐 아니냐
	if (m_aSlotInfo[2]->GetInfo().eID == IT_SKILL)
	{
		if (m_aSlotInfo[2]->GetInfo().sTag == "Skill_1")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL1);
		else if (m_aSlotInfo[2]->GetInfo().sTag == "Skill_2")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL2);
		else if (m_aSlotInfo[2]->GetInfo().sTag == "Skill_3")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL3);
		else if (m_aSlotInfo[2]->GetInfo().sTag == "Skill_4")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL4, 'D');
	}
	else if (m_aSlotInfo[2]->GetInfo().eID == IT_CONSUM)
	{
		CInvenMgr::Get_Instance()->Use_Item(m_aSlotInfo[2]->GetInfo().InvenID);
	}
}

void CSlotMgr::Use1()
{
	if (m_aSlotInfo[3]->GetInfo().InvenID == 100)
		return;

	// 스킬이냐 아니냐
	if (m_aSlotInfo[3]->GetInfo().eID == IT_SKILL)
	{
		if (m_aSlotInfo[3]->GetInfo().sTag == "Skill_1")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL1);
		else if (m_aSlotInfo[3]->GetInfo().sTag == "Skill_2")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL2);
		else if (m_aSlotInfo[3]->GetInfo().sTag == "Skill_3")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL3);
		else if (m_aSlotInfo[3]->GetInfo().sTag == "Skill_4")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL4 ,'1');
	}
	else if (m_aSlotInfo[3]->GetInfo().eID == IT_CONSUM)
	{
		CInvenMgr::Get_Instance()->Use_Item(m_aSlotInfo[3]->GetInfo().InvenID);
	}
}

void CSlotMgr::Use2()
{
	if (m_aSlotInfo[4]->GetInfo().InvenID == 100)
		return;

	// 스킬이냐 아니냐
	if (m_aSlotInfo[4]->GetInfo().eID == IT_SKILL)
	{
		if (m_aSlotInfo[4]->GetInfo().sTag == "Skill_1")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL1);
		else if (m_aSlotInfo[4]->GetInfo().sTag == "Skill_2")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL2);
		else if (m_aSlotInfo[4]->GetInfo().sTag == "Skill_3")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL3);
		else if (m_aSlotInfo[4]->GetInfo().sTag == "Skill_4")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL4, '2');
	}
	else if (m_aSlotInfo[4]->GetInfo().eID == IT_CONSUM)
	{
		CInvenMgr::Get_Instance()->Use_Item(m_aSlotInfo[4]->GetInfo().InvenID);
	}
}

void CSlotMgr::Use3()
{
	if (m_aSlotInfo[5]->GetInfo().InvenID == 100)
		return;

	// 스킬이냐 아니냐
	if (m_aSlotInfo[5]->GetInfo().eID == IT_SKILL)
	{
		if (m_aSlotInfo[5]->GetInfo().sTag == "Skill_1")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL1);
		else if (m_aSlotInfo[5]->GetInfo().sTag == "Skill_2")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL2);
		else if (m_aSlotInfo[5]->GetInfo().sTag == "Skill_3")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL3);
		else if (m_aSlotInfo[5]->GetInfo().sTag == "Skill_4")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL4, '3');
	}
	else if (m_aSlotInfo[5]->GetInfo().eID == IT_CONSUM)
	{
		CInvenMgr::Get_Instance()->Use_Item(m_aSlotInfo[5]->GetInfo().InvenID);
	}
}

void CSlotMgr::UseZ()
{
	if (m_aSlotInfo[6]->GetInfo().InvenID == 100)
		return;

	// 스킬이냐 아니냐
	if (m_aSlotInfo[6]->GetInfo().eID == IT_SKILL)
	{
		if (m_aSlotInfo[6]->GetInfo().sTag == "Skill_1")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL1);
		else if (m_aSlotInfo[6]->GetInfo().sTag == "Skill_2")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL2);
		else if (m_aSlotInfo[6]->GetInfo().sTag == "Skill_3")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL3);
		else if (m_aSlotInfo[6]->GetInfo().sTag == "Skill_4")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL4, 'Z');
	}
	else if (m_aSlotInfo[6]->GetInfo().eID == IT_CONSUM)
	{
		CInvenMgr::Get_Instance()->Use_Item(m_aSlotInfo[6]->GetInfo().InvenID);
	}
}

void CSlotMgr::UseX()
{
	if (m_aSlotInfo[7]->GetInfo().InvenID == 100)
		return;

	// 스킬이냐 아니냐
	if (m_aSlotInfo[7]->GetInfo().eID == IT_SKILL)
	{
		if (m_aSlotInfo[7]->GetInfo().sTag == "Skill_1")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL1);
		else if (m_aSlotInfo[7]->GetInfo().sTag == "Skill_2")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL2);
		else if (m_aSlotInfo[7]->GetInfo().sTag == "Skill_3")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL3);
		else if (m_aSlotInfo[7]->GetInfo().sTag == "Skill_4")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL4, 'X');
	}
	else if (m_aSlotInfo[7]->GetInfo().eID == IT_CONSUM)
	{
		CInvenMgr::Get_Instance()->Use_Item(m_aSlotInfo[7]->GetInfo().InvenID);
	}
}

void CSlotMgr::UseC()
{
	if (m_aSlotInfo[8]->GetInfo().InvenID == 100)
		return;

	// 스킬이냐 아니냐
	if (m_aSlotInfo[8]->GetInfo().eID == IT_SKILL)
	{
		if (m_aSlotInfo[8]->GetInfo().sTag == "Skill_1")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL1);
		else if (m_aSlotInfo[8]->GetInfo().sTag == "Skill_2")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL2);
		else if (m_aSlotInfo[8]->GetInfo().sTag == "Skill_3")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL3);
		else if (m_aSlotInfo[8]->GetInfo().sTag == "Skill_4")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL4, 'C');
	}
	else if (m_aSlotInfo[8]->GetInfo().eID == IT_CONSUM)
	{
		CInvenMgr::Get_Instance()->Use_Item(m_aSlotInfo[8]->GetInfo().InvenID);
	}
}

void CSlotMgr::Use4()
{
	if (m_aSlotInfo[9]->GetInfo().InvenID == 100)
		return;

	// 스킬이냐 아니냐
	if (m_aSlotInfo[9]->GetInfo().eID == IT_SKILL)
	{
		if (m_aSlotInfo[9]->GetInfo().sTag == "Skill_1")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL1);
		else if (m_aSlotInfo[9]->GetInfo().sTag == "Skill_2")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL2);
		else if (m_aSlotInfo[9]->GetInfo().sTag == "Skill_3")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL3);
		else if (m_aSlotInfo[9]->GetInfo().sTag == "Skill_4")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL4, '4');
	}
	else if (m_aSlotInfo[9]->GetInfo().eID == IT_CONSUM)
	{
		CInvenMgr::Get_Instance()->Use_Item(m_aSlotInfo[9]->GetInfo().InvenID);
	}
}

void CSlotMgr::Use5()
{
	if (m_aSlotInfo[10]->GetInfo().InvenID == 100)
		return;

	// 스킬이냐 아니냐
	if (m_aSlotInfo[10]->GetInfo().eID == IT_SKILL)
	{
		if (m_aSlotInfo[10]->GetInfo().sTag == "Skill_1")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL1);
		else if (m_aSlotInfo[10]->GetInfo().sTag == "Skill_2")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL2);
		else if (m_aSlotInfo[10]->GetInfo().sTag == "Skill_3")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL3);
		else if (m_aSlotInfo[10]->GetInfo().sTag == "Skill_4")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL4, '5');
	}
	else if (m_aSlotInfo[10]->GetInfo().eID == IT_CONSUM)
	{
		CInvenMgr::Get_Instance()->Use_Item(m_aSlotInfo[10]->GetInfo().InvenID);
	}
}

void CSlotMgr::Use6()
{
	if (m_aSlotInfo[11]->GetInfo().InvenID == 100)
		return;

	// 스킬이냐 아니냐
	if (m_aSlotInfo[11]->GetInfo().eID == IT_SKILL)
	{
		if (m_aSlotInfo[11]->GetInfo().sTag == "Skill_1")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL1);
		else if (m_aSlotInfo[11]->GetInfo().sTag == "Skill_2")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL2);
		else if (m_aSlotInfo[11]->GetInfo().sTag == "Skill_3")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL3);
		else if (m_aSlotInfo[11]->GetInfo().sTag == "Skill_4")
			CSkillMgr::Get_Instance()->UseSkill(SK_SKILL4, '6');
	}
	else if (m_aSlotInfo[11]->GetInfo().eID == IT_CONSUM)
	{
		CInvenMgr::Get_Instance()->Use_Item(m_aSlotInfo[11]->GetInfo().InvenID);
	}
}
