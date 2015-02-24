/******************************************************************************
*
* (c) Copyright 2012-2013 Xilinx, Inc. All rights reserved.
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

/*****************************************************************************
*
* @file fsbl_hooks.c
*
* This file provides functions that serve as user hooks.  The user can add the
* additional functionality required into these routines.  This would help retain
* the normal FSBL flow unchanged.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date        Changes
* ----- ---- -------- -------------------------------------------------------
* 3.00a np   08/03/12 Initial release
* </pre>
*
* @note
*
******************************************************************************/


#include "fsbl.h"
#include "xstatus.h"
#include "fsbl_hooks.h"

#include "xgpiops.h"

/************************** Variable Definitions *****************************/

	XGpioPs Gpio;	/* The driver instance for GPIO Device. */
/************************** Function Prototypes ******************************/


/******************************************************************************
* This function is the hook which will be called  before the bitstream download.
* The user can add all the customized code required to be executed before the
* bitstream download to this routine.
*
* @param None
*
* @return
*		- XST_SUCCESS to indicate success
*		- XST_FAILURE.to indicate failure
*
****************************************************************************/
u32 FsblHookBeforeBitstreamDload(void)
{
	u32 Status;

	Status = XST_SUCCESS;

	/*
	 * User logic to be added here. Errors to be stored in the status variable
	 * and returned
	 */
	fsbl_printf(DEBUG_INFO,"In FsblHookBeforeBitstreamDload function \r\n");

	return (Status);
}

/******************************************************************************
* This function is the hook which will be called  after the bitstream download.
* The user can add all the customized code required to be executed after the
* bitstream download to this routine.
*
* @param None
*
* @return
*		- XST_SUCCESS to indicate success
*		- XST_FAILURE.to indicate failure
*
****************************************************************************/
u32 FsblHookAfterBitstreamDload(void)
{
	u32 Status;

	Status = XST_SUCCESS;

	/*
	 * User logic to be added here.
	 * Errors to be stored in the status variable and returned
	 */
	fsbl_printf(DEBUG_INFO, "In FsblHookAfterBitstreamDload function \r\n");

	return (Status);
}

/******************************************************************************
* This function is the hook which will be called  before the FSBL does a handoff
* to the application. The user can add all the customized code required to be
* executed before the handoff to this routine.
*
* @param None
*
* @return
*		- XST_SUCCESS to indicate success
*		- XST_FAILURE.to indicate failure
*
****************************************************************************/
u32 FsblHookBeforeHandoff(void)
{

#define EMIO_BANK		XGPIOPS_BANK2	/* Bank to be used for emio */
#define GPIO_DEVICE_ID  	XPAR_XGPIOPS_0_DEVICE_ID
#define LED_DELAY		1000000


	XGpioPs_Config *ConfigPtr;
	volatile int Delay;

	u32 Status;

	Status = XST_SUCCESS;

	/*
	 * User logic to be added here.
	 * Errors to be stored in the status variable and returned
	 */
	fsbl_printf(DEBUG_GENERAL,"In FsblHookBeforeHandoff function D1\r\n");

    //need to enable ADI reset pins

	/*
	 * Initialize the GPIO driver.
	 */
	ConfigPtr = XGpioPs_LookupConfig(GPIO_DEVICE_ID);
	XGpioPs_CfgInitialize(&Gpio, ConfigPtr,
					ConfigPtr->BaseAddr);

	XGpioPs_SetDirection(&Gpio, EMIO_BANK, 0xFFFF);
	XGpioPs_SetOutputEnable(&Gpio, EMIO_BANK, 0xFFFF);

	XGpioPs_SetDirection(&Gpio, 3, 0xFFFF);
	XGpioPs_SetOutputEnable(&Gpio, 3, 0xFFFF);

	//Set DC1_Sw_CTRL
	XGpioPs_WritePin(&Gpio, 99, 0x0);

	//ADI Pins
	XGpioPs_WritePin(&Gpio, 58, 0x1);
	XGpioPs_WritePin(&Gpio, 59, 0x1);

	//Ethernet PHY reset
	XGpioPs_WritePin(&Gpio, 71, 0x1);

	//USB Reset
	XGpioPs_WritePin(&Gpio, 83, 0x1);

	//Emmc Reset
	XGpioPs_WritePin(&Gpio, 84, 0x1);

	//LEDs
	XGpioPs_WritePin(&Gpio, 54, 0x1);
	XGpioPs_WritePin(&Gpio, 55, 0x1);
	XGpioPs_WritePin(&Gpio, 56, 0x1);
	XGpioPs_WritePin(&Gpio, 57, 0x1);

	for (Delay = 0; Delay < LED_DELAY; Delay++);

	//ADI Pins
	XGpioPs_WritePin(&Gpio, 58, 0x0);
	XGpioPs_WritePin(&Gpio, 59, 0x0);

	//Ethernet PHY reset
	XGpioPs_WritePin(&Gpio, 71, 0x0);

	//USB Reset
	XGpioPs_WritePin(&Gpio, 83, 0x0);

	//Emmc Reset
	XGpioPs_WritePin(&Gpio, 84, 0x0);

	//LEDs
	XGpioPs_WritePin(&Gpio, 54, 0x0);
	XGpioPs_WritePin(&Gpio, 55, 0x0);
	XGpioPs_WritePin(&Gpio, 56, 0x0);
	XGpioPs_WritePin(&Gpio, 57, 0x0);


	for (Delay = 0; Delay < LED_DELAY; Delay++);

	//ADI Pins
	XGpioPs_WritePin(&Gpio, 58, 0x1);
	XGpioPs_WritePin(&Gpio, 59, 0x1);

	//Ethernet PHY reset
	XGpioPs_WritePin(&Gpio, 71, 0x1);


	//USB Reset
	XGpioPs_WritePin(&Gpio, 83, 0x1);

	//Emmc Reset
	XGpioPs_WritePin(&Gpio, 84, 0x1);

	//LEDs
	XGpioPs_WritePin(&Gpio, 54, 0x1);
	XGpioPs_WritePin(&Gpio, 55, 0x1);
	XGpioPs_WritePin(&Gpio, 56, 0x1);
	XGpioPs_WritePin(&Gpio, 57, 0x1);

	/**(int*) 0xf8000008 = 0xDF0D;

    *(int*) 0xf8000170 = 0x00100400;
    *(int*) 0xf8000180 = 0x00100400;
    *(int*) 0xf8000190 = 0x00100400;
    *(int*) 0xf80001A0 = 0x00100400;

    *(int*) 0xf8000004 = 0x767B;*/

	fsbl_printf(DEBUG_GENERAL, "Reset Complete\r\n");

	return (Status);
}


/******************************************************************************
* This function is the hook which will be called in case FSBL fall back
*
* @param None
*
* @return None
*
****************************************************************************/
void FsblHookFallback(void)
{
	/*
	 * User logic to be added here.
	 * Errors to be stored in the status variable and returned
	 */
	fsbl_printf(DEBUG_INFO,"In FsblHookFallback function \r\n");
	memtest_main();

	while(1);
}


