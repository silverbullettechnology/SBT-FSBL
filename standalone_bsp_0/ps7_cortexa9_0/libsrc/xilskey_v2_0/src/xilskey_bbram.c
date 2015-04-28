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
* 			xilskey_bbram.c
* @note
*
*  			.
*
* MODIFICATION HISTORY:
*
* Ver   Who  	Date     Changes
* ----- ---- 	-------- --------------------------------------------------------
* 1.01a hk      09/18/13 First release
*
****************************************************************************/
/***************************** Include Files *********************************/
#include "xparameters.h"
#include "xil_types.h"
#include "xilskey_utils.h"
#include "xilskey_bbram.h"

/************************** Constant Definitions *****************************/
/**************************** Type Definitions ******************************/
/***************** Macros (Inline Functions) Definitions ********************/
/************************** Variable Definitions ****************************/
/************************** Function Prototypes *****************************/
/**
 * 	JTAG Server Initialization routine for Bbram
 */
extern int JtagServerInitBbram(XilSKey_Bbram *InstancePtr);

/**
 * BBRAM Algorithm - Initialization
 */
extern int Bbram_Init(XilSKey_Bbram *InstancePtr);

/**
 * BBRAM Algorithm - Program key
 */
extern int Bbram_ProgramKey(XilSKey_Bbram *InstancePtr);

/**
 * BBRAM Algorithm - Verify key
 */
extern int Bbram_VerifyKey(XilSKey_Bbram *InstancePtr);

/**
 * De-initialization
 */
extern void Bbram_DeInit(void);

/***************************************************************************/
/****************************************************************************/
/**
*
* This function implements the BBRAM algorithm for programming and
* verifying key. The program and verify will only work together in and
* in that order.
*
* @param  BBRAM instance pointer
*
* @return
*
*	- XST_FAILURE - In case of failure
*	- XST_SUCCESS - In case of Success
*
*
* @note
*
*****************************************************************************/
int XilSKey_Bbram_Program(XilSKey_Bbram *InstancePtr)
{
	u32 ArmPllFdiv;
	u32 ArmClkDivisor;
	u32 RefClk;
	int Status;

	if(NULL == InstancePtr)	{
		return XST_FAILURE;
	}

	/**
	 *  Extract PLL FDIV value from ARM PLL Control Register
	 */
	ArmPllFdiv = (Xil_In32(XSK_ARM_PLL_CTRL_REG)>>12 & 0x7F);

	/**
	 *  Extract Clock divisor value from ARM Clock Control Register
	 */
	ArmClkDivisor = (Xil_In32(XSK_ARM_CLK_CTRL_REG)>>8 & 0x3F);

	/**
	 * Initialize the variables
	 */
	RefClk = ((XPAR_PS7_CORTEXA9_0_CPU_CLK_FREQ_HZ * ArmClkDivisor)/
				ArmPllFdiv);

	/*
	 * Initialize and start the timer
	 */
	XilSKey_Efuse_StartTimer(RefClk);

	/*
	 * JTAG server initialization
	 */
	if(JtagServerInitBbram(InstancePtr) != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * BBRAM Algorithm initialization
	 */
	Status = Bbram_Init(InstancePtr);
	if(Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * BBRAM - Program key
	 */
	Status = Bbram_ProgramKey(InstancePtr);
	if(Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * BBRAM - Verify key
	 */
	Status = Bbram_VerifyKey(InstancePtr);
	if(Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * De-initialization
	 */
	Bbram_DeInit();

	return XST_SUCCESS;
}

