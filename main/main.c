#include "reg52.h"
#include <math.h>
#include "intrins.h"
#include "stdlib.h"
#include "stdio.h"
//#include "bmp.h"

#include "oled.h"
#include "LCD1602.h"
#include "90614.h"
bit FLAG1=0;
sbit button1 = P2^2;						//按下测温
sbit button2 = P0^7;            //模式选择  O表面 B体温
sbit button3 = P2^3;						//报警温度
sbit button4 = P2^4;						//选择时间1-12
sbit YellowLed = P2^0;
sbit WARN = P2^1;




double BT;  //温度
unsigned int temp[12][2]={0},pass,WARNING1=33;
unsigned char i;
//unsigned char	btemp[5];

void UART_init()    //
{
      TMOD = 0x20;
      TH1 = 0xfd;
      TL1 = 0xfd;  //波特率9600
      SM0 = 0;  
      SM1 = 1;   // 串口工作方式1 10位异步
      REN = 1;  //串口允许接收
      TR1 = 1;
      EA = 1;
      ES =1 ;  //串口中断
}

void Delay(unsigned int xms)
{
	unsigned char i, j;
	while(xms--)
	{
		i = 2;
		j = 139;
		do
		{
			while (--j);
		} while (--i);
	}
}

void Warning()
{	
	YellowLed=1;
	for(i=0;i<=100;i++)
	{
		WARN = 0;
		Delay(1);
		WARN = 1;
	}
}

void main()
{
	unsigned char mode=1,time=0;											//

	int a,b;
	 UART_init();  //波特率9600
	//unsigned char l,n,num,lasty;
	//unsigned char a=0,b=0,c=127,d=63,e=0,f=0,g=0,h,j,k;
	WARN=0;
	LCD_Init();
	OLED_Init();
	OLED_Clear();
	LCD_ShowString(0,0,"WAITING");
	LCD_ShowString(2,4,"Hello L1MOJ");
	OLED_ShowString(20,50,"Hello L1MOJ",8);
	Delay_50ms(20);



	Delay_50ms(10);
	OLED_Clear();																					//初始化
	
	Draw_dimond(43,30,20);
	OLED_DrawLine(43,10,93,21);
	Delay_50ms(10);
	OLED_DrawLine(43,50,93,39);
	Draw_Hline(65,85,30,30);
	Draw_dimond(93,30,10);
	Delay_50ms(10);
  OLED_ShowString(20,50,"Activated!",8);
	//Draw_Rectangle(1,1,126,62,5);
	Delay_50ms(20);	 																			//初始化成功
	OLED_Clear();		
	LCD_Init();										//LCD清屏，显示月日 用户USER１　时间０－12　　默认USER０　０点

	while(1)
	{
	  WARN=0;
		if(button2==0)													//两个模式选择
		{
			mode++;
			if(mode==3)
				mode=1;
		}
		
		if(button3==0)													//报警温度
		{
			WARNING1++;
			if(WARNING1>36)
				WARNING1=33;
		}
		
		if(button4==0)													//测温时间
		{
			time++;
			if(time>11)
				time=0;
		}
		BT = Read_ObjectTemp();
	  LCD_ShowString(1,7,"7.6 ");
	  LCD_ShowString(2,1,"USER");
	  LCD_ShowNum(2,5,0,1);
	  LCD_ShowNum(1,15,time,2);   
		LCD_ShowNum(2,15,WARNING1,2); 
		if(mode==1)
		{	
			LCD_ShowString(1,1,"SURF");
		}
		if(mode==2)
		{
			BT = 0.2676*BT+2745;
			LCD_ShowString(1,1,"BODY");
		}
		
		

	/*	a = BT/1000;
		btemp[0]=a+'0';
		b=(BT-1000*a)/100;
		btemp[1]=b+'0';
		c=(BT-1000*a-100*b)/10;
		btemp[2]='.';
		btemp[3]=c+'0';
		d=BT-1000*a-100*b-10*c;
		btemp[4]=d+'0';*/																		//ObjectT--string
		
		a = BT/100;
		b = BT-100*a;

		LCD_ShowNum(2,7,a,2);															//温度显示
		LCD_ShowNum(2,10,b,2);
		LCD_ShowChar(2,9,'.');
		Delay_50ms(10);
	
		//LCD_ShowString(2,7,btemp);
		while(button1==0)                                 //按下测温
		{	
			temp[time][0] = a;
			temp[time][1] = b;

			//LCD_ShowString(2,7,"!!!!!");
				if(a>=WARNING1)
			{
				Warning();
				LCD_ShowString(2,7,"!!!!!");
				Delay_50ms(10);
			}
		}
			                                //按钮按下测温 保存该温度一段时间，在oled记录
		YellowLed=0;
		LCD_ShowChar(2,12,'C');
		//for(i=1;i<=12;i++)
		//{
		OLED_ShowNum(0,0,temp[0][0],2,16);										//OLED显示
		OLED_ShowChar(16,0,'.',16);
		OLED_ShowNum(18,0,temp[0][1],2,16);

		OLED_ShowNum(40,0,temp[1][0],2,16);
		OLED_ShowChar(56,0,'.',16);
		OLED_ShowNum(58,0,temp[1][1],2,16);		
		
		OLED_ShowNum(80,0,temp[2][0],2,16);
		OLED_ShowChar(96,0,'.',16);
		OLED_ShowNum(98,0,temp[2][1],2,16);	
		
		OLED_ShowNum(0,2,temp[3][0],2,16);
		OLED_ShowChar(16,2,'.',16);
		OLED_ShowNum(18,2,temp[3][1],2,16);	

		OLED_ShowNum(40,2,temp[4][0],2,16);
		OLED_ShowChar(56,2,'.',16);
		OLED_ShowNum(58,2,temp[4][1],2,16);		
		
		OLED_ShowNum(80,2,temp[5][0],2,16);
		OLED_ShowChar(96,2,'.',16);
		OLED_ShowNum(98,2,temp[5][1],2,16);	
		
		OLED_ShowNum(0,4,temp[6][0],2,16); 												
		OLED_ShowChar(16,4,'.',16);
		OLED_ShowNum(18,4,temp[6][1],2,16);
		
		OLED_ShowNum(40,4,temp[7][0],2,16);
		OLED_ShowChar(56,4,'.',16);
		OLED_ShowNum(58,4,temp[7][1],2,16);		
		
		OLED_ShowNum(80,4,temp[8][0],2,16);
		OLED_ShowChar(96,4,'.',16);
		OLED_ShowNum(98,4,temp[8][1],2,16);	
		
		OLED_ShowNum(0,6,temp[9][0],2,16);
		OLED_ShowChar(16,6,'.',16);
		OLED_ShowNum(18,6,temp[9][1],2,16);	

		OLED_ShowNum(40,6,temp[10][0],2,16);
		OLED_ShowChar(56,6,'.',16);
		OLED_ShowNum(58,6,temp[10][1],2,16);		
		
		OLED_ShowNum(80,6,temp[11][0],2,16);
		OLED_ShowChar(96,6,'.',16);
		OLED_ShowNum(98,6,temp[11][1],2,16);	
	}
}

