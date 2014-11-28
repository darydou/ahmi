#include "stdafx.h"
#include "pointer.h"
#include "MatrixGenerate.h"

void DrawPointer(U8 width,U8 height, S16 x, S16 y,
	TileInfo &tile_info,
	ROMInfo &rom_info,
	MatrixMask &Matrixmask,
	TileInfoMask &tileinfomask,
	U8(&matrix)[MatrixSize],
	U8 &RomAddr,
	U8 &TEXADD)
{
	tileinfomask.tileinfomask1[TEXADD].flag = 2;
	tileinfomask.tileinfomask1[TEXADD].height = 128;
	tileinfomask.tileinfomask1[TEXADD].width = 16;
	tileinfomask.tileinfomask1[TEXADD].mask = 0;
	TEXADD++;
	U16 rominfosize = 128 * 16 >> 6;
	rom_info.tex[RomAddr].texel = new U64[rominfosize];
	for (U16 i = 0; i < rominfosize; i++)
	{
		*(rom_info.tex[RomAddr].texel + i) = (U64)((U8)pointer16_128[i * 8]) << 56
			                               | (U64)((U8)pointer16_128[i * 8 + 1]) << 48
			                               | (U64)((U8)pointer16_128[i * 8 + 2]) << 40
			                               | (U64)((U8)pointer16_128[i * 8 + 3]) << 32
			                               | (U64)((U8)pointer16_128[i * 8 + 4]) << 24
			                               | (U64)((U8)pointer16_128[i * 8 + 5]) << 16
			                               | (U64)((U8)pointer16_128[i * 8 + 6]) << 8
			                               | (U64)((U8)pointer16_128[i * 8 + 7]);
	}
	RomAddr++;
	U8 cy = 0;
	if (height>128)
	{
		cy = (U8)(height >> 7);
		cy = cy << 4;
	}
	else
	{
		cy = (U8)(height >> 3);
		if (height < 8)
		{
			cout << "the height is error" << endl;
			exit(0);
		}
	}
	U8 cx = 0;
	if (width > 16)
	{
		cx = (U8)(width >> 4);
		cx = cx << 4;
	}
	else
	{
		cx = (U8)width;
		if (width < 8)
		{
			cout << "the width is error" << endl;
			exit(0);
		}
	}
	S16 tx = (S16)(x - 16) << 4;
	S16 ty = (S16)(y - 128) << 4;
	MatrixGenerate matrixgenerate;
	matrixgenerate.Triscale(cx, cy);
	matrixgenerate.Tritranslate(tx, ty);
	matrixgenerate.GetMatrix(tile_info, Matrixmask, matrix, TEXADD);
}