#ifndef _MATRIXGENERATE
#define _MATRIXGENERATE
#include "ALLHeader.h"
static const U8 MSize = 9;
const U16 magnitude=7;
class MatrixGenerate
{
private:
	S16 Matrix[MSize];
	S16 MatrixTemp[MSize];
	S16 MatrixCurrent[MSize];
	void CORDIC(S16 &Radian, S16 &COS, S16 &SIN);//由角度计算cos和sin
public:
	MatrixGenerate();
	void Triscale(S16 cx, S16 cy);
	void Tritranslate(S1_B_4 tx, S1_B_4 ty);
	void Trirotate(S16 degrees);
	void Trihorizontal(S1_1_6 sv);
	void Trivertical(S1_1_6 sh);
	void MatrixING();
	void GetMatrix(TileInfo &tile_info,
		MatrixMask &Matrixmask,
		U8 (&matrix)[MatrixSize],
		U8 TEXADD);
	~MatrixGenerate();
};
#endif