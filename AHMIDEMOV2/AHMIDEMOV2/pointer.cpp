#include "stdafx.h"
#include "pointer.h"
#include "MatrixGenerate.h"

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
	static S16 score4[] = { 16, 8, 5, 4, 3 };
	tileinfomask.tileinfomask1[TEXADD].flag = 2;//flag=2是指ahpla颜色，mask为0代表着是1bit,1代表着8bits
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
	//U8 cy = 0;
	//if (height>pointerradius)
	//{
	//	cy = static_cast<U8>(height >> 7);//height/pointerradius
	//	y = static_cast<S16>(static_cast<S32>(y * score4[cy-1])>>4);
	//	//更改，由于输入的是逆变换矩阵参数，需要转换为正变换矩阵参数
	//	U8 buffery1[4];
	//	for (U8 i = 0; i < 4; i++)
	//	{
	//		buffery1[i] =(cy>>i)&0x1;
	//	}
	//	cy =  static_cast<U8>(buffery1[0]) << 4
	//		| static_cast<U8>(buffery1[1]) << 3
	//		| static_cast<U8>(buffery1[2]) << 2
	//		| static_cast<U8>(buffery1[3]) << 1;
	//}
	//else
	//{
	//	cy = height;
	//	//y = y*static_cast<S16>(static_cast<U8>(cy))>>7;
	//	U8 buffery2[3];
	//	for (U8 i = 0; i < 3&&cy>=0; i++)
	//	{
	//		buffery2[2-i] = static_cast<U8>(cy) >> (7-i);
	//		if (cy>=static_cast<U8>(128 >> i))
	//		cy = cy - static_cast<U8>(128 >> i);
	//	}
	//	cy =  static_cast<U8>(buffery2[0]) << 6
	//		| static_cast<U8>(buffery2[1]) << 5
	//		| static_cast<U8>(buffery2[2]) << 4;
	//	//更改偏移量使之符合绕定点旋转
	//	y = y*static_cast<S16>(buffery2[0] * 4 + buffery2[1] * 2 + buffery2[2]);
	//	if (height < (pointerradius>>3))
	//	{
	//		cout << "the height is error" << endl;
	//		exit(0);
	//	}
	//}
	//U8 cx = 0;
	//if (width > 16)
	//{
	//	cx = static_cast<U8>(width >> 4);//width/16默认的指针宽度
	//	x = static_cast<S16>(static_cast<S32>(x * score4[cx - 1]) >> 4);
	//	U8 bufferx1[4];
	//	for (U8 i = 0; i < 4; i++)
	//	{
	//		bufferx1[i] = (cx >> i) & 0x1;
	//	}
	//	cx =  static_cast<U8>(bufferx1[0]) << 4
	//		| static_cast<U8>(bufferx1[1]) << 3
	//		| static_cast<U8>(bufferx1[2]) << 2
	//		| static_cast<U8>(bufferx1[3]) << 1;
	//}
	//else
	//{
	//	cx = width;
	//	//x = x*static_cast<S16>(static_cast<U8>(cx)) >> 2;
	//	U8 bufferx2[3];
	//	for (U8 i = 0; i < 3 && cx >= 0; i++)
	//	{
	//		bufferx2[2 - i] = static_cast<U8>(cx) >> (4 - i);//16的开方为2
	//		if (cx >= static_cast<U8>(16 >> i))
	//			cx = cx - static_cast<U8>(16 >> i);
	//	}
	//	cx =  static_cast<U8>(bufferx2[0]) << 6
	//		| static_cast<U8>(bufferx2[1]) << 5
	//		| static_cast<U8>(bufferx2[2]) << 4;
	//	//更改偏移量使之绕圆心旋转
	//	x = x*static_cast<S16>(bufferx2[0] * 4 + bufferx2[1] * 2 + bufferx2[2]);
	//	if (width < 2)
	//	{
	//		cout << "the width is error" << endl;
	//		exit(0);
	//	}
	//}
	//以下变换使得可以绕着圆心旋转
	//S16 tx = (S16)(-x + pointerradius) << 4;
	//S16 ty = (S16)(-y + pointerradius) << 4;
	//S16 R = 181<<4;//R=pointerradius/(sqrt(2)/2)
	//S16 COS1 = 1, SIN1 = 0;
	//CORDIC(-225, COS1, SIN1);
	//COS1 = COS1 >> (10 - 4);
	//SIN1 = SIN1 >> (10 - 4);
	//S16 oldx = (R*COS1>>4)&0xfff0;
	//S16 oldy = (R*SIN1>>4)&0xfff0;
	//S16 COS2 = 1, SIN2 = 0;
	//CORDIC(-225 + degrees, COS2, SIN2);
	//COS2 = COS2 >> (10 - 4);
	//SIN2 = SIN2 >> (10 - 4);
	//S16 newx = (R*COS2>>4)&0xfff0;
	//S16 newy = (R*SIN2>>4)&0xfff0;
	//tx =  tx - newx + oldx ;
	//ty =  ty + newy - oldy ;
	//matrixgenerate.Triscale(cx, cy);
	MatrixGenerate matrixgenerate;
	
	//matrixgenerate.Tritranslate( -500<<4, -500<<4);
	
	matrixgenerate.Triscale(16, 16);
	matrixgenerate.Trirotate(30);
	matrixgenerate.GetMatrix(tile_info, Matrixmask, matrix, TEXADD);
}