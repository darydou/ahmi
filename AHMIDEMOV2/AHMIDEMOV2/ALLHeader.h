#ifndef _ALLHeader
#define _ALLHeader
#include <iostream>
#include <windows.h>
using namespace std;

#ifndef __DEFINE
#define __DEFINE
#define SCREENHEIGHT 768
#define SCREENWIDTH  1024
#define TILEINDEXSIZE  32*32
#define SOURCEADDRSIZE 20480
#define MatrixSize  256
#define TextureIndexSize 256
#define ROMInfoSize  32   
#define MIN(a,b) ((a)<(b))?(a):(b)
#define MAX(a,b) ((a)>(b))?(a):(b)
#define MAX3(a,b,c)    ((a) >  ((b)>(c)?(b):(c))  ? (a) : ((b)>(c)?(b):(c))  )    //定义求三个数最大值的函数
#define MIN3(a,b,c)    ((a) <  ((b)<(c)?(b):(c))  ? (a) : ((b)<(c)?(b):(c))  )    //定义求三个数最小值的函数
#define MAX4(a,b,c,d) (  ((a)>(b)?(a):(b)) >  ((c)>(d)?(c):(d))   ?   ((a)>(b)?(a):(b))  :((c)>(d)?(c):(d))   )  //四个数的最大值函数
#define MIN4(a,b,c,d) (  ((a)<(b)?(a):(b)) <  ((c)<(d)?(c):(d))   ?   ((a)<(b)?(a):(b))  :((c)<(d)?(c):(d))   )  //四个数的最小值函数
#endif



typedef short S1_B_4;//定点数1.11.4:1符号位，11整数位，4小数位
typedef char  S1_3_4;//定点数1.3.4：1符号位，3整数位，4小数位
typedef unsigned short U16;//无符号16位
typedef unsigned char  U8;//无符号 8位
typedef unsigned long long U64;//无符号64位
typedef int S32;//有符号32位
typedef unsigned int U32;//无符号32位
typedef short S16;//有符号16位
typedef char S8;//有符号8位
typedef long long S64;//有符号64位

//定点数2.8.11.11.1.31：
//2位纹理格式位
//8位纹理矩阵地址
//11位纹理高
//11位纹理宽
//1位mask位
//31位纹理地址位
typedef long long S2_8_11_11_1_31;

//定点数2.8.11.11.1.31：
//2位纹理格式位
//8位纹理矩阵地址
//11位纹理高
//11位纹理宽
//1位mask位
//24位纯色颜色
//7位保留
typedef long long S2_8_11_11_1_24_7;

#ifndef __Matrix
#define __Matrix
typedef struct _Matrix{
	S1_3_4  A;
	S1_3_4  B;
	S1_3_4  C;
	S1_3_4  D;
	S1_B_4 E;
	S1_B_4 F;
} Matrix;
#endif

#ifndef __TileInfo
#define __TileInfo
typedef struct _TileInfo{
	U16 TileIndex[TILEINDEXSIZE];
	U8 SourceAddr[SOURCEADDRSIZE];
	U64 TextureIndex[TextureIndexSize];
	Matrix Matrix[MatrixSize];
}TileInfo;
#endif


#ifndef __Texture
#define __Texture
typedef struct _Texture{
	U64* texel;
}Texture;
#endif 

#ifndef __ROMInfo
#define __ROMInfo
typedef struct _ROMInfo{
	Texture tex[ROMInfoSize];
}ROMInfo;
#endif

#ifndef __TileInfoMask1
#define __TileInfoMask1
typedef struct _TileInfoMask1
{
	U8  flag;
	U16 width;
	U16 height;
	U64 PixelLength;
	BOOL mask;
}TileInfoMask1;
#endif

#ifndef __TileInfoMask
#define __TileInfoMask
typedef struct _TileInfoMask
{
	TileInfoMask1 tileinfomask1[TextureIndexSize];
}TileInfoMask;
#endif

#ifndef	  __MatrixMask1
#define	  __MatrixMask1
typedef struct _MatrixMask1
{
	S1_B_4 Matrix[9];
}MatrixMask1;
#endif

#ifndef __MatrixMask
#define __MatrixMask
typedef struct _MatrixMask
{
	MatrixMask1 Matrixmask1[MatrixSize];
}MatrixMask;
#endif

#ifndef __POINT
#define __POINT
typedef struct _Point
{
	S32 x;
	S32 y;
}Point;
#endif

#endif