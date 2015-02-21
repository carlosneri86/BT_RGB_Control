/*HEADER******************************************************************************************
*
* Comments:
*
*
**END********************************************************************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                      Includes Section                        
///////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdint.h>
#include "TPM.h"
#include "BoardConfig.h"
#include "RGB_Control.h"
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Defines & Macros Section                   
///////////////////////////////////////////////////////////////////////////////////////////////////
//! PWM period, in hertz
#define RGB_PERIOD			(100)
//! Prescaler used for the PWM module
#define RGB_TIMER_PRESCALER	(TPM_PRESCALER_4)
//! Calculate the period based on the PWM module clock and prescaler
#define RGB_PWM_PERIOD	(uint16_t)((BUS_CLOCK/(4))/RGB_PERIOD)
//! Initial duty. Set to 50% for all the PWM channels
#define RGB_INIT_DUTY_CYCLE		((RGB_PWM_PERIOD*50)/100)
//! Constant for scaling from 8 bit RGB values to equivalent on RGB_PWM_PERIOD
#define RGB_SCALE_CONSTANT		(uint16_t)(RGB_PWM_PERIOD/(UINT8_MAX))
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                       Typedef Section                        
///////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////
//                                  Function Prototypes Section                 
///////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Global Constants Section                   
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Static Constants Section                   
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Global Variables Section                   
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Static Variables Section                   
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
//                                      Functions Section                       
///////////////////////////////////////////////////////////////////////////////////////////////////

void RGB_vfnInit(void)
{
	/* Set the TPM CLK source and period all the LEDs*/	
	TPM_vfnInit(TPM0,TPM_CLK_FLL_PLL,RGB_PWM_PERIOD);
	
	TPM_vfnInit(TPM2,TPM_CLK_FLL_PLL,RGB_PWM_PERIOD);
	/* Enable the proper timers for PWM */
	TPM_vfnConfigChannel(RGB_RED_TIMER,RGB_RED_CHANNEL,TPM_MSB_MSA_10,TPM_ELSB_ELSA_10,RGB_INIT_DUTY_CYCLE);
	
	TPM_vfnConfigChannel(RGB_GREEN_TIMER,RGB_GREEN_CHANNEL,TPM_MSB_MSA_10,TPM_ELSB_ELSA_10,RGB_INIT_DUTY_CYCLE);
	
	TPM_vfnConfigChannel(RGB_BLUE_TIMER,RGB_BLUE_CHANNEL,TPM_MSB_MSA_10,TPM_ELSB_ELSA_10,RGB_INIT_DUTY_CYCLE);
	/* Once enabled, start the timers */
	TPM_vfnStartTimer(RGB_RED_TIMER,RGB_TIMER_PRESCALER);
	
	TPM_vfnStartTimer(RGB_BLUE_TIMER,RGB_TIMER_PRESCALER);
	
}

void RGB_vfnChangeColor(uint8_t bNewRed, uint8_t bNewGreen, uint8_t bNewBlue)
{
	uint16_t wNewColor = 0;
	/* Calculate the PWM duty based on the period 										*/
	/* The LEDs are connected to the anode, hence, the full bright is 0 and off is FF	*/
	
	wNewColor = (uint16_t)((uint32_t)RGB_PWM_PERIOD - ((uint32_t)(RGB_PWM_PERIOD*bNewRed)/UINT8_MAX));
	
	TPM_vfnUpdateChannel(RGB_RED_TIMER,RGB_RED_CHANNEL,wNewColor);
	
	wNewColor = (uint16_t)((uint32_t)RGB_PWM_PERIOD - ((uint32_t)(RGB_PWM_PERIOD*bNewGreen)/UINT8_MAX));
	
	TPM_vfnUpdateChannel(RGB_GREEN_TIMER,RGB_GREEN_CHANNEL,wNewColor);
	
	wNewColor = (uint16_t)((uint32_t)RGB_PWM_PERIOD - ((uint32_t)(RGB_PWM_PERIOD*bNewBlue)/UINT8_MAX));
	
	TPM_vfnUpdateChannel(RGB_BLUE_TIMER,RGB_BLUE_CHANNEL,wNewColor);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////////////////////////////////////
