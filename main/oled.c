#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"  
 

/**********************************************
//IIC Start
**********************************************/
void IIC_Start()
{

	OLED_SCLK_Set() ;
	OLED_SDIN_Set();
	OLED_SDIN_Clr();
	OLED_SCLK_Clr();
}

/**********************************************
//IIC Stop
**********************************************/
void IIC_Stop()
{
	OLED_SCLK_Set() ;
//	OLED_SCLK_Clr();
	OLED_SDIN_Clr();
	OLED_SDIN_Set();
	
}

void IIC_Wait_Ack()
{

	//GPIOB->CRH &= 0XFFF0FFFF;	//设置PB12为上拉输入模式
	//GPIOB->CRH |= 0x00080000;
//	OLED_SDA = 1;
//	delay_us(1);
	//OLED_SCL = 1;
	//delay_us(50000);
/*	while(1)
	{
		if(!OLED_SDA)				//判断是否接收到OLED 应答信号
		{
			//GPIOB->CRH &= 0XFFF0FFFF;	//设置PB12为通用推免输出模式
			//GPIOB->CRH |= 0x00030000;
			return;
		}
	}
*/
	OLED_SCLK_Set() ;
	OLED_SCLK_Clr();
}
/**********************************************
// IIC Write byte
**********************************************/

void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	unsigned char m,da;
	da=IIC_Byte;
	OLED_SCLK_Clr();
	for(i=0;i<8;i++)		
	{
			m=da;
		//	OLED_SCLK_Clr();
		m=m&0x80;
		if(m==0x80)
		{OLED_SDIN_Set();}
		else OLED_SDIN_Clr();
			da=da<<1;
		OLED_SCLK_Set();
		OLED_SCLK_Clr();
		}


}
/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
   IIC_Start();
   Write_IIC_Byte(0x78);            //Slave address,SA0=0
	IIC_Wait_Ack();	
   Write_IIC_Byte(0x00);			//write command
	IIC_Wait_Ack();	
   Write_IIC_Byte(IIC_Command); 
	IIC_Wait_Ack();	
   IIC_Stop();
}
/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
   IIC_Start();
   Write_IIC_Byte(0x78);			//D/C#=0; R/W#=0
	IIC_Wait_Ack();	
   Write_IIC_Byte(0x40);			//write data
	IIC_Wait_Ack();	
   Write_IIC_Byte(IIC_Data);
	IIC_Wait_Ack();	
   IIC_Stop();
}
void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd)
			{

   Write_IIC_Data(dat);
   
		}
	else {
   Write_IIC_Command(dat);
		
	}
}


/********************************************
// fill_Picture
********************************************/
/*void fill_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<5;m++)
	{
		OLED_WR_Byte(0xb0+m,0);		//page0-page1
		OLED_WR_Byte(0x00,0);		//low column start address
		OLED_WR_Byte(0x10,0);		//high column start address
		for(n=0;n<64;n++)
			{
				OLED_WR_Byte(fill_Data,1);
			}
	}
}	*/

void Draw_Hline(unsigned char x0,unsigned char x,unsigned char y0,unsigned int time)
{	
	unsigned char y,mod,pos,i;
	if(y0%8==0){
		 y=y0/8;
		 pos = 0x01;
	}
	else{
		y = y0/8;
		mod = y0%8;
		switch(mod)
		{
			case 1:
			pos = 0x02;
			break;
			case 2:
			pos = 0x04;
			break;
			case 3:
			pos = 0x08;
			break;
			case 4:
			pos = 0x10;
			break;
			case 5:
			pos = 0x20;
			break;
			case 6:
			pos = 0x40;
			break;
			case 7:
			pos = 0x80;
			break;
			default:
			break;

		}
	}
	OLED_Set_Pos(x0,y);
	for(i=x0;i<x+1;i++)
	{
		Delay_1ms(time);
		OLED_WR_Byte(pos,1);	
	}

}

