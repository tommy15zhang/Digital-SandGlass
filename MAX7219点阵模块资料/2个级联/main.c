//��Ƭ������12M
//��ʾ�й�
#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint  unsigned int
//����Max7219�˿�
sbit Max7219_pinCLK = P2^2;
sbit Max7219_pinCS  = P2^1;
sbit Max7219_pinDIN = P2^0;
uchar code disp1[2][8]=
{     
  {0x10,0xFE,0x92,0x92,0xFE,0x10,0x10,0x10},//��
  {0xFE,0xBA,0x92,0xBA,0x92,0x9A,0xBA,0xFE},//��
};
void Delay_xms(uint x);
void Write_Max7219_byte(uchar DATA);//д��һ�ֽ�
void Write_Max7219(uchar address1,uchar dat1,uchar address2,uchar dat2);
void Init_MAX7219(void);
                      // �������Ӧ�Ĵ���


void main(void)
{
 uchar i,j;
 Delay_xms(50);
 Init_MAX7219();  
 while(1)
 {

   for(i=1;i<9;i++)
   
   Write_Max7219(i,disp1[1][i-1],i,disp1[0][i-1]);


   Delay_xms(1000);
  
 } 
}
void Init_MAX7219(void)
{
  Write_Max7219(0x09, 0x00,0x09, 0x00);       //���뷽ʽ��BCD��
  Write_Max7219(0x0a, 0x03,0x0a, 0x03);       //���� 
  Write_Max7219(0x0b, 0x07,0x0b, 0x07);       //ɨ����ޣ�8���������ʾ
  Write_Max7219(0x0c, 0x01,0x0c, 0x01);       //����ģʽ��0����ͨģʽ��1
  Write_Max7219(0x0f, 0x00,0x0f, 0x00);       //��ʾ���ԣ�1�����Խ�����������ʾ��0
}
//-------------------------------------------
//���ܣ���MAX7219д������
//��ڲ�����address��dat
//���ڲ�������
//˵����
void Write_Max7219(uchar address1,uchar dat1,uchar address2,uchar dat2)
{ 
     uchar i;
     Max7219_pinCS=0;
     Write_Max7219_byte(address1);           //д���ַ��������ܱ��
     Write_Max7219_byte(dat1);              //д�����ݣ����������ʾ���� 
     Write_Max7219_byte(address2);           //д���ַ��������ܱ��
     Write_Max7219_byte(dat2);      //д�����ݣ����������ʾ���� 
	      _nop_();
     
     Max7219_pinCS=1;                        
}

//--------------------------------------------
//���ܣ���MAX7219(U3)д���ֽ�
//��ڲ�����DATA 
//���ڲ�������
//˵����
void Write_Max7219_byte(uchar DATA)         
{
    	uchar i;    
	    for(i=8;i>=1;i--)
          {		  
            Max7219_pinCLK=0;
            Max7219_pinDIN=DATA&0x80;
            DATA=DATA<<1;
            Max7219_pinCLK=1;
           }                                 
}
void Delay_xms(uint x)
{
 uint i,j;
 for(i=0;i<x;i++)
  for(j=0;j<112;j++);
}
