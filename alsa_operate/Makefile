ARCH?=mips

TOPDIR=${PWD}

CFLAGS := -Wall

Q=@

ifeq ($(ARCH), arm)
CROSS_COMPILE=/opt/allwiner_compiler/external-toolchain/bin/arm-linux-gnueabi-
LIBS_PATH=/opt/yoko_libs

#libzbar
CFLAGS += -I${LIBS_PATH}/allwinner/zbar_qronly/include
LDFLAGS += -lzbar -L${LIBS_PATH}/allwinner/zbar_qronly/lib
else

ifeq ($(ARCH), mips)
CROSS_COMPILE=/opt/ingenic_compiler/mips-gcc472-glibc216/bin/mips-linux-gnu-
LIBS_PATH=/opt/yoko_libs/ingenic


else
$(error "Unknow ARCH")
endif #mips
endif #arm

CXX=${CROSS_COMPILE}g++
CC=${CROSS_COMPILE}gcc


ifdef FULL
CFLAGS_FULL:= -Wextra -Wfloat-equal -save-temps 
else
CFLAGS_FULL:=
endif

#CFLAGS += -I${PWD}/api

#libsound
CFLAGS += -I ${LIBS_PATH}/alsa-lib/.install/include/
LDFLAGS +=-L ${LIBS_PATH}/alsa-lib/.install/lib/

LDFLAGS += -lasound -lm

src := amixer.c volume_mapping.c

#src += misc/yokotime.cpp
# cmd.cpp 

objects=$(patsubst %.c,%.o, $(src))
target = amix

.PHONY:all
all:${target}

${target}:$(objects)
	$(Q)$(CC) $^ ${LDFLAGS} -o $@
	
%.o:%.c
	$(Q)$(CC) -c $^ ${CFLAGS} ${CFLAGS_FULL} -o $@

.PHONY:clean
clean:
	@rm -f  ${target}
	@find -name "*.o" -execdir rm {} \;
