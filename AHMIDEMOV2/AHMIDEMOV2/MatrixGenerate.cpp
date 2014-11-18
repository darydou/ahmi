#include "stdafx.h"
#include "MatrixGenerate.h"
//构造函数
MatrixGenerate::MatrixGenerate()
{
	Matrix[0] = 1 << 4;
	Matrix[1] = 0;
	Matrix[2] = 0;
	Matrix[3] = 0;
	Matrix[4] = 1 << 4;
	Matrix[5] = 0;
	Matrix[6] = 0;
	Matrix[7] = 0;
	Matrix[8] = 1 << 4;
	for (S32 i = 0; i < MSize; i++)
	{
		MatrixTemp[i] = Matrix[i];
		MatrixCurrent[i] = Matrix[i];
	}
}
//析构函数
MatrixGenerate::~MatrixGenerate()
{

}

//由角度转换成正弦值和余弦值
void MatrixGenerate::CORDIC(S16 &Radian, S16 &COS, S16 &SIN)
{
	S16 Angle[14] = { 5760, 3400, 1797, 912, 458, 229, 115, 57, 29, 14, 7, 4, 2, 1 };             //将上述角度扩大128倍
	S16 cosine[14] = { 181, 162, 157, 156, 156, 155, 155, 155, 155, 155, 155, 155, 155, 155 };   //cos@的结果乘以256
	S16 x, y;
	x = COS;
	y = SIN;
	x = x * 1024;
	y = y * 1024;
	S32 count_i;
	S32 coeff1 = 0, coeff2 = 0;
	while (Radian >= 360)
		Radian = Radian - 360;
	while (Radian < 0)
		Radian = Radian + 360;
	if (Radian == 0 || Radian == 180)
	{

		if (Radian == 0)
		{
			COS = x;
			SIN = y;
		}
		else //(Radian == 180)
		{
			COS = -x;
			SIN = y;
		}
	}
	else if (Radian == 90 || Radian == 270)
	{

		if (Radian == 90)
		{
			COS = y;
			SIN = x;
		}
		else //(Radian == 270)
		{
			COS = y;
			SIN = -x;
		}
	}
	else
	{
		if (Radian > 0 && Radian < 90)
		{
			coeff1 = 1, coeff2 = 1;
		}
		else if (Radian >= 90 && Radian < 180)
		{
			Radian = Radian - 90;
			Radian = 90 - Radian;
			coeff1 = -1, coeff2 = 1;
		}
		else if (Radian > 180 && Radian < 270)
		{
			Radian = Radian - 180;
			coeff1 = -1, coeff2 = -1;
		}
		else if (Radian >= 270 && Radian < 360)
		{
			Radian = Radian - 270;
			Radian = 90 - Radian;
			coeff1 = 1, coeff2 = -1;
		}
		Radian = Radian * 128;
		for (count_i = 0; count_i <= 13; count_i++)
		{
			if (Radian>0)      //大于0表示，在角度30下面，要继续逆时针旋转，小于0表示在角度30度上面，要回转
			{
				Radian = Radian - Angle[count_i];
				COS = (x - (y >> count_i));
				SIN = (y + (x >> count_i));
				x = COS;
				y = SIN;
			}
			else if (Radian < 0)
			{
				Radian = Radian + Angle[count_i];
				COS = (x + (y >> count_i));
				SIN = (y - (x >> count_i));
				x = COS;
				y = SIN;
			}
			if (Radian == 0)
			{
				COS = coeff1*COS*cosine[count_i] >> 8;
				SIN = coeff2*SIN*cosine[count_i] >> 8;
				break;
			}
		}
	}
}
//尺度变换
void MatrixGenerate::Triscale(S1_3_4 cx, S1_3_4 cy)
{
	if ((cx == 0) != 0 || (cy == 0) != 0)
		printf("The number cx and cy can not be valued with zero!\n");
	for (S32 i = 0; i < MSize; i++)
		MatrixCurrent[i] = Matrix[i];
	Matrix[0] = (S1_B_4(MatrixCurrent[0] * (S1_B_4)cx)) >> 4;
	Matrix[1] = (S1_B_4(MatrixCurrent[1] * (S1_B_4)cy)) >> 4;
	Matrix[3] = (S1_B_4(MatrixCurrent[3] * (S1_B_4)cx)) >> 4;
	Matrix[4] = (S1_B_4(MatrixCurrent[4] * (S1_B_4)cy)) >> 4;
	Matrix[6] = (S32((S32)MatrixCurrent[6] * (S32)cx)) >> 4;
	Matrix[7] = (S32((S32)MatrixCurrent[7] * (S32)cy)) >> 4;
	for (S32 i = 0; i < MSize; i++)
		MatrixCurrent[i] = MatrixTemp[i];
	//cx,cy等于零时没有规避
	MatrixTemp[0] = (S32(((S32)MatrixCurrent[0]) << 4) / (S32)cy);
	MatrixTemp[1] = (S32(((S32)MatrixCurrent[1]) << 4) / (S32)cy);
	MatrixTemp[3] = (S32(((S32)MatrixCurrent[3]) << 4) / (S32)cy);
	MatrixTemp[4] = (S32(((S32)MatrixCurrent[4]) << 4) / (S32)cx);
	MatrixTemp[5] = (S32(((S32)MatrixCurrent[5]) << 4) / (S32)cx);
	MatrixTemp[6] = (S32(((S32)MatrixCurrent[6]) << 4) / (S32)(cx*cy));
	MatrixTemp[7] = (S32(((S32)MatrixCurrent[7]) << 4) / (S32)(cx*cy));
	MatrixTemp[8] = (S32(((S32)MatrixCurrent[8]) << 4) / (S32)(cx*cy));
}

