#include "ThreeKShell.h"
#include "StatusBarBase.h"

fresult StatusBarBase::BaseInit( Repositories* reps, Factories* facts)
{
	_Repositories = reps;
	_Factories = facts;
	_Visible = TRUE;
	return SUCCESS;
}

Size StatusBarBase::GetSize()
{
	Size sz;

	sz.Width = SCREENX;
	sz.Height = 16;

	return sz;
}

fresult StatusBarBase::SetHeaderText( char* headerText )
{
	fresult fres;
	
	if (_txtHeader != NULL)
	{
		fres = _txtHeader->SetText(headerText);
		ENSURESUCCESS(fres);
		fres = _txtHeader->Draw();
		ENSURESUCCESS(fres);
	}

	return SUCCESS;
}

fresult StatusBarBase::Draw()
{
	fresult fres;
	if (_Visible)
	{
		if (_pnlBasePanel !=NULL)
		{
			if (_Visible)
			{
				fres = _pnlBasePanel->Draw();
			}
		}
	}

	return SUCCESS;
}

fresult StatusBarBase::CreateStatusBar()
{
	fresult fres;
	Size sbSz;
	sbSz = GetSize();

	Position sbPos;
	sbPos.data = 0;

	ubyte_t controlsCount = GetControlsCount();

	fres = _Factories->GetPanelFactory()->GetPanel(sbSz, sbPos, controlsCount,CL_HEADER_BACKGROUND, &_pnlBasePanel);
	ENSURESUCCESS(fres);

	return SUCCESS;
}

fresult StatusBarBase::CreateBatteryLevelControl(Position pos, ScaledValueImageList** o_batteryLevel )
{
	fresult fres;
	ScaledValueImageList* battery;

	ImageHandle* images;
	ubyte_t imgCount;
	fres = GetBatteryImages(&images, &imgCount);
	ENSURESUCCESS(fres);

	fres = _Factories->GetImageListFactory()->GetScaledImageList(pos, images, 0, 100, imgCount, &battery);
	ENSURESUCCESS(fres);

	*o_batteryLevel = battery;
	return SUCCESS;
}

fresult StatusBarBase::GetBatteryImages( ImageHandle** o_batteryImages, ubyte_t* o_count )
{
	o_batteryImages = NULL;
	o_count =0;
	return SUCCESS;
}

fresult StatusBarBase::CreateNetworkLevelControl( Position pos, ScaledValueImageList** o_networkLevel )
{
	fresult fres;
	ScaledValueImageList* network;

	ImageHandle* images;
	ubyte_t imgCount;
	fres = GetNetworkImages(&images, &imgCount);
	ENSURESUCCESS(fres);

	fres = _Factories->GetImageListFactory()->GetScaledImageList(pos, images, 0, 120, imgCount, &network);
	ENSURESUCCESS(fres);

	*o_networkLevel = network;
	return SUCCESS;
}

fresult StatusBarBase::GetNetworkImages(ImageHandle** o_networkImages, ubyte_t* o_count)
{
	*o_networkImages = NULL;
	*o_count =0;
	return SUCCESS;
}

fresult StatusBarBase::AddBatteryLevel( Position pos )
{
	fresult fres;
	ScaledValueImageList* ctrl;

	fres = CreateBatteryLevelControl(pos, &ctrl);
	ENSURESUCCESS(fres);

	fres = _pnlBasePanel->AppendControl(ctrl);
	ENSURESUCCESS(fres);

	_BatteryLevel = ctrl;

	return SUCCESS;
}

fresult StatusBarBase::AddNetworkLevel( Position pos )
{
	fresult fres;
	ScaledValueImageList* ctrl;

	fres = CreateNetworkLevelControl(pos, &ctrl);
	ENSURESUCCESS(fres);

	fres = _pnlBasePanel->AppendControl(ctrl);
	ENSURESUCCESS(fres);

	_NetworkLevel = ctrl;

	return SUCCESS;
}

ubyte_t StatusBarBase::GetControlsCount()
{
	return 0;
}

fresult StatusBarBase::SetVisible( bool_t visibileValue )
{
	_Visible = visibileValue;
	return SUCCESS;
}

bool_t StatusBarBase::GetVisible()
{
	return _Visible;
}
