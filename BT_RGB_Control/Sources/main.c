/*
 * main implementation: use this 'C' sample to create your own application
 *
 */





#include "derivative.h" /* include peripheral declarations */
#include "BoardConfig.h"
#include "SW_Timer.h"
#include "Bluetooth.h"
#include "MiscFunctions.h"
#include "RGB_Control.h"


//! Red initial intensity
#define RED_INIT_VALUE					(0xFF)
//! Green initial intensity
#define GREEN_INIT_VALUE				(0x00)
//! Blue initial intensity
#define BLUE_INIT_VALUE					(0x00)

#define COMMAND_BUFFER_SIZE				(10)

#define COMMAND_RGB_SIZE				(6)

#define RED_OFFSET_BYTE_1				(0)

#define RED_OFFSET_BYTE_2				(1)

#define GREEN_OFFSET_BYTE_1				(2)

#define GREEN_OFFSET_BYTE_2				(3)

#define BLUE_OFFSET_BYTE_1				(4)

#define BLUE_OFFSET_BYTE_2				(5)

uint8_t bfnGetColorFromAscii(uint8_t * pbRgbBuffer);

uint8_t gbaCommandBuffer[COMMAND_BUFFER_SIZE];

int main(void)
{
	uint8_t bCommandBufferOffset = 0;
	uint8_t bRed = 0;
	uint8_t bGreen = 0;
	uint8_t bBlue = 0;
	
	BoardConfig_vfnInit();
	SWTimer_vfnInit();
	Bluetooth_vfnInitModule();
	RGB_vfnInit();
	
	RGB_vfnChangeColor(RED_INIT_VALUE,GREEN_INIT_VALUE,BLUE_INIT_VALUE);
	
	for(;;) 
	{	   
		SWTimer_vfnServiceTimers();
		Bluetooth_vfnStateMachine();
		/* Confirm there's a BT device connected */
		if(BLUETOOTH_CHECK_STATUS(BLUETOOTH_CONNECTED))
		{
			/* poll for BT data */
			if(BLUETOOTH_CHECK_STATUS(BLUETOOTH_DATA_READY))
			{
				/* fill the command buffer, once the amount of bytes received matches 	*/
				/* the expected, convert it from ascii and change the RGB value 		*/
				/* assumes that data is always right									*/
				gbaCommandBuffer[bCommandBufferOffset] = Bluetooth_bfnReadData();
				
				bCommandBufferOffset++;
				
				if(bCommandBufferOffset >= COMMAND_RGB_SIZE)
				{
					bCommandBufferOffset = 0;
					
					bRed = bfnGetColorFromAscii(&gbaCommandBuffer[RED_OFFSET_BYTE_1]);
					
					bGreen = bfnGetColorFromAscii(&gbaCommandBuffer[GREEN_OFFSET_BYTE_1]);
				
					bBlue = bfnGetColorFromAscii(&gbaCommandBuffer[BLUE_OFFSET_BYTE_1]);
					
					RGB_vfnChangeColor(bRed, bGreen, bBlue);
					
				}
			}
		}
			
	}
	
	return 0;
}
/* [TODO] move it to a misc file or something */
uint8_t bfnGetColorFromAscii(uint8_t * pbRgbBuffer)
{
	uint8_t bHigherNibble;
	uint8_t bColorData;
	
	bHigherNibble = bfnAsciiToHex(pbRgbBuffer[0]);
	bColorData = bHigherNibble << 4;
	bColorData |= bfnAsciiToHex(pbRgbBuffer[1]);
	
	return (bColorData);
}
