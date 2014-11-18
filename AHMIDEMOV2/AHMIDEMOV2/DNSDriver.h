#ifndef __DNSDRIVER
#define __DNSDRIVER
#include "ALLHeader.h"

static bool boxtest(Matrix &tile_info_Matrix,
	int &tile_num,
	MatrixMask  *&Matrixmask,
	TileInfoMask1 &tileinfomask,
	int &tex_num);
void LoadTIndexSAddr(U16 (&tile_info_TileIndex)[TILEINDEXSIZE],
	U8 (&tile_info_SourceAddr)[SOURCEADDRSIZE],
	Matrix (&tileinfo_Matrix)[MatrixSize],
	MatrixMask  *&Matrixmask,
	U8 *&matrix,
	TileInfoMask *&tileinfomask,
	U8 TEXADD);
void LoadTexIndex(U64 (&tile_info_textureindex)[TextureIndexSize],
	U8  *&matrix,
	TileInfoMask *&tileinfomask,
	U8 TEXADD,
	ROMInfo *rominfo);
#endif
