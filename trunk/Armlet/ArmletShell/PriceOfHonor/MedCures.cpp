#include "ArmletShell.h"
#include "Med.h"

namespace price_of_honor {

/*
typedef struct _CureStrings_t {
	CURE_ID const id;					//cure id
	char const*const Name;				//cure name
	char const*const Purpose;			//cure purpose description
	char const*const Effect;			//cure effect description
	char const*const Contraindications;	//cure contraindications description
	char const*const SideEffects;		//cure side effects description
} CureStrings_t;

const CureStrings_t CureStrings[MaxCureId] =
*/

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
		RespiratoryNanoPack,
		"��� ����������� ������������",
		"������� ������� ����������� � ������������� ������� �����",
		"",
		"",
		""
	},
	{
		RespiratoryNanoPack,
		"��� ����������� ������������",
		"������� ������� ����������� � ������������� ������� �����",
		"",
		"",
		""
	},
	{
		RespiratoryNanoPack,
		"��� ����������� ������������",
		"������� ������� ����������� � ������������� ������� �����",
		"",
		"",
		""
	},
	{
		RespiratoryNanoPack,
		"��� ����������� ������������",
		"������� ������� ����������� � ������������� ������� �����",
		"",
		"",
		""
	},
	{
		RespiratoryNanoPack,
		"��� ����������� ������������",
		"������� ������� ����������� � ������������� ������� �����",
		"",
		"",
		""
	},
	{
		RespiratoryNanoPack,
		"��� ����������� ������������",
		"������� ������� ����������� � ������������� ������� �����",
		"",
		"",
		""
	},
	{
		RespiratoryNanoPack,
		"��� ����������� ������������",
		"������� ������� ����������� � ������������� ������� �����",
		"",
		"",
		""
	}
};
COMPILE_TIME_CHECK(sizeof(CureDescs)/sizeof(CURE_DESC)==MaxCureId);

#define NEW_CURE(x)	\
	class x##Cure_t : public Cure_t { \
	public: \
		static CURE_ID const id = x; \
		virtual void OnUse(void) const; \
		virtual void OnTick(void) const; \
	}; \
	x##Cure_t const x##Cure
#define CURE_PTR(x)	&x##Cure

NEW_CURE(Anesthetics);
NEW_CURE(Antispasmodic);
NEW_CURE(Pyretic);
NEW_CURE(Aspirator);
NEW_CURE(CoagulationFactor);
NEW_CURE(SyntheticBlood);
NEW_CURE(Leatherette);
NEW_CURE(Myorelaxant);
NEW_CURE(VisceraNanoPack);
NEW_CURE(RespiratoryNanoPack);

const Cure_t* Cures[MaxCureId] = {
	CURE_PTR(Anesthetics),
	CURE_PTR(Antispasmodic),
	CURE_PTR(Pyretic),
	CURE_PTR(Aspirator),
	CURE_PTR(CoagulationFactor),
	CURE_PTR(SyntheticBlood),
	CURE_PTR(Leatherette),
	CURE_PTR(Myorelaxant),
	CURE_PTR(VisceraNanoPack),
	CURE_PTR(RespiratoryNanoPack)
};
COMPILE_TIME_CHECK(sizeof(Cures)/sizeof(Cure_t)==MaxCureId);

#define CURE_STATIC_MEMBER_AS_INLINE_GETTER(x) \
	inline const char* Cure_t::Cure##x(void) \
	{ \
		return CureDesc[Cure_t::id].x; \
	}

CURE_STATIC_MEMBER_AS_INLINE_GETTER(Name);
CURE_STATIC_MEMBER_AS_INLINE_GETTER(Purpose);
CURE_STATIC_MEMBER_AS_INLINE_GETTER(Effect);
CURE_STATIC_MEMBER_AS_INLINE_GETTER(Contraindications);
CURE_STATIC_MEMBER_AS_INLINE_GETTER(SideEffects);

inline const Cure_t* GetCureById(CURE_ID id)
{
	return Cures[id];
}

