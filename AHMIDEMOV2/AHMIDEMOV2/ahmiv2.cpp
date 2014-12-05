// ahmiv2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ahmiv2.h"


extern Color16 * FrameBuffer;
ahmi::ahmi(int width,int height)
{
	screen_height = height;
	screen_width = width;
}
void ahmi::InitTile(Tile* tile,U16 x,U16 y)
{
	int i=0;
	for(i=0;i<1024;i++)
	{
		tile->AlphaBuffer[i]=0;
		tile->x=x;
		tile->y=y;
		tile->MaskBuffer[i]=0;
		tile->mask_usage=1;
		tile->ColorBuffer[i].r=0;
		tile->ColorBuffer[i].g=0;
		tile->ColorBuffer[i].b=0;
		tile->ColorBuffer[i].a=0;
		tile->ColorBuffer[i].m=0;
		tile->color_done=0;
	}
}

void ahmi::InitFinalTile(FinalTile* final_tile,U16 x,U16 y)
{
	int i=0;
	for(i=0;i<1024;i++)
	{
		final_tile->x=x;
		final_tile->y=y;
		final_tile->TileBuffer[i].r=0;
		final_tile->TileBuffer[i].g=0;
		final_tile->TileBuffer[i].b=0;
	}
}

void ahmi::color_blending(FinalTile* final_tile,Tile* tile)
{
	if(tile->mask_usage)
	{
		for(int i=0;i<1024;i++)
		{
			if(tile->ColorBuffer[i].m /*&& tile->MaskBuffer[i]*/)
			{
				final_tile->TileBuffer[i].r=(tile->ColorBuffer[i].r*tile->AlphaBuffer[i]+final_tile->TileBuffer[i].r*(32-tile->AlphaBuffer[i]))/32;
				final_tile->TileBuffer[i].g=(tile->ColorBuffer[i].g*tile->AlphaBuffer[i]+final_tile->TileBuffer[i].g*(32-tile->AlphaBuffer[i]))/32;
				final_tile->TileBuffer[i].b=(tile->ColorBuffer[i].b*tile->AlphaBuffer[i]+final_tile->TileBuffer[i].b*(32-tile->AlphaBuffer[i]))/32;				
				//final_tile->TileBuffer[i].r=(MUL(tile->ColorBuffer[i].r,tile->AlphaBuffer[i])+MUL(final_tile->TileBuffer[i].r,(32-tile->AlphaBuffer[i])))/32;
				//final_tile->TileBuffer[i].g=(MUL(tile->ColorBuffer[i].g,tile->AlphaBuffer[i])+MUL(final_tile->TileBuffer[i].g,(32-tile->AlphaBuffer[i])))/32;
				//final_tile->TileBuffer[i].b=(MUL(tile->ColorBuffer[i].b,tile->AlphaBuffer[i])+MUL(final_tile->TileBuffer[i].b,(32-tile->AlphaBuffer[i])))/32;
			}
		}
	}
	else
	{
		for(int i=0;i<1024;i++)
		{
			if(tile->ColorBuffer[i].m)
			{
				final_tile->TileBuffer[i].r=(tile->ColorBuffer[i].r*tile->ColorBuffer[i].a+final_tile->TileBuffer[i].r*(32-tile->ColorBuffer[i].a))/32;
				final_tile->TileBuffer[i].g=(tile->ColorBuffer[i].g*tile->ColorBuffer[i].a+final_tile->TileBuffer[i].g*(32-tile->ColorBuffer[i].a))/32;
				final_tile->TileBuffer[i].b=(tile->ColorBuffer[i].b*tile->ColorBuffer[i].a+final_tile->TileBuffer[i].b*(32-tile->ColorBuffer[i].a))/32;			
			}
		}
	}
}

