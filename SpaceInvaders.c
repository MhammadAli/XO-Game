// SpaceInvaders.c
// Runs on LM4F120/TM4C123
// Jonathan Valvano and Daniel Valvano
// This is a starter project for the edX Lab 15
// In order for other students to play your game
// 1) You must leave the hardware configuration as defined
// 2) You must not add/remove any files from the project
// 3) You must add your code only this this C file
// I.e., if you wish to use code from sprite.c or sound.c, move that code in this file
// 4) It must compile with the 32k limit of the free Keil

// April 10, 2014
// http://www.spaceinvaders.de/
// sounds at http://www.classicgaming.cc/classics/spaceinvaders/sounds.php
// http://www.classicgaming.cc/classics/spaceinvaders/playguide.php
/* This example accompanies the books
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2013

   "Embedded Systems: Introduction to Arm Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2013

 Copyright 2014 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
// ******* Required Hardware I/O connections*******************
// Slide pot pin 1 connected to ground
// Slide pot pin 2 connected to PE2/AIN1
// Slide pot pin 3 connected to +3.3V 
// fire button connected to PE0
// special weapon fire button connected to PE1
// 8*R resistor DAC bit 0 on PB0 (least significant bit)
// 4*R resistor DAC bit 1 on PB1
// 2*R resistor DAC bit 2 on PB2
// 1*R resistor DAC bit 3 on PB3 (most significant bit)
// LED on PB4
// LED on PB5

// Blue Nokia 5110
// ---------------
// Signal        (Nokia 5110) LaunchPad pin
// Reset         (RST, pin 1) connected to PA7
// SSI0Fss       (CE,  pin 2) connected to PA3
// Data/Command  (DC,  pin 3) connected to PA6
// SSI0Tx        (Din, pin 4) connected to PA5
// SSI0Clk       (Clk, pin 5) connected to PA2
// 3.3V          (Vcc, pin 6) power
// back light    (BL,  pin 7) not connected, consists of 4 white LEDs which draw ~80mA total
// Ground        (Gnd, pin 8) ground

// Red SparkFun Nokia 5110 (LCD-10168)
// -----------------------------------
// Signal        (Nokia 5110) LaunchPad pin
// 3.3V          (VCC, pin 1) power
// Ground        (GND, pin 2) ground
// SSI0Fss       (SCE, pin 3) connected to PA3
// Reset         (RST, pin 4) connected to PA7
// Data/Command  (D/C, pin 5) connected to PA6
// SSI0Tx        (DN,  pin 6) connected to PA5
// SSI0Clk       (SCLK, pin 7) connected to PA2
// back light    (LED, pin 8) not connected, consists of 4 white LEDs which draw ~80mA total

#include "tm4c123gh6pm.h"
#include "Nokia5110.h"
#include "Random.h"
#include "TExaS.h"

void Delay100ms(unsigned long count); // time delay in 0.1 seconds
char checkWin(void);


int main(void){
	
	 unsigned long SW1,SW2,SW3;
	 TExaS_Init(SSI0_Real_Nokia5110_Scope);  // set system clock to 80 MHz
	 Random_Init(1);
 	 Nokia5110_Init();
	 Nokia5110_ClearBuffer();	
	 
	 PortF_Init();
	 PORTE_INIT();
	
	
	 game_Init(start());  // choose Game type  3*3 or 4*4 
	 Nokia5110_Clear();
	 Delay100ms(10);
	 Draw();
	 set_Cursor();        //put the cursor in the specific positions 
	 Nokia5110_SetCursor(0,0);
	
 
while(1){
		 SW1 = GPIO_PORTF_DATA_R&0x10;     // read PF4 into SW1
  		 SW2 = GPIO_PORTF_DATA_R&0x01;     // read PF0 into SW2
		 SW3 = GPIO_PORTE_DATA_R&0x01;     // read PE0 into SW3
		
	
			
			if(!(SW2)&&done){ // SW2 pressed right
				 
        remove_Cursor();				
				
				pos++;
				if(pos>game_element)pos=game_element; 		// game element 3 * 3 = 8 --->bottom right square
    	 			while(!(GPIO_PORTF_DATA_R&0x01));               // if user still pressing the button no thing will happen
				
				  set_Cursor();
				
				  
			
			  	Delay100ms(4);
				
			}
				
			if(!(SW1)&&done) // SW1 pressed left
			{
				remove_Cursor();
				
				pos--;
				if(pos<0)pos=0;                               // top left square
				while(!(GPIO_PORTF_DATA_R&0x10));
				
				  set_Cursor();
				  Delay100ms(4);
				  			
				
				
			}
			if(SW3&&done){ // SW3 pressed
				
				while(GPIO_PORTE_DATA_R&0x01);                     // if user still pressing the button no thing will happen
				
				if(!(player)){
					
					if(position[pos/game_Type][pos%game_Type]=='_')
					{/*draw x in screen and put value X in the array*/
				  	Nokia5110_OutChar('X');          
				  	position[pos/game_Type][pos%game_Type]='X';
						
						
						pos++;                  // increment cursor
					  if(pos>game_element)pos=game_element;              //  bottom right square
						
						
					
						
						
						Nokia5110_SetCursor(0,5);
						Nokia5110_OutString("Player O..."); 
						set_Cursor();
						
						player^=1;             // toggle for player O
						
					}
					
				}
					
				else{
					if(position[pos/game_Type][pos%game_Type]=='_')
						{
							Nokia5110_OutChar('O');
							position[pos/game_Type][pos%game_Type]='O';
							
							// increment cursor
							pos++;
							if(pos>game_element)pos=game_element;
								
							
							
							
							
							Nokia5110_SetCursor(0,5);						
							Nokia5110_OutString("Player X...");
							set_Cursor();
						
							player^=1;                        // toggle for player X
					}
				}
				
				
				Delay100ms(4);
			}
			if(checkWin()){                             /* returns  X---> player X wins
			                                                        Y---> player Y wins
										q---> game is full and noone wins*/
				if( checkWin() =='x') {
					if(done){
					Nokia5110_Clear();
					Nokia5110_SetCursor(0,2);
					Nokia5110_OutString("player X Win");
					GPIO_PORTF_DATA_R = 0x04 ;// blue led
					GPIO_PORTE_DATA_R = 0x02 ;// porte pin 0 pin 1 
						done=0;
					}
				}
				if(checkWin()=='o') {
					if(done){
					Nokia5110_Clear();
					Nokia5110_SetCursor(0,2);
					Nokia5110_OutString("player Y Win");
				  GPIO_PORTF_DATA_R = 0x08;   // LED is green
						GPIO_PORTE_DATA_R = 0x02 ;

						done=0;
					}
				}
				if(checkWin()=='q') {
					if(done){
					Nokia5110_Clear();
					Nokia5110_SetCursor(0,2);
					Nokia5110_OutString("Game Over..");
						GPIO_PORTF_DATA_R = 0x02; // red led
						GPIO_PORTE_DATA_R = 0x02 ;
						done=0;
					}
				}
				
			}
				
		
  }

}


