#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
sbit K1=P3^7;
uchar i,sec,cishu;
bit anjian;
uchar LED[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};	
void Delay(uint ms)
{
uchar t;
while(ms--) for(t=0;t<120;t++);
}

void kaiguan()
{    
if(anjian==0)
{
cishu=(cishu+1)%3;
switch(cishu)
{
case 1: EA=1;ET0=1;TR0=1;break;
case 2: EA=0;ET0=0;TR0=0;break;
case 0: P0=0x3f;P2=0x3f;i=0;sec=0;
}
}
}

void main()
{
P0=0x3f;
P2=0x3f;
i=0;
sec=0;
cishu=0;
anjian=1;
TMOD=0x01;
TH0=(65536-50000)/256;
TL0=(65536-50000)%256;
while(1)
{
if(anjian!=K1)
{
Delay(10);
anjian=K1;
kaiguan();
}
}
}

void xianshi() interrupt 1
{
TH0=(65536-50000)/256;
TL0=(65536-50000)%256;
if(++i==20)
{
i=0;
sec++;
P0=LED[sec/10];
P2=LED[sec%10];
if(sec==60)
{
P0=0x3f;
P2=0x3f;
sec=0;
}
}
}