/*void Draw_Vline(unsigned char y0,unsigned char y,unsigned char x0,unsigned int time)
{	
	unsigned char y1,y2,pos,pos1,mod0,mod1,i;
		if(y0%8==0){
		 y1=y0/8;
		 pos = 0xff;
	}
	else{
		y1 = y0/8;
		mod0 = y0%8;
		switch(mod0)
		{
			case 1:
			pos = 0xfe;
			break;
			case 2:
			pos = 0xfc;
			break;
			case 3:
			pos = 0xf8;
			break;
			case 4:
			pos = 0x10;
			break;
			case 5:
			pos = 0xe0;
			break;
			case 6:
			pos = 0xc0;
			break;
			case 7:
			pos = 0x80;
			break;
			default:
			break;

		}
	}
	if(y%8==0){
		 y2=y/8;
		 pos1 = 0x01;
	}
	else{
		y2 = y/8;
		mod1 = y%8;
		switch(mod1)
		{
			case 1:
			pos1 = 0x03;
			break;
			case 2:
			pos1 = 0x07;
			break;
			case 3:
			pos1 = 0x0f;
			break;
			case 4:
			pos1 = 0x1f;
			break;
			case 5:
			pos1 = 0x3f;
			break;
			case 6:
			pos1 = 0x7f;
			break;
			case 7:
			pos1 = 0xff;
			break;
			default:
			break;

		}
	}
	OLED_Set_Pos(x0,y1);
	OLED_WR_Byte(pos,1);
	Delay_1ms(time);
	OLED_Set_Pos(x0,y1+1);
	for(i=y1+1;i<y2;i++)
	{
		Delay_1ms(time);
		OLED_Set_Pos(x0,i);
		OLED_WR_Byte(0xff,1);	
	} 
   	OLED_Set_Pos(x0,y2);
	Delay_1ms(time);
	OLED_WR_Byte(pos1,1);


}
/*void Clear(unsigned char y0,unsigned char y,unsigned char x0,unsigned int time)
{	
	unsigned char y1,y2,pos,pos1,mod0,mod1,i;
		if(y0%8==0){
		 y1=y0/8;
		 pos = 0x00;
	}
	else{
		y1 = y0/8;
		mod0 = y0%8;
		switch(mod0)
		{
			case 1:
			pos = 0xfe;
			break;
			case 2:
			pos = 0xfc;
			break;
			case 3:
			pos = 0xf8;
			break;
			case 4:
			pos = 0x10;
			break;
			case 5:
			pos = 0xe0;
			break;
			case 6:
			pos = 0xc0;
			break;
			case 7:
			pos = 0x80;
			break;
			default:
			break;

		}
	}
	if(y%8==0){
		 y2=y/8;
		 pos1 = 0x01;
	}
	else{
		y2 = y/8;
		mod1 = y%8;
		switch(mod1)
		{
			case 1:
			pos1 = 0x03;
			break;
			case 2:
			pos1 = 0x07;
			break;
			case 3:
			pos1 = 0x0f;
			break;
			case 4:
			pos1 = 0x1f;
			break;
			case 5:
			pos1 = 0x3f;
			break;
			case 6:
			pos1 = 0x7f;
			break;
			case 7:
			pos1 = 0xff;
			break;
			default:
			break;

		}
	}
	OLED_Set_Pos(x0,y1);
	OLED_WR_Byte(pos,1);
	Delay_1ms(time*8);
	OLED_Set_Pos(x0,y1+1);
	for(i=y1+1;i<y2;i++)
	{
		Delay_1ms(time*8);
		OLED_Set_Pos(x0,i);
		OLED_WR_Byte(0x00,1);	
	} 
   	OLED_Set_Pos(x0,y2);
	Delay_1ms(time*8);
	OLED_WR_Byte(pos1,1);


}
*/

/*void Draw_Rectangle(unsigned char x0,unsigned char y0,unsigned char x,unsigned char y,unsigned int time)
{
	 Draw_Hline(x0,x-1,y0,time);

	 Draw_Vline(y0,y,x,time*8);

	 Draw_Hline(x0+1,x-1,y,time);

	 Draw_VlineF(y0,y,x0,time*8);


}/*
void Draw_RectangleF(unsigned char x0,unsigned char y0,unsigned char x,unsigned char y,unsigned int time)
{
	 Draw_Hline(x0,x-1,y0,time);
	 Delay_50ms(10);
	 Draw_Vline(y0,y,x0,time);
	 Delay_50ms(10);
	 Draw_Hline(x0+1,x-1,y,time);
	 Delay_50ms(10);
	 Draw_VlineF(y0,y,x,time);
	 Delay_50ms(10);

}
*/
void Setpos(unsigned char x0,unsigned char y0)
{
	unsigned char y,mod,pos;
	if(y0%8==0){
		 y=y0/8;
		 pos = 0x01;
	}
	else{
		y = y0/8;
		mod = y0%8;
		switch(mod)
		{
			case 1:
			pos = 0x02;
			break;
			case 2:
			pos = 0x04;
			break;
			case 3:
			pos = 0x08;
			break;
			case 4:
			pos = 0x10;
			break;
			case 5:
			pos = 0x20;
			break;
			case 6:
			pos = 0x40;
			break;
			case 7:
			pos = 0x80;
			break;
			default:
			break;

		}
	}
	OLED_Set_Pos(x0,y);
	OLED_WR_Byte(pos,1);

}

