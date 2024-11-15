# Copyright (c) 2023 Elliot Nunn
# Licensed under the MIT license

# Build the drivers (PPC and 68k) with:
#     PATH=Retro68-build/toolchain/bin make
all: classic ndrv build/test
classic: build/classic/declrom
ndrv: build/ndrv/ndrvloader

# Tell make not to delete the intermediate files
# (helpful when debugging this ususual build process)
.SECONDARY:

# Create subdirectories for the build to go into
$(shell mkdir -p build/classic build/ndrv)

# The supported Virtio devices for each Mac platform (see device-9p.c etc)
#     "CLASSIC" means a 68k DRVR for a NuBus device under qemu-system-m68k
#     "NDRV" means a PowerPC NDRV for a PCI device under qemu-system-ppc
DEVICES_CLASSIC = block 9p input
DEVICES_NDRV = block 9p input

# And these are the C files that each device-*.c depends on (some are arch-specific)
SUPPORT := $(filter-out device-%.c,$(wildcard *.c))
SUPPORT := $(filter-out slotexec-%.c,$(SUPPORT)) # special files
SUPPORT := $(filter-out ndrvloader.c,$(SUPPORT)) # special file
SUPPORT_CLASSIC = $(filter-out %-ndrv.c,$(SUPPORT))
SUPPORT_NDRV = $(filter-out %-classic.c,$(SUPPORT))

# Settle a dispute between MacTypes.h and stdbool.h
CDEFS = -DTYPE_BOOL -Dbool=_Bool -Dtrue=1 -Dfalse=0 -Wno-scalar-storage-order

# Uncomment this to generate a CPU time profile for the 9p driver
# To view it, run "./9profile.sh | flamegraph.pl > fg.svg"
# INSTRUMENT = -DINSTRUMENT=1 -finstrument-functions

############################# CLASSIC DRVR #############################

INTERFACEONLY = $(shell m68k-apple-macos-gcc -print-file-name=libInterface.a)
ALLLIBS = $(shell for x in libInterface.a libgcov.a libg.a libm.a libstdc++.a libgcc.a libc.a; do m68k-apple-macos-gcc -print-file-name=$$x; done)

# The classic drivers are linked together into one "card declaration ROM":
#     qemu-system-m68k -device nubus-virtio-mmio,romfile=build/classic/declrom
# This ROM incorporates the actual DRVRs and a few "slotexec" functions.
SLOTEXECS = $(patsubst slotexec-%.c,%,$(wildcard slotexec-*.c))
build/classic/declrom: declrom.s \
		$(patsubst %,build/classic/drvr-%.elf,$(DEVICES_CLASSIC)) \
		$(patsubst %,build/classic/slotexec-%,$(SLOTEXECS))
	m68k-apple-macos-as -o build/classic/declrom.o declrom.s
	m68k-apple-macos-ld -o build/classic/declrom.elf build/classic/declrom.o
	m68k-apple-macos-objcopy -O binary -j .text build/classic/declrom.elf $@
	python3 scripts/calculatecrc.py $@

# The "slotexec" helper functions are also needed in the declaration ROM,
# but are built using different compiler options (PC-relative addressing FYI)
build/classic/slotexec-%.o: slotexec-%.c
	m68k-apple-macos-gcc $(CDEFS) -c -m68040 -Os -mpcrel -o $@ $^

# Wrap an "sExecBlock" header around the slotexec code using a linker script
build/classic/slotexec-%.elf: slotexec.lds build/classic/slotexec-%.o
	m68k-apple-macos-ld --no-warn-rwx-segments -o $@ --script $^ $(ALLLIBS)

# Extract the "sExecBlock" from an ELF, ready for inclusion in the decl ROM
build/classic/slotexec-%: build/classic/slotexec-%.elf
	m68k-apple-macos-objcopy -O binary -j .exec $^ $@

# Compile the DRVR code files (slotexec code has different compiler options)
build/classic/%.o: %.c
	m68k-apple-macos-gcc $(CDEFS) $(INSTRUMENT) -c -m68040 -Os -msep-data -ffunction-sections -fdata-sections -o $@ $<

# Link each driver into an ELF, which will be DRVRised by slotexec-drvrload.c
# This code uses A5-refs (-msep-data) so we cannot use the Retro68 libc, but Interfaces are fine
build/classic/drvr-%.elf: drvr.lds build/classic/drvr.o build/classic/jumpglue.o build/classic/device-%.o $(patsubst %.c,build/classic/%.o,$(SUPPORT_CLASSIC)) $(wildcard  a5libs/*.a)
	m68k-apple-macos-ld.real -Ttext-segment 0xcd790000 -e drvrROMEntry --gc-sections -o $@ --script $^ $(INTERFACEONLY)

# The DRVR has some assembly code to call through to C
build/classic/%.o: %.s
	m68k-apple-macos-as -o $@ $^

############################# POWERPC NDRV #############################

# Open Firmware compatible program to load our drivers into the device tree
# (These section addresses match the Mac OS Trampoline loader, so they're safe.)
build/ndrv/ndrvloader: ndrvloader.s ndrvloader.c build/ndrv/allndrv
	powerpc-apple-macos-gcc $(CDEFS) -Os -e entrytvec -Wl,--section-start=.data=0x100000 -Wl,--section-start=.text=0x200000 -o $@ ndrvloader.s ndrvloader.c

# Glom all the NDRVs together: the loader shim can unpick them
build/ndrv/allndrv: $(patsubst %,build/ndrv/ndrv-%,$(DEVICES_NDRV))
	cat $^ >$@

build/ndrv/%.o: %.c
	powerpc-apple-macos-gcc $(CDEFS) -c -Os -ffunction-sections -fdata-sections -o $@ $<

NDRVSTATICLIBS = $(shell for x in libStdCLib.a libDriverServicesLib.a libNameRegistryLib.a libPCILib.a libVideoServicesLib.a libInterfaceLib.a libControlsLib.a libgcc.a libc.a; do powerpc-apple-macos-gcc -print-file-name=$$x; done)
build/ndrv/ndrv-%.so: ndrv.lds build/ndrv/device-%.o $(patsubst %.c,build/ndrv/%.o,$(SUPPORT_NDRV))
	powerpc-apple-macos-ld --gc-sections --gc-keep-exported -bE:ndrv.exp -o $@ --script $^ $(NDRVSTATICLIBS)

build/ndrv/ndrv-%: build/ndrv/ndrv-%.so
	MakePEF -o $@ $^

############################### TEST APP ###############################

build/test: $(wildcard test/*.c)
	m68k-apple-macos-gcc $(CDEFS) -o $@.dsk $^
	DumpHFS $@.dsk build/ || echo temporary hack pending implementation of AppleDouble
