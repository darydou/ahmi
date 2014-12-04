#ifndef _MATRIXGENERATE
#define _MATRIXGENERATE
#include "ALLHeader.h"
const U8 MSize = 9;

class MatrixGenerate
{
private:
	S1_B_4 Matrix[MSize];
	S1_B_4 MatrixTemp[MSize];
	S1_B_4 MatrixCurrent[MSize];
	void CORDIC(S16 &Radian, S16 &COS, S16 &SIN);//由角度计算cos和sin
public:
	MatrixGenerate();
	void Triscale(S1_3_4 cx, S1_3_4 cy);
	void Tritranslate(S1_B_4 tx, S1_B_4 ty);
	void Trirotate(S16 degrees);
	void Trihorizontal(S1_3_4 sv);
	void Trivertical(S1_3_4 sh);
	void MatrixING();
	void GetMatrix(TileInfo &tile_info,
		MatrixMask &Matrixmask,
		U8 (&matrix)[MatrixSize],
		U8 TEXADD);
	~MatrixGenerate();
};
#endif