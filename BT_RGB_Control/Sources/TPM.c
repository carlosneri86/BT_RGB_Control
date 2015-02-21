/*HEADER******************************************************************************************
*
* Comments:
*
*
**END********************************************************************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                      Includes Section                        
///////////////////////////////////////////////////////////////////////////////////////////////////
#include <derivative.h>
#include <stdint.h>
#include <stddef.h>
#include "NVIC.h"
#include "TPM.h"
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Defines & Macros Section                   
///////////////////////////////////////////////////////////////////////////////////////////////////
//! TPM available registers.
enum eTPM_Registers
{
	TPM_SC = 0,
	TPM_CNT,
	TPM_MOD,
	TPM_CH0_SC,
	TPM_CH0_V,
	TPM_CH1_SC,
	TPM_CH1_V,
	TPM_CH2_SC,
	TPM_CH2_V,
	TPM_CH3_SC,
	TPM_CH3_V,
	TPM_CH4_SC,
	TPM_CH4_V,
	TPM_CH5_SC,
	TPM_CH5_V,
	TPM_STATUS,
	TPM_CONF,
	TPM_MAX_REGISTERS
	
};

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
//! Corresponding clock gate masks for all the TPM modules.
static const uint32_t TPM_gadwClockGateMask[MAX_TPM] =
{
		SIM_SCGC6_TPM0_MASK,
		SIM_SCGC6_TPM1_MASK,
		SIM_SCGC6_TPM2_MASK
};
//! Registers address of all the TPM modules.
static volatile uint32_t * const TPM_gapdwRegisters[MAX_TPM][TPM_MAX_REGISTERS] =
{
		{
			&TPM0_SC,
			&TPM0_CNT,
			&TPM0_MOD,
			&TPM0_C0SC,
			&TPM0_C0V,
			&TPM0_C1SC,
			&TPM0_C1V,
			&TPM0_C2SC,
			&TPM0_C2V,
			&TPM0_C3SC,
			&TPM0_C3V,
			&TPM0_C4SC,
			&TPM0_C4V,
			&TPM0_C5SC,
			&TPM0_C5V,
			&TPM0_STATUS,
			&TPM0_CONF
		},
		{
			&TPM1_SC,
			&TPM1_CNT,
			&TPM1_MOD,
			&TPM1_C0SC,
			&TPM1_C0V,
			&TPM1_C1SC,
			&TPM1_C1V,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			&TPM1_STATUS,
			&TPM1_CONF
		},
		{
			&TPM2_SC,
			&TPM2_CNT,
			&TPM2_MOD,
			&TPM2_C0SC,
			&TPM2_C0V,
			&TPM2_C1SC,
			&TPM2_C1V,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			&TPM2_STATUS,
			&TPM2_CONF
		}
};

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Global Variables Section                   
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Static Variables Section                   
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
//                                      Functions Section                       
///////////////////////////////////////////////////////////////////////////////////////////////////

void TPM_vfnInit(uint8_t bTPMToEnable, uint8_t bTPMClockSource, uint16_t wTPMModulo)
{
	uint32_t * pdwTPM_ModRegister;
	
	/* Confirm the TPM to be enable is within the available on the SoC */
	if(bTPMToEnable < MAX_TPM)
	{
		
		SIM_SCGC6 |= TPM_gadwClockGateMask[bTPMToEnable];
		
		/* Select the TPM clock source and load the period*/
		SIM_SOPT2 |= SIM_SOPT2_TPMSRC(bTPMClockSource);
		
		pdwTPM_ModRegister = (uint32_t*)TPM_gapdwRegisters[bTPMToEnable][TPM_MOD];
		
		
		*pdwTPM_ModRegister = wTPMModulo;
	}
		
}

void TPM_vfnStartTimer(uint8_t bTPMToEnable, uint8_t bTPMPrescaler)
{
	uint32_t * pdwTPM_SCRegister;
	
	if(bTPMToEnable < MAX_TPM)
	{
		pdwTPM_SCRegister = (uint32_t*)TPM_gapdwRegisters[bTPMToEnable][TPM_SC];
		/* Enable module with internal CLK and */
		*pdwTPM_SCRegister = TPM_SC_CMOD(0x01)|TPM_SC_PS(bTPMPrescaler);
	}
}


void TPM_vfnConfigChannel(uint8_t bTPMToEnable, uint8_t bTPMChannel, uint8_t bTPMMSx, uint8_t bTPMELSx, uint16_t wChannelValue)
{
	uint32_t * pdwChannelSC;
	uint32_t * pdwChannelValue;
	/* Get the channel registers address*/
	pdwChannelSC = (uint32_t*)TPM_gapdwRegisters[bTPMToEnable][TPM_CH0_SC+(2*bTPMChannel)];
	pdwChannelValue = (uint32_t*)TPM_gapdwRegisters[bTPMToEnable][TPM_CH0_V+(bTPMChannel*2)];
	/*	Configure the channel*/
	*pdwChannelSC = (bTPMMSx<<TPM_CnSC_MSA_SHIFT)|(bTPMELSx<<TPM_CnSC_ELSA_SHIFT);
	*pdwChannelValue = wChannelValue;
}


void TPM_vfnUpdateChannel(uint8_t bTPMToEnable, uint8_t bTPMChannel, uint16_t wChannelValue)
{
	uint32_t * pdwChannelValue;
	/* get the channel register address and updated it */
	pdwChannelValue = (uint32_t*)TPM_gapdwRegisters[bTPMToEnable][TPM_CH0_V+(bTPMChannel*2)];
	
	*pdwChannelValue = wChannelValue;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////////////////////////////////////

