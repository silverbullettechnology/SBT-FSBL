/*
 * Copyright (c) 2013-2014 Xilinx, Inc.  All rights reserved.
 *
 *                 XILINX CONFIDENTIAL PROPERTY
 * This   document  contains  proprietary information  which   is
 * protected by  copyright. All rights  are reserved. No  part of
 * this  document may be photocopied, reproduced or translated to
 * another  program  language  without  prior written  consent of
 * XILINX Inc., San Jose, CA. 95124
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef XILSKEY_JTAG_H
#define XILSKEY_JTAG_H

#include "xil_types.h"

void JtagInitGpio();
void GpioConfig(volatile unsigned long *addr, unsigned long mask, unsigned long val);
int JtagServerInit(XilSKey_EPl *PlInstancePtr);
int JtagValidateMioPins(void);
void JtagWrite(unsigned char row, unsigned char bit);
void JtagRead(unsigned char row, unsigned int * row_data, unsigned char marginOption);

#endif /*XILSKEY_JTAG_H*/