void ahmi::cache(U64 block_addr,U16 in_block_addr,Texture* texture,unsigned int * texel,U8 TexType,bool mask_alpha)
{
	U64 tex_out;
	U64 alpha_out;
	Color color0,color1,color2,color3;
	U16 BColor1;
	U16 BColor2;
	unsigned int index_temp;
	U8 index;

	switch (TexType)
	{
	case(0):
		{
			tex_out=*((texture->texel)+block_addr);
			//BColor1=(tex_out&0xFFFF000000000000)>>48;
			//BColor2=(tex_out&0xFFFF00000000)>>32;	
			BColor1=(tex_out&0xFFFF000000000000)>>48;
			BColor2=(tex_out&0xFFFF00000000)>>32;
			BColor1=((BColor1&0xff)<<8)+((BColor1&0xff00)>>8);
			BColor2=((BColor2&0xff)<<8)+((BColor2&0xff00)>>8);
			//index=((tex_out&0xFFFFFFFF)>>in_block_addr)%4;
			index_temp=tex_out&0xFFFFFFFF;
			index_temp=((index_temp&0xff)<<24)+((index_temp&0xff00)<<8)+((index_temp&0xff0000)>>8)+((index_temp&0xff000000)>>24);
			index=(index_temp>>(2*in_block_addr))%4;
				color0.b=(BColor1&0xF800)>>11;
				color0.g=(BColor1&0x07E0)>>6;
				color0.r=(BColor1&0x001F)<<0;
				color0.m=1;
				color1.b=(BColor2&0xF800)>>11;
				color1.g=(BColor2&0x07E0)>>6;
				color1.r=(BColor2&0x001F)<<0;
				color1.m=1;
				if (BColor1>BColor2)
				{
					   color2.r = ( color0.r * 2 + color1.r + 1 ) / 3;
                       color2.g = ( color0.g * 2 + color1.g + 1 ) / 3;
                       color2.b = ( color0.b * 2 + color1.b + 1 ) / 3;
					   color2.m = color0.m | color1.m;
                       
                       color3.r = ( color0.r + color1.r * 2 + 1 ) / 3;
                       color3.g = ( color0.g + color1.g * 2 + 1 ) / 3;
                       color3.b = ( color0.b + color1.b * 2 + 1 ) / 3;
					   color3.m = color0.m | color1.m;
				}
				else 
				{
					   color2.r = ( color0.r + color1.r ) / 2;
                       color2.g = ( color0.g + color1.g ) / 2;
                       color2.b = ( color0.b + color1.b ) / 2;
					   color2.m = color0.m | color1.m;
                       
                       color3.r = ( color0.r + color1.r * 2 + 1 ) / 3;
                       color3.g = ( color0.g + color1.g * 2 + 1 ) / 3;
                       color3.b = ( color0.b + color1.b * 2 + 1 ) / 3;
					   color3.m = color0.m | color1.m;
				}
				switch (index)
					{
					case 0:
						*texel=((Color16)(color0.m)<<15)+((Color16)(color0.r)<<10)+((Color16)(color0.g)<<5)+color0.b;
						break;						 									
					case 1:							 									
						*texel=((Color16)(color1.m)<<15)+((Color16)(color1.r)<<10)+((Color16)(color1.g)<<5)+color1.b;
						break;						 									
					case 2:							 									
						*texel=((Color16)(color2.m)<<15)+((Color16)(color2.r)<<10)+((Color16)(color2.g)<<5)+color2.b;
						break;	
					case 3:
						if (BColor1>BColor2)
						{
						*texel=((Color16)(color3.m)<<15)+((Color16)(color3.r)<<10)+((Color16)(color3.g)<<5)+color3.b;
						}
						else 
						{
							//*((*BMPImageData)->pixels+(i+k/4)*(*BMPImageData)->width*3+(j+k%4)*3  )=color3.r;
							//*((*BMPImageData)->pixels+(i+k/4)*(*BMPImageData)->width*3+(j+k%4)*3+1)=color3.g;
							//*((*BMPImageData)->pixels+(i+k/4)*(*BMPImageData)->width*3+(j+k%4)*3+2)=color3.b;
							*texel=0x7FFFFF;
							//预留 将Alpha值可以保存
						}
						break;
					}
		}
				break;
	case(1):
			tex_out=*((texture->texel)+block_addr*2+1);
			alpha_out=*((texture->texel)+block_addr*2);
			BColor1=(tex_out&0xFFFF000000000000)>>48;
			BColor2=(tex_out&0xFFFF00000000)>>32;
			BColor1=((BColor1&0xff)<<8)+((BColor1&0xff00)>>8);
			BColor2=((BColor2&0xff)<<8)+((BColor2&0xff00)>>8);
			//index=((tex_out&0xFFFFFFFF)>>in_block_addr)%4;
			index_temp=tex_out&0xFFFFFFFF;
			index_temp=((index_temp&0xff)<<24)+((index_temp&0xff00)<<8)+((index_temp&0xff0000)>>8)+((index_temp&0xff000000)>>24);
			index=(index_temp>>(2*in_block_addr))%4;
			alpha_out=((alpha_out&0xff)<<56)+((alpha_out&0xff00)<<40)+((alpha_out&0xff0000)<<24)+((alpha_out&0xff000000)<<8)+((alpha_out&0xff00000000)>>8)+((alpha_out&0xff0000000000)>>24)+((alpha_out&0xff000000000000)>>40)+((alpha_out&0xff00000000000000)>>56);
				//color0.r=(BColor1&0x7C00)>>10;
				//color0.g=(BColor1&0x3E0)>>5;
				//color0.b=(BColor1&0x001F);
				//color0.m=(BColor1&0x8000)>>15;
				////color0.m=1;
				//color1.r=(BColor2&0x7C00)>>10;
				//color1.g=(BColor2&0x3E0)>>5;
				//color1.b=(BColor2&0x001F);
				//color1.m=(BColor2&0x8000)>>15;
				////color1.m=1;
			//color0.r=(BColor1&0x7C00)>>10;
			//color0.g=(BColor1&0x3E0)>>5;
			//color0.b=(BColor1&0x001F);
			//color0.m=(BColor1&0x8000)>>15;
			//color0.m=1;
			//color1.r=(BColor2&0x7C00)>>10;
			//color1.g=(BColor2&0x3E0)>>5;
			//color1.b=(BColor2&0x001F);
			//color1.m=(BColor2&0x8000)>>15;
			//color1.m=1;
				color0.r=(BColor1&0xF800)>>11;
				color0.g=(BColor1&0x07E0)>>6;
				color0.b=(BColor1&0x001F)<<0;
				color0.m=1;
				color1.r=(BColor2&0xF800)>>11;
				color1.g=(BColor2&0x07E0)>>6;
				color1.b=(BColor2&0x001F)<<0;
				color1.m=1;
				if (BColor1>BColor2)
				{
					   color2.r = ( color0.r * 2 + color1.r + 1 ) / 3;
                       color2.g = ( color0.g * 2 + color1.g + 1 ) / 3;
                       color2.b = ( color0.b * 2 + color1.b + 1 ) / 3;
					   color2.m = color0.m | color1.m;
                       
                       color3.r = ( color0.r + color1.r * 2 + 1 ) / 3;
                       color3.g = ( color0.g + color1.g * 2 + 1 ) / 3;
                       color3.b = ( color0.b + color1.b * 2 + 1 ) / 3;
					   color3.m = color0.m | color1.m;
				}
				else 
				{
					   color2.r = ( color0.r + color1.r ) / 2;
                       color2.g = ( color0.g + color1.g ) / 2;
                       color2.b = ( color0.b + color1.b ) / 2;
					   color2.m = color0.m | color1.m;
                       
                       color3.r = ( color0.r + color1.r * 2 + 1 ) / 3;
                       color3.g = ( color0.g + color1.g * 2 + 1 ) / 3;
                       color3.b = ( color0.b + color1.b * 2 + 1 ) / 3;
					   color3.m = color0.m | color1.m;
				}
				switch (index)
					{
					case 0:
						*texel=((Color16)(color0.m)<<15)+((Color16)(color0.r)<<10)+((Color16)(color0.g)<<5)+color0.b+((((alpha_out>>(4*in_block_addr))%16)*2)<<16);
						break;						 									
					case 1:							 									
						*texel=((Color16)(color1.m)<<15)+((Color16)(color1.r)<<10)+((Color16)(color1.g)<<5)+color1.b+((((alpha_out>>(4*in_block_addr))%16)*2)<<16);
						break;						 									
					case 2:							 									
						*texel=((Color16)(color2.m)<<15)+((Color16)(color2.r)<<10)+((Color16)(color2.g)<<5)+color2.b+((((alpha_out>>(4*in_block_addr))%16)*2)<<16);
						break;	
					case 3:
						if (BColor1>BColor2)
						{
						*texel=((Color16)(color3.m)<<15)+((Color16)(color3.r)<<10)+((Color16)(color3.g)<<5)+color3.b+((((alpha_out>>(4*in_block_addr))%16)*2)<<16);
						}
						else 
						{
							//*((*BMPImageData)->pixels+(i+k/4)*(*BMPImageData)->width*3+(j+k%4)*3  )=color3.r;
							//*((*BMPImageData)->pixels+(i+k/4)*(*BMPImageData)->width*3+(j+k%4)*3+1)=color3.g;
							//*((*BMPImageData)->pixels+(i+k/4)*(*BMPImageData)->width*3+(j+k%4)*3+2)=color3.b;
							*texel=0x7FFFFF+((((alpha_out>>(60-4*in_block_addr))%16)*2)<<16);
							//预留 将Alpha值可以保存
						}
						break;
					}
		
			
	break;

	case(2):
			tex_out=*((texture->texel)+block_addr);
			if(mask_alpha)
				*texel=(tex_out>>(56-in_block_addr*8))%256;
			else
				*texel=(tex_out>>(63-in_block_addr))%2 ? 255 : 0;
	break;
	default:
		break;
	}
}

