#include "ArmletAppSDK.h"
#include "Med.h"

namespace medicine {

const char* SymptomEffects[] = {
    "������� ���������� � ��������� ��������� ����.",
    "������� ������� �����, ����� �� ������� �� �� ������ �������� ����.",
    "������� ��������� ���� ����� ����, ��� �� ������� ��� ������� ����� ����������.",
    "������� ��������� ���� ����� ����, ��� �� ������� ��� ������� ����� ����������.",
    "�������, ��� ������� ���� ������ �� ���������.",
    "� ���� ����� �������� ������ (����� ��� ������), ������� ����, ��� � ���� ����.",
    "���-�� ����� ������ ��� ����, ������� ��� �����������, ������ � ����. ���� ������ ��� ����������, ��� ������.",
    "���� ������ ������, ������� �� ���������� ���� ������ ����, �������� �����.",
    "� ���� ������� � ������, ������ ������� �����������.",
    "� ������ ���������� ����, �� ������� ����� ����������.",
    "����� �� �������, ���� ��������� ���������� ����� �� ����� ����.",
    "������� ����� ��������� ���� ����, ����� ����������, ������ ��������, ������ ���������������.",
    "�� ��� �������� � ������ �� ����������. ��� � � �������.",
    "� ���� �������� ������. ����� ����� �� ���������� ���� ����.",
    "�� ������������� � ��������, ����� ��� ����� �������� ��� ���������. ��� - ���������� ������ ����� �����, ������� ��������� ���� ���������.",
    "������������ ���������, � ������� �� ������ ���������� - �������� � ����� �� ����, ������ ���� ������ � ������� � ��� ������. ���� ���� ���������� ����������� - �� ������� �� ���� �����, ���� ���� �� ��������.",
    "�� �� ������ ��������. �����, �������� �� �����, ��������� ����� - ��� ������ �����, ��� ������ ����� ����������!",
    "���� ��� ������, ��� ������ ������� � ����� ������.",
    "���� ������� ����������.",
    "�� �� ������ ��������������� - ��������� �������� �� ������� �������, �� ������ ��������� ������ �� ����.",
    "� ������ � ���� �����, �� ����� ������� �����, �� ������ �������� �� ����������� ���������.",
    "���� �� �������� ������ ����, �� �������, ��� ������ ������. ��� ������ ������ � �������� � �����������.",
    "�� ���������� �������� � �����, �������� - � �������. ���, ��� ������ ��������� ������� ����� �����, ������ ������� �����.",
    "����� ������ ������ ���� � �������� ������, ����������� ������, ������ �����������, ������� ������� �� ���.",
    "� ���� ������ ������. ���� ����� ��������.",
    "�� �� ������ ���� � ���� ������ ��� ����� ��� ������.",
    "�������� ���������� ������� ����. �������� ������ �� �� ������ ��������� �� ���������.",
    "�� �������, ��� � ������� �������� �����. �� ��������� �� �������� � �������� �� ����.",
    "������ ���� ��� ����� ���-�� ��������. ������� ���� ��������� ���� �� ���������.",
    "��� ������ �������� ������ ���� ���������� ���-�� ������, ������� ��������� ����.",
    "������ ����, ��� �� ������������ ����, ����������� ���� ��������.",
    "�� ���������� ������� ��������� ����. ��� ������, ����� ������ �������.",
    "���� ������ ������. ������ ��� ��� ����� ����, �������� ����� - ����� ����, ��� ����� �����.",
    "���� �����. ����� ������ ���� � ��������, ���� �� �������.",
    "���� ������. ��� ������ �������� � ������ ����� �������. ������� ��� �����, ������ �����. ���������� ����.",
    "������� ����� ����� ����������� �� ����� ������������� � �������������� ����� ���. ��� ������ � ����� ���� �������.",
    "���� ������ ���� ������. ��� � ��� ��������� ������� � ������ ������.",
    "���� ������ ������! ��������� �� ��� ��� ��������� ��� ����� ���� � ���������� �� ������������.",
    "�� ���������� ������� ������� ���� � ���� � ������� ��������.",
    "� ���� ������� ����� �����, �������, ������ ����� � ��� �������.",
    /*40*/"�� �� ������ ��������� ��� �������������� � �����. ������ �� ������.",
    "�� �� ������ ��������� ��� ��������� ������ - �������� ������� ���� ������.",
    "������ ������ ����, ��� ��������� � ����, ������� ��� � ������.",
    "�� ���������� ����������� ��� �� ���� ����, ������ ��� � ������� ������ ��� ����������� ����, ���� ���� �� �������� �� ������������� ����.",
    "���� �� �������� �������� ���� ���������� � ��������� ���������.",
    "�� ����� ���� �������� ��������� ������, �� ������ ������������ ����� � �����.",
    "���� ���� �������� ���������, ������ ������������� � ������� �������� ������� ����.",
    "�� �������� �� ������, ����� ����� ������, ���������� ��� ������.",
    "�� �������� ���� ������ � ���������. � ��� ����� ������ �������.",
    "������� �������� ��������� ��� ���� ����, ��������� ���������� �����, ��������� ������, ��������������� ������. ��� ������������ �������� ��� ����� ������.",
    "������ ���� ��� ����� ���������� ���� � ����. �� ���������� � �����, �� � ����� �����������. ��� ������������ �������� ��� ����� ������.",
    "�� ���������� ��������. ���� ������ ���������� �������� � ���������.",
    "� ���� � ���� ������, ���� ������� ������������ ��������. ��� �������, �� �������, ����� ������ ������.",
    "�� ���������� �������� �������� � ������� � ������� � �����.",
    "���� ��������� �������� ���, �� ���������� ��������, ���� ������ ���������������.",
    "� ������ ����� ��� � ��������, �� ���������� ������� ��������. ���� �������, ��� ��� ���������� ��� ���-�� ������.",
    "�� ������ ������ ������, ������ �����. ���, ��� ���������� ������, ���-�� ���������. ����� �������.",
    "� ������ � ���� ������ ������� �����, ���� ������� ������� � ��������������, �� ��� ���������.",
    "�� ��� ����� �������������� �������, ������ ��������, ��� ���� �����, ���������� ������� ���� ������, ��� ����� �� �������.",
    "�� ���������� ��������� ������� ���� � ������. �� �������� �� ����� ����. ����� ���� ��������� ������. ����� ���� ������ ���� �� ���������.",
    "�� ���������� ������� ���� �� ���� ����. �� �����������. ���� ��������� �������� ��� �� �����! ������ ���-������ ����������!",
    "������ � ���� � ����� ������ �������� � ������, ������ ���� ���������� �� ���� ����.",
    "� ���� ����� �������� ������ - ������ ��� ����� � ���� �� ���� �������. ����� ���� � ����� ����������.",
    "� ���� ����� ������, ��� ������ ��������� ��� �������� ��� ������ ����� ������� � ������ �����.",
    "� ���� ����� ������, ��� ������ ��������� ��� �������� ��� ������ ����� ������� � ������ �����.",
    "�� ���������� ������� ��� � �������� �� ���� ����, ���� ������� �����, �� ��� ���� ��� � �������.",
    "�� ���������� ���������� ��� �� ���� ����, ��� ������ ������, ���� ������ � ������� ����.",
    "���� �����, ������ ����� ����.",
    "���� �������, ���� ���� �����, ���� ������.",
    "���� ������� ����. �������� ���, ��� ������ - ���� �� ������� �����!",
    "���� ������ �� ������, ������ �� �����, ��� ����� ������� �� ������.",
    "�� ���������� ��� � ��������� ����. �� ��� ����� ������� �������, ������ ����� � ��������.",
    "� ������ � ���� ������ ������� �����, ���� ������� ������� � ��������������, �� ��� ���������.",
    "� ���� ��������� ������� �� ���, �� ���������� �������� � ��������������, ���� ������ ���������������.",
    "����, ����� � ������������ �������� ����.�� ��������. Rest In Peace."
	};
	COMPILE_TIME_CHECK(sizeof(SymptomEffects)/sizeof(char*)==MaxSymptom);

	extern const char* SymptomEffects[MaxSymptom];

} //namespace
