// AHMIDEMOV2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AHMIDEMOV2.h"

void start()
{
	TileInfo  tile_info   ;
	ROMInfo rom_info  ;
	/**************驱动必须无需改变****************/
	TileInfoMask *tileinfomask = new TileInfoMask;
	MatrixMask *Matrixmask     = new MatrixMask;
	U8 *matrix=new U8 [MatrixSize];//纹理标记数组，取值0~256
	TileInfoMaskIng(tileinfomask);
	//memset(tile_info, 0, sizeof(TileInfo));
	//memset(Matrixmask,0,sizeof(MatrixMask));
	U8 RomAddr = 0;//记录非纯色纹理的数目
	U8 TEXADD =  0; //记录全部纹理的数目
	/********************************************/
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
	//ReadROMinfo(PICNAME0, &rom_info, tileinfomask, RomAddr, TEXADD, 1);
	MatrixGenerate Matrixgenerate;
	Matrixgenerate.Tritranslate(((S1_B_4)-100) << 4, ((S1_B_4)-100) << 4);//已测试
	Matrixgenerate.Triscale(3<<4,3<<4);//本身不为负数 已测试
	//MatrixGenerate.Trihorizontal(3);//本身不为负数 已测试
	//MatrixGenerate.Trivertical(1);//本身不为负数 已测试
	Matrixgenerate.Trirotate((S16)-45); //已测试
	Matrixgenerate.GetMatrix(tile_info,
		Matrixmask,
		matrix,
		TEXADD);//获取矩阵
	//ReadROMinfo(PICNAME1, rom_info, tileinfomask, RomAddr, TEXADD, 1);
	GetMatrix(matrix, TEXADD, 0);
	//ReadROMinfo(PICNAME2, rom_info, tileinfomask, RomAddr, TEXADD, 0);
	GetMatrix(matrix, TEXADD, 0);
	//ADDPurity(tileinfomask,TEXADD,1,125,96,125,1024,768);
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
	for (U8 i = 0; i < RomAddr; i++)
		delete[] rom_info.tex[i].texel;
	delete tileinfomask;
	delete Matrixmask;
	delete[] matrix;
}

void display(void)
{
	// 清除屏幕并不必要
	// 每次绘制时，画面都覆盖整个屏幕
	// 因此无论是否清除屏幕，结果都一样
	// glClear(GL_COLOR_BUFFER_BIT);

	// 绘制像素
	glDrawPixels(ImageWidth, ImageHeight,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, PixelData);

	// 完成绘制
	glutSwapBuffers();
}
//void mouse_move(int x, int y)
//{
//	//_CrtSetBreakAlloc(2754);
//	/*************测试一段代码时间***************/
//	//unsigned long ticks1,ticks2;
//	//ticks1 = GetTickCount();
//	//start(x, y);
//	//ticks2 = GetTickCount();
//	//printf("The Start count num is %d\nThe start run time is %d \n", 
//	//	    ++count, ticks2 - ticks1);
//	/******************************************/
//	//for (int i = 0; i<ImageWidth*ImageHeight; i++)
//	//{
//	//	*(PixelData + i * 3) = GLubyte(((*(FrameBuffer + i)) & 0x7C00) >> 7);
//	//	*(PixelData + i * 3 + 1) = GLubyte(((*(FrameBuffer + i)) & 0x03E0) >> 2);
//	//	*(PixelData + i * 3 + 2) = GLubyte(((*(FrameBuffer + i)) & 0x001F) << 3);
//	//}
//	display();
//	glutPostRedisplay();
//	printf("%d %d\n", x, 768 - y);
//}
int main(int argc, char* argv[])
{
	//_CrtSetBreakAlloc(168);
	int i, j, addr, k = 0;
	PixelData = (GLubyte*)malloc(PixelLength);
	
	//运行主程序产生所需的数据
	start();

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

	//将产生的数据强制转换并保存到PixelData中
	for (i = 0; i<768; i++)
		for (j = 0; j<1024; j++)
		{
		addr = i * 1024 + j;
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
//	glutPassiveMotionFunc(mouse_move);
	glutMainLoop();

	// 释放内存
	// 实际上，glutMainLoop函数永远不会返回，这里也永远不会到达
	// 这里写释放内存只是出于一种个人习惯
	// 不用担心内存无法释放。在程序结束时操作系统会自动回收所有内存
	free(PixelData);

	return 0;
}


