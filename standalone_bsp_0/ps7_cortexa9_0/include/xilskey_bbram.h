/******************************************************************************
*
* (c) Copyright 2013-2014 Xilinx, Inc. All rights reserved.
*
* This file contains confidential and proprietary information of Xilinx, Inc.
* and is protected under U.S. and international copyright and other
* intellectual property laws.
*
* DISCLAIMER
* This disclaimer is not a license and does not grant any rights to the
* materials distributed herewith. Except as otherwise provided in a valid
* license issued to you by Xilinx, and to the maximum extent permitted by
* applicable law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND WITH ALL
* FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES AND CONDITIONS, EXPRESS,
* IMPLIED, OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF
* MERCHANTABILITY, NON-INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE;
* and (2) Xilinx shall not be liable (whether in contract or tort, including
* negligence, or under any other theory of liability) for any loss or damage
* of any kind or nature related to, arising under or in connection with these
* materials, including for any direct, or any indirect, special, incidental,
* or consequential loss or damage (including loss of data, profits, goodwill,
* or any type of loss or damage suffered as a result of any action brought by
* a third party) even if such damage or loss was reasonably foreseeable or
* Xilinx had been advised of the possibility of the same.
*
* CRITICAL APPLICATIONS
* Xilinx products are not designed or intended to be fail-safe, or for use in
* any application requiring fail-safe performance, such as life-support or
* safety devices or systems, Class III medical devices, nuclear facilities,
* applications related to the deployment of airbags, or any other applications
* that could lead to death, personal injury, or severe property or
* environmental damage (individually and collectively, "Critical
* Applications"). Customer assumes the sole risk and liability of any use of
* Xilinx products in Critical Applications, subject only to applicable laws
* and regulations governing limitations on product liability.
*
* THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE
* AT ALL TIMES.
*
*******************************************************************************/
/*****************************************************************************/
/**
*
* @file
*
* 		xilskey_bbram.h
* @note
*		 Contains the function prototypes, defines and macros for
*		 BBRAM functionality.
*
* MODIFICATION HISTORY:
*
* Ver   Who  	Date     Changes
* ----- ---- 	-------- --------------------------------------------------------
* 1.01a hk      09/18/13 First release
*
****************************************************************************/
#ifndef XILSKEY_BBRAM_H
#define XILSKEY_BBRAM_H

#ifdef __cplusplus
extern "C" {
#endif
/***************************** Include Files *********************************/
/************************** Constant Definitions *****************************/
/**************************** Type Definitions ******************************/
/***************** Macros (Inline Functions) Definitions ********************/
/************************** Variable Definitions ****************************/
typedef struct {

	/**
	 * If XTRUE then part has to be power cycled to be able to be reconfigured
	 */
	u32	ForcePowerCycle;
	/**
	 * If XTRUE then permanently sets the Zynq ARM DAP controller in bypass mode
	 */
	u32 JtagDisable;
	/**
	 * This is for the aes_key value
	 */;
	u8 AESKey[32];
	/**
	 * TDI MIO Pin Number
	 */
	u32 JtagMioTDI;
	/**
	 * TDO MIO Pin Number
	 */
	u32 JtagMioTDO;
	/**
	 * TCK MIO Pin Number
	 */
	u32 JtagMioTCK;
	/**
	 * TMS MIO Pin Number
	 */
	u32 JtagMioTMS;
	/**
	 * MUX Selection MIO Pin Number
	 */
	u32 JtagMioMuxSel;
	/**
	 * Value on the MUX Selection line
	 */
	u32	JtagMuxSelLineDefVal;

}XilSKey_Bbram;
/************************** Constant Definitions *****************************/
/*
 * Constant definitions for instruction used in BBRAM key program and verify
 */
#define JPROGRAM 0x0B
#define ISC_NOOP 0x14
#define ISC_ENABLE 0x10
#define ISC_PROGRAM_KEY 0x12
#define ISC_PROGRAM 0x11
#define ISC_READ 0x15
#define ISC_DISABLE 0x16
#define BYPASS 0x3F

/*
 * Pre and post pads
 */
#define IRHEADER	0
#define IRTRAILER	4
#define DRHEADER	0
#define DRTRAILER	1

/*
 * Pre and post pads for BYPASS in de-init
 */
#define IRHEADER_BYP	0
#define IRTRAILER_BYP	0
#define DRHEADER_BYP	0
#define DRTRAILER_BYP	0

/*
 * Instruction load length
 */
#define IRLENGTH	6

/*
 * Data register lengths for program
 */
#define DRLENGTH_PROGRAM	32
/*
 * Data register lengths for verify
 */
#define DRLENGTH_VERIFY		37
/*
 * Data register lengths for data load after ISC_ENABLE
 */
#define DRLENGTH_EN		5
/*
 * Data register load after ISC_ENABLE
 */
#define DR_EN		0x15

/*
 * Timer function load for 100msec
 */
#define TIMER_100MS	1000000

/*
 * IRCAPTURE status - init complete mask
 */
#define INITCOMPLETEMASK	0x10

/*
 * Number of char's in a KEY
 */
#define NUMCHARINKEY	32
/*
 * Number of words in a KEY
 */
#define NUMWORDINKEY	8

/*
 * Data register shift before key verify
 */
#define DATAREGCLEAR	0x1FFFFFFFE0

/*
 * Number of LSB status bits in 37 bit read to shifted out
 */
#define NUMLSBSTATUSBITS	5

/*
 * Data and instruction loads in de-init
 */
#define IRDEINIT_H		0x03
#define IRDEINIT_L		0xFF
#define DRDEINIT		0x00

/*
 * Data and instruction lenghts in de-init
 */
#define IRDEINITLEN		10
#define DRDEINITLEN		2

/************************** Function Prototypes *****************************/
/*
 * Function for BBRAM program and vefiry algorithm
 */
int XilSKey_Bbram_Program(XilSKey_Bbram *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif	/* End of XILSKEY_BBRAM_H */
