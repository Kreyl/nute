#include "ArmletAppSDK.h"
#include "Med.h"

namespace medicine {

	const char* CureNames[] = {
		"����� ��������������",			//common
		"�����������",					//common
		"��������������",				//common
		"���������",					//common
		"����������",					//common
		"������������� �����",			//med
		"������������� ����",			//med
		"������������",					//med
		"������� ��������� ������",		//med
		"������� ������",				//med
		"����������",					//common
		"���������",					//med
		"��������",						//med
		"��������������",				//med
		"�������"						//MG
	};

	const char* CureEffects[] = {
		"���� ������� ����... ������ ����� ������.",
		"���� ������� ����... �� ���������� ���������� ����������.",
		"���� ������� ����... ���������� ��������.",
		"������ ����� ������ �����...",
		"���� ������� ����... ������� ����������.",
		"���� ������� ����... �� ���������� ������� ���.",
		"������� ��������� ������ ���� ������� �� ����� ����� �������...",
		"���� ������� ����... ��� ���� �������������.",
		"���� ������� ����... ���� ������ ����� �������� �������.",
		"���� ������� ����... ����� ����� ������ �� �����������.",
		"�� ����� ��������...",
		"�� ����� ��������� �����, �������� �������...",
		"���� ������� ����... ���� ������ ����� ������ ���������� � ����������.",
		"---",
		"���� ������� ����...�� ������� � ������������, ��� ������� ������."
	};

	COMPILE_TIME_CHECK(sizeof(CureNames)/sizeof(char*)==MaxCureId);
	COMPILE_TIME_CHECK(sizeof(CureEffects)/sizeof(char*)==MaxCureId);

	CURE_DESC CureDescs[MaxCureId];

	void InitCureDescs()
	{
		for (int i=0;i<MaxCureId;i++) {
			CureDescs[i].id = (CURE_ID)i;
			CureDescs[i].Name = CureNames[i];
			CureDescs[i].Effect = CureEffects[i];
		}
	}	

} //namespace

/*
const CURE_DESC CureDescs[MaxCureId] = 
{
	{
		Anesthetics,
		"����� ��������������",
		"�������� ������� ��������",
		"�������� ������� ���� �� 1",
		"�������� �������",
		"�������, ������������ � ������� ���� 2 (�� ��������� ��������������)"
	},
	{
		Antispasmodic,
		"�����������",
		"���������� ����� �����������, �������������� �����, ����� � �������",
		"��������� ����� � �����, ������������� ������, �������� � �����."
			"����� ������������ ������ �������� � '���������' �� ���� �������", //regeneration based
		"��� ����������������",
		"�������� ����, ������� ���� 1"
	},
	{
		Pyretic,
		"��������������",
		"��������� ����, ���������� ��������",
		"������� ���, ��������� ��������, �������� ����������",
		"�������� �����, �������� ��������, ������",
		"�������� �������� ������ � ������, �������� �����, �����"
	},
	{
		Aspirator,
		"���������",
		"����������� �������",
		"������������ ������� �������� � ������� 10 �����",
		"��� ����������������",
		"������� �����, ������ ������"
	},
	{
		CoagulationFactor,
		"������ �������������� �����",
		"������������ �����������",
		"����������� ������������. ����������� ����� �����.", //regeneration based
		"��� ����������������",
		"��� �������� �������� ������ � ����� �������� ������� ���� �� 1"
		"��� ���������� �� ������ � ������������ ��������� ��������� ������� � ��������� ��������� (��������� 1 ��� �� �������)"

	},
	{
		SyntheticBlood,
		"������������� �����",
		"�������������� ������ �����",
		"����������� ����� �����. ���������� ������������� �������", //regeneration based
		"��� ����������������",
		"�����, ���"
	},
	{
		Leatherette,
		"������������� ����",
		"������� ������",
		"�������� ������� ����, ��������������� ����� �����, ��������� ����", //regeneration based
		"���� �������",
		"���"
	},
	{
		Myorelaxant,
		"������������",
		"����������� �������, ������������ ���� �������",
		"'���������' �� ���� �������, �������� � ����� ������������",
		"�����, ������������� ������� �����",
		"������ �����, ������ ��� �����������������, ��������� �� ������������� �������� �������"
	},
	{
		VisceraNanoPack,
		"��� ������������ ��� ���������� �������",
		"������� ������ � ��������",
		"",
		"",
		""
	},
	{
		Anesthetics,
		"��� ����������� ������������",
		"������� ������� ����������� � ������������� ������� �����",
		"",
		"",
		""
	},
	{
		Antibiotic,
		"��� ����������� ������������",
		"������� ������� ����������� � ������������� ������� �����",
		"",
		"",
		""
	},
	{
		Absorber,
		"��� ����������� ������������",
		"������� ������� ����������� � ������������� ������� �����",
		"",
		"",
		""
	},
	{
		PlasterNanoPack,
		"��� ����������� ������������",
		"������� ������� ����������� � ������������� ������� �����",
		"",
		"",
		""
	},
	{
		NanoExoFrame,
		"��� ����������� ������������",
		"������� ������� ����������� � ������������� ������� �����",
		"",
		"",
		""
	},
	{
		MagicCure,
		"��� ����������� ������������",
		"������� ������� ����������� � ������������� ������� �����",
		"",
		"",
		""
	}
};
COMPILE_TIME_CHECK(sizeof(CureDescs)/sizeof(CURE_DESC)==MaxCureId);
}
*/
