#include <xc.h>
#include <sys/attribs.h>
#include "leds.h"
#include "interrupt.h"
#include "switch.h"
#include "timer.h"
#include "lcd.h"

typedef enum STATEenum{
  start,
  stop
}STATE;

volatile STATE state = stop;

#define PORTx_HIGH 1
#define PORTx_LOW 0

#define LATx_HIGH 1
#define LATx_LOW 0

#define START_LED LATGbits.LATG14
#define STOP_LED LATGbits.LATG12

/* Please note that the configuration file has changed from lab 0.
 * the oscillator is now of a different frequency.
 */
int main(void){
    SYSTEMConfigPerformance(10000000);
    enableInterrupts();
    initLEDs();
    initSW();
    StopWatch_Init();
    LCD_Init();
    while(1){
      switch(state){
        case start:
          START_LED = LATx_HIGH;
          STOP_LED = LATx_LOW;
          LCD_MoveCursor(1,1);
          LCD_PrintString("Running:");
          LCD_MoveCursor(1,2);
          LCD_PrintString(getTimeString());
          break;
        case stop:
          START_LED = LATx_LOW;
          STOP_LED = LATx_HIGH;
          LCD_MoveCursor(1,1);
          LCD_PrintString("Stopped:");
          LCD_MoveCursor(1,2);
          LCD_PrintString(getTimeString());
          break;
      }
    }
    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void){
  PORTA;
  PORTD;
  if(IFS1bits.CNAIF == 1){// Interrupt from Start/Stop Button
    IFS1bits.CNAIF = 0;
    if(PORTAbits.RA7 == PORTx_LOW){// Start/Stop Button Pressed
      if(state == start){
        state = stop;
        T1CONbits.ON = 0;// Stop Timer
      }else if(state == stop){
        LCD_Clear();
        state = start;
        T1CONbits.ON = 1;// Start Timer
      };
    };
  }else if(IFS1bits.CNDIF == 1){// Interrupt from Reset Button
    IFS1bits.CNDIF = 0;
    if(PORTDbits.RD6 == PORTx_LOW){// Reset Button Pressed
      T1CONbits.ON = 0;// Turn Timer Off
      StopWatch_Reset();
      state = stop;// Set FSM to stop
    };
  };
}
