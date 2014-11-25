#ifndef __DNSDRIVER
#define __DNSDRIVER
#include "ALLHeader.h"

bool boxtest(TileInfo &tile_info,
	int &tile_num,
	MatrixMask  &Matrixmask,
	U8(&matrix)[MatrixSize],
	TileInfoMask &tileinfomask,
	int &tex_num);
void RTLIndxSD(TileInfo &tile_info,
	MatrixMask  &Matrixmask,
	U8(&matrix)[MatrixSize],
	TileInfoMask &tileinfomask,
	U8 &TEXADD);
void RTLTexIndex(TileInfo &tile_info,
	             U8(&matrix)[MatrixSize],
	             TileInfoMask &tileinfomask,
				 U8 &TEXADD,
				 ROMInfo &rom_info);
#endif
