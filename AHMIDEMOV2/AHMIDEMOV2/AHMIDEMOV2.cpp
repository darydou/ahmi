// AHMIDEMOV2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AHMIDEMOV2.h"
#include "DrawTool.h"
static int bigcircledegree = 45;
static int smallcircleldegree = 45;
static int smallcirclerdegree = 135;
static int bigflag = 0;
static int smallflag = 0;
static int smallflag1 = 0;
//所需的全局变量
//add by darydou 12.26
//将所有的驱动所需数据在此申明
TileInfo  tile_info;
ROMInfo   rom_info;
/**************驱动必须无需改变****************/
TileInfoMask tileinfomask;
MatrixMask Matrixmask;
U8 matrix[MatrixSize];//纹理标记数组，取值0~256
U8 RomAddr = 0;//记录非纯色纹理的数目
U8 TEXADD = 0;//记录全部纹理的数目
/********************************************/

void globalstart(int a,int b,int c)
{
	//TileInfo  tile_info;
	//ROMInfo   rom_info ;
	///**************驱动必须无需改变****************/
	//TileInfoMask tileinfomask;
	//MatrixMask Matrixmask;
	//U8 matrix[MatrixSize];//纹理标记数组，取值0~256
	//TileInfoMaskIng(tileinfomask);
	////memset(tile_info, 0, sizeof(TileInfo));
	//memset(Matrixmask,0,sizeof(MatrixMask));
	//U8 RomAddr = 0;//记录非纯色纹理的数目
	//U8 TEXADD =  0;//记录全部纹理的数目
	/********************************************/
	//导入字库函数
	//LoadEnglishLibrary("songtienglish16.dat","fym1.dat",8,16);
	//LoadEnglishLibrary("english32.dat", "englishlibrary32.dat", 16, 32);
	/********请依照下述添加纹理及其变换矩阵********/
	//添加alpha或者*.dds纹理
	//ReadROMinfo(char*filename, 
	//	        rom_info, 
	//			tileinfomask, 
	//			RomAddr, 
	//			TEXADD, 
	//           int mask);
	//添加纯色纹理
	//ADDPurity(tileinfomask,
	//	        TEXADD,
	//	        int mask,
	//	        unsigned char r,
	//	        unsigned char g,
	//	        unsigned char b,
	//	        unsigned short width,
	//	        unsigned short height);
	//添加变换矩阵
	//MatrixGenerate MatrixGenerate;
	//MatrixGenerate.Triscale(float cx, float cy);//尺度变换
	//MatrixGenerate.Trirotate(int degrees);//旋转角度
	//MatrixGenerate.Tritranslate(short tx, short ty);//平移
	//MatrixGenerate.Trihorizontal(char sh);//水平偏移
	//MatrixGenerate.Trivertical(char sv);//垂直偏移
	//MatrixGenerate.GetMatrix(tile_info, 
	//                        Matrixmask, 
	//			              matrix, 
	//			              TEXADD);//获取矩阵
	//不添加变换矩阵
	//MatrixGenerate MatrixGenerate;
	//MatrixGenerate.GetMatrix(tile_info, 
	//                        Matrixmask, 
	//                        matrix, 
	//                        TEXADD);//获取矩阵
	//与前任一纹理保持一致
	// GetMatrix(matrix,TEXADD,int num);//num表示第几个纹理
	/********************************************/
	ReadROMinfo(PICNAME4, rom_info, tileinfomask, RomAddr, TEXADD, 0);
	TOOL::MatrixGenerate Matrixgenerater;
	//
	//
	//Matrixgenerate.Triscale(2<<magnitude, 2<<magnitude);
	//Matrixgenerate.Trirotate(10);
	Matrixgenerater.Tritranslate(80, 80);
	//
	Matrixgenerater.GetMatrix(tile_info,
		Matrixmask,
		matrix,
		TEXADD);

	ReadROMinfo(PICNAME5, rom_info, tileinfomask, RomAddr, TEXADD, 0);
	TOOL::MatrixGenerate Matrixgenerater1;
	//
	//
	//Matrixgenerate.Triscale(2<<magnitude, 2<<magnitude);
	//Matrixgenerate.Trirotate(10);
	Matrixgenerater1.Tritranslate(1024-320, 80);
	//
	Matrixgenerater1.GetMatrix(tile_info,
		Matrixmask,
		matrix,
		TEXADD);

	ReadROMinfo(PICNAME3, rom_info, tileinfomask, RomAddr, TEXADD, 0);
	TOOL::MatrixGenerate Matrixgenerate;
	//
	//
	//Matrixgenerate.Triscale(2<<magnitude, 2<<magnitude);
	//Matrixgenerate.Trirotate(10);
	Matrixgenerate.Tritranslate(280, 280);
	//
	Matrixgenerate.GetMatrix(tile_info,
		Matrixmask,
		matrix,
		TEXADD);
	TOOL::ADDPurity(tileinfomask, TEXADD,
		1, 255, 255, 255,
		1024,
		768);
	//ADDPurity(tileinfomask, TEXADD, 1, 125, 96, 125, 1024, 768);
	//WriteChinese("大",rom_info,tileinfomask,RomAddr,TEXADD);

	//DrawCircle(128, 200, 200,
	//	tile_info,
	//	rom_info,
	//	Matrixmask,
	//	tileinfomask,
	//	matrix,
	//	RomAddr,
	//	TEXADD, 255, 255, 255);
	DrawPointer(tile_info,
		rom_info,
		Matrixmask,
		tileinfomask,
		matrix,
		RomAddr,
		TEXADD,
		200, 200, b, 88);
	
	//DrawCircle(128, 1024-200, 200,
	//	tile_info,
	//	rom_info,
	//	Matrixmask,
	//	tileinfomask,
	//	matrix,
	//	RomAddr,
	//	TEXADD, 255, 255, 255);
	
	DrawPointer(tile_info,
		rom_info,
		Matrixmask,
		tileinfomask,
		matrix,
		RomAddr,
		TEXADD,
		1024 - 200, 200, c, 88);
	
	 //DrawCircle(190, 500, 500,
	 //	tile_info,
	 //	rom_info,
	 //	Matrixmask,
	 //	tileinfomask,
	 //	matrix,
	 //	RomAddr,
	 //	TEXADD,255,255,255);
	
	WriteChinese("速度", 16, 444, 623,
		rom_info,
		tile_info,
		Matrixmask,
		tileinfomask,
		matrix,
		RomAddr,
		TEXADD,0,0,0);
	
	WriteEnglish("km/h", 16, 520, 623,
		rom_info,
		tile_info,
		Matrixmask,
		tileinfomask,
		matrix,
		RomAddr,
		TEXADD,0,0,0);
	//void WriteEnglish(string word, U8 size, S16 tx, S16 ty,
	//	ROMInfo &rom_info,
	//	TileInfo &tile_info,
	//	MatrixMask &Matrixmask,
	//	TileInfoMask &tileinfomask,
	//	U8(&matrix)[MatrixSize],
	//	U8 &RomAddr,
	//	U8 &TEXADD);
	int value = ((a - 42) % 273) * 260 / 273;
	WriteNum(value, 16, 470, 640,
		rom_info,
		tile_info,
		Matrixmask,
		tileinfomask,
		matrix,
		RomAddr,
		TEXADD, 255, 255, 255);
	DrawPointer(tile_info,
	  	rom_info     ,
	  	Matrixmask   ,
	  	tileinfomask ,
	  	matrix , 
	  	RomAddr,
	  	TEXADD ,
		500, 500, a,200);


	//ReadROMinfo(PICNAME1, rom_info, tileinfomask, RomAddr, TEXADD,0);
	//MatrixGenerate Matrixgenerate;
	//Matrixgenerate.Tritranslate(((S1_B_4)-1000) << 4, ((S1_B_4)-300) << 4);//已测试
	//Matrixgenerate.Triscale(2,2);//本身不为负数 已测试
	//MatrixGenerate.Trihorizontal(3);//本身不为负数 已测试
	//MatrixGenerate.Trivertical(1);//本身不为负数 已测试
	//Matrixgenerate.Trirotate((S16)-180); //已测试
	//Matrixgenerate.GetMatrix(tile_info,
	//	Matrixmask,
	//	matrix,
	//	TEXADD);//获取矩阵
	//ReadROMinfo(PICNAME1, rom_info, tileinfomask, RomAddr, TEXADD, 1);
	//GetMatrix(matrix, TEXADD, 0);
	//ReadROMinfo(PICNAME2, rom_info, tileinfomask, RomAddr, TEXADD, 0);
	//GetMatrix(matrix, TEXADD, 0);
	
	/*******************更新tile_info信息*********************/
	TileInfoGenrate(tile_info,
		Matrixmask,
		matrix,
		tileinfomask,
		TEXADD,
		rom_info);
	/********************************************************/
	/********************************************************/
	memset(FrameBuffer, 0, sizeof(U16) * ScreenWidth * ScreenHeight);
	ahmi  my_ahmi(ScreenWidth, ScreenHeight);
	ahmi *my_ahmi_p = &my_ahmi;
	Flush(my_ahmi_p, &tile_info, &rom_info);
	/********************************************************/
	//for (U8 i = 0; i < RomAddr; i++)
	//	delete[] rom_info.tex[i].texel;
}
void start(int a, int b,int c)
{
	DrawPointer(tile_info,
		rom_info,
		Matrixmask,
		tileinfomask,
		matrix,
		3+1+1+1-2+1,
		200, 200, b, 88);
	DrawPointer(tile_info,
		rom_info,
		Matrixmask,
		tileinfomask,
		matrix,
		7+1+1+1-2+1-2,
		1024 - 200, 200, c, 88);
	int value = ((a - 42) % 273) * 260 / 273;
	WriteNum(value, 40,
		rom_info,
		tile_info,
		Matrixmask,
		tileinfomask,
		matrix,
		7+1-1+1-1,
		14+1-2+1+1-2+1-2, 0, 0, 0);
	DrawPointer(
		tile_info,
		rom_info,
		Matrixmask,
		tileinfomask,
		matrix,
		17+1-2+1+1-2+1-2,
		500, 500, a, 200);
	/*******************更新tile_info信息*********************/
	TileInfoGenrate(tile_info,
		Matrixmask,
		matrix,
		tileinfomask,
		TEXADD,
		rom_info);
	/********************************************************/
	/********************************************************/
	memset(FrameBuffer, 0, sizeof(U16) * ScreenWidth * ScreenHeight);
	ahmi  my_ahmi(ScreenWidth, ScreenHeight);
	ahmi *my_ahmi_p = &my_ahmi;
	Flush(my_ahmi_p, &tile_info, &rom_info);
	/********************************************************/
}

