#include<lpc21xx.h>
#include"delay_header.h"

#define TRIG (1<<11)
#define ECHO (1<<12)

void timer1_init(void)
{
    T1PR = 60-1;        
    T1TCR = 0x02;     
    T1TCR = 0x00;     
    T1TCR = 0x01;     
}

void ultrasonic_trigger(void)
{
    IOCLR0 = TRIG;
    delay_us(2);
    IOSET0 = TRIG;
    delay_us(10);
    IOCLR0 = TRIG;
}

unsigned int get_echo_time(void)
{
    unsigned int start, end;
    T1TC = 0;           
    ultrasonic_trigger(); 
    while(!(IOPIN0 & ECHO)); 
    start = T1TC;
    while(IOPIN0 & ECHO); 
    end = T1TC;
    return (end - start);    
}

unsigned int get_distance(void)
{
    unsigned int time;

    time = get_echo_time();

    return (time / 58); 
}
