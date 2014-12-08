#include "stdafx.h"
#include "DrawCircle.h"
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
	U16 cx = 0;
	if (radius>=128)
	{
		cx = (U16)((radius<<magnitude)>> 7);
	}
	else
	{
		//更改矩阵后只能进行放大操作
		cx = 1<<7;
		//cx = (U8)(radius >> 3);
		//if (radius < 8)
		//{
		//	cout << "the radius is error" << endl;
		//	exit(0);
		//}
	}
	//进行微调整，使之偏移到圆心位置。
	MatrixGenerate matrixgenerate;
	matrixgenerate.Triscale(cx, cx);
	matrixgenerate.GetMatrix(tile_info, Matrixmask, matrix, TEXADD);
	U16 circlex = 128, circley = 128;
	S16 A = Matrixmask.Matrixmask1[matrix[TEXADD - 1]].matrix >> 48 & 0xffff;
	S16 B = Matrixmask.Matrixmask1[matrix[TEXADD - 1]].matrix >> 32 & 0xffff;
	S16 C = Matrixmask.Matrixmask1[matrix[TEXADD - 1]].matrix >> 16 & 0xffff;
	S16 D = Matrixmask.Matrixmask1[matrix[TEXADD - 1]].matrix & 0xffff;
	S16 E = Matrixmask.Matrixmask1[matrix[TEXADD - 1]].matrixEF >> 16 & 0xffff;
	S16 F = Matrixmask.Matrixmask1[matrix[TEXADD - 1]].matrixEF & 0xffff;
	//去除误差
	S16 circlexcurrent = 0, circleycurrent = 0;
	circlexcurrent = static_cast<S16>
		(static_cast<S32>(circlex)*static_cast<S32>(tile_info.matrix[matrix[TEXADD - 1]].A)
		+ static_cast<S32>(circley)*static_cast<S32>(tile_info.matrix[matrix[TEXADD - 1]].C)
		>> magnitude);
	circleycurrent = static_cast<S16>
		(static_cast<S32>(circlex)*static_cast<S32>(tile_info.matrix[matrix[TEXADD - 1]].B)
		+ static_cast<S32>(circley)*static_cast<S32>(tile_info.matrix[matrix[TEXADD - 1]].D)
		>> magnitude);
	S16 circlexnow = 0, circleynow = 0;
	circlexnow = static_cast<S16>
		(static_cast<S32>(circlexcurrent)*static_cast<S32>((S16)A)
		+ static_cast<S32>(circleycurrent)*static_cast<S32>((S16)C)
		>> magnitude);
	circleynow = static_cast<S16>
		(static_cast<S32>(circlexcurrent)*static_cast<S32>((S16)B)
		+ static_cast<S32>(circleycurrent)*static_cast<S32>((S16)D)
		>> magnitude);
	circlex = circlex * 2 - circlexnow;
	circley = circley * 2 - circleynow;
	/*****************************************************************************/
	circlexnow = static_cast<S16>(static_cast<S32>(circlex)*static_cast<S32>(A)+static_cast<S32>(circley)*static_cast<S32>(C) >> magnitude);
	circleynow = static_cast<S16>(static_cast<S32>(circlex)*static_cast<S32>(B)+static_cast<S32>(circley)*static_cast<S32>(D) >> magnitude);
	x = x - circlexnow;
	y = y - circleynow;
	matrixgenerate.Tritranslate(x, y);
	matrixgenerate.GetMatrix(tile_info, Matrixmask, matrix, TEXADD);
}