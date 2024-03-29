// Roman
// UserInterface �������� ������ �������������� � �������������, ������� �� ������� � �� ������� ������
#pragma once
#include "UIDesigner.h"
#include "ArmletShell.h"
#include "Osanve.h"



// �������� ��������� ������ ����������
class UserInterface : public UIDesigner
{


//	sword_t GetRoomIdFromLustraId(sword_t lustraId);
	
//	fresult AddNewWound(TARGET bodyPart);
// ������������
	fresult RedrawIfForeground(Form* form);

	void LogError(char* message);
	
//	bool_t _woundSelected;
public: 
	fresult Init();

	//void OnPillConnected(sword_t cure_id, sword_t charges);
	void SetPlayerName(char* name);
	//void SetRoom(sword_t room);
	fresult SetBatteryLevel(ubyte_t batteryLevel);
	//fresult SetRadioStatus(sword_t gateId, sword_t level);
	bool OnPreFightTimer();
	fresult OnButtonPressed( ButtonState button );
	bool OnOsanveTimer();
	void DoForceTick();
	bool OnBatteryTimer();
	void Int2Str(uword_t value, char* buff, ubyte_t buffSize);

};