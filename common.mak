CFLAGS = -std=c99 -m32 -nostdlib -nostdinc -g -O0 -Wall -Werror
CCFLAGS = -std=c++17 -fno-exceptions -fno-rtti -m32 -ffreestanding -nostdlib -g -O0 -Wall -Werror

CFILES = $(wildcard *.c)
CCFILES = $(wildcard *.cc)
SFILES = $(wildcard *.S) $(wildcard *.s)

OFILES = $(subst .cc,.o,$(CCFILES)) $(subst .c,.o,$(CFILES)) $(subst .s,.o,$(subst .S,.o,$(SFILES)))

# keep all files
.SECONDARY :

%.o :  Makefile %.c
	gcc -c -MD $(CFLAGS) $*.c

%.o :  Makefile %.cc
	g++ -c -MD $(CCFLAGS) $*.cc

%.o :  Makefile %.S
	gcc -MD -m32 -c $*.S

%.o :  Makefile %.s
	gcc -MD -m32 -c $*.s

%.bin : Makefile %
	objcopy -O binary $* $*.bin

%.img : Makefile %.bin
	dd if=$*.bin of=$*.img bs=512 conv=sync > /dev/null 2>&1

clean ::
	rm -f *.img
	rm -f *.bin
	rm -f *.o
	rm -f *.d

-include *.d