void UART_INTERRUPT() interrupt 4																		//中断，蓝牙传输
{        
              pass = SBUF;
              RI = 0;   
							if(pass==0)
							{
								SBUF = temp[0][0];
								while(!TI);
								TI = 0;   
								SBUF = temp[0][1];
								while(!TI);
								TI = 0;   
							}
							else if(pass==1)
							{
								SBUF = temp[1][0];
								while(!TI);
								TI = 0;   
								SBUF = temp[1][1];
								while(!TI);
								TI = 0; 
							}
							else if(pass==2)
							{
								SBUF = temp[2][0];
								while(!TI);
								TI = 0;   
								SBUF = temp[2][1];
								while(!TI);
								TI = 0; 
							}
							else if(pass==3)
							{
								SBUF = temp[3][0];
								while(!TI);
								TI = 0;   
								SBUF = temp[3][1];
								while(!TI);
								TI = 0; 
							}
							else if(pass==4)
							{
								SBUF = temp[4][0];
								while(!TI);
								TI = 0;   
								SBUF = temp[4][1];
								while(!TI);
								TI = 0; 
							}
							else if(pass==5)
							{
								SBUF = temp[5][0];
								while(!TI);
								TI = 0;   
								SBUF = temp[5][1];
								while(!TI);
								TI = 0; 
							}
							else if(pass==6)
							{
								SBUF = temp[6][0];
								while(!TI);
								TI = 0;   
								SBUF = temp[6][1];
								while(!TI);
								TI = 0; 
							}
							else if(pass==7)
							{
								SBUF = temp[7][0];
								while(!TI);
								TI = 0;   
								SBUF = temp[7][1];
								while(!TI);
								TI = 0; 
							}
							else if(pass==8)
							{
								SBUF = temp[8][0];
								while(!TI);
								TI = 0;   
								SBUF = temp[8][1];
								while(!TI);
								TI = 0; 
							}
							else if(pass==9)
							{
								SBUF = temp[9][0];
								while(!TI);
								TI = 0;   
								SBUF = temp[9][1];
								while(!TI);
								TI = 0; 
							}
							else if(pass==10)
							{
								SBUF = temp[10][0];
								while(!TI);
								TI = 0;   
								SBUF = temp[10][1];
								while(!TI);
								TI = 0; 
							}
							else if(pass==11)
							{
								SBUF = temp[11][0];
								while(!TI);
								TI = 0;   
								SBUF = temp[11][1];
								while(!TI);
								TI = 0; 
							}							
							else
							{
							SBUF = pass;    //手机和蓝牙模块通讯时，我们可以打开电脑串口调试工具查看我们的发送值）
              while(!TI);
              TI = 0;  
							}
							}


