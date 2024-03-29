#pragma once 
#include "IControl.h"
#include "IRender.h"

namespace ThreeKShell {

//Base class for any control
class ControlBase : public IControl
{

protected:
	Position _Position;
	Size _Size;
	//TODO: rename
	bool_t _bVisible;
	ubyte_t _ZOrder;
	IRender* _render;

	fresult virtual BaseInit( Size size, Position position, IRender* render)
	{
		_Size = size;
		_Position = position;
		_render = render;
		_bVisible = TRUE;

		return SUCCESS;
	}

public:

	Size virtual GetSize() 
	{
		return _Size;
	}

	Position virtual GetPosition() 
	{
		return _Position;
	}

	ubyte_t virtual GetZOrder()
	{
		return _ZOrder;
	}

	bool_t virtual GetVisible()
	{
		return _bVisible;
	}


	void virtual SetVisible( bool_t visible )
	{
		_bVisible = visible;
	};

	void virtual SetZOrder( ubyte_t ZOrder )
	{
		_ZOrder= ZOrder;
	};

	fresult virtual SetSize( Size size )
	{
		_Size = size;
		return SUCCESS;
	}

	fresult virtual SetPosition( Position position )
	{
		_Position = position;
		return SUCCESS;
	}

	fresult virtual Draw() 
	{
		return DrawArea(_Position, _Size);
	}

};

}
