#include<lpc21xx.h>
void delay_seconds(unsigned int sec)
{
T0PR=15000000-1;
T0TCR=0x01;
while(T0TC<sec);
T0TCR=0x03;
T0TCR=0X00;
}
void delay_milliseconds(unsigned int sec)
{
T0PR=60000-1;
T0TCR=0x01;
while(T0TC<sec);
T0TCR=0x03;
T0TCR=0X00;
}		
void delay_microseconds(unsigned int sec)
{
T0PR=15-1;
T0TCR=0x01;
while(T0TC<sec);
T0TCR=0x03;
T0TCR=0X00;
}

