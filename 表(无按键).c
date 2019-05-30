#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int

uchar sec,min,hour;
uchar counter10ms0,counter10ms1; 
uchar counter05s0;
uchar Disbuff[8]={1,2,10,3,4,10,5,6};
uchar DisCode[12]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf,0xff}; 

void Delaynms(uint dly)
{
	uchar i;
	while(dly--)
		for(i=0;i<123;i++);
}

void Display(void)
{
	uchar i,n=0x01;
	for(i=0;i<8;i++)
	{
	 	P0=DisCode[Disbuff[i]];
		P2=n;
		Delaynms(1);
		n=n<<1;
		P0=0xff;
		P2=0x00;
	}
}


void TimeDataBin2Bcd()
{
	 Disbuff[0]=hour/10;
	 Disbuff[1]=hour%10;
	 Disbuff[3]=min/10;
	 Disbuff[4]=min%10;
	 Disbuff[6]=sec/10;
	 Disbuff[7]=sec%10;

}

void main(void)
{
	TMOD=0x11;
	TH0=(65536-10000)/256;
	TL0=(65536-10000)%256;
	TH1=(65536-10000)/256;
	TL1=(65536-10000)%256;
	ET0=1;ET1=1;
	EA=1;

	while(1)
	{
		TR0=1;
			TR1=0;
		TimeDataBin2Bcd();
		Display();
	}
}

void Timer0(void) interrupt 1
{
	TH0=(65536-10000)/256;
	TL0=(65536-10000)%256;
	counter10ms0++;
	if(counter10ms0==50)
	{
	 	counter10ms0=0;
		if(++counter05s0==2)
		{ 	
			counter05s0=0;
			sec++;
			if(sec==60)
			{
		 		sec=0;
				min++;
				if(min==60)
				{
			 		min=0;
					hour++;
					if(hour==24)hour=0;
				}
			}
		}
	}
}

void Timer1(void) interrupt 3
{
	TH1=(65536-10000)/256;
	TL1=(65536-10000)%256;
	counter10ms1++;
	if(counter10ms1==50)
	{
	 	counter10ms1=0;
	}		
}
