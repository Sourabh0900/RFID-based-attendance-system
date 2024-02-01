#include "header20.h"
#include <LPC21xx.H>
#include<stdlib.h>

void uart0_init(u32 baud)
{

PINSEL0|=0x5;
U0LCR=0x83;
U0DLL=97;
U0DLM=0;
U0LCR=0x03;
}

void uart0_tx(u8 data)
{
U0THR=data;
while(THRE==0);
}

void uart0_tx_string(s8 *p)
{
while(*p)
{
U0THR=*p;	
while(THRE==0);
p++;
}
}

u8 uart0_rx(void)
{
while(RDR==0);
	return U0RBR;
}

 //////////////////////////REQUIRMENT FOR UART CALCULATOR///////////////////////////////////////
 void uart0_rx_string(char *p)
{
	s32 i=0;

	while(1)
	{	
		while(RDR==0);
		p[i]=U0RBR;	
		uart0_tx(p[i]);
		if(p[i]=='\r')
		{
	//	uart0_tx_string("\r\n");
		p[i]='\0';
		break;
		}																					  
		i++;
	}
}

void uart0_cal(char *p)
{
 s32 i=0,n1,n2,n3;
 u8 s[20],d[20];
 char ch;
 char *cp=p;
 while(*p)
 {
 	if(*p=='+'||*p=='-'||*p=='*'||*p=='/'||*p=='%')
	{	
	break;
	}
	s[i++]=*p;
	p++;
 }
 s[i]='\0';
 //uart0_tx_string(s);
 i=0;
 p++;
	while(*p)
	{
	d[i++]=*p;
	p++;
	}
	d[i]='\0';
//	uart0_tx_string("\r\n");
//	uart0_tx_string(d);

	while(*cp)
	{
		if(*cp=='+'||*cp=='-'||*cp=='*'||*cp=='/'||*cp=='%')
		{
		ch=*cp;
		break;
		}
		cp++;
	}
	//uart0_tx(ch);

	n1=atoi(s);
	n2=atoi(d);
	switch(ch)
	 {
	 	case '+' : n3=n1+n2; break;
	 	case '-' : n3=n1-n2; break;
	 	case '*' : n3=n1*n2; break;
	    case '/' : n3=n1/n2; break;
		case '%' : n3=n1%n2; break;
	}

	uart0_tx_string("\r\n res=");
	uart0_tx_integer(n3);
	uart0_tx_string("\r\n");

}




void uart0_tx_integer(int num)
{
int a[10],i;
if(num==0)
{
uart0_tx('0');
return;
}
if(num<0){
uart0_tx('-');
num=-num;
}
i=0;					 
while(num>0)
{
a[i]=num%10;
num=num/10;
i++;
}

for(i=i-1;i>=0;i--)
{
uart0_tx(a[i]+48);
}
}

//void uart0_tx_float(float num)
//{
//	s8 buf[10];
//	sprintf(buf,"%.1f",num);
//	uart0_tx_string(buf);
//}


void uart0_GSM(u8 *p)
{
	s32 i=0;
	u8 t; 
	while(1)
	{	
			while(RDR==0);
		t=U0RBR;	
		p[i]=t;
	//lcd_4bit_data(t);
	//	delay_ms(200);										
		if(p[i]=='\0')
		{
		p[i]=0;
		break;
		}																					  
		i++;
	}
}

void uart0_float(float num)
{
int n=num;
uart0_tx_integer(n);
uart0_tx('.');
n=(num-n)*10;
uart0_tx_integer(n);
}