//近邻4个纹素坐标
void xy_uv(short u,short v,short* u1,short* v1,short* u2,short* v2,short* u3,short* v3,short* u4,short* v4)
{
				*u1=u/16;
				*v1=v/16;
				*u2=u/16+1;
				*v2=v/16;
				*u3=u/16;
				*v3=v/16+1;
				*u4=u/16+1;
				*v4=v/16+1;
}

//双线性插值参数
void inter_para(short u,short v,unsigned short* u_para,unsigned short* v_para)
{
	*u_para=(u>=0)? (u%16) : (u%16+16);
	*v_para=(v>=0)? (v%16) : (v%16+16);
}

void ahmi::TexRaster(Tile* tile,Matrix* matrix,Texture* texture,U16 tex_width,U16 tex_height,U8 texture_ctrl,Color16 InitColor)
{
	U8 TexType;
	short u0;
	short v0;
	bool mask_usage;
	bool mask_alpha;
	
	TexType = (texture_ctrl & 0x6) >> 1;
	mask_alpha = (texture_ctrl&0x1);
	//u（x，y）=Ax + Cy + E；v（x，y）= Bx + Dy +F
	u0 = (matrix->A * tile->x + matrix->C * tile->y)/64 + matrix->E;
	v0 = (matrix->B * tile->x + matrix->D * tile->y)/64 + matrix->F;
	//u0 = (MUL(matrix->A , tile->x) + MUL(matrix->C , tile->y))/16 + matrix->E;
	//v0 = (MUL(matrix->B , tile->x) + MUL(matrix->D , tile->y))/16 + matrix->F;
	switch(TexType)
	{
	case(0):
			mask_usage = ((texture_ctrl & 0x1) == 1) ? 1 : 0;
			tile->mask_usage=mask_usage;
			for(int i = 0;i < 1024;i++)
			{
				short u,v;
				short u_u[4];
				short v_v[4];
				unsigned short u_para,v_para;
				U8 x,y;
				unsigned int texel[4];
				int block_row;
				x=i%32;
				y=i/32;
				u = u0 + (matrix->A * x + matrix->C * y) / 4;
				v = v0 + (matrix->B * x + matrix->D * y) / 4;
				block_row = tex_width/4+(((tex_width&0x3)==0)?0:1);
				if((u+32<=0)||(u/16>tex_width-1)||(v+32<=0)||(v/16>tex_height-1))
				{
					//for(int j=0;j<4;j++)
					//{
					//	texel[j]=0;
					//}
					tile->ColorBuffer[i].r=0;
					tile->ColorBuffer[i].g=0;
					tile->ColorBuffer[i].b=0;
					tile->ColorBuffer[i].m=0;
				}
				
				else
				{
					xy_uv(u,v,&u_u[0],&v_v[0],&u_u[1],&v_v[1],&u_u[2],&v_v[2],&u_u[3],&v_v[3]);
					inter_para(u,v,&u_para,&v_para);
					if(u_u[0]<0)
					{
						u_u[0]=u_u[3];
						u_u[2]=u_u[3];
					}
					if(v_v[0]<0)
					{
						v_v[0]=v_v[3];
						v_v[1]=v_v[3];
					}
					if(u_u[1]>tex_width-1)
					{
						u_u[1]=u_u[0];
						u_u[3]=u_u[0];
					}
					if(v_v[3]>tex_height-1)
					{
						v_v[2]=v_v[0];
						v_v[3]=v_v[0];
					}
					for(int j=0;j<4;j++)
					{

						U64 block_addr;
						U16 in_block_addr;
						//block_addr=block_row*(v_v[j]/4)+u_u[j]/4;
						block_addr=MUL(block_row,(v_v[j]/4))+u_u[j]/4;
						in_block_addr=(u_u[j]&0x3)+((v_v[j]&0x3)<<2);
						ahmi::cache(block_addr,in_block_addr,texture,&texel[j],TexType,mask_alpha);
					}
					tile->ColorBuffer[i].r=((16-u_para)*(16-v_para)*((texel[0]&0x7C00)>>10)+(u_para)*(16-v_para)*((texel[1]&0x7C00)>>10)+(16-u_para)*(v_para)*((texel[2]&0x7C00)>>10)+(u_para)*(v_para)*((texel[0]&0x7C00)>>10))/256;
					tile->ColorBuffer[i].g=((16-u_para)*(16-v_para)*((texel[0]&0x3E0)>>5)+(u_para)*(16-v_para)*((texel[1]&0x3E0)>>5)+(16-u_para)*(v_para)*((texel[2]&0x3E0)>>5)+(u_para)*(v_para)*((texel[0]&0x3E0)>>5))/256;
					tile->ColorBuffer[i].b=((16-u_para)*(16-v_para)*((texel[0]&0x1F))+(u_para)*(16-v_para)*((texel[1]&0x1F))+(16-u_para)*(v_para)*((texel[2]&0x1F))+(u_para)*(v_para)*((texel[0]&0x1F)))/256;
					tile->ColorBuffer[i].a=31;
					//tile->ColorBuffer[i].r=(MUL(MUL((16-u_para),(16-v_para)),((texel[0]&0x7C00)>>10))+MUL(MUL((u_para),(16-v_para)),((texel[1]&0x7C00)>>10))+MUL(MUL((16-u_para),(v_para)),((texel[2]&0x7C00)>>10))+MUL((u_para)*(v_para),((texel[0]&0x7C00)>>10)))/256;
					//tile->ColorBuffer[i].g=(MUL((16-u_para)*(16-v_para),((texel[0]&0x3E0)>>5))+MUL((u_para)*(16-v_para),((texel[1]&0x3E0)>>5))+MUL((16-u_para)*(v_para),((texel[2]&0x3E0)>>5))+MUL((u_para)*(v_para),((texel[0]&0x3E0)>>5)))/256;
					//tile->ColorBuffer[i].b=(MUL((16-u_para)*(16-v_para),((texel[0]&0x1F)))+MUL((u_para)*(16-v_para),((texel[1]&0x1F)))+MUL((16-u_para)*(v_para),((texel[2]&0x1F)))+MUL((u_para)*(v_para),((texel[0]&0x1F))))/256;
					tile->ColorBuffer[i].m=((texel[0]&0x8000)==0x8000)?1:0;
					//tile->ColorBuffer[i].r =(texel[0]&0x7C00)>>10;
					//tile->ColorBuffer[i].g =(texel[0]&0x3E0)>>5;
					//tile->ColorBuffer[i].b =texel[0]&0x1F;
					//tile->ColorBuffer[i].m =((texel[0]&0x8000)==0x8000)?1:0;
				}
				tile->color_done=1;
			}			
		break;
	case(1):
			mask_usage = ((texture_ctrl & 0x1) == 1) ? 1 : 0;
			tile->mask_usage=mask_usage;
			for(int i = 0;i < 1024;i++)
			{
				short u,v;
				short u_u[4];
				short v_v[4];
				unsigned short u_para,v_para;
				U8 x,y;
				unsigned int texel[4];
				int block_row;
				x=i%32;
				y=i/32;
				u = u0 + (matrix->A * x + matrix->C * y) / 4;
				v = v0 + (matrix->B * x + matrix->D * y) / 4;
				block_row = tex_width/4+(((tex_width&0x3)==0)?0:1);
				if((u+32<=0)||(u/16>tex_width-1)||(v+32<=0)||(v/16>tex_height-1))
				{
					//for(int j=0;j<4;j++)
					//{
					//	texel[j]=0;
					//}
					tile->ColorBuffer[i].r=0;
					tile->ColorBuffer[i].g=0;
					tile->ColorBuffer[i].b=0;
					tile->ColorBuffer[i].m=0;
					tile->ColorBuffer[i].a=0;
				}
				
				else
				{
					xy_uv(u,v,&u_u[0],&v_v[0],&u_u[1],&v_v[1],&u_u[2],&v_v[2],&u_u[3],&v_v[3]);
					inter_para(u,v,&u_para,&v_para);
					if(u_u[0]<0)
					{
						u_u[0]=u_u[3];
						u_u[2]=u_u[3];
					}
					if(v_v[0]<0)
					{
						v_v[0]=v_v[3];
						v_v[1]=v_v[3];
					}
					if(u_u[1]>tex_width-1)
					{
						u_u[1]=u_u[0];
						u_u[3]=u_u[0];
					}
					if(v_v[3]>tex_height-1)
					{
						v_v[2]=v_v[0];
						v_v[3]=v_v[0];
					}
					for(int j=0;j<4;j++)
					{

						U64 block_addr;
						U16 in_block_addr;
						block_addr=block_row*(v_v[j]/4)+u_u[j]/4;
						//block_addr=MUL(block_row,(v_v[j]/4))+u_u[j]/4;
						in_block_addr=(u_u[j]&0x3)+((v_v[j]&0x3)<<2);
						ahmi::cache(block_addr,in_block_addr,texture,&texel[j],TexType,mask_alpha);
					}
					//tile->ColorBuffer[i].r=((16-u_para)*(16-v_para)*((texel[0]&0x7C00)>>10)+(u_para)*(16-v_para)*((texel[1]&0x7C00)>>10)+(16-u_para)*(v_para)*((texel[2]&0x7C00)>>10)+(u_para)*(v_para)*((texel[0]&0x7C00)>>10))/256;
					//tile->ColorBuffer[i].g=((16-u_para)*(16-v_para)*((texel[0]&0x3E0)>>5)+(u_para)*(16-v_para)*((texel[1]&0x3E0)>>5)+(16-u_para)*(v_para)*((texel[2]&0x3E0)>>5)+(u_para)*(v_para)*((texel[0]&0x3E0)>>5))/256;
					//tile->ColorBuffer[i].b=((16-u_para)*(16-v_para)*((texel[0]&0x1F))+(u_para)*(16-v_para)*((texel[1]&0x1F))+(16-u_para)*(v_para)*((texel[2]&0x1F))+(u_para)*(v_para)*((texel[0]&0x1F)))/256;
					tile->ColorBuffer[i].r=(texel[0]&0x7C00)>>10;
					tile->ColorBuffer[i].g=(texel[0]&0x3E0)>>5;
					tile->ColorBuffer[i].b=texel[0]&0x1F;
					//tile->ColorBuffer[i].r=(MUL(MUL((16-u_para),(16-v_para)),((texel[0]&0x7C00)>>10))+MUL(MUL((u_para),(16-v_para)),((texel[1]&0x7C00)>>10))+MUL(MUL((16-u_para),(v_para)),((texel[2]&0x7C00)>>10))+MUL((u_para)*(v_para),((texel[0]&0x7C00)>>10)))/256;
					//tile->ColorBuffer[i].g=(MUL((16-u_para)*(16-v_para),((texel[0]&0x3E0)>>5))+MUL((u_para)*(16-v_para),((texel[1]&0x3E0)>>5))+MUL((16-u_para)*(v_para),((texel[2]&0x3E0)>>5))+MUL((u_para)*(v_para),((texel[0]&0x3E0)>>5)))/256;
					//tile->ColorBuffer[i].b=(MUL((16-u_para)*(16-v_para),((texel[0]&0x1F)))+MUL((u_para)*(16-v_para),((texel[1]&0x1F)))+MUL((16-u_para)*(v_para),((texel[2]&0x1F)))+MUL((u_para)*(v_para),((texel[0]&0x1F))))/256;
					//tile->ColorBuffer[i].m=((texel[0]&0x8000)==0x8000)?1:0;
					tile->ColorBuffer[i].m=1;
					tile->ColorBuffer[i].a=(texel[0]&0x1F0000)>>16;
					//tile->ColorBuffer[i].a=((16-u_para)*(16-v_para)*((texel[0]&0x1F0000)>>16)+(u_para)*(16-v_para)*((texel[1]&0x1F0000)>>16)+(16-u_para)*(v_para)*((texel[2]&0x1F0000)>>16)+(u_para)*(v_para)*((texel[0]&0x1F0000)>>16))/256;
					//tile->ColorBuffer[i].r =(texel[0]&0x7C00)>>10;
					//tile->ColorBuffer[i].g =(texel[0]&0x3E0)>>5;
					//tile->ColorBuffer[i].b =texel[0]&0x1F;
					//tile->ColorBuffer[i].m =((texel[0]&0x8000)==0x8000)?1:0;
				}
				tile->color_done=1;
			}
	break;
	case(2):
			for(int i = 0;i < 1024;i++)
			{
				short u,v;
				short u_u[4];
				short v_v[4];
				unsigned short u_para,v_para;
				U8 x,y;
				unsigned int alpha[4];
				x=i%32;
				y=i/32;
				u = u0 + (matrix->A * x + matrix->C * y) / 4;
				v = v0 + (matrix->B * x + matrix->D * y) / 4;
				int xx = 0;
				if((u+48<=0)||(u/16>tex_width-1)||(v+48<=0)||(v/16>tex_height-1))
				{
					tile->AlphaBuffer[i]=0;
				}
				else
				{
					xy_uv(u,v,&u_u[0],&v_v[0],&u_u[1],&v_v[1],&u_u[2],&v_v[2],&u_u[3],&v_v[3]);
					inter_para(u,v,&u_para,&v_para);
					for(int j=0;j<4;j++)
					{
						U64 block_addr;
						U16 in_block_addr;
						if((u_u[j]<0)||(u_u[j]>tex_width-1)||(v_v[j]<0)||(v_v[j]>tex_height-1))
						{alpha[j]=0;}
						else
						{
							//block_addr=(u/16+(u&0x8)>>3+(v/16+(v&0x8)>>3)*tex_width)/8;
							//in_block_addr=(u/16+(u&0x8)>>3+(v/16+(v&0x8)>>3)*tex_width)%8;
							if (mask_alpha)
							{
								block_addr = (u_u[j] + v_v[j] * tex_width) / 8;
								in_block_addr = (u_u[j] + v_v[j] * tex_width) % 8;
							}
							else
							{
								block_addr = (u_u[j] + v_v[j] * tex_width) / 64;
								in_block_addr = (u_u[j] + v_v[j] * tex_width) % 64;
							}
							ahmi::cache(block_addr,in_block_addr,texture,&alpha[j],TexType,mask_alpha);
						}
					}
					tile->AlphaBuffer[i]=((16-u_para)*(16-v_para)*((alpha[0]&0x1F))+(u_para)*(16-v_para)*((alpha[1]&0x1F))+(16-u_para)*(v_para)*((alpha[2]&0x1F))+(u_para)*(v_para)*((alpha[3]&0x1F)))/256;
					//tile->AlphaBuffer[i]=(MUL(MUL((16-u_para),(16-v_para)),(alpha[0]&0x1F))+MUL(MUL((u_para),(16-v_para)),(alpha[0]&0x1F))+MUL(MUL((16-u_para),(v_para)),(alpha[0]&0x1F))+MUL((u_para)*(v_para),(alpha[0]&0x1F)))/256;
				 }

			}
	break;
	case(3):
			for(int i = 0;i < 1024;i++)
				{
					mask_usage = ((texture_ctrl & 0x1) == 1) ? 1 : 0;
					tile->mask_usage=mask_usage;
					tile->ColorBuffer[i].r=(InitColor&0x7C00)>>10;
					tile->ColorBuffer[i].g=(InitColor&0x3E0)>>5;
					tile->ColorBuffer[i].b=InitColor&0x1F;
					tile->ColorBuffer[i].a=31;
					tile->ColorBuffer[i].m=1;
				}
			tile->color_done=1;
	break;
	default:
	break;
	}
}



