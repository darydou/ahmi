#ifndef __DNSDRIVER
#define __DNSDRIVER
#include "ALLHeader.h"
 

void LoadIndexSoueAddr(TileInfo &tile_info,
	MatrixMask  &Matrixmask,
	U8(&matrix)[MatrixSize],
	TileInfoMask &tileinfomask,
	U8 &TEXADD);
void LoadTextureIndex(TileInfo &tile_info,
	             U8(&matrix)[MatrixSize],
	             TileInfoMask &tileinfomask,
				 U8 &TEXADD,
				 ROMInfo &rom_info);
#endif