//TODO DBG
bool CheckCures()
{
	for (int i=0; i<MaxCureId; i++)
	{
		Cure_t const*const obj = GetCureById((CURE_ID)i);
		if (obj->id != i) goto out;
	}
	return true;
out:
	return false;
}

void AnestheticsCure_t::OnUse(void) const
{
//	�������� ������� ��������.

	//CureDuration = 20
	//Reduce PAIN_LEVEL 1
/*
"� ��������� � ��������� ��������� ������,
�������� ������� �������� � ��������� �������
�������� ���������� ����������� ������� � ������������.
������� ���� 2 (�� ��������� ��������������)."
*/
}

void AnestheticsCure_t::OnTick(void) const
{
}

void AntispasmodicCure_t::OnUse(void) const
{
//	���������� ����� �����������, �������������� �����, ����� � �������.

	//CureDuration = ?
	//Reg 1: "��������� ����� � �����, ������������� ������, �������� � �����.
//				��������������� ������ ��������, ""���������"" �� ���� �������."
	//Reg 2: "��������� ����� � �����, ������������� ������, �������� � �����, �������� ��������������� ������ ��������."
	//Reg 3: "��������� ����� � �����, ������������� ������ �������� � �����"
/*
�������� ����, ������� ����: 1
*/
}

void AntispasmodicCure_t::OnTick(void) const
{
}

void PyreticCure_t::OnUse(void) const
{
//	��������� ����, ���������� ��������.

	//������� ���, ��������� ��������, �������� ����������.
/*
"� ��������� � ��������� ������� � �������� ������������ ���������� �������� �������� �������� ������ � ������.
������. � ��������� � ������ ��������� � ������� ��������, �������� ����� ��� �������.
"
*/
}

void PyreticCure_t::OnTick(void) const
{
}

void AspiratorCure_t::OnUse(void) const
{
//	����������� ������� ��� ������� ���������� �������.

	//������������ ������� �������� � ������� 10 �����.
/*
������� ���� ��� ����� � ������, ������������� �������� �����.
*/
}

void AspiratorCure_t::OnTick(void) const
{
}

void CoagulationFactorCure_t::OnUse(void) const
{
//	������������ �����������

//	Reg 1: �����: ����������� ������������
	//Reg 2: "����������: +5 ��. ����� �����: ����������� ������������"
	//Reg 3: "����������: +10 ��. ����� �����: + 1 ��. ����� � ������"
/*
"� ��������� � ��������� ��������� ������ � ����� �������� ������� ���� �� 1.
��� ���������� �� ������ � ������������ ��������� ��������� ������� � ��������� ��������� (��������� 1 ��� �� �������).
"
*/
}

void CoagulationFactorCure_t::OnTick(void) const
{
}

void SyntheticBloodCure_t::OnUse(void) const
{
	//�������������� ������ �����

	//Reg 1: "����������: +10 ��. �����
	//Reg 2: "	"����������: +20 ��. �����
	//Reg 3: "	"����������: +30 ��. �����
/*
������������� ������� ��������� � ���������� ��������� (��������� 1 ��� �� �������).
"	����� (��������� ����� ������ � �����), ���.
*/
}

void SyntheticBloodCure_t::OnTick(void) const
{
}

void LeatheretteCure_t::OnUse(void) const
{
	//������� ������

	//Reg 1: "�������� ������� ���� �� 1 + 5 ��. �����"
	//Reg 2: 	"�������� ������� ���� �� 1 + 10 ��. �����"
	//Reg 3: 	"�������� ������� ���� �� 1 + 10 ��. ����� ���� ��������� � ���������� ��������� (��������� 1 ��� �� �������)"
/*
�� ����������� � ��������� � ���� �������.
*/
}

void LeatheretteCure_t::OnTick(void) const
{
}