void display(void)
{
	// 清除屏幕并不必要
	// 每次绘制时，画面都覆盖整个屏幕
	// 因此无论是否清除屏幕，结果都一样
	// glClear(GL_COLOR_BUFFER_BIT);

	// 绘制像素
	glDrawPixels(ImageWidth, ImageHeight,
		GL_RGB, GL_UNSIGNED_BYTE, PixelData);

	// 完成绘制
	glutSwapBuffers();
}

void myIdle(void)
{
	///* 新的函数，在空闲时调用，作用是把指针旋转一度并重新绘制，达到动画效果 */
	//++day;
	//if (day  >= 360)
	//	day  = 0;
	if (smallcircleldegree >= 314)
		smallflag = 1;
	else if (smallcircleldegree <= 45)
		smallflag = 0;
	if (smallflag == 0)
		++smallcircleldegree;
	else if (smallflag == 1)
		--smallcircleldegree;
	if (smallcirclerdegree >= 314)
		smallflag1 = 1;
	else if (smallcirclerdegree <= 135)
		smallflag1 = 0;
	if (smallflag1 == 0)
		++smallcirclerdegree;
	else if (smallflag1 == 1)
		--smallcirclerdegree;
	if (bigcircledegree >= 314)
		bigflag=1;
	else if (bigcircledegree <= 45)
		bigflag=0;
	if (bigflag == 0)
		++bigcircledegree;
	else if (bigflag == 1)
		--bigcircledegree;
	start(bigcircledegree, smallcircleldegree,smallcirclerdegree);
	int k = 0;
	for (int i = 0; i<ImageHeight; i++)
		for (int j = 0; j<ImageWidth; j++)
		{
			int addr = (ImageHeight - 1 - i) * ImageWidth + j;
			*(PixelData + k) = GLubyte(((*(FrameBuffer + addr)) & 0x7C00) >> 7);
			*(PixelData + k + 1) = GLubyte(((*(FrameBuffer + addr)) & 0x03E0) >> 2);
			*(PixelData + k + 2) = GLubyte(((*(FrameBuffer + addr)) & 0x001F) << 3);
			k = k + 3;
		}
	display();
}
//void mouse_move(int x, int y)
//{
	//_CrtSetBreakAlloc(2754);
	/*************测试一段代码时间***************/
	//unsigned long ticks1,ticks2;
	//ticks1 = GetTickCount();
	//start(x, y);
	//ticks2 = GetTickCount();
	//printf("The Start count num is %d\nThe start run time is %d \n", 
	//	    ++count, ticks2 - ticks1);
	/******************************************/
	//for (int i = 0; i<ImageWidth*ImageHeight; i++)
	//{
	//	*(PixelData + i * 3) = GLubyte(((*(FrameBuffer + i)) & 0x7C00) >> 7);
	//	*(PixelData + i * 3 + 1) = GLubyte(((*(FrameBuffer + i)) & 0x03E0) >> 2);
	//	*(PixelData + i * 3 + 2) = GLubyte(((*(FrameBuffer + i)) & 0x001F) << 3);
	//}
	//start(x+y);
	//int k = 0;
	//for (int i = 0; i<768; i++)
	//	for (int j = 0; j<1024; j++)
	//	{
	//	int addr = (767 - i) * 1024 + j;
	//	*(PixelData + k) = GLubyte(((*(FrameBuffer + addr)) & 0x7C00) >> 7);
	//	*(PixelData + k + 1) = GLubyte(((*(FrameBuffer + addr)) & 0x03E0) >> 2);
	//	*(PixelData + k + 2) = GLubyte(((*(FrameBuffer + addr)) & 0x001F) << 3);
	//	k = k + 3;
	//	}
	//display();
	//glutPostRedisplay();
