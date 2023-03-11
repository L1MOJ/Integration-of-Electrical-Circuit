#ifndef __90614_H__
#define __90614_H__

void   start_bit();                 //MLX90614 发起始位子程序 
void   stop_bit();                 //MLX90614 发结束位子程序 
unsigned char  rx_byte(void);              //MLX90614 接收字节子程序 
void   send_bit(void);             //MLX90614 发送位子程序 
void   tx_byte(unsigned char dat_byte);     //MLX90614 接收字节子程序 
void   receive_bit(void);           //MLX90614 接收位子程序 
double Read_AmbientTemp(void);             //读环境温度数据 
double Read_ObjectTemp(void);             //读物体温度数据 
void Temp_Init(void);							//初始化
double TF_to_Tbody();              //额温转体温，温度修正

#endif