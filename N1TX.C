#include<lpc21xx.h>	  
#include"can2_driver.c" 
#include"header.h"
#include"delay_header.h"
#include"lcd_4bit_header.h"

#define ldr  16
#define led1  1<<17

unsigned int adc_read(void);

int main()
{
unsigned int adc_value;
unsigned int value;
CAN2_MSG m1;
//CAN2_MSG m2;
lcd_init();
can2_init();
IODIR0 |=led1;
IOSET0=led1;
	/*sending data frame*/
	m1.id=0x150;
	m1.rtr=0;//data frame
	m1.dlc=8;
//	m1.byteA=0xDDCCBBAA;
//	m1.byteB=0;

//	m2.id=0x100;
//	m2.rtr=0;//data frame
//	m2.dlc=4;
////	m2.byteA=0xDDCCBBAA;
//	m2.byteB=0;

while(1)
{			  
lcd_cmd(0X01);
lcd_cmd(0X80);
lcd_str("FUEL:");
adc_value=adc_read();
value = (adc_value * 100) / 1023;
	m1.byteA=(unsigned int)value;
//m1.byteB=value;
lcd_cmd(0X85); 
lcd_int(value); 
lcd_data('%');
//can2_tx(m1);
//delay_s(1);
if(((IOPIN0 >> ldr)&1)==1)
{
m1.byteB=1;
lcd_cmd(0xC0);
lcd_str("LED  ON");
IOCLR0= led1;
}
else
{m1.byteB=0;
lcd_cmd(0xC0);
lcd_str("LED OFF");
IOSET0=led1;
}
can2_tx(m1);//data-frame
delay_s(1);
}

}

unsigned int adc_read(void)
{ unsigned int adc;
PINSEL1|= 1<<22;  //P0.27 AS ADC
ADCR=(1<<0)|(4<<8)|(1<<21);
ADCR |= (1<<24);
while(!(ADDR&0X80000000));
adc=((ADDR>>6)&0X3FF);
return adc;
}
