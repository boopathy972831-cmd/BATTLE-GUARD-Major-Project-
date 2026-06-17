/* main_nodeA_TX.c */
//#include<stdio.h>
#include "lcd_4bit_header.h"
#include "header.h"
#include "can2_driver.c"
#include "uart0_driver.c"
#include<string.h>
main()
{	
     unsigned char sol1_id[]="060067F1C656";
	 unsigned char tag[13];


	unsigned char i;
	CAN2_MSG m1;
	 uart0_init(9600);
	 	can2_init();


	m1.id=0x150;
	m1.rtr=0;//data frame
	m1.dlc=4;
	while(1)
		{ 
		for(i=0;i<12;i++)
	        {
	           tag[i]=uart0_rx();	    
	        }
                tag[12]='\0'; 
		

					
		 
		if((strcmp((char *)tag,(char *)sol1_id) == 0))

		{
		
		m1.byteA=1;
			m1.byteB=0;
		}
		else
		{
		
		m1.byteA=0;
			m1.byteB=0;
		}		
		can2_tx(m1);//data-frame
		delay_milliseconds(1000);
	
	
}	






}
