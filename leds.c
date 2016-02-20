/*
* File:   leds.c
* Author: 
*
* Created on December 27, 2014, 1:31 PM
*/

#include <xc.h>

#define TRISx_OUTPUT 0;

#define LATx_HIGH 1;

#define ODCx_ENABLE 1;

void initLEDs(){
  // Set Tristate Registers as Outputs
  //FOR PRODUCTION:
  TRISGbits.TRISG12 = TRISx_OUTPUT;
  ODCGbits.ODCG12 = ODCx_ENABLE;
  //FOR PRODUCTION:
  TRISGbits.TRISG14 = TRISx_OUTPUT;
  ODCGbits.ODCG14 = ODCx_ENABLE;
}