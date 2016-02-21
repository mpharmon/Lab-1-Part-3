/*
 * File:   switch.c
 * Author: Garrett
 *
 * Created on September 19, 2015, 10:46 AM
 */

#include <xc.h>

#define TRISx_INPUT 1;

#define CNPUx_ENABLE 1;

void initSW(){
  // Set Tristate Registers as Input
  TRISAbits.TRISA7 = TRISx_INPUT;
  TRISDbits.TRISD6 = TRISx_INPUT;
  // Enable Pull Up Resistor
  CNPUAbits.CNPUA7 = 1;
  CNPUDbits.CNPUD6 = 1;
  // Enable Change Notification on Port
  CNCONAbits.ON = 1;
  CNCONDbits.ON = 1;
  // Enable CN Interrupt
  IEC1bits.CNAIE = 1;
  IEC1bits.CNDIE = 1;
  // Enable Interrupt on PIN
  CNENAbits.CNIEA7 = 1;
  CNENDbits.CNIED6 = 1;
  // Put Interrupt Flag Down
  IFS1bits.CNAIF = 0;
  IFS1bits.CNDIF = 0;
  // Set Interrupt Priority
  IPC8bits.CNIP = 7;
}
