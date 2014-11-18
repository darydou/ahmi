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
#define MAX3(a,b,c)    ((a) >  ((b)>(c)?(b):(c))  ? (a) : ((b)>(c)?(b):(c))  )    //���������������ֵ�ĺ���
#define MIN3(a,b,c)    ((a) <  ((b)<(c)?(b):(c))  ? (a) : ((b)<(c)?(b):(c))  )    //��������������Сֵ�ĺ���
#define MAX4(a,b,c,d) (  ((a)>(b)?(a):(b)) >  ((c)>(d)?(c):(d))   ?   ((a)>(b)?(a):(b))  :((c)>(d)?(c):(d))   )  //�ĸ��������ֵ����
#define MIN4(a,b,c,d) (  ((a)<(b)?(a):(b)) <  ((c)<(d)?(c):(d))   ?   ((a)<(b)?(a):(b))  :((c)<(d)?(c):(d))   )  //�ĸ�������Сֵ����
#endif



typedef short S1_B_4;//������1.11.4:1����λ��11����λ��4С��λ
typedef char  S1_3_4;//������1.3.4��1����λ��3����λ��4С��λ
typedef unsigned short U16;//�޷���16λ
typedef unsigned char  U8;//�޷��� 8λ
typedef unsigned long long U64;//�޷���64λ
typedef int S32;//�з���32λ
typedef unsigned int U32;//�޷���32λ
typedef short S16;//�з���16λ
typedef char S8;//�з���8λ
typedef long long S64;//�з���64λ

//������2.8.11.11.1.31��
//2λ�����ʽλ
//8λ��������ַ
//11λ�����
//11λ�����
//1λmaskλ
//31λ�����ַλ
typedef long long S2_8_11_11_1_31;

//������2.8.11.11.1.31��
//2λ�����ʽλ
//8λ��������ַ
//11λ�����
//11λ�����
//1λmaskλ
//24λ��ɫ��ɫ
//7λ����
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