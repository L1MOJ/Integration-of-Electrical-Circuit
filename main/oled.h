//////////////////////////////////////////////////////////////////////////////////	 
//嵌入式开发网
//mcudev.taobao.com
//  功能描述   : OLED 4接口演示例程(51系列)
//              说明: 
//              ----------------------------------------------------------------
//              GND    电源地
//              VCC  接5V或3.3v电源
//              D0   P1^0（SCL）
//              D1   P1^1（SDA）
//              RES  接P12
//              DC   接P13
//              CS   接P14               
//              ----------------------------------------------------------------
 
//******************************************************************************/
#include "reg52.h"
#ifndef __OLED_H
#define __OLED_H			  	 
//#include "sys.h"
//#include "stdlib.h"	  
#define  u8 unsigned char 
#define  u32 unsigned int 
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
#define OLED_MODE 0


sbit OLED_SCL=P3^6;//时钟 D0（SCLK)
sbit OLED_SDIN=P3^7;//D1（MOSI） 数据


#define OLED_CS_Clr()  OLED_CS=0
#define OLED_CS_Set()  OLED_CS=1

#define OLED_RST_Clr() OLED_RST=0
#define OLED_RST_Set() OLED_RST=1

#define OLED_DC_Clr() OLED_DC=0
#define OLED_DC_Set() OLED_DC=1

#define OLED_SCLK_Clr() OLED_SCL=0
#define OLED_SCLK_Set() OLED_SCL=1

#define OLED_SDIN_Clr() OLED_SDIN=0
#define OLED_SDIN_Set() OLED_SDIN=1





//OLED模式设置
//0:4线串行模式
//1:并行8080模式

#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED端口定义----------------  					   

void delay_ms(unsigned int ms);


//OLED控制用函数
//void Draw_RectangleF(unsigned char x0,unsigned char y0,unsigned char x,unsigned char y,unsigned int time);
void Draw_Rectangle(unsigned char x0,unsigned char y0,unsigned char x,unsigned char y,unsigned int time);
void OLED_WR_Byte(unsigned dat,unsigned cmd);  
//void OLED_Display_On(void);
//void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_DrawLine(int x1,int y1,int x2,int y2);
void OLED_Clear(void);

void Setpos(unsigned char x0,unsigned char y0);
//void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y, u8 *p,u8 Char_Size);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
//void OLED_ShowCHinese(u8 x,u8 y,u8 no);
//void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void Delay_50ms(unsigned int Del_50ms);
void Delay_1ms(unsigned int Del_1ms);
//void fill_picture(unsigned char fill_Data);

void Draw_Hline(unsigned char x0,unsigned char x,unsigned char y0,unsigned int time);
void Draw_Vline(unsigned char y0,unsigned char y,unsigned char x0,unsigned int time);
void Draw_VlineF(unsigned char y0,unsigned char y,unsigned char x0,unsigned int time);
void Clear(unsigned char y0,unsigned char y,unsigned char x0,unsigned int time);

//void IIC_Start();
//void IIC_Stop();
//void Write_IIC_Command(unsigned char IIC_Command);
//void Write_IIC_Data(unsigned char IIC_Data);
//void Write_IIC_Byte(unsigned char IIC_Byte);
//void IIC_Wait_Ack();
void Draw_dimond(unsigned char x0,unsigned char y0,unsigned char R);
void OLED_P6x8Str(unsigned char x, y,unsigned char ch[]);
void OLED_WrDat(unsigned char IIC_Data);
#endif  
	 



