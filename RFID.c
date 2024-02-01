#include <LPC21xx.H>
#include "header20.h"

int main()
{
int i=0,c=0,l=0;
char p[20],s1[20];//std2[20];
uart0_init(9600); 
lcd_4bit_init();


while(1)
{

uart0_rx_RFID(p);
lcd_4bit_cmd(0x01);
lcd_string(p);
if(l==0)
{
  while(*p)
  {
  s1[i]=p[i];
  i++;
  }
 }
lcd_4bit_cmd(0xc0);

//lcd_string(s1);
  for(i=0,c=0;p[i];i++)
  {
 	if(p[i]!=s1[i])
	{
		   c++;
			break;
			}
	}
	if(c==0)
	lcd_string("Vector student");

	else
	lcd_string("Non_vect ");
	if(l==0)
	{
	lcd_4bit_cmd(0x01);
	l++;
	}

}
}