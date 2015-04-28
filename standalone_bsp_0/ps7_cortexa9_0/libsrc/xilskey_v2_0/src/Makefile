####################################/-*-Makefile-*- 
#
# Copyright (c) 2013-2014 Xilinx, Inc.  All rights reserved.
#
# Xilinx, Inc.
#
# XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A 
# COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
# ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR 
# STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
# IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE 
# FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.  
# XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO 
# THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO 
# ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE 
# FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY 
# AND FITNESS FOR A PARTICULAR PURPOSE.
# 
######################################################

COMPILER=
ARCHIVER=
CP=cp
COMPILER_FLAGS=
EXTRA_COMPILER_FLAGS=

RELEASEDIR=../../../lib
INCLUDEDIR=../../../include
INCLUDES=-I${INCLUDEDIR} 
SKEY_DIR = .

LIB_SRCS = $(SKEY_DIR)/xilskey_eps.c \
          $(SKEY_DIR)/xilskey_epl.c \
          $(SKEY_DIR)/xilskey_utils.c \
          $(SKEY_DIR)/xilskey_jslib.c \
          $(SKEY_DIR)/xilskey_jscmd.c \
          $(SKEY_DIR)/xilskey_bbram.c
          
# create ISF_SRCS based on configured options

SKEY_SRCS = $(LIB_SRCS)

SKEY_OBJS = $(SKEY_SRCS:%.c=%.o)
          

EXPORT_INCLUDE_FILES = $(SKEY_DIR)/include/xilskey_eps.h \
			$(SKEY_DIR)/include/xilskey_epl.h \
			$(SKEY_DIR)/include/xilskey_utils.h \
			$(SKEY_DIR)/include/xilskey_bbram.h 

			
libs: libxilskey.a
	cp libxilskey.a $(RELEASEDIR)
	make clean

include: 
	@for i in $(EXPORT_INCLUDE_FILES); do \
	echo ${CP} -r $$i ${INCLUDEDIR}; \
	${CP} -r $$i ${INCLUDEDIR}; \
	done

clean:
	rm -rf obj/*.o	
	rmdir obj
	rm libxilskey.a


libxilskey.a: obj_dir print_msg_isf_base $(SKEY_OBJS) 
	@echo "Creating archive $@"
	$(ARCHIVER) rc $@ obj/*.o

obj_dir:
	mkdir obj

print_msg_isf_base:
	@echo "Compiling Xilinx Secure Key Library..."

.c.o:
	$(COMPILER) $(COMPILER_FLAGS) $(EXTRA_COMPILER_FLAGS) $(INCLUDES) -c $< -o obj/$(@F)
