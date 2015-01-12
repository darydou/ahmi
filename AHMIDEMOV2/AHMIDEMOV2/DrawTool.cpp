#include "stdafx.h"
#include "DrawTool.h"
namespace TOOL{
	void ADDPurity(TileInfoMask &tileinfomask,
		U8 &TEXADD,
		BOOL mask,
		U8 r,
		U8 g,
		U8 b,
		U16 width,
		U16 height)
	{
		tileinfomask.tileinfomask1[TEXADD].flag = 3;
		tileinfomask.tileinfomask1[TEXADD].height = height;
		tileinfomask.tileinfomask1[TEXADD].width = width;
		tileinfomask.tileinfomask1[TEXADD].PixelLength = (U64)((U8)r << 10 & 0x7c00) + (U64)((U8)g << 5 & 0x3e0) + (U64)((U8)b >> 3 & 0x1f);
		tileinfomask.tileinfomask1[TEXADD].mask = mask;
		TEXADD++;
	}
	void GetMatrix(U8(&matrix)[MatrixSize],
		U8 TEXADD,
		U8 num)
	{
		matrix[TEXADD - 1] = num;
	}
}