//旋转功能
void MatrixGenerate::Trirotate(S16 degrees)
{
	S16 COS = 1, SIN = 0;
	CORDIC(degrees, COS, SIN);
	S1_B_4 cos = COS >> (10 - 4);
	S1_B_4 sin = SIN >> (10 - 4);
	for (int i = 0; i < MSize; i++)
		MatrixCurrent[i] = Matrix[i];
	Matrix[0] = (MatrixCurrent[0] * cos - MatrixCurrent[1] * sin) >> 4;
	Matrix[1] = (MatrixCurrent[0] * sin + MatrixCurrent[1] * cos) >> 4;
	Matrix[3] = (MatrixCurrent[3] * cos - MatrixCurrent[4] * sin) >> 4;
	Matrix[4] = (MatrixCurrent[3] * sin + MatrixCurrent[4] * cos) >> 4;
	Matrix[6] = ((S32)(MatrixCurrent[6] * cos) - (S32)(MatrixCurrent[7] * sin)) >> 4;
	Matrix[7] = ((S32)(MatrixCurrent[6] * sin) + (S32)(MatrixCurrent[7] * cos)) >> 4;
	for (int i = 0; i < MSize; i++)
		MatrixCurrent[i] = MatrixTemp[i];
	MatrixTemp[0] = (cos*MatrixCurrent[0] - sin*MatrixCurrent[3]) >> 4;
	MatrixTemp[1] = (cos*MatrixCurrent[1] - sin*MatrixCurrent[4]) >> 4;
	MatrixTemp[2] = (cos*MatrixCurrent[2] - sin*MatrixCurrent[5]) >> 4;
	MatrixTemp[3] = (sin*MatrixCurrent[0] + cos*MatrixCurrent[3]) >> 4;
	MatrixTemp[4] = (sin*MatrixCurrent[1] + cos*MatrixCurrent[4]) >> 4;
	MatrixTemp[5] = (sin*MatrixCurrent[2] + cos*MatrixCurrent[5]) >> 4;
}
//平移功能
void MatrixGenerate::Tritranslate(S1_B_4 tx, S1_B_4 ty)
{
	for (int i = 0; i < MSize; i++)
		MatrixCurrent[i] = Matrix[i];
	Matrix[0] = MatrixCurrent[0] + ((MatrixCurrent[2] * tx) >> 4);
	Matrix[1] = MatrixCurrent[1] + ((MatrixCurrent[2] * ty) >> 4);
	Matrix[3] = MatrixCurrent[3] + ((MatrixCurrent[5] * tx) >> 4);
	Matrix[4] = MatrixCurrent[4] + ((MatrixCurrent[5] * ty) >> 4);
	Matrix[6] = MatrixCurrent[6] + (((S32)(MatrixCurrent[8] * tx)) >> 4);
	Matrix[7] = MatrixCurrent[7] + (((S32)(MatrixCurrent[8] * ty)) >> 4);
	for (int i = 0; i < MSize; i++)
		MatrixCurrent[i] = MatrixTemp[i];
	MatrixTemp[6] = (S32(-(S32)tx*(S32)MatrixCurrent[0] - (S32)ty*(S32)MatrixCurrent[3]) >> 4) + MatrixCurrent[6];
	MatrixTemp[7] = (S32(-(S32)tx*(S32)MatrixCurrent[1] - (S32)ty*(S32)MatrixCurrent[4]) >> 4) + MatrixCurrent[7];
	MatrixTemp[8] = (S32(-(S32)tx*(S32)MatrixCurrent[2] - (S32)ty*(S32)MatrixCurrent[5]) >> 4) + MatrixCurrent[8];
}
//水平偏移
void MatrixGenerate::Trivertical(S1_3_4 sv)
{
	for (int i = 0; i < MSize; i++)
		MatrixCurrent[i] = Matrix[i];
	Matrix[0] = MatrixCurrent[0] + ((MatrixCurrent[1] * ((S1_B_4)sv)) >> 4);
	Matrix[3] = MatrixCurrent[3] + ((MatrixCurrent[4] * ((S1_B_4)sv)) >> 4);
	Matrix[6] = MatrixCurrent[6] + ((S32(MatrixCurrent[7] * ((S1_B_4)sv))) >> 4);
	for (int i = 0; i < MSize; i++)
		MatrixCurrent[i] = MatrixTemp[i];
	MatrixTemp[3] = (S32(-(S1_B_4)sv*MatrixCurrent[0]) >> 4) + MatrixCurrent[3];
	MatrixTemp[4] = (S32(-(S1_B_4)sv*MatrixCurrent[1]) >> 4) + MatrixCurrent[4];
	MatrixTemp[5] = (S32(-(S1_B_4)sv*MatrixCurrent[2]) >> 4) + MatrixCurrent[5];
}
//垂直偏移
void MatrixGenerate::Trihorizontal(S1_3_4 sh)
{
	for (int i = 0; i < MSize; i++)
		MatrixCurrent[i] = Matrix[i];
	Matrix[1] = ((MatrixCurrent[0] * ((S1_B_4)sh)) >> 4) + MatrixCurrent[1];
	Matrix[4] = ((MatrixCurrent[3] * ((S1_B_4)sh)) >> 4) + MatrixCurrent[4];
	Matrix[7] = ((S32(MatrixCurrent[6] * ((S1_B_4)sh)) >> 4)) + MatrixCurrent[7];
	for (int i = 0; i < MSize; i++)
		MatrixCurrent[i] = MatrixTemp[i];
	MatrixTemp[0] = MatrixCurrent[0] - (S32(((S1_B_4)sh)*MatrixCurrent[3]) >> 4);
	MatrixTemp[1] = MatrixCurrent[1] - (S32(((S1_B_4)sh)*MatrixCurrent[4]) >> 4);
	MatrixTemp[2] = MatrixCurrent[2] - (S32(((S1_B_4)sh)*MatrixCurrent[5]) >> 4);
}
//传递变换矩阵
void MatrixGenerate::GetMatrix(struct _Matrix &tile_info_matrix,
	MatrixMask1 &Matrixmask,
	U8 &matrix,
	U8 TEXADD)
{
	//for (int i = 0; i < MSize; i++)
	//	Matrixmask->Matrixmask1[TEXADD - 1].Matrix[i] = Matrix[i];
	//int FloatValue, Exp, MantissaPart, FloatPath, bfloat;
	//char a[4] = {0,0,0,0};
	//int count = 0;
	//unsigned char flag = 0;
	//for (int i = 0; i < MSize - 3; i++)
	//{
	//	if (i % 3 < 2)
	//	{
	//		FloatValue = *reinterpret_cast<int*>(&Matrix[i]); //MatrixTemp[i]
	//		if (FloatValue == 0||FloatValue==0x80000000)//等于正零或者负零时直接赋零
	//			a[count] = 0;
	//		else
	//		{
	//			flag = 0;
	//			if (FloatValue & 0x80000000)
	//				flag = 1;
	//			Exp = (FloatValue >> 23) & 0xff;
	//			MantissaPart = (FloatValue & 0x7fffff) | 0x800000;//尾数字段，23位加一个默认位，共24位。
	//			if ((MantissaPart >> (150 - Exp)) >8)//150=127+23编译原理
	//			{
	//				cout << "The num is out of the size!\n" << endl;
	//				system("pause");
	//				exit(0);
	//			}
	//			else
	//			{
	//				//整数部分1.3.4
	//				char zs = ((MantissaPart >> (150 - Exp)) * 16);
	//				//小数部分1.3.4
	//				FloatPath = MantissaPart&(0xffffff >>((Exp - 126)>0?(Exp-126):0));//取得小数部分
	//				char xs = ((FloatPath / float(1 << (150 - Exp))) * 16);
	//				if (flag== 1)
	//				{
	//					a[count] = -(zs | xs);
	//				}
	//				else
	//					a[count] = zs | xs;
	//			}
	//		}
	//		count++; 
	//	}
	//}
	//short b[2] = {0,0};
	//count = 0;
	//for (int i = MSize - 3; i < MSize-1; i++)
	//{
	//	FloatValue = *reinterpret_cast<int*>(&Matrix[i]);//(&MatrixTemp[i])
	//	if (FloatValue == 0||FloatValue==0x80000000)
	//		b[count] = 0;
	//	else
	//	{
	//		flag = 0;
	//		if (FloatValue & 0x80000000)
	//			flag=1;
	//		Exp = (FloatValue >> 23) & 0xff;
	//		MantissaPart = (FloatValue & 0x7fffff) | 0x800000;//尾数字段，23位加一个默认位，共24位。
	//		if ((MantissaPart >> (150 - Exp)) >2048)
	//		{
	//			cout << "The num is out of the size!\n" << endl;
	//			system("pause");
	//			exit(0);
	//		}
	//		else
	//		{
	//			//整数部分1.3.4
	//			short zs = ((MantissaPart >> (150 - Exp)) * 16);
	//			//小数部分1.3.4
	//			FloatPath = MantissaPart&(0xffffff >> ((Exp - 126)>0?(Exp-126):0));//取得小数部分
	//			short xs = ((FloatPath / float(1 << (150 - Exp))) * 16);
	//			if (flag == 1)
	//			{
	//				b[count] = -(zs | xs);
	//			}
	//			else
	//				b[count] = zs | xs;
	//		}
	//	}
	//	count++;
	//} 

	tile_info_matrix.A = (S1_3_4)Matrix[0];
	tile_info_matrix.B = (S1_3_4)Matrix[1];
	tile_info_matrix.C = (S1_3_4)Matrix[3];
	tile_info_matrix.D = (S1_3_4)Matrix[4];
	tile_info_matrix.E = Matrix[6];
	tile_info_matrix.F = Matrix[7];
	matrix = TEXADD - 1;
}
