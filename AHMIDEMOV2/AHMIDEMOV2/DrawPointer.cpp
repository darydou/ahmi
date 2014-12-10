#include "stdafx.h"
#include "DrawPointer.h"
#include "MatrixGenerate.h"
#include "DrawTool.h"

void DrawPointer(
	TileInfo &tile_info,
	ROMInfo &rom_info,
	MatrixMask &Matrixmask,
	TileInfoMask &tileinfomask,
	U8(&matrix)[MatrixSize],
	U8 &RomAddr,
	U8 &TEXADD,
	S16 x, S16 y, S16 degrees, U16 width, U16 height, U8 r, U8 g, U8 b)
{
	const S16 pointerradius = 128;
	const U16 pointerahplawidth  = 256;
	const U16 pointerahplaheight = 256;
	static S16 score4[] = { 16, 8, 5, 4, 3 };
	tileinfomask.tileinfomask1[TEXADD].flag = 2;//flag=2是指ahpla颜色，mask为0代表着是1bit,1代表着8bits
	tileinfomask.tileinfomask1[TEXADD].height = pointerahplaheight;
	tileinfomask.tileinfomask1[TEXADD].width = pointerahplawidth;
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
	//进行放缩处理
	U16 cx, cy;
	if (width >= 16)
	{
		cx = (width << magnitude) >> 4;
	}
	else
	{
		cx = 1 << 7;
	}
	if (height >= pointerradius)
	{
		cy = (height << magnitude) >> 7;
	}
	else
	{
		cy = 1 << 7;
	}
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
	
	//先进行放缩和旋转操作，最后进行平移操作；
	TOOL::MatrixGenerate matrixgenerate;
	matrixgenerate.Triscale(cx, cy);
	degrees = degrees - 180;
	matrixgenerate.Trirotate(degrees);
	matrixgenerate.GetMatrix(tile_info, Matrixmask, matrix, TEXADD);
	U16 circlex = 128, circley = 128;
	S16 A = Matrixmask.Matrixmask1[matrix[TEXADD-1]].matrix >> 48 & 0xffff;
	S16 B = Matrixmask.Matrixmask1[matrix[TEXADD-1]].matrix >> 32 & 0xffff;
	S16 C = Matrixmask.Matrixmask1[matrix[TEXADD-1]].matrix >> 16 & 0xffff;
	S16 D = Matrixmask.Matrixmask1[matrix[TEXADD-1]].matrix & 0xffff;
	S16 E = Matrixmask.Matrixmask1[matrix[TEXADD-1]].matrixEF >> 16 & 0xffff;
	S16 F = Matrixmask.Matrixmask1[matrix[TEXADD-1]].matrixEF & 0xffff;
	//去除误差
	S16 circlexcurrent = 0, circleycurrent = 0;
	circlexcurrent = static_cast<S16>
		 (static_cast<S32>(circlex)*static_cast<S32>(tile_info.matrix[matrix[TEXADD-1]].A)
		+ static_cast<S32>(circley)*static_cast<S32>(tile_info.matrix[matrix[TEXADD-1]].C)
		>> magnitude);
	circleycurrent = static_cast<S16>
		 (static_cast<S32>(circlex)*static_cast<S32>(tile_info.matrix[matrix[TEXADD-1]].B)
		+ static_cast<S32>(circley)*static_cast<S32>(tile_info.matrix[matrix[TEXADD-1]].D)
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
	//添加纯色纹理
	//为文字添加颜色
	TOOL::ADDPurity(tileinfomask, TEXADD, 
		1, r, g, b,
		tileinfomask.tileinfomask1[TEXADD - 1].width,
		tileinfomask.tileinfomask1[TEXADD - 1].height);
	TOOL::GetMatrix(matrix, TEXADD, TEXADD - 2);
}