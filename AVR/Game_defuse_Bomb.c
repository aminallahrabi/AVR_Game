#include <io.h>
#include <mega32.h>
#include <delay.h>
#include <alcd.h>
#include <stdio.h>      
#include <stdlib.h>
#include <math.h>


char scan[4]={0XFE,0XFD,0XFB,0XF7};
char key;
int row , col;
char keypad [4][4] = { {'7','8','9','/'},
                                      {'4','5','6','*'},
                                      {'1','2','3','-'},
                                      {'c','0','=','+'}};     

char K;
char Seven_Segment(char Data){
 
 switch (Data){
 case 0: K=0x7E;return K;  break;
 case 1: K=0x0C;return K;  break;
 case 2: K=0xB6;  return K;break;
 case 3: K=0x9E;  return K;break;
 case 4: K=0xCC;  return K;break;
 case 5: K=0xDA;  return K;break;
 case 6: K=0xFA;  return K;break;
 case 7: K=0x0E;  return K;break;
 case 8: K=0xFE;  return K;break;
 case 9: K=0xDE;  return K;break;
 default: K=0x00;  return K;break;
    } 
 
 }   

void key_pad(){
char rands = '7';
        char Data=9;
        int j = 0;
        while(1){
                j++;
                PORTC = Seven_Segment(Data);
            if(j%1000==0){
                Data--;
             }
             
             if (Data == 0){
             PORTC = Seven_Segment(Data);
             PORTD = 0X00;
             PORTD.5 = 1;
             lcd_clear();
             lcd_gotoxy(2,1);
             lcd_puts(" Bomb Exploded ");
             delay_ms(2500);
             break;
            }
            
            for(row=0; row <=3; row++){
            
                PORTB = scan[row];
                
                col = 5;
                
                if(PINB.4 ==0){
                    col = 0;
                }
                if(PINB.5 ==0){
                    col = 1;
                }
                if(PINB.6 ==0){
                    col = 2;
                }
                if(PINB.7 ==0){
                    col = 3;
                }
                
                if(col != 5){ 
                    //while (PINB.4 == 0);
                    //while (PINB.5 == 0);
                   //while (PINB.6 == 0);
                   //while (PINB.7 == 0); 
                 delay_ms(250);    
                 key = keypad[row][col];
                 if(key=='c' || key== '=' || key == '+' || key=='-' || key=='/' || key=='*' ){
                    lcd_init(16);  
                    lcd_clear();
                }
                else{
                    if(key != 'c'){
                         lcd_clear();
                        lcd_gotoxy(0,0);
                        lcd_putchar(key);
                    }
                    if(key > rands){   
                        lcd_gotoxy(0,1);
                        lcd_puts("Guess Lower");
                    }
                    else if(key < rands){   
                        lcd_gotoxy(0,1);
                        lcd_puts("Guess Greater");
                    }
                    else{
                        lcd_gotoxy(2,1);
                        lcd_puts("Bomb Defused");
                        PORTD = 0X00;
                        PORTD.7 = 1;
                        delay_ms(2500);
                        break;
                    }
                }
                }   
            }
            if(PIND.7 == 1){
                break;
            }        
   }
    
}
    
void main(){
 DDRC=0xFF;
 DDRB = 0x0F;
 PORTC=0x00;
 DDRD = 0xFF;
 PORTD = 0X00;
 PORTD.6 = 1;
 
 lcd_init(16);
 lcd_clear();
 
 while(1){

 key_pad();
 
 PORTD = 0X00;
 lcd_clear(); 
 
 break;
 }
 }