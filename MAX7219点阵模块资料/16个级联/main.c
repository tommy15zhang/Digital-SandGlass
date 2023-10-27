//单片机晶振12M
#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint  unsigned int

#define count 16           //级联个数
//定义Max7219端口
sbit Max7219_pinCLK = P2^2;
sbit Max7219_pinCS  = P2^1;
sbit Max7219_pinDIN = P2^0;
uchar code disp1[16][8]=
{     
 {0x92,0xfe,0x10,0x3e,0x62,0x94,0x08,0x70},//4 岁
 {0xfe,0x20,0x20,0x3e,0x22,0x42,0x84,0x08},//3 万  
 {0xFE,0xBA,0x92,0xBA,0x92,0x9A,0xBA,0xFE},//2 国
 {0x10,0xFE,0x92,0x92,0xFE,0x10,0x10,0x10},//1 中

 {0x7C,0x42,0x42,0x42,0x42,0x42,0x42,0x7C},//4 D		   
 {0x3C,0x42,0x40,0x40,0x40,0x40,0x42,0x3C},//3 C		   
 {0x7C,0x42,0x42,0x7C,0x42,0x42,0x42,0x7C},//2 B
 {0x18,0x24,0x42,0x42,0x7E,0x42,0x42,0x42},//1 A

 {0x44,0x44,0x44,0x7C,0x44,0x44,0x44,0x44},//4 H
 {0x3C,0x40,0x40,0x40,0x40,0x44,0x44,0x3C},//3 G  
 {0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x40},//2 F
 {0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x7C},//1 E

 {0x08,0x18,0x28,0x48,0xFE,0x08,0x08,0x08},//4 4
 {0x7E,0x02,0x02,0x7E,0x02,0x02,0x02,0x7E},//3 3
 {0x7E,0x02,0x02,0x7E,0x40,0x40,0x40,0x7E},//2 2
 {0x08,0x18,0x28,0x08,0x08,0x08,0x08,0x3E},//1 1

};
void Delay_xms(uint x);
void Write_Max7219_byte(uchar DATA);//写入一字节
void Write_Max7219(uchar address1,uchar dat1,uchar address2,uchar dat2);
void Init_MAX7219(void);
                      // 锁存进相应寄存器


void main(void)
{
 uchar i,j;
 Delay_xms(50);
 Init_MAX7219();  
 while(1)
 {
  // for(i=1;i<9;i++)
 //   Write_Max7219(i,disp1[1][i-1],i,disp1[0][i-1]);

   for(i=1;i<9;i++)
   {
   
 //  Write_Max7219(i,disp1[1][i-1],i,disp1[0][i-1]);

    Max7219_pinCS=0;
    for(j=0;j<count;j++)
    {
        Write_Max7219_byte(i);           //写入地址，即数码管编号
        Write_Max7219_byte(disp1[count-1-j][i-1]);              //写入数据，即数码管显示数字 
  	      _nop_();
     }
     Max7219_pinCS=1;    
 
   }
   Delay_xms(1000);
  
 } 
}
void Init_MAX7219(void)
{ 
/*   Write_Max7219(0x09, 0x00,0x09, 0x00);       //译码方式：BCD码
  Write_Max7219(0x0a, 0x03,0x0a, 0x03);       //亮度 
  Write_Max7219(0x0b, 0x07,0x0b, 0x07);       //扫描界限；8个数码管显示
  Write_Max7219(0x0c, 0x01,0x0c, 0x01);       //掉电模式：0，普通模式：1
  Write_Max7219(0x0f, 0x00,0x0f, 0x00);       //显示测试：1；测试结束，正常显示：0
  */
uchar  i;
  Max7219_pinCS=0;
  for(i=0;i<count;i++)
  {
    Write_Max7219_byte(0x09); //译码方式：BCD码       
    Write_Max7219_byte(0x00);    
  }
  Max7219_pinCS=1;
  _nop_();
  Max7219_pinCS=0;
  for(i=0;i<count;i++)
  {
    Write_Max7219_byte(0x0a); //亮度    
    Write_Max7219_byte(0x03);    
  }
  Max7219_pinCS=1;
 _nop_();
   Max7219_pinCS=0;
  for(i=0;i<count;i++)
  {
    Write_Max7219_byte(0x0b); // //扫描界限；8个数码管显示  
    Write_Max7219_byte(0x07);    
  }
  Max7219_pinCS=1;
  _nop_();
  Max7219_pinCS=0;
  for(i=0;i<count;i++)
  {
    Write_Max7219_byte(0x0c); //   //掉电模式：0，普通模式：1
    Write_Max7219_byte(0x01);    
  }
  Max7219_pinCS=1;
  Max7219_pinCS=0;
  for(i=0;i<count;i++)
  {
    Write_Max7219_byte(0x0f); //显示测试：1；测试结束，正常显示：0
    Write_Max7219_byte(0x00);    
  }
  Max7219_pinCS=1;
  _nop_();
}
void Write_Max7219(uchar address1,uchar dat1,uchar address2,uchar dat2)
{ 
     uchar i;
     Max7219_pinCS=0;
     Write_Max7219_byte(address1);           //写入地址，即数码管编号
     Write_Max7219_byte(dat1);              //写入数据，即数码管显示数字 
     Write_Max7219_byte(address2);           //写入地址，即数码管编号
     Write_Max7219_byte(dat2);      //写入数据，即数码管显示数字 
	      _nop_();
     
     Max7219_pinCS=1;                        
}
//--------------------------------------------
//功能：向MAX7219(U3)写入字节
//入口参数：DATA 
//出口参数：无
//说明：
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
