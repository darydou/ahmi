// AHMIDEMOV2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AHMIDEMOV2.h"

void start()
{
	TileInfo  tile_info   ;
	ROMInfo rom_info  ;
	/**************������������ı�****************/
	TileInfoMask *tileinfomask = new TileInfoMask;
	MatrixMask *Matrixmask     = new MatrixMask;
	U8 *matrix=new U8 [MatrixSize];//���������飬ȡֵ0~256
	TileInfoMaskIng(tileinfomask);
	//memset(tile_info, 0, sizeof(TileInfo));
	//memset(Matrixmask,0,sizeof(MatrixMask));
	U8 RomAddr = 0;//��¼�Ǵ�ɫ�������Ŀ
	U8 TEXADD =  0; //��¼ȫ���������Ŀ
	/********************************************/
	/********�������������������任����********/
	//���alpha����*.dds����
	//ReadROMinfo(char*filename, 
	//	        rom_info, 
	//			tileinfomask, 
	//			RomAddr, 
	//			TEXADD, 
	//           int mask);
	//��Ӵ�ɫ����
	//ADDPurity(tileinfomask,
	//	        TEXADD,
	//	        int mask,
	//	        unsigned char r,
	//	        unsigned char g,
	//	        unsigned char b,
	//	        unsigned short width,
	//	        unsigned short height);
	//��ӱ任����
	//MatrixGenerate MatrixGenerate;
	//MatrixGenerate.Triscale(float cx, float cy);//�߶ȱ任
	//MatrixGenerate.Trirotate(int degrees);//��ת�Ƕ�
	//MatrixGenerate.Tritranslate(short tx, short ty);//ƽ��
	//MatrixGenerate.Trihorizontal(char sh);//ˮƽƫ��
	//MatrixGenerate.Trivertical(char sv);//��ֱƫ��
	//MatrixGenerate.GetMatrix(tile_info, 
	//                        Matrixmask, 
	//			              matrix, 
	//			              TEXADD);//��ȡ����
	//����ӱ任����
	//MatrixGenerate MatrixGenerate;
	//MatrixGenerate.GetMatrix(tile_info, 
	//                        Matrixmask, 
	//                        matrix, 
	//                        TEXADD);//��ȡ����
	//��ǰ��һ������һ��
	// GetMatrix(matrix,TEXADD,int num);//num��ʾ�ڼ�������
	/********************************************/
	//ReadROMinfo(PICNAME0, &rom_info, tileinfomask, RomAddr, TEXADD, 1);
	MatrixGenerate Matrixgenerate;
	Matrixgenerate.Tritranslate(((S1_B_4)-100) << 4, ((S1_B_4)-100) << 4);//�Ѳ���
	Matrixgenerate.Triscale(3<<4,3<<4);//����Ϊ���� �Ѳ���
	//MatrixGenerate.Trihorizontal(3);//����Ϊ���� �Ѳ���
	//MatrixGenerate.Trivertical(1);//����Ϊ���� �Ѳ���
	Matrixgenerate.Trirotate((S16)-45); //�Ѳ���
	Matrixgenerate.GetMatrix(tile_info,
		Matrixmask,
		matrix,
		TEXADD);//��ȡ����
	//ReadROMinfo(PICNAME1, rom_info, tileinfomask, RomAddr, TEXADD, 1);
	GetMatrix(matrix, TEXADD, 0);
	//ReadROMinfo(PICNAME2, rom_info, tileinfomask, RomAddr, TEXADD, 0);
	GetMatrix(matrix, TEXADD, 0);
	//ADDPurity(tileinfomask,TEXADD,1,125,96,125,1024,768);
	//GetMatrix(matrix, TEXADD, 0);
	/*******************����tile_info��Ϣ*********************/
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
	// �����Ļ������Ҫ
	// ÿ�λ���ʱ�����涼����������Ļ
	// ��������Ƿ������Ļ�������һ��
	// glClear(GL_COLOR_BUFFER_BIT);

	// ��������
	glDrawPixels(ImageWidth, ImageHeight,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, PixelData);

	// ��ɻ���
	glutSwapBuffers();
}
//void mouse_move(int x, int y)
//{
//	//_CrtSetBreakAlloc(2754);
//	/*************����һ�δ���ʱ��***************/
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
	
	//����������������������
	start();

	_CrtDumpMemoryLeaks();//�����ڴ�й¶����
	// ���ļ�
	//FILE* pFile = fopen("Bliss.bmp", "rb");
	//if( pFile == 0 )
	//    exit(0);

	// ��ȡͼ��Ĵ�С��Ϣ
	//fseek(pFile, 0x0012, SEEK_SET);
	//fread(&ImageWidth, sizeof(ImageWidth), 1, pFile);
	//fread(&ImageHeight, sizeof(ImageHeight), 1, pFile);

	// �����������ݳ���
	//PixelLength = ImageWidth * 3;
	//while( PixelLength % 4 != 0 )
	//    ++PixelLength;
	//PixelLength *= ImageHeight;

	// ��ȡ��������
	//if( PixelData == 0 )
	//    exit(0);

	//fseek(pFile, 54, SEEK_SET);
	//fread(PixelData, PixelLength, 1, pFile);

	// �ر��ļ�
	//fclose(pFile);

	//������������ǿ��ת�������浽PixelData��
	for (i = 0; i<768; i++)
		for (j = 0; j<1024; j++)
		{
		addr = i * 1024 + j;
		*(PixelData + k) = GLubyte(((*(FrameBuffer + addr)) & 0x7C00) >> 7);
		*(PixelData + k + 1) = GLubyte(((*(FrameBuffer + addr)) & 0x03E0) >> 2);
		*(PixelData + k + 2) = GLubyte(((*(FrameBuffer + addr)) & 0x001F) << 3);
		k = k + 3;
		}

	// ��ʼ��GLUT������
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(ImageWidth, ImageHeight);
	glutCreateWindow(FileName);
	glutDisplayFunc(&display);
//	glutPassiveMotionFunc(mouse_move);
	glutMainLoop();

	// �ͷ��ڴ�
	// ʵ���ϣ�glutMainLoop������Զ���᷵�أ�����Ҳ��Զ���ᵽ��
	// ����д�ͷ��ڴ�ֻ�ǳ���һ�ָ���ϰ��
	// ���õ����ڴ��޷��ͷš��ڳ������ʱ����ϵͳ���Զ����������ڴ�
	free(PixelData);

	return 0;
}


