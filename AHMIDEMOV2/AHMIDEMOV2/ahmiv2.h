#ifndef __AHMIV2
#define __AHMIV2
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
using namespace std;
#include "ALLHeader.h"

const int TileSize=32;
const int ScreenWidth=1024;
const int ScreenHeight=768;

#define 	Alpha 	unsigned char
#define 	Mask 	bool
#define 	BitMask 	bool
#define     Color16  unsigned short
static U64 Mul_count = 0;
#define MUL(a,b) (Mul_count++,(U64)((U64)(a)*(U64)(b))) 

#define TRUE 1
#define FALSE 0
#define NULL 0

typedef struct _Color{
		U8 r;
		U8 g;
		U8 b;
		U8 a;
		U8 m;
		} Color;


typedef struct _Tile{
	U16 x;  //coordinate of left-bottom of the tile 
	U16 y;  //coordinate of left-bottom of the tile
	Color ColorBuffer[TileSize * TileSize];//for color
	Alpha AlphaBuffer[TileSize * TileSize];//for alpha
	Mask MaskBuffer[TileSize * TileSize];//for mask
	bool mask_usage;//�Ƿ�ʹ��mask��alpha
	bool color_done;
	}Tile;

typedef struct _FinalColor{
		U8 r;
		U8 g;
		U8 b;
		} FinalColor;

typedef struct _FinalTile {
	U16 x;
	U16 y;
	FinalColor TileBuffer[TileSize* TileSize];
	} FinalTile;

//Color16 FrameBuffer[ScreenWidth* ScreenHeight];

class ahmi{
	public:	ahmi(int screen_width,int screen_height);
			void DrawFrame(TileInfo* ,ROMInfo* ,Color16* FrameBuffer);//����֡
	private: void TileInfoRead(TileInfo* );   //��ȡtileinfo������tile��x��y	
			 void TexRaster(Tile* ,Matrix* ,Texture* ,U16 tex_width,U16 tex_heigth,U8 texture_ctrl,Color16 InitColor);//�����դ��
			 void InitTile(Tile*,U16 x,U16 y);
			 void cache(U64 block_addr,U16 in_block_addr,Texture*,unsigned int* texel,U8 TexType,bool mask_alpha);//�����ȡ
			 void InitFinalTile(FinalTile*,U16 x,U16 y);
			 void color_blending(FinalTile* ,Tile*);//��ɫ���
			 void Write_Frame(FinalTile* ,Color16* FrameBuffer);//��tile������ɫд��frame buffer			 

			int screen_height;//��Ļ��
			int screen_width;//��Ļ��
			int tile_x;
			int tile_y;
			FinalTile theFinalTile;//tile���ս��
};

void start();
#endif