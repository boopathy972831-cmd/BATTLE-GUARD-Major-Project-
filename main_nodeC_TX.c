#include "header.h"
#include<lpc21xx.h>
//#include "can_driver.c"
#include "delay_header.h"
#define buzzer 1<<3

CAN2_MSG m1;

/*
 * SG90 servo: 20ms period PWM, pulse 1ms=0°, 1.5ms=90°, 2ms=180°
 * PCLK = 60 MHz, PWMPR = 59 ? timer ticks at 1 MHz (1 µs per tick)
 * PWMMR0 = 20000 ? 20 ms period
 * MR1: 1000 = 1 ms (0°/closed), 1500 = 1.5 ms (90°), 2000 = 2 ms (180°/open)
 */
void pwm_init(void)
{
    /* P0.0 = PWM1 output: PINSEL0 bits[1:0] = 10 */
   // PINSEL0 |= (PINSEL0 & ~0x3UL) | 0x2UL;
	  PINSEL0 &= ~0x3;
      PINSEL0 |= 0x2;
    PWMPR  = 59;           /* prescaler: 60 MHz / 60 = 1 µs per tick  */
     //PWMPR  = 14;          /* 15 MHz / 15 = 1 MHz => 1 us tick */
	PWMTCR = 0x02;         /* reset counter                           */
    PWMMR0 = 20000;        /* 20 ms period                            */
    PWMMCR = (1 << 1);     /* reset on MR0 match                      */
    PWMMR1 = 1000;         /* start at 0° (closed)                    */
    PWMLER = (1 << 0) | (1 << 1);   /* latch MR0, MR1               */
    PWMPCR = (1 << 9);     /* enable PWM1 output                      */
    PWMTCR = 0x09;         /* enable timer + PWM mode                 */
}

void servo_open(void)
{
    PWMMR1 = 2000;         /* 2 ms pulse = 180° (gate open)  */
    PWMLER = (1 << 1);
}

void servo_close(void)
{
    PWMMR1 = 1000;         /* 1 ms pulse = 0° (gate closed)  */
    PWMLER = (1 << 1);
}

int main(void)
{
IODIR0=  buzzer;
    can2_init();
    
    pwm_init();
    servo_close();         /* ensure gate starts closed */
  
    while(1)
    {
        can2_rx(&m1);
            if(m1.id == 0x150)        
            {
	      if(m1.byteA==1)
	      {
                servo_open();
                delay_milliseconds(2000);      
                servo_close();
		}
		else
		{
		IOCLR0=buzzer;
		delay_milliseconds(2000);
		IOSET0=buzzer;
		}
            }          
       
    }   
}  
