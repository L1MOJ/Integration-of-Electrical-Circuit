#ifndef __90614_H__
#define __90614_H__

void   start_bit();                 //MLX90614 ����ʼλ�ӳ��� 
void   stop_bit();                 //MLX90614 ������λ�ӳ��� 
unsigned char  rx_byte(void);              //MLX90614 �����ֽ��ӳ��� 
void   send_bit(void);             //MLX90614 ����λ�ӳ��� 
void   tx_byte(unsigned char dat_byte);     //MLX90614 �����ֽ��ӳ��� 
void   receive_bit(void);           //MLX90614 ����λ�ӳ��� 
double Read_AmbientTemp(void);             //�������¶����� 
double Read_ObjectTemp(void);             //�������¶����� 
void Temp_Init(void);							//��ʼ��
double TF_to_Tbody();              //����ת���£��¶�����

#endif