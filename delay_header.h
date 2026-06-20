#include<lpc21xx.h>
void delay_s(unsigned int s)
{T0PR=60000000-1; // SET TOPR VALUE FOR 1 SEC
T0TCR=0X01;	 //0001 -  RST-0,E=1
while(T0TC<s);
T0TCR=0X03;	  //0011 -  RST-1,E=1
T0TCR=0X00;	  //0000 -  RST-0,E=0
}
void delay_ms(unsigned int ms)
{T0PR=60000-1;
T0TCR=0X01;
while(T0TC<ms);
T0TCR=0X03;
T0TCR=0X00;
}
void delay_us(unsigned int us)
{T0PR=60-1;
T0TCR=0X01;
while(T0TC<us);
T0TCR=0X03;
T0TCR=0X00;
}