void OLED_DrawLine(int x1,int y1,int x2,int y2)
{
    int dx,dy,e;
    dx=x2-x1; 
    dy=y2-y1;
    if(dx>=0)
    {
        if(dy >= 0) // dy>=0
        {
            if(dx>=dy) // 1/8 octant
            {
                e=dy-dx/2;
                while(x1<=x2)
                {
                    Setpos(x1,y1);
                    if(e>0){y1+=1;e-=dx;}   
                    x1+=1;
                    e+=dy;
                }
            }
            else        // 2/8 octant
            {
                e=dx-dy/2;
                while(y1<=y2)
                {
                    Setpos(x1,y1);
                    if(e>0){x1+=1;e-=dy;}   
                    y1+=1;
                    e+=dx;
                }
            }
        }
        else           // dy<0
        {
            dy=-dy;   // dy=abs(dy)
            if(dx>=dy) // 8/8 octant
            {
                e=dy-dx/2;
                while(x1<=x2)
                {
                    Setpos(x1,y1);
                    if(e>0){y1-=1;e-=dx;}   
                    x1+=1;
                    e+=dy;
                }
            }
            else        // 7/8 octant
            {
                e=dx-dy/2;
                while(y1>=y2)
                {
                    Setpos(x1,y1);
                    if(e>0){x1+=1;e-=dy;}   
                    y1-=1;
                    e+=dx;
                }
            }
        }   
    }
    else //dx<0
    {
        dx=-dx;     //dx=abs(dx)
        if(dy >= 0) // dy>=0
        {
            if(dx>=dy) // 4/8 octant
            {
                e=dy-dx/2;
                while(x1>=x2)
                {
                    Setpos(x1,y1);
                    if(e>0){y1+=1;e-=dx;}   
                    x1-=1;
                    e+=dy;
                }
            }
            else        // 3/8 octant
            {
                e=dx-dy/2;
                while(y1<=y2)
                {
                  Setpos(x1,y1);

                    if(e>0){x1-=1;e-=dy;}   
                    y1+=1;
                    e+=dx;
                }
            }
        }
        else           // dy<0
        {
            dy=-dy;   // dy=abs(dy)
            if(dx>=dy) // 5/8 octant
            {
                e=dy-dx/2;
                while(x1>=x2)
                {
                   Setpos(x1,y1);
                    if(e>0){y1-=1;e-=dx;}   
                    x1-=1;
                    e+=dy;
                }
            }
            else        // 6/8 octant
            {
                e=dx-dy/2;
                while(y1>=y2)
                {
                   Setpos(x1,y1);
                    if(e>0){x1-=1;e-=dy;}   
                    y1-=1;
                    e+=dx;
                }
            }
        }   
    }
}

void Draw_dimond(unsigned char x0,unsigned char y0,unsigned char R)
{
	unsigned char xi,yi,di;
	di = 0-(R>>1);
	xi = 0;
	yi = R;
	while(yi>=xi)
	{
		Setpos(x0+xi-1,y0+yi-1);
		Setpos(x0+yi-1,y0+xi-1);
		Setpos(x0-xi,y0+yi-1);
		Setpos(x0-yi,y0+xi-1);
		Setpos(x0-xi,y0-yi);
		Setpos(x0-yi,y0-xi);
		Setpos(x0+xi-1,y0-yi);
		Setpos(x0+yi-1,y0-xi);
		xi++;
		if(di<0)
		{
			di+=xi;

		}
		else {
			yi--;
			di+=xi-yi;
		}	
	}
}

