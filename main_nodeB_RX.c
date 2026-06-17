/* main_nodeB_RX.c */
#include<lpc21xx.h>
#include "header.h"
#include "can2_driver.c"
#include"delay_header.h"
//#include"lcd_4bit_header.h"
//#include "uart0_driver.c"
#define lcd 0xf0
#define rs 1<<8
#define E 1<<9
void lcd_init(void);
void lcd_command(unsigned char);
void lcd_data(unsigned char);
void lcd_str(unsigned char*);

main(){	
	CAN2_MSG m1;

	can2_init();
    	 	lcd_init();
	lcd_command(0x80);

	lcd_str("ID:V25CE5B2");

	lcd_command(0xc0);
	lcd_str("NAME:BOOPATHY");

	delay_milliseconds(2000);
		lcd_command(0x01);
	lcd_command(0x80);

 	lcd_str("BATTLE GUARD");
		lcd_command(0xc0);
	lcd_str("(MAJOR PROJECT)");
	delay_milliseconds(2000);
         lcd_command(0x01);
	 	 
	while(1){
	
	lcd_command(0x80);		   
	lcd_str("RFID SCANING...");		
		can2_rx(&m1);	
	if(m1.id==0x150){
			if(m1.byteA==1)
		   { 
		      lcd_command(0x01);


lcd_command(0x80);


lcd_str("RFID VERIFIED");


lcd_command(0xc0);


lcd_str("ACCESS GRANTED");


delay_milliseconds(1500);


lcd_command(0x01);


lcd_command(0x80);


lcd_str("SOLDIER B12");


lcd_command(0xc0);


lcd_str("MAIN GATE OPEN");


delay_milliseconds(2500);
		   }
		   else
		   {
	lcd_command(0x01);


lcd_command(0x80);


lcd_str("WARNING!");


lcd_command(0xc0);


lcd_str("UNAUTHURIZED CARD");


delay_milliseconds(1500);


lcd_command(0x01);


lcd_command(0x80);


lcd_str("ACCESS DENIED");


lcd_command(0xc0);


lcd_str("SECURITY ALERT!");


delay_milliseconds(2500);


lcd_command(0x01);
		      
		   }
		   delay_milliseconds(4000);
		   lcd_command(0x01);
		}	
			
	}
	
}


void lcd_str(unsigned char*c)
{
  while(*c)
  lcd_data(*c++);
  }

void lcd_init(void)

{

IODIR0=lcd|rs|E;

delay_milliseconds(20);

IOCLR0=rs;
IOCLR0=lcd;

IOSET0=0x30;

IOSET0=E;

delay_milliseconds(5);

IOCLR0=E;


IOCLR0=lcd;

IOSET0=0x30;

IOSET0=E;

delay_milliseconds(1);

IOCLR0=E;


IOCLR0=lcd;

IOSET0=0x30;

IOSET0=E;

delay_milliseconds(1);

IOCLR0=E;


IOCLR0=lcd;

IOSET0=0x20;

IOSET0=E;

delay_milliseconds(1);

IOCLR0=E;


lcd_command(0x01);//to clear the display

lcd_command(0x02);//to place the cursor in home position

lcd_command(0x0c);//display ON cursor OFF

lcd_command(0x28);//8 bit interfacing mode with both lines 

}

void lcd_command(unsigned char cmd)

{ //upper nibble

IOCLR0=lcd;//to clear data pins

IOSET0=(cmd&0xf0);//assigning cmd byte to datapins

IOCLR0=rs;//rs=o,to select command register

IOSET0=E;

delay_milliseconds(2);

IOCLR0=E;

//lower nibble

IOCLR0=lcd;//to clear data pins

IOSET0=((cmd<<4)&0xf0);//assigning cmd byte to datapins

IOCLR0=rs;//rs=o,to select command register

IOSET0=E;

delay_milliseconds(2);

IOCLR0=E;

}

void lcd_data(unsigned char data)

{
IOCLR0=lcd;//to clear data pins

IOSET0=(data&0xf0);//assigning cmd byte to datapins

IOSET0=rs;//rs=o,to select command register

IOSET0=E;
delay_milliseconds(2);
IOCLR0=E;
IOCLR0=lcd;//to clear data pins
IOSET0=((data<<4)&0xf0);//assigning cmd byte to datapins
IOSET0=rs;//rs=o,to select command register
IOSET0=E;
delay_milliseconds(2);
IOCLR0=E;
}