void ahmi::Write_Frame(FinalTile *finaltile,Color16 * FrameBuffer)
{
   Color16 i=0,j=0;
   int address;
   	for (j=0;j<TileSize;j++)
   		for (i=0;i<TileSize;i++)
		{
			address=((int)(*finaltile).y/16+j)*1024+(*finaltile).x/16+i;
			*(FrameBuffer+address)=(Color16)(((*finaltile).TileBuffer[j*32+i].r)<<10)&0x7C00 | (((*finaltile).TileBuffer[j*32+i].g)<<5)&0x03E0 | (((*finaltile).TileBuffer[j*32+i].b))&0x001F;
		}


}

void ahmi::DrawFrame(TileInfo* tileinfo,ROMInfo* rominfo,Color16* FrameBuffer)
{
	Texture*  texture = new Texture;
	FinalTile* theFinalTile = new FinalTile;
	//U64 matrix;
	Matrix* cur_matrix=new Matrix;
	Tile* out =new Tile;
	int tile_num = 0;
	for(tile_num = 0;tile_num < 768;tile_num ++)
	{
		tile_x=(tile_num%32)*32*16;
		tile_y=(int)(tile_num/32)*32*16;
		if((tile_x < screen_width * 16) && (tile_y < screen_height * 16))
		{
			InitFinalTile(theFinalTile,tile_x,tile_y);
			InitTile(out,tile_x,tile_y);
			U16 addr=tileinfo->TileIndex[tile_num];
			U16 next_addr = tileinfo->TileIndex[tile_num+1],cur_addr;
			U8 SourceAddr;

			for(cur_addr = addr; cur_addr < next_addr; cur_addr ++)
			{
				SourceAddr=tileinfo->SourceAddr[cur_addr];
				U64	TextureIndex=tileinfo->TextureIndex[SourceAddr];
				U8 TexCtrl;
				U16 tex_width,tex_height,InitColor;
				unsigned int tex_num;
				unsigned int matrix_num;
				TexCtrl=((TextureIndex&0xC000000000000000)>>61)+((TextureIndex&0x80000000)>>31);
				if((TexCtrl&0x6)==6)
					{
						tex_num=0;//TextureIndex&0x7FFFFFFF;
						matrix_num=0;//(TextureIndex&0x3FC0000000000000)>>54;
						*texture=rominfo->tex[tex_num];
						*cur_matrix=tileinfo->matrix[matrix_num];
						tex_width=(TextureIndex&0x7FF00000000)>>32;
						tex_height=(TextureIndex&0x3FF80000000000)>>43;
						InitColor=TextureIndex&0x7FFF;
					}
				else
				{
					tex_num=TextureIndex&0x7FFFFFFF;
					matrix_num=(TextureIndex&0x3FC0000000000000)>>54;
					*texture=rominfo->tex[tex_num];
					*cur_matrix=tileinfo->matrix[matrix_num];
					tex_width=(TextureIndex&0x7FF00000000)>>32;
					tex_height=(TextureIndex&0x3FF80000000000)>>43;
					InitColor=0;
				}
				ahmi::TexRaster(out,cur_matrix,texture,tex_width,tex_height,TexCtrl,InitColor);
				if(out->color_done==1)
				ahmi::color_blending(theFinalTile,out);
			}
			//ahmi::color_blending(theFinalTile,out);
			ahmi::Write_Frame(theFinalTile,FrameBuffer);
		}
	}
	//Modify by darydou 2014/10/14
	//free(texture);
	//free(theFinalTile);
	//free(out);
	//free(cur_matrix);
	delete texture;
	delete theFinalTile;
	delete out;
	delete cur_matrix;
}

