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
void DrawPointer(
	TileInfo &tile_info,
	ROMInfo &rom_info,
	MatrixMask &Matrixmask,
	TileInfoMask &tileinfomask,
	U8(&matrix)[MatrixSize],
	U8 &RomAddr,
	U8 &TEXADD,
	S16 x, S16 y, S16 degrees, U16 width, U16 height)
{
	const S16 pointerradius = 128;
	const U16 pointerahplawidth = 256;
	const U16 pointerahplaheight = 256;

	tileinfomask.tileinfomask1[TEXADD].flag = 2;
	tileinfomask.tileinfomask1[TEXADD].height = pointerahplawidth;
	tileinfomask.tileinfomask1[TEXADD].width = pointerahplaheight;
	tileinfomask.tileinfomask1[TEXADD].mask = 0;
	TEXADD++;
	U16 rominfosize = pointerahplawidth * pointerahplaheight >> 6;
	rom_info.tex[RomAddr].texel = new U64[rominfosize];
	for (U16 i = 0; i < rominfosize; i++)
	{
		*(rom_info.tex[RomAddr].texel + i) = static_cast<U64>(pointer256_256[i * 8]    ) << 56
			                               | static_cast<U64>(pointer256_256[i * 8 + 1]) << 48
			                               | static_cast<U64>(pointer256_256[i * 8 + 2]) << 40
			                               | static_cast<U64>(pointer256_256[i * 8 + 3]) << 32
			                               | static_cast<U64>(pointer256_256[i * 8 + 4]) << 24
			                               | static_cast<U64>(pointer256_256[i * 8 + 5]) << 16
			                               | static_cast<U64>(pointer256_256[i * 8 + 6]) << 8
			                               | static_cast<U64>(pointer256_256[i * 8 + 7]);
	}
	RomAddr++;
	U8 cy = 0;
	if (height>pointerradius)
	{
		cy = static_cast<U8>(height >> 7);//height/pointerradius
		y = y * static_cast<S16>(static_cast<U8>(cy));
		//更改，由于输入的是逆变换矩阵参数，需要转换为正变换矩阵参数
		U8 buffery1[4];
		for (U8 i = 0; i < 4; i++)
		{
			buffery1[i] =(cy>>i)&0x1;
		}
		cy =  static_cast<U8>(buffery1[0]) << 4
			| static_cast<U8>(buffery1[1]) << 3
			| static_cast<U8>(buffery1[2]) << 2
			| static_cast<U8>(buffery1[3]) << 1;
	}
	else
	{
		cy = height;
		y = y*static_cast<S16>(static_cast<U8>(cy))>>7;
		U8 buffery2[3];
		for (U8 i = 0; i < 3&&cy>=0; i++)
		{
			buffery2[2-i] = static_cast<U8>(cy) >> (7-i);
			if (cy>=static_cast<U8>(128 >> i))
			cy = cy - static_cast<U8>(128 >> i);
		}
		cy =  static_cast<U8>(buffery2[0]) << 6
			| static_cast<U8>(buffery2[1]) << 5
			| static_cast<U8>(buffery2[2]) << 4;
		if (height < (pointerradius>>3))
		{
			cout << "the height is error" << endl;
			exit(0);
		}
	}
	U8 cx = 0;
	if (width > 16)
	{
		cx = static_cast<U8>(width >> 4);//width/16默认的指针宽度
		x = x*static_cast<S16>(static_cast<U8>(cx));
		U8 bufferx1[4];
		for (U8 i = 0; i < 4; i++)
		{
			bufferx1[i] = (cx >> i) & 0x1;
		}
		cx =  static_cast<U8>(bufferx1[0]) << 4
			| static_cast<U8>(bufferx1[1]) << 3
			| static_cast<U8>(bufferx1[2]) << 2
			| static_cast<U8>(bufferx1[3]) << 1;
	}
	else
	{
		cx = width;
		x = x*static_cast<S16>(static_cast<U8>(cx)) >> 2;
		U8 bufferx2[3];
		for (U8 i = 0; i < 3 && cx >= 0; i++)
		{
			bufferx2[2 - i] = static_cast<U8>(cx) >> (4 - i);//16的开方为2
			if (cx >= static_cast<U8>(16 >> i))
				cx = cx - static_cast<U8>(16 >> i);
		}
		cx =  static_cast<U8>(bufferx2[0]) << 6
			| static_cast<U8>(bufferx2[1]) << 5
			| static_cast<U8>(bufferx2[2]) << 4;
		if (width < 2)
		{
			cout << "the width is error" << endl;
			exit(0);
		}
	}
	//以下变换使得可以绕着圆心旋转
	S16 tx = (S16)(-x + pointerradius) << 4;
	S16 ty = (S16)(-y + pointerradius) << 4;
	S16 R = 181<<4;//R=pointerradius/(sqrt(2)/2)
	MatrixGenerate matrixgenerate;
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
	tx =  tx - newx + oldx ;
	ty =  ty + newy - oldy ;
	matrixgenerate.Triscale(cx, cy);
	matrixgenerate.Tritranslate(tx, ty);
	matrixgenerate.Trirotate(degrees);
	
	matrixgenerate.GetMatrix(tile_info, Matrixmask, matrix, TEXADD);
}