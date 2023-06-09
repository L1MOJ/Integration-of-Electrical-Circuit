#include <REGX52.H>
#include <intrins.h>
#include <math.h>
#include "delay.h"

sbit  SCL=P3^6;//时钟线 
sbit  SDA=P3^7;//数据线 
bdata unsigned char flag;//可位寻址数据 
sbit bit_out=flag^7; 
sbit bit_in=flag^0; 
unsigned char DataH,DataL,Pecreg;
#define  Nack_counter  10;



/*void Temp_Init(void)
{
	SCL=1;
	SDA=1;
	_nop_();  
	_nop_();
	_nop_();
	_nop_();  
	SCL=0;  
	delay(1000);  
	SCL=1;
}*/


void   start_bit(void) 
{    
	SDA=1;    
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();    
	SCL=1;    
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();   
	SDA=0;   
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();    
	SCL=0;    
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();

} 
//------------------------------ 
void   stop_bit(void) 
{
	SCL=0;  
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_(); 
	SDA=0;   
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	SCL=1;  
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	SDA=1; 
} 

//-----------发送一个位--------- 
void  send_bit(void) 
{   
	if(bit_out==0)
		SDA=0;
	else     
		SDA=1; 
	_nop_(); 
	SCL=1; 
	_nop_();
	_nop_();
	_nop_();
	_nop_(); 
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	SCL=0;
	_nop_();
	_nop_();
	_nop_();
	_nop_(); 
	_nop_();
	_nop_();
	_nop_();
	_nop_(); 
} 

//----------接收一个位----------
void receive_bit(void) 
{   
	SDA=1;
	bit_in=1;  
	SCL=1;  
	_nop_();
	_nop_();
	_nop_();
	_nop_();  
	_nop_();
	_nop_();
	_nop_();
	_nop_(); 
	bit_in=SDA;
	_nop_(); 
	SCL=0; 
	_nop_();
	_nop_();
	_nop_();
	_nop_(); 
	_nop_();
	_nop_();
	_nop_();
	_nop_(); 
} 

//---------发送一个字节---------
  
void  tx_byte(unsigned char dat_byte) 
{    
	char i,n,dat;   
	n=Nack_counter; 
TX_again:    
	dat=dat_byte;    
	for(i=0;i<8;i++)    
	{      
		if(dat&0x80)       
			bit_out=1;      
		else       
			bit_out=0;      
		send_bit();      
		dat=dat<<1;    
	}    
	receive_bit();    
	if(bit_in==1)    
	{     
		stop_bit();     
		if(n!=0)     
			{n--;goto Repeat;}     
		else     
			goto exit;    
	}    
	else     
		goto exit; 
Repeat:     
	start_bit();    
	goto TX_again; 
exit: 
	; 
} 


//----------接收一个字节-------- 
unsigned char rx_byte(void) 
{  
	unsigned char i,dat;   
	dat=0;  
	for(i=0;i<8;i++)   
	{   
		dat=dat<<1;     
		receive_bit(); 
		if(bit_in==1)      
			dat=dat+1;   
	} 
	send_bit();   
	return dat; 
} 


/*double Read_AmbientTemp(void) 
{  
	double temp;
	start_bit(); 
	tx_byte(0x00);  //Send SlaveAddress 
	tx_byte(0x06);  //Send Command   //------------  
	start_bit();   
	tx_byte(0x01); 
	bit_out=0;  
	DataL=rx_byte(); 
	bit_out=0;  
	DataH=rx_byte();  
	bit_out=1;  
	Pecreg=rx_byte(); 
	stop_bit(); 
	temp =100*((DataH*256+DataL)*0.02-273.15);
	//temp = (int)temp;
	//temp = ((float)((int)((temp+0.005)*100)))/100;          //保留两位小数
	return temp; 
}*/

double Read_ObjectTemp(void) 
{  
	double temp;
	start_bit(); 
	tx_byte(0x00);  //Send SlaveAddress 
	tx_byte(0x07);  //Send Command   //------------  
	start_bit();   
	tx_byte(0x01); 
	bit_out=0;  
	DataL=rx_byte(); 
	bit_out=0;  
	DataH=rx_byte();  
	bit_out=1;  
	Pecreg=rx_byte(); 
	stop_bit(); 
	temp =100*((DataH*256+DataL)*0.02-273.15);
	//temp = (int)temp;
	//temp=2*(DataH*256+DataL)-27315;
	//temp = 100*(temp-floor(temp));
	//temp = ((float)((int)((temp+0.005)*100)))/100; */         //保留两位小数
	
	return temp; 
}

/*double Read_BodyTemp(void)
{
	double temp;
	start_bit(); 
	tx_byte(0x00);  //Send SlaveAddress 
	tx_byte(0x07);  //Send Command   //------------  
	start_bit();   
	tx_byte(0x01); 
	bit_out=0;  
	DataL=rx_byte(); 
	bit_out=0;  
	DataH=rx_byte();  
	bit_out=1;  
	Pecreg=rx_byte(); 
	stop_bit(); 
	temp =0.2676*((DataH*256+DataL)*0.02-273.15)+2745;
	return temp;
}*/
