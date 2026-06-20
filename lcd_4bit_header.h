#include<lpc21xx.h>
#include"fun_decalr.h"
#define lcd 0XF00
#define rs 1<<12
#define e 1<<13



void lcd_init(void)
{
    IODIR0 |= lcd | rs | e ;
    lcd_cmd(0x02);
    lcd_cmd(0x28);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
}


void lcd_data(unsigned char data)
{ IOCLR0= lcd;
IOSET0=((data<<4)&0xf00);
IOSET0=rs;
IOSET0=e;
delay_ms(2);
IOCLR0=e;
	
	IOCLR0= lcd;
IOSET0=((data<<8)&0xf00);
IOSET0=rs;
IOSET0=e;
delay_ms(2);
IOCLR0=e;
}

void lcd_cmd(unsigned char cmd)
{IOCLR0=lcd;
IOSET0=((cmd<<4)&0xf00);
IOCLR0=rs;
IOSET0=e;
delay_ms(2);
IOCLR0=e;
	
	IOCLR0=lcd;
IOSET0=((cmd<<8)&0xf00);
IOCLR0=rs;
IOSET0=e;
delay_ms(2);
IOCLR0=e;
}
void lcd_str(unsigned char*s)
{while(*s)
	lcd_data(*s++);
}
void lcd_int(int n)
{
    unsigned char arr[16];
    int i = 0;
    if(n == 0)
    {
        lcd_data('0');
        return;
    }

    if(n < 0)
    {  lcd_data('-');
        n = -n;
    }
    while(n != 0)
    {  arr[i++] = n % 10;
        n /= 10;
    }
    while(i > 0)
    {
        lcd_data(arr[--i] + '0');
    }
}
void lcd_float(float f)
{
int temp=f;
lcd_int(temp);
temp=(f-temp)*100;
lcd_int(temp);
}