//	printf("%d %d\n", x, y);
//}

int main(int argc, char* argv[])
{
	//_CrtSetBreakAlloc(168);
	int i, j, addr, k=0 ;
	PixelData = (GLubyte*)malloc(PixelLength);
	
	_CrtDumpMemoryLeaks();//报告内存泄露函数
	// 打开文件
	//FILE* pFile = fopen("Bliss.bmp", "rb");
	//if( pFile == 0 )
	//    exit(0);

	// 读取图象的大小信息
	//fseek(pFile, 0x0012, SEEK_SET);
	//fread(&ImageWidth, sizeof(ImageWidth), 1, pFile);
	//fread(&ImageHeight, sizeof(ImageHeight), 1, pFile);

	// 计算像素数据长度
	//PixelLength = ImageWidth * 3;
	//while( PixelLength % 4 != 0 )
	//    ++PixelLength;
	//PixelLength *= ImageHeight;

	// 读取像素数据
	//if( PixelData == 0 )
	//    exit(0);

	//fseek(pFile, 54, SEEK_SET);
	//fread(PixelData, PixelLength, 1, pFile);

	// 关闭文件
	//fclose(pFile);

	//add by darydou 12.26
	//运行主程序产生所需的数据
	TileInfoMaskIng(tileinfomask);
	globalstart(45,45,135);
	//将产生的数据强制转换并保存到PixelData中
	for (i = 0; i<ImageHeight; i++)
		for (j = 0; j<ImageWidth; j++)
		{
			addr = (ImageHeight-1 - i) * ImageWidth + j;
			*(PixelData + k) = GLubyte(((*(FrameBuffer + addr)) & 0x7C00) >> 7);
			*(PixelData + k + 1) = GLubyte(((*(FrameBuffer + addr)) & 0x03E0) >> 2);
			*(PixelData + k + 2) = GLubyte(((*(FrameBuffer + addr)) & 0x001F) << 3);
			k = k + 3;
		}
	// 初始化GLUT并运行
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(ImageWidth, ImageHeight);
	glutCreateWindow(FileName);
	glutDisplayFunc(&display);
	glutIdleFunc(&myIdle);// 新加入了这句
	//glutPassiveMotionFunc(mouse_move);
	glutMainLoop();

	// 释放内存
	// 实际上，glutMainLoop函数永远不会返回，这里也永远不会到达
	// 这里写释放内存只是出于一种个人习惯
	// 不用担心内存无法释放。在程序结束时操作系统会自动回收所有内存

	free(PixelData);

	return 0;
}


