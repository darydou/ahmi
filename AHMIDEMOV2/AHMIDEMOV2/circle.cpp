#include "stdafx.h"
#include "circle.h"
#include "MatrixGenerate.h"

void DrawCircle(U16 radius, S16 x, S16 y,
	TileInfo &tile_info,
	ROMInfo &rom_info,
	MatrixMask &Matrixmask,
	TileInfoMask &tileinfomask,
	U8(&matrix)[MatrixSize],
	U8 &RomAddr,
	U8 &TEXADD)
{
	tileinfomask.tileinfomask1[TEXADD].flag = 2;
	tileinfomask.tileinfomask1[TEXADD].height = 256;
	tileinfomask.tileinfomask1[TEXADD].width = 256;
	tileinfomask.tileinfomask1[TEXADD].mask = 0;
	TEXADD++;
	U16 rominfosize = 256 * 256 >> 6;
	rom_info.tex[RomAddr].texel = new U64[rominfosize];
	for (U16 i = 0; i < rominfosize; i++)
	{
		*(rom_info.tex[RomAddr].texel + i) = (U64)((U8)circleB256_256[i * 8]) << 56
			                               | (U64)((U8)circleB256_256[i * 8 + 1]) << 48
			                               | (U64)((U8)circleB256_256[i * 8 + 2]) << 40
			                               | (U64)((U8)circleB256_256[i * 8 + 3]) << 32
			                               | (U64)((U8)circleB256_256[i * 8 + 4]) << 24
			                               | (U64)((U8)circleB256_256[i * 8 + 5]) << 16
			                               | (U64)((U8)circleB256_256[i * 8 + 6]) << 8
			                               | (U64)((U8)circleB256_256[i * 8 + 7]);
	}
	RomAddr++;
	U8 cx = 0;
	if (radius>128)
	{
		cx = (U8)(radius >> 7);
	}
	else
	{
		//更改矩阵后只能进行放大操作
		cx = 1;
		//cx = (U8)(radius >> 3);
		//if (radius < 8)
		//{
		//	cout << "the radius is error" << endl;
		//	exit(0);
		//}
	}
	//进行微调整，使之偏移到圆心位置。
	S16 tx = x-128;
	S16 ty = y-128;
	MatrixGenerate matrixgenerate;
	//matrixgenerate.Triscale(cx, cx);
	matrixgenerate.Tritranslate(tx, ty);
	matrixgenerate.GetMatrix(tile_info, Matrixmask, matrix, TEXADD);
}