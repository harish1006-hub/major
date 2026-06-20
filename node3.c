#include<lpc21xx.h>	  
#include"can2_driver.c" 
#include"ultrasonic.h"
#include"header.h"
#include"lcd_4bit_header.h"

#define TRIG (1<<11)
#define ECHO (1<<12)
#define buzzer (1<<13)


int main()

{unsigned int adc_value;

float voltage;

float temp;
unsigned int limit=6;
unsigned int distance;
CAN2_MSG m1;

lcd_init();
 timer1_init();
can2_init();
IODIR0 |=TRIG|buzzer;
        m1.id=0x120;
	m1.rtr=0;//data frame
	m1.dlc=8;

while(1)
{  IOSET0= buzzer;
    adc_value = adc_read();

voltage = (adc_value * 3.3) / 1023.0;
temp = voltage * 100.0;

lcd_cmd(0x80);
lcd_str("Temp:");
lcd_int((int)temp);
m1.byteA=((int)temp);
lcd_str("C");
distance = get_distance();
m1.byteB=((int)distance);
lcd_cmd(0xC0);
lcd_str("Dist:");
lcd_int(distance);
lcd_str("cm");
if (distance<=limit)
{IOCLR0= buzzer;
}
can2_tx(m1);
    delay_ms(1000);
    lcd_cmd(0x01); 

}

}


unsigned int adc_read(void)

{ unsigned int adc;

PINSEL1|= 1<<22;

ADCR=(1<<0)|(14<<8)|(1<<21);

ADCR |= (1<<24);

while(!(ADDR&0X80000000));

adc=((ADDR>>6)&0X3FF);

return adc;

}
