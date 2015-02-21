/*HEADER******************************************************************************************
*
* Comments:
*
*
**END********************************************************************************************/
#ifndef TPM_H_
#define TPM_H_



///////////////////////////////////////////////////////////////////////////////////////////////////
//                                      Includes Section                                         
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
//                                  Defines & Macros Section                                     
///////////////////////////////////////////////////////////////////////////////////////////////////
//! Available TPM modules on the MCU.
enum eTPM
{
	TPM0 = 0,	
	TPM1,
	TPM2,
	MAX_TPM
};
//! Available TPM channels. Usually this is based on the TPM with most channels
enum eTPMChannel
{
	TPM_CH0 = 0,
	TPM_CH1,
	TPM_CH2,
	TPM_CH3,
	TPM_CH4,
	TPM_CH5
};
//! TPM Clock sources
enum eTPMSourceCLK
{
	TPM_DISABLED = 0,		//!< TPM Disabled
	TPM_CLK_FLL_PLL = 1,	//!< Uses PLL or FLL, depending on which is active on the MCG
	TPM_CLK_OSC,			//!< Uses the oscillator output
	TPM_CLK_IRC				//!< Uses the internal reference
};
//! TPM Channel Mode Select options. Refer to the MCU reference manual for definitions
enum eTPMMSBMSA
{
	TPM_MSB_MSA_00 = 0,	//!< Input capture mode
	TPM_MSB_MSA_01,		//!< Output compare mode
	TPM_MSB_MSA_10,		//!< PWM mode
	TPM_MSB_MSA_11,		//!< Output compare mode
};
//! TPM Channel Edge/Level Select options. Refer to the MCU reference manual for definitions
enum eTPMELSBELSA
{
	TPM_ELSB_ELSA_00 = 0,	
	TPM_ELSB_ELSA_01,
	TPM_ELSB_ELSA_10,
	TPM_ELSB_ELSA_11,
};
//! TPM Source clock prescaler
enum eTPMPrescaler
{
	TPM_PRESCALER_1 = 0,
	TPM_PRESCALER_2,
	TPM_PRESCALER_4,
	TPM_PRESCALER_8,
	TPM_PRESCALER_16,
	TPM_PRESCALER_32,
	TPM_PRESCALER_64,
	TPM_PRESCALER_128
};

//! Selects the prescaler to be used
#define TPM_APPLICATION_PRESCALER	(TPM_PRESCALER_32)
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                      Typedef Section                                          
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                Function-like Macros Section                                   
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                  Extern Constants Section                                     
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                  Extern Variables Section                                     
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                Function Prototypes Section                                    
///////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus
/*!
 *	@brief	Initializes a TPM module
 * 
 *	@param	bTPMToEnable	[in]	The TPM module to configure, based on eTPM enumeration
 * 
 *	@param	bTPMClockSource	[in]	TPM clock source, based on eTPMSourceCLK enumeration. Note the
 * 									source must be enabled or the TPM won't work
 * 	@param	wTPMModule		[in]	TPM period
 * 	
 * 	@return	void								
 *	
*/
void TPM_vfnInit(uint8_t bTPMToEnable, uint8_t bTPMClockSource, uint16_t wTPMModulo);
/*!
 *	@brief	Enable the TPM selected
 * 
 *	@param	bTPMToEnable	[in]	The TPM module to enable, based on eTPM enumeration
 * 
 *	@param	bTPMPrescaler	[in]	Prescaler to be applied on the Source clock. Based on 
 *									eTPMPrescaler enumeration
 *									
 * 	@return	void								
 *	
*/

void TPM_vfnStartTimer(uint8_t bTPMToEnable, uint8_t bTPMPrescaler);
/*!
 *	@brief	Configures the selected channel from the specified TPM module
 * 
 *	@param	bTPMToEnable	[in]	The TPM module, based on eTPM enumeration
 * 
 *	@param	bTPMChannel		[in]	Channel to configure. Based on eTPMChannel
 *									enumeration
 *									
 *	@param	bTPMMSx			[in]	Channel mode. Based on eTPMMSBMSA
 *									enumeration
 *									
 *	@param	bTPMELSx		[in]	Channel edge/level setting. Based on eTPMELSBELSA
 *									enumeration	
 *									
 *	@param	wChannelValue	[in]	Channel period
 *								
 * 	@return	void								
 *	
*/
void TPM_vfnConfigChannel(uint8_t bTPMToEnable, uint8_t bTPMChannel, uint8_t bTPMMSx, uint8_t bTPMELSx, uint16_t wChannelValue);
/*!
 *	@brief	Changes the channel period
 * 
 *	@param	bTPMToEnable	[in]	The TPM module, based on eTPM enumeration
 * 
 *	@param	bTPMChannel		[in]	Channel to configure. Based on eTPMChannel
 *									enumeration	
 *									
 *	@param	wChannelValue	[in]	Channel period
 *								
 * 	@return	void								
 *	
*/
void TPM_vfnUpdateChannel(uint8_t bTPMToEnable, uint8_t bTPMChannel, uint16_t wChannelValue);

#if defined(__cplusplus)
}
#endif // __cplusplus


#endif /* TPM_H_ */
///////////////////////////////////////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////////////////////////////////////