//void start()
//{
//	TileInfo* tile_info = new TileInfo;
//	ROMInfo* rom_info=new ROMInfo;
//	//Matrix* matrix_temp =new Matrix;
//	int i;
//	U64 PixelLength;
//	U64 temp1,temp2,temp;
//	char fuck[4];
//	char fuck2[1000];
//	PixelLength=1024*768;
//	////open the file
//	//std::ifstream infile("arrow.dds",std::ios::binary);
//	//std::ifstream infile1("test.dds",std::ios::binary);
//	//std::ifstream infile2("ALPHA1.data");
//	//if(infile == NULL)
//	//{
//	//	std :: cout << "unable to open the file TEX.data";
//	//	exit(0);
//	//}
//	for(i=0;i<768;i++)
//		tile_info->TileIndex[i]=3*i;
//	for(i=0;i<20480;i++)
//		{
//			if(i%3==1)
//				tile_info->SourceAddr[i]=2;
//			else if(i%3==2)
//				tile_info->SourceAddr[i]=1;
//			else
//				tile_info->SourceAddr[i]=0;
//			//if(i%2)
//			//	tile_info->SourceAddr[i]=1;
//			//else
//			//	tile_info->SourceAddr[i]=2;
//		}
//	tile_info->TextureIndex[0]=(((long long)768)<<43)+(((long long)1024)<<32)+(((long long)1)<<31)+1;
//	//tile_info->TextureIndex[1]=(((long long)3)<<62)+(((long long)1)<<31);
//	tile_info->TextureIndex[1]=(((long long)1)<<62)+(((long long)256)<<43)+(((long long)256)<<32)+(((long long)0)<<31)+0;
//	tile_info->TextureIndex[2]=(((long long)2)<<62)+(((long long)768)<<43)+(((long long)1024)<<32)+(((long long)1)<<31)+2;
//	//tile_info->TextureIndex[2]=(((long long)3)<<62)+0xffff+(((long long)1)<<31);
//	tile_info->Matrix[0].A=13;
//	tile_info->Matrix[0].B=7 ;
//	tile_info->Matrix[0].C=-7;
//	tile_info->Matrix[0].D=13; 
//	//tile_info->Matrix[0].A=16;
//	//tile_info->Matrix[0].B=0;
//	//tile_info->Matrix[0].C=0;
//	//tile_info->Matrix[0].D=16;
//	tile_info->Matrix[0].E=8;
//	tile_info->Matrix[0].F=8;
//	//read the file
//	//rom_info->tex[0].texel = new U64[PixelLength];
//	//rom_info->tex[1].texel = new U64[PixelLength];
//	//rom_info->tex[2].texel = new U64[PixelLength];
//	//for(i=0;i<49152;i++)
//	//i=0;
//	//int test;
//	//infile.read(fuck2,128*sizeof(char));
//	//while(!infile.eof())
//	//{
//	//
//	//	//infile >> std::hex >> temp1;
//	//	//infile >> std::hex >> temp2;		
//	//	infile.read(fuck,4*sizeof(char));
//	//	temp = ((U64)((U8)fuck[0])<<56)+((U64)((U8)fuck[1])<<48)+((U64)((U8)fuck[2])<<40)+((U64)((U8)fuck[3])<<32);
//	//	infile.read(fuck,4*sizeof(char));
//	//	temp = temp + ((U64)((U8)fuck[0])<<24)+((U64)((U8)fuck[1])<<16)+((U64)((U8)fuck[2])<<8)+((U64)((U8)fuck[3])<<0);
//	//	*((*rom_info).tex[0].texel+i)=temp;
//	//	i++;
//	//} 
//	//i=0;
//	//while(!infile2.eof())
//	//{
//	//
//	//	infile2 >> std::hex >> temp1;
//	//	infile2 >> std::hex >> temp2;
//	//	temp = (temp1 << 32) + temp2;
//	//	*((*rom_info).tex[2].texel+i)=temp;
//	//	i++;
//	//}
//	//i=0;
//	//infile1.read(fuck2,128*sizeof(char));
//	//while(!infile1.eof())
//	//{
//	//
//	//	//infile >> std::hex >> temp1;
//	//	//infile >> std::hex >> temp2;		
//	//	infile1.read(fuck,4*sizeof(char));
//	//	temp = ((U64)((U8)fuck[0])<<56)+((U64)((U8)fuck[1])<<48)+((U64)((U8)fuck[2])<<40)+((U64)((U8)fuck[3])<<32);
//	//	infile1.read(fuck,4*sizeof(char));
//	//	temp = temp + ((U64)((U8)fuck[0])<<24)+((U64)((U8)fuck[1])<<16)+((U64)((U8)fuck[2])<<8)+((U64)((U8)fuck[3])<<0);
//	//	*((*rom_info).tex[1].texel+i)=temp;
//	//	i++;
//	//}
//	unsigned long ticks1,ticks2;
//	//在你要测试的开头写上
//	ticks1 = GetTickCount();
//
//	READTEX readtex("arrow.dds");
//	(*rom_info).tex[0].texel = new U64[readtex.GetTexSize()];
//	readtex.GetTexPixel((*rom_info).tex[0].texel);
//	
//	READTEX readtex1("test.dds");
//	(*rom_info).tex[1].texel = new U64[readtex1.GetTexSize()];
//	readtex1.GetTexPixel((*rom_info).tex[1].texel);
//	
//	READTEX readtex2("ALPHA1.data");
//	(*rom_info).tex[2].texel = new U64[readtex2.GetTexSize()];
//	readtex2.GetTexPixel((*rom_info).tex[2].texel);
//
//	memset(FrameBuffer,0,sizeof(Color16)*1024 * 768 );
//	ahmi my_ahmi(1024,768);
//	my_ahmi.DrawFrame(tile_info,rom_info,FrameBuffer);
//	
//	//printf("mul count is %d",Mul_count);
//	//return 1;
//}