void MyorelaxantCure_t::OnUse(void) const
{
	//����������� �������, ������������ ���� ������� ������� �������� �������.

	//������� "�����������" �� ���� �������, �������� � ����� ������������.
/*
"������ ����� 5 ��.
������ ��������� � �������� � ������ (��������� ������� � ��������� ������������).
������ ��������� � �������� � ����������� ����� (��������� ������� � ��������� ������������).
��� ������������� ������ ��� ����� 10 ����� ����� ������������ ��������� ����� ������� � ��������� ���������."
*/
}

void MyorelaxantCure_t::OnTick(void) const
{
}

void VisceraNanoPackCure_t::OnUse(void) const
{
	//"��������� ��� ������� ������ � �������� ��������� 2 � ����.
	//����� ������������ ��� ������� ���������� ���������� � �����."
/*
Reg1:
"��������� ������������ ��� ������� ���� �� 1 ��������� �� 20 ����� �� ������� ���������.
���������� ����������� ��� ������������� ��������."

Reg2:
"��������� ������������ ��� ������� ���� �� 1 ��������� �� 15 ����� �� ������� ���������.
�������� ������� ���� �� 1.
���������� ����������� ��� ������������� ��������."

Reg3:
"��������� ������������ ��� ������� ���� �� 1 ��������� �� 10 ����� �� ������� ���������.
���������� ����������� ��� ������������� ��������.
�������� ������� ���� �� 1
+ 3 ��. ����� � ������ �� ������� ��������������.
"

"�������� ����� � ���� �� ���� ����, ������� ����� (��������� ����� ������ � �����).
�� ��������� � �������� � ���� �������.
� ���� ��������� � ������������ �������, �������� ������� ���������� � ��������� ������� � ��������� ���������.
"
*/
}

void VisceraNanoPackCure_t::OnTick(void) const
{
}

void RespiratoryNanoPackCure_t::OnUse(void) const
{
	/*
	��������� ��� ������� ������� ����������� � ���������� ����� ������� ���������.

	"��������� ������� ����������� ��� ��������� ����� �� 1 ��������� �� 20 ����� �� ������� ���������.
	���������� ���� � ������ ��� 1 � 2 ���������� �������."

	"��������� ������� ����������� ��� ��������� ����� �� 1 ��������� �� 15 ����� �� ������� ���������.
	�������� ������� ���� �� 1.
	���������� ���� � ������ ��� 1 � 2 ���������� �������."

	"��������� ������� ����������� ��� ��������� ����� �� 1 ��������� �� 10 ����� �� ������� ���������.
	���������� ���� � ������ ��� 1 � 2 ���������� �������.
	�������� ������� ���� �� 1
	+ 3 ��. ����� � ������ �� ������� ��������������.

"�������� ����� � ���� �� ���� ����, ������� ����� (��������� ����� ������ � �����).
�� ��������� � �������� � ���� �������.
� ���� ��������� � ������������ �������, �������� ������� ���������� � ��������� ������� � ��������� ���������.
"
*/
}

void RespiratoryNanoPackCure_t::OnTick(void) const
{
}

}//namespace

