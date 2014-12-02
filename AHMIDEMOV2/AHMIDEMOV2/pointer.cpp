#include "stdafx.h"
#include "pointer.h"
#include "MatrixGenerate.h"
static void CORDIC(S16 Radian, S16 &COS, S16 &SIN)
{
	S16 Angle[14] = { 5760, 3400, 1797, 912, 458, 229, 115, 57, 29, 14, 7, 4, 2, 1 };             //将上述角度扩大128倍
	S16 cosine[14] = { 181, 162, 157, 156, 156, 155, 155, 155, 155, 155, 155, 155, 155, 155 };   //cos@的结果乘以256
	S16 x, y;
	x = COS;
	y = SIN;
	x = x * 1024;
	y = y * 1024;
	S32 count_i;
	S32 coeff1 = 0, coeff2 = 0;
	while (Radian >= 360)
		Radian = Radian - 360;
	while (Radian < 0)
		Radian = Radian + 360;
	if (Radian == 0 || Radian == 180)
	{

		if (Radian == 0)
		{
			COS = x;
			SIN = y;
		}
		else //(Radian == 180)
		{
			COS = -x;
			SIN = y;
		}
	}
	else if (Radian == 90 || Radian == 270)
	{

		if (Radian == 90)
		{
			COS = y;
			SIN = x;
		}
		else //(Radian == 270)
		{
			COS = y;
			SIN = -x;
		}
	}
	else
	{
		if (Radian > 0 && Radian < 90)
		{
			coeff1 = 1, coeff2 = 1;
		}
		else if (Radian >= 90 && Radian < 180)
		{
			Radian = Radian - 90;
			Radian = 90 - Radian;
			coeff1 = -1, coeff2 = 1;
		}
		else if (Radian > 180 && Radian < 270)
		{
			Radian = Radian - 180;
			coeff1 = -1, coeff2 = -1;
		}
		else if (Radian >= 270 && Radian < 360)
		{
			Radian = Radian - 270;
			Radian = 90 - Radian;
			coeff1 = 1, coeff2 = -1;
		}
		Radian = Radian * 128;
		for (count_i = 0; count_i <= 13; count_i++)
		{
			if (Radian>0)      //大于0表示，在角度30下面，要继续逆时针旋转，小于0表示在角度30度上面，要回转
			{
				Radian = Radian - Angle[count_i];
				COS = (x - (y >> count_i));
				SIN = (y + (x >> count_i));
				x = COS;
				y = SIN;
			}
			else if (Radian < 0)
			{
				Radian = Radian + Angle[count_i];
				COS = (x + (y >> count_i));
				SIN = (y - (x >> count_i));
				x = COS;
				y = SIN;
			}
			if (Radian == 0)
			{
				COS = coeff1*COS*cosine[count_i] >> 8;
				SIN = coeff2*SIN*cosine[count_i] >> 8;
				break;
			}
		}
	}
}
void DrawPointer(U8 width, U8 height, S16 x, S16 y, S16 degrees,
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
	U16 rominfosize = 256*256 >> 6;
	rom_info.tex[RomAddr].texel = new U64[rominfosize];
	for (U16 i = 0; i < rominfosize; i++)
	{
		*(rom_info.tex[RomAddr].texel + i) = (U64)((U8)pointer256_256[i * 8]) << 56
			                               | (U64)((U8)pointer256_256[i * 8 + 1]) << 48
			                               | (U64)((U8)pointer256_256[i * 8 + 2]) << 40
			                               | (U64)((U8)pointer256_256[i * 8 + 3]) << 32
			                               | (U64)((U8)pointer256_256[i * 8 + 4]) << 24
			                               | (U64)((U8)pointer256_256[i * 8 + 5]) << 16
			                               | (U64)((U8)pointer256_256[i * 8 + 6]) << 8
			                               | (U64)((U8)pointer256_256[i * 8 + 7]);
	}
	RomAddr++;
	U8 cy = 0;
	if (height>128)
	{
		cy = (U8)(height >> 7);
		//更改，由于输入的是逆变换矩阵参数，需要转换为正变换矩阵参数
		U8 buffer[4];
		for (U8 i = 0; i < 4; i++)
		{
			buffer[i] = cy - (cy >> 1);
			cy = cy >> 1;
		}
		cy = (U8)buffer[0] << 3 | (U8)buffer[1] << 2 | (U8)buffer[2] << 1 | (U8)buffer[3];
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
	S16 tx = (S16)(-x +128) << 4;
	S16 ty = (S16)(-y +128) << 4;
	S16 R = 181<<4;
	MatrixGenerate matrixgenerate;
	////matrixgenerate.Triscale(cx, cy);
	S16 COS1 = 1, SIN1 = 0;
	CORDIC(-225, COS1, SIN1);
	COS1 = COS1 >> (10 - 4);
	SIN1 = SIN1 >> (10 - 4);
	S16 oldx = (R*COS1>>4)&0xfff0;
	S16 oldy = (R*SIN1>>4)&0xfff0;
	S16 COS2 = 1, SIN2 = 0;
	CORDIC(-225 + degrees, COS2, SIN2);
	COS2 = COS2 >> (10 - 4);
	SIN2 = SIN2 >> (10 - 4);
	S16 newx = (R*COS2>>4)&0xfff0;
	S16 newy = (R*SIN2>>4)&0xfff0;
	tx = tx - newx + oldx;
	ty = ty +newy - oldy;
	matrixgenerate.Tritranslate(tx, ty);
	matrixgenerate.Trirotate(degrees);
	matrixgenerate.GetMatrix(tile_info, Matrixmask, matrix, TEXADD);
}