#include "reg52.h"
#include"intrins.h" 
#include <stdio.h>
#include <math.h>
#include <stdlib.h>



#include "LCD1602.h"
#include "delay.h"
#include "90614.h"

//sbit BUZZER = P2^1;


 
double BT,BT_z,BT_x,AT,AT_z,AT_x;  //ÎÂ¶È
bit FLAG1=0;

void main()
{

	LCD_Init();
	LCD_ShowString(1,1,"Ambient:");
	LCD_ShowString(2,1,"BOdy:");
	while(1)
	{
		BT = Read_ObjectTemp();
		AT = Read_AmbientTemp();
		BT_z = floor(BT);
		BT_x = (BT-BT_z)*100;
		AT_z = floor(AT);
		AT_x = (AT-AT_z)*100;
		LCD_ShowNum(1,9,BT_z,2);
		LCD_ShowNum(1,12,BT_x,2);
				
	}
	
	
	

}

 

