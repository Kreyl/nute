#pragma once

#include "project.h"
#include "IntegrationWithKeltur.h"

struct TextFormat
{
	Color FgColor;
	Color BgColor;
	Font Font;
};

fresult GetTextFormat(int fontId, Color bgColor, Color fgColor, TextFormat* oFormat);

