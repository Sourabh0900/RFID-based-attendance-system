#include <LPC21xx.H>
#include "header.h"

void lcd_data(unsigned char data)
{
unsigned int temp;
IOCLR1|=0x00FE0000;
temp=(data&0xf0)<<16;
IOSET1=temp;

IOSET1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;

IOCLR1|=0x00fe0000;
temp=(data&0x0f)<<20;
IOSET1=temp;

IOSET1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;
}

void lcd_cmd(unsigned char cmd)
{
unsigned int temp;
IOCLR1|=0x00fe0000;
temp=(cmd&0xf0)<<16;
IOSET1=temp;

IOCLR1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;

IOCLR1|=0x00fe0000;
temp=(cmd&0x0f)<<20;
IOSET1=temp;

IOCLR1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;
}

void lcd_init()
{
IODIR1|=0x00fe0000;
PINSEL2=0;
lcd_cmd(0x02);
lcd_cmd(0x03);
lcd_cmd(0x28);
lcd_cmd(0x0E);
lcd_cmd(0x01);

}

void lcd_string(char *ptr)
{
while(*ptr)
{
lcd_data(*ptr);
ptr++;
}
}

void lcd_integer(int n)
{
char a[10];
int i;

	if(n==0)
	{
	lcd_data('0');
	return;
	}
	if(n<0)
	{
	lcd_data('-');
	n=-n;
	}
	i=0;
	while(n>0)
		{
		a[i]=n%10;
		n=n/10;
		i++;
		}
		for(i=i-1;i>=0;i--)
		{	
		lcd_data(a[i]+48);
		}
	}
void lcd_float(float f)
{
int n=f;
	lcd_integer(n);
	n=(f-n)*1000;
	lcd_data('.');
	lcd_integer(n);
}

unsigned char b[]={0x00,0x0A,0x1f,0x1f,0x1f,0x0e,0x04};

void cgram_init1(void)
{														   
	 int i;
	lcd_cmd(0x40);
	for(i=0;i<=7;i++)
	{
	lcd_data(b[i]);
	}
}


	 
   