/*void Draw_VlineF(unsigned char y0,unsigned char y,unsigned char x0,unsigned int time)
{	
	unsigned char y1,y2,pos,pos1,mod0,mod1,i;
		if(y0%8==0){
		 y1=y0/8;
		 pos = 0xff;
	}
	else{
		y1 = y0/8;
		mod0 = y0%8;
		switch(mod0)
		{
			case 1:
			pos = 0xfe;
			break;
			case 2:
			pos = 0xfc;
			break;
			case 3:
			pos = 0xf8;
			break;
			case 4:
			pos = 0x10;
			break;
			case 5:
			pos = 0xe0;
			break;
			case 6:
			pos = 0xc0;
			break;
			case 7:
			pos = 0x80;
			break;
			default:
			break;

		}
	}
	if(y%8==0){
		 y2=y/8;
		 pos1 = 0x01;
	}
	else{
		y2 = y/8;
		mod1 = y%8;
		switch(mod1)
		{
			case 1:
			pos1 = 0x03;
			break;
			case 2:
			pos1 = 0x07;
			break;
			case 3:
			pos1 = 0x0f;
			break;
			case 4:
			pos1 = 0x1f;
			break;
			case 5:
			pos1 = 0x3f;
			break;
			case 6:
			pos1 = 0x7f;
			break;
			case 7:
			pos1 = 0xff;
			break;
			default:
			break;

		}
	}
	OLED_Set_Pos(x0,y2);
	OLED_WR_Byte(pos1,1);
	Delay_1ms(time);
	OLED_Set_Pos(x0,y1+1);
	for(i=y2-1;i>y1;i--)
	{
		Delay_1ms(time);
		OLED_Set_Pos(x0,i);
		OLED_WR_Byte(0xff,1);	
	} 
   	OLED_Set_Pos(x0,y1);
	Delay_1ms(time);
	OLED_WR_Byte(pos,1);


}
*/


/***********************Delay****************************************/
void Delay_50ms(unsigned int Del_50ms)
{
	unsigned int m;
	for(;Del_50ms>0;Del_50ms--)
		for(m=6245;m>0;m--);
}

void Delay_1ms(unsigned int Del_1ms)
{
	unsigned char j;
	while(Del_1ms--)
	{	
		for(j=0;j<123;j++);
	}
}

//坐标设置
/*void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WrCmd(0xb0+y);
	OLED_WrCmd(((x&0xf0)>>4)|0x10);
	OLED_WrCmd((x&0x0f)|0x01);
}*/ 

void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD); 
}   	  
//开启OLED显示    
/*void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//关闭OLED显示     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	   */

void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //更新显示
}
/*void OLED_On(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte(1,OLED_DATA); 
	} //更新显示
}
//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示				 
//size:选择字体 16/12 */	   
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//得到偏移后的值			
		if(x>Max_Column-1){x=0;y=y+2;}
		if(Char_Size ==16)
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
			}
			else {	
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
				OLED_WR_Byte(F6x8[c][i],OLED_DATA);
				
			}
}
				  

void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],Char_Size);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);
	 		  
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
} 
			

//屏幕滑动
/*
void Scroll()
{	 	
	OLED_WR_Byte(0X2A,OLED_CMD);
	OLED_WR_Byte(0X00,OLED_CMD);
	OLED_WR_Byte(0X00,OLED_CMD);
	OLED_WR_Byte(0X02,OLED_CMD);
	OLED_WR_Byte(0X07,OLED_CMD);
	OLED_WR_Byte(0X2F,OLED_CMD);
} 		  /*
//显示汉字
void OLED_ShowCHinese(u8 x,u8 y,u8 no)
{      			    
	u8 t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
				adder+=1;
      }					
}	  */



//初始化SSD1306					    
void OLED_Init(void)
{ 	
 
	OLED_WR_Byte(0xAE,OLED_CMD);//--display off
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  
	OLED_WR_Byte(0xB0,OLED_CMD);//--set page address
	OLED_WR_Byte(0x81,OLED_CMD); // contract control
	OLED_WR_Byte(0xFF,OLED_CMD);//--128   
	OLED_WR_Byte(0xA1,OLED_CMD);//set segment remap 
	OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
	OLED_WR_Byte(0xC8,OLED_CMD);//Com scan direction
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
	OLED_WR_Byte(0x00,OLED_CMD);//
	
	OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
	OLED_WR_Byte(0x80,OLED_CMD);//
	
	OLED_WR_Byte(0xD8,OLED_CMD);//set area color mode off
	OLED_WR_Byte(0x05,OLED_CMD);//
	
	OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
	OLED_WR_Byte(0xF1,OLED_CMD);//
	
	OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
	OLED_WR_Byte(0x12,OLED_CMD);//
	
	OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
	OLED_WR_Byte(0x30,OLED_CMD);//
	
	OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
	OLED_WR_Byte(0x14,OLED_CMD);//
	
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
}  






