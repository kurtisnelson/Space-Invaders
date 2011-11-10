################################################################################
# These are variables for the GBA toolchain build
# You can add others if you wish to
# NOTICE:  Your name here or you will lose points
################################################################################

# The name of your desired GBA game
# This should be a just a name i.e MyFirstGBAGame
# No SPACES AFTER THE NAME.
PROGNAME = SpaceInvaders

# The object files you want to compile into your program
# This should be a space (SPACE!) separated list of .o files
OFILES = lib/video.o lib/dma.o images/paused.o images/title.o images/alien.o images/player.o images/bullet.o images/gameover.o bullet.o player.o alien.o spaceinvaders.o

# The header files you have created.
# This is necessary to determine when to recompile for files.
# This should be a space (SPACE!) separated list of .h files
HFILES = lib/gba.h lib/input.h lib/color.h lib/video.h lib/dma.h images/paused.h images/title.h images/alien.h images/player.h images/bullet.h images/gameover.h bullet.h player.h alien.h spaceinvaders.h

# The flags to run the vba program with
# for a list of options run /usr/local/cs2110-tools/bin/vbam
# Most notable ones are -f0 -f1 -f13 -f15
# -f0  : Stretch 1x 
# -f1  : Stretch 2x
# -f13 : Stretch 3x
# -f15 : Stretch 4x
VBAOPT	 = -f1

################################################################################
# These are various settings used to make the GBA toolchain work
# DO NOT EDIT BELOW.
################################################################################

TOOLDIR  = /usr/local/cs2110-tools
CFLAGS   = -Wall -Werror -std=c99 -pedantic -O2
CFLAGS  += -mthumb-interwork -mlong-calls -nostartfiles
LDFLAGS = -L $(TOOLDIR)/lib \
		  -L $(TOOLDIR)/lib/gcc/arm-thumb-eabi/4.4.1/thumb \
		  -L $(TOOLDIR)/arm-thumb-eabi/lib \
		  --script $(TOOLDIR)/arm-thumb-eabi/lib/arm-gba.ld
CC      = $(TOOLDIR)/bin/arm-thumb-eabi-gcc
AS      = $(TOOLDIR)/bin/arm-thumb-eabi-as
LD      = $(TOOLDIR)/bin/arm-thumb-eabi-ld
OBJCOPY = $(TOOLDIR)/bin/arm-thumb-eabi-objcopy
GDB     = $(TOOLDIR)/bin/arm-thumb-eabi-gdb
GBADEPS = gbadeps
CFILES  = $(OFILES:.o=.c)

################################################################################
# These are the targets for the GBA build system
################################################################################

all: $(GBADEPS) $(PROGNAME).gba

$(PROGNAME).gba: $(PROGNAME).elf
	@echo "Linking files together to create $(PROGNAME).gba"
	@$(OBJCOPY) -O binary $(PROGNAME).elf $(PROGNAME).gba

$(PROGNAME).elf: crt0.o $(OFILES)
	@$(LD) $(LDFLAGS) -o $(PROGNAME).elf $^ -lgcc -lc -lgcc

crt0.o: $(TOOLDIR)/arm-thumb-eabi/lib/crt0.s
	@$(AS) -mthumb-interwork $^ -o crt0.o

%.o: %.c
	@echo "[COMPILE] Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Removing all generated files"
	@rm -f *.o *.elf *.gba $(GBADEPS)

vba: $(PROGNAME).gba
	@echo "[RUN] Running Emulator"
	@$(TOOLDIR)/bin/vbam $(VBAOPT) $(PROGNAME).gba > /dev/null

rebuild: clean $(PROGNAME).gba

rebuildvba: clean vba

$(GBADEPS): $(CFILES) $(HFILES)
	@$(CC) $(CFLAGS) -MM $(CFILES) > $(GBADEPS)

-include $(GBADEPS)
