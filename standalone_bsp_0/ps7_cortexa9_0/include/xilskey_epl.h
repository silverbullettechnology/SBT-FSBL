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
* 		xilskey_epl.h
* @note
*		 Contains the function prototypes, defines and macros for the PL eFUSE
*		 functionality.
*
* MODIFICATION HISTORY:
*
* Ver   Who  	Date     Changes
* ----- ---- 	-------- --------------------------------------------------------
* 1.00a rpoolla 04/26/13 First release
* 1.02a hk      10/28/13 Added API's to read status bits and key :
* 			 u32 XilSKey_EfusePl_ReadKey(XilSKey_EPl *InstancePtr)
*			 u32 XilSKey_EfusePl_ReadKey(XilSKey_EPl *InstancePtr)
* 2.00  hk      22/01/14 Corrected PL voltage checks to VCCINT and VCCAUX.
*                        CR#768077
*
*
****************************************************************************/
#ifndef XILSKEY_EPL_H
#define XILSKEY_EPL_H

#ifdef __cplusplus
extern "C" {
#endif
/***************************** Include Files *********************************/

/************************** Constant Definitions *****************************/
/**
 *  AES Key size in Bytes
 */
#define XSK_EFUSEPL_AES_KEY_SIZE_IN_BYTES				(32)
/**
 *  User Key size in Bytes
 */
#define XSK_EFUSEPL_USER_KEY_SIZE_IN_BYTES				(4)
/**************************** Type Definitions ******************************/
/***************** Macros (Inline Functions) Definitions ********************/

/************************** Variable Definitions ****************************/
/**
 * XSK_EfusePl is the PL eFUSE driver instance. Using this
 * structure, user can define the eFUSE bits to be
 * blown.
 */
typedef struct {
	/**
	 * Following are the FUSE CNTRL bits[1:5, 8-10]
	 */

	/**
	 * If XTRUE then part has to be power cycled to be able to be reconfigured
	 */
	u32	ForcePowerCycle;
	/**
	 * If XTRUE will disable eFUSE write to FUSE_AES and FUSE_USER blocks
	 */
	u32 KeyWrite;
	/**
	 * If XTRUE will disable eFUSE read to FUSE_AES block and also disables
	 * eFUSE write to FUSE_AES and FUSE_USER blocks
	 */
	u32 AESKeyRead;
	/**
	 * If XTRUE will disable eFUSE read to FUSE_USER block and also disables
	 * eFUSE write to FUSE_AES and FUSE_USER blocks
	 */
	u32 UserKeyRead;
	/**
	 * If XTRUE will disable eFUSE write to FUSE_CNTRL block
	 */
	u32	CtrlWrite;
	/**
	 * If XTRUE will force eFUSE key to be used if booting Secure Image
	 */
	u32 AESKeyExclusive;
	/**
	 * If XTRUE then permanently sets the Zynq ARM DAP controller in bypass mode
	 */
	u32 JtagDisable;
	/**
	 * If XTRUE will force to use Secure boot with eFUSE key only
	 */
	u32 UseAESOnly;
	/**
	 * Following is the define to select if the user wants to select AES key
	 * and User Low Ley
	 */
	u32 ProgAESandUserLowKey;
	/**
	 * Following is the define to select if the user wants to select
	 * User Low Ley
	 */
	u32 ProgUserHighKey;
	/**
	 * This is the REF_CLK value in Hz
	 */
	/*u32	RefClk;*/
	/**
	 * This is for the aes_key value
	 */
	u8 AESKey[XSK_EFUSEPL_AES_KEY_SIZE_IN_BYTES];
	/**
	 * This is for the user_key value
	 */
	u8 UserKey[XSK_EFUSEPL_USER_KEY_SIZE_IN_BYTES];
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
	/**
	 * AES key read
	 */
	u8 AESKeyReadback[XSK_EFUSEPL_AES_KEY_SIZE_IN_BYTES];
	/**
	 * User key read
	 */
	u8 UserKeyReadback[XSK_EFUSEPL_USER_KEY_SIZE_IN_BYTES];
	/**
	 * Internal variable to check if timer, XADC and JTAG are initialized.
	 */
	u32 SystemInitDone;

}XilSKey_EPl;
/************************** Function Prototypes *****************************/
/************************** Constant Definitions *****************************/

u32 XilSKey_EfusePl_Program(XilSKey_EPl *PlInstancePtr);

u32 XilSKey_EfusePl_ReadStatus(XilSKey_EPl *InstancePtr, u32 *StatusBits);

u32 XilSKey_EfusePl_ReadKey(XilSKey_EPl *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif	/* End of XILSKEY_EPL_H */
