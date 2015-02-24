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
/*****************************************************************************/
/**
*
* @file main.c
*
* The main file for the First Stage Boot Loader (FSBL).
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver	Who	Date		Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00a jz	06/04/11	Initial release
* 2.00a mb	25/05/12	standalone based FSBL
* 3.00a np/mb	08/03/12	Added call to FSBL user hook - before handoff.
*				DDR ECC initialization added
* 				fsbl print with verbose added
* 				Performance measurement added
* 				Flushed the UART Tx buffer
* 				Added the performance time for ECC DDR init
* 				Added clearing of ECC Error Code
* 				Added the watchdog timer value
* 4.00a sgd 02/28/13	Code Cleanup
* 						Fix for CR#681014
* 						Fix for CR#689077
*						Fix for CR#694038
*						Fix for CR#694039
*                       Fix for CR#699475
*                       Removed DDR initialization check
*                       Removed DDR ECC initialization code
*						Modified hand off address check to 1MB
*						Added RSA authentication support
*						Watchdog disabled for AES E-Fuse encryption
* 5.00a sgd 05/17/13	Fallback support for E-Fuse encryption
*                       Fix for CR#708728
* </pre>
*
* @note
* FSBL runs from OCM, Based on the boot mode selected, FSBL will copy
* the partitions from the flash device. If the partition is bitstream then
* the bitstream is programmed in the Fabric and for an partition that is
* an application , FSBL will copy the application into DDR and does a
* handoff.The application should not be starting at the OCM address,
* FSBL does not remap the DDR. Application should use DDR starting from 1MB
*
* FSBL can be stitched along with bitstream and application using bootgen
*
* Refer to fsbl.h file for details on the compilation flags supported in FSBL
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "fsbl.h"
#include "qspi.h"
#include "nand.h"
#include "nor.h"
#include "sd.h"
#include "pcap.h"
#include "image_mover.h"
#include "xparameters.h"
//#include "xil_cache.h"
#include "xil_exception.h"
#include "xstatus.h"
#include "fsbl_hooks.h"
#include "xtime_l.h"

#ifdef XPAR_XWDTPS_0_BASEADDR
#include "xwdtps.h"
#endif

#ifdef STDOUT_BASEADDRESS
#include "xuartps_hw.h"
#endif

/************************** Constant Definitions *****************************/

#ifdef XPAR_XWDTPS_0_BASEADDR
#define WDT_DEVICE_ID		XPAR_XWDTPS_0_DEVICE_ID
#define WDT_EXPIRE_TIME		100
#define WDT_CRV_SHIFT		12
#endif



/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

#ifdef XPAR_XWDTPS_0_BASEADDR
XWdtPs Watchdog;		/* Instance of WatchDog Timer	*/
#endif
/************************** Function Prototypes ******************************/
extern int ps7_init();
#ifdef PS7_POST_CONFIG
extern int ps7_post_config();
#endif
#ifdef PEEP_CODE
extern void init_ddr(void);
#endif

static void Update_MultiBootRegister(void);
/* Exception handlers */
static void RegisterHandlers(void);
static void Undef_Handler (void);
static void SVC_Handler (void);
static void PreFetch_Abort_Handler (void);
static void Data_Abort_Handler (void);
static void IRQ_Handler (void);
static void FIQ_Handler (void);


#ifdef XPAR_XWDTPS_0_BASEADDR
int InitWatchDog(void);
u32 ConvertTime_WdtCounter(u32 seconds);
void  CheckWDTReset(void);
#endif

u32 NextValidImageCheck(void);

u32 DDRInitCheck(void);

/************************** Variable Definitions *****************************/
/*
 * Base Address for the Read Functionality for Image Processing
 */
u32 FlashReadBaseAddress = 0;
/*
 * Silicon Version
 */
u32 Silicon_Version;

/*
 * Boot Device flag
 */
u8 LinearBootDeviceFlag;

u32 PcapCtrlRegVal;

u8 SystemInitFlag;

extern ImageMoverType MoveImage;
extern XDcfg *DcfgInstPtr;
extern u8 BitstreamFlag;
#ifdef XPAR_PS7_QSPI_LINEAR_0_S_AXI_BASEADDR
extern u32 QspiFlashSize;
#endif
/*****************************************************************************/
/**
*
* This is the main function for the FSBL ROM code.
*
*
* @param	None.
*
* @return
*		- XST_SUCCESS to indicate success
*		- XST_FAILURE.to indicate failure
*
* @note
*
****************************************************************************/
int main(void)
{
	u32 BootModeRegister = 0;
	u32 HandoffAddress = 0;
	u32 Status = XST_SUCCESS;

#ifdef PEEP_CODE
	/*
	 * PEEP DDR initialization
	 */
	init_ddr();
#else
	/*
	 * PCW initialization for MIO,PLL,CLK and DDR
	 */
	ps7_init();
#endif

	/*
	 * Unlock SLCR for SLCR register write
	 */
	SlcrUnlock();

	/* If Performance measurement is required 
	 * then read the Global Timer value , Please note that the
	 * time taken for mio, clock and ddr initialisation
	 * done in the ps7_init function is not accounted in the FSBL
	 *
	 */
#ifdef FSBL_PERF
	XTime tCur = 0;
	FsblGetGlobalTime(tCur);
#endif

	/*
	 * Flush the Caches
	 */
	Xil_DCacheFlush();

	/*
	 * Disable Data Cache
	 */
	Xil_DCacheDisable();

	/*
	 * Register the Exception handlers
	 */
	
	/*
	 * Print the FSBL Banner
	 */
	fsbl_printf(DEBUG_GENERAL,"\n\rXilinx TDSDR First Stage Boot Loader \n\r");
	fsbl_printf(DEBUG_GENERAL,"Release %d.%d/%d.%d	%s-%s\r\n",
			SDK_RELEASE_VER, SDK_SUB_VER,
			SDK_RELEASE_YEAR, SDK_RELEASE_QUARTER,
			__DATE__,__TIME__);

#ifdef XPAR_PS7_DDR_0_S_AXI_BASEADDR
#endif

memtest_main();




	return Status;
}


