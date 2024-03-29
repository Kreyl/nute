#pragma once

#define NO_IMAGE 0
#define ORANGE_ARROW_DOWN 1

#define ArrowDownOrangeHeight 24
#define ArrowDownOrangeWidth 24
extern const unsigned short ArrowDownOrangeBitmap[ArrowDownOrangeHeight*ArrowDownOrangeWidth];

fresult GetImageById(ubyte_t imageId, unsigned short ** oBitmap, Size* oBitmapSize);