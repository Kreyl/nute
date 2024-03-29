#include "OpenSpace.h"


fresult OpenSpaceLogic::Init()
{
	fresult fres;
	
	MedLogic = &_medLogicInstance;
	fres = MedLogic->Init();
	ENSURESUCCESS(fres);

	BehaviorLogic = &_behLogicInstance;
	fres = BehaviorLogic->Init();
	ENSURESUCCESS(fres);

	_stressCruelty =0;
	_stressEgo =0;
	_stressHelplessness = 0;

	return SUCCESS;
}


bool_t OpenSpaceLogic::SetStressHelplessness( ubyte_t level )
{
	_stressHelplessness = level;
	if (_stressHelplessness == 7)
	{
		return TRUE;
	}
	
	return FALSE;
}

ubyte_t OpenSpaceLogic::GetStressHelplessness()
{
	return _stressHelplessness;
}

bool_t OpenSpaceLogic::SetStressEgo( ubyte_t level )
{
	_stressEgo = level;
	if (_stressEgo == 0)
	{
		return TRUE;
	}

	return FALSE;
}

ubyte_t OpenSpaceLogic::GetStressEgo()
{
	return _stressEgo;
}

bool_t OpenSpaceLogic::SetStressCruelty( ubyte_t level )
{

	_stressCruelty = level;
	if (_stressCruelty == 7)
	{
		return TRUE;
	}
	
	return FALSE;
}

ubyte_t OpenSpaceLogic::GetStressCruelty()
{
	return _stressCruelty;
}

ColorHandle OpenSpaceLogic::GetStressColor( StressType stress, ubyte_t level )
{
	ColorHandle clr;
	if (level < 2)
	{
		if (stress == StressEgo)
		{
			clr = CL_OS_LIGHTRED;
		}
		else
		{
			clr = CL_OS_GREEN;
		}
	}
	else if (level >= 2 && level < 5)
	{
		clr = CL_OS_ORANGE;
	}
	else if (level >=5)
	{
		if (stress == StressEgo)
		{
			clr = CL_OS_GREEN;
		}
		else
		{
			clr = CL_OS_LIGHTRED;
		}
	}
	return clr;
}

char* OpenSpaceLogic::getStressMP3FileName( StressType stress )
{
	return "C:\\None";
}