#if 0
��� ������������ ��� ���������� �������.	"��������� ��� ������� ������ � �������� ��������� 2 � ����.
����� ������������ ��� ������� ���������� ���������� � �����."	"��������� ������������ ��� ������� ���� �� 1 ��������� �� 20 ����� �� ������� ���������.
���������� ����������� ��� ������������� ��������."	"��������� ������������ ��� ������� ���� �� 1 ��������� �� 15 ����� �� ������� ���������.
�������� ������� ���� �� 1.
���������� ����������� ��� ������������� ��������."	"��������� ������������ ��� ������� ���� �� 1 ��������� �� 10 ����� �� ������� ���������.
���������� ����������� ��� ������������� ��������.
�������� ������� ���� �� 1
+ 3 ��. ����� � ������ �� ������� ��������������.
"	"�������� ����� � ���� �� ���� ����, ������� ����� (��������� ����� ������ � �����).
�� ��������� � �������� � ���� �������.
� ���� ��������� � ������������ �������, �������� ������� ���������� � ��������� ������� � ��������� ���������.
"
��� ����������� ������������	��������� ��� ������� ������� ����������� � ���������� ����� ������� ���������.	"��������� ������� ����������� ��� ��������� ����� �� 1 ��������� �� 20 ����� �� ������� ���������.
���������� ���� � ������ ��� 1 � 2 ���������� �������."	"��������� ������� ����������� ��� ��������� ����� �� 1 ��������� �� 15 ����� �� ������� ���������.
�������� ������� ���� �� 1.
���������� ���� � ������ ��� 1 � 2 ���������� �������."	"��������� ������� ����������� ��� ��������� ����� �� 1 ��������� �� 10 ����� �� ������� ���������.
���������� ���� � ������ ��� 1 � 2 ���������� �������.
�������� ������� ���� �� 1
+ 3 ��. ����� � ������ �� ������� ��������������.
"	"�������� ����� � ���� �� ���� ����, ������� ����� (��������� ����� ������ � �����).
�� ��������� � �������� � ���� �������.
� ���� ��������� � ������������ �������, �������� ������� ���������� � ��������� ������� � ��������� ���������.
"

//Anesthetics_CureEffect
//Anesthetics_SideEffect

/*
CURES:
name, function, action (3 per regeneration level), side effects

""

�������� ������� ���� �� 1
�������� ������� ���� �� 1
�������� ������� ���� �� 1
"� ��������� � ��������� ��������� ������, �������� ������� �������� � ���������
������� �������� ���������� ����������� ������� � ������������.
������� ���� 2 (�� ��������� ��������������)."
�����
*/

/*
FEELING FACTORS:
(aka SYMPTOMS:
	name, brief description, description for patient
PAIN		(1-3)
SPECIFIC_PAIN (1-3)	//"������� ����, ��������� ����, �������"
COUGH		(1-2)	//"������/�������" "������"
CONVULTION	(1-2)	//"������/�������" "��������"
WHEEZE		(1-2)	//"������/�������" "����"
FEVER		(1)		//"���"
UNCONSCIOUS (1)		//"��� ��������"
DELIRIUM	(1)		//"����"
CONFUSION	(1)		//"�������� �������"
VISUAL HALLUTINATIONS "���������� ������������"
DISRUPTED PERCEPTION "���������� ��������"
nausea				//"�������"
retching			//"�����"
cannot breathe		//"������� �� ����� ������"
Impaired fine motor skills //"������ �������� ��������"
BOXER_POSE			//"���� �������"
VERTIGO				//"��������������"
*/
}
#endif

void OnUseAnesthetics()
{
	//PainLevel -= 1;
/*
	if (
		(Body.Wounds[HEAD_SHOT]==Insidious)||
		(Body.Wounds[KNOCKOUT]==Insidious)
		)
	{
		//SPECIFIC_PAIN[�������]
	}
*/

	//Head
/*
"� ��������� � ��������� ��������� ������, �������� ������� �������� � ��������� ������� �������� ���������� ����������� ������� � ������������.
������� ���� 2 (�� ��������� ��������������)."
*/
}

void OnTickAnesthetics()
{
}
void OnUseAntispasmodic()
{
}
void OnTickAntispasmodic()
{
}
void OnUsePyretic()
{
}
void OnTickPyretic()
{
}
void OnUseAspirator()
{
}
void OnTickAspirator()
{
}
void OnUseCoagulationFactor()
{
}
void OnTickCoagulationFactor()
{
}
void OnUseSyntheticBlood()
{
}
void OnTickSyntheticBlood()
{
}
void OnUseLeatherette()
{
}
void OnTickLeatherette()
{
}
void OnUseMyorelaxant()
{
}
void OnTickMyorelaxant()
{
}
void OnUseVisceraNanoPack()
{
}
void OnTickVisceraNanoPack()
{
}
void OnUseRespiratoryNanoPack()
{
}
void OnTickRespiratoryNanoPack()
{
}

