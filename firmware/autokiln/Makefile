##############################################################################
# Build global options
# NOTE: Can be overridden externally.  # 
# Compiler options here.
ifeq ($(USE_OPT),)
  USE_OPT = -Og -g -fno-omit-frame-pointer -falign-functions=16
endif

# C specific options here (added to USE_OPT).
ifeq ($(USE_COPT),)
  USE_COPT = 
endif

# C++ specific options here (added to USE_OPT).
ifeq ($(USE_CPPOPT),)
  USE_CPPOPT = -fno-rtti -fno-exceptions -std=c++11 
endif

# Enable this if you want the linker to remove unused code and data
ifeq ($(USE_LINK_GC),)
  USE_LINK_GC = yes
endif

ifeq ($(USE_LDOPT),)
  USE_LDOPT = 
endif

ifeq ($(USE_LTO),)
  USE_LTO = yes
endif

# If enabled, this option allows to compile the application in THUMB mode.
ifeq ($(USE_THUMB),)
  USE_THUMB = yes
endif

# Enable this if you want to see the full log while compiling.
ifeq ($(USE_VERBOSE_COMPILE),)
  USE_VERBOSE_COMPILE = no
endif

ifeq ($(USE_SMART_BUILD),)
  USE_SMART_BUILD = yes
endif

#
# Build global options
##############################################################################

##############################################################################
# Architecture or project specific options
#

ifeq ($(USE_PROCESS_STACKSIZE),)
  USE_PROCESS_STACKSIZE = 0x200
endif

ifeq ($(USE_EXCEPTIONS_STACKSIZE),)
  USE_EXCEPTIONS_STACKSIZE = 0x400
endif

#
# Architecture or project specific options
##############################################################################

##############################################################################
# Project, sources and paths
#

# Define project name here
PROJECT = autokiln-app

# Imported source files and paths
CHIBIOS = ../libraries/ChibiOS
PROJLIBS = ../libraries
COMMON = ../../common
include $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC/mk/startup_stm32f0xx.mk
include $(CHIBIOS)/os/hal/hal.mk
include $(CHIBIOS)/os/hal/ports/STM32/STM32F0xx/platform.mk
include board.mk
include $(CHIBIOS)/os/hal/osal/rt/osal.mk
include $(CHIBIOS)/os/rt/rt.mk
include $(CHIBIOS)/os/rt/rt.mk
include $(CHIBIOS)/os/rt/ports/ARMCMx/compilers/GCC/mk/port_v6m.mk

# Define linker script file here
LDSCRIPT = linker.app.ld

# C sources that can be compiled in ARM or THUMB mode depending on the global
# setting.
#
# WARNING: Compile all project sources as C++ using a ".cpp" extension.
#  For an unknown reason, adding C sources which declare "const" data
#  can cause the ARM to fail booting (it gets stuck in bootloader).
#
CSRC = $(PORTSRC) \
       $(KERNSRC) \
       $(TESTSRC) \
       $(HALSRC) \
       $(PLATFORMSRC) \
       $(BOARDSRC) \
       $(STARTUPSRC) \
       $(OSALSRC) \
			 $(CHIBIOS)/os/hal/lib/streams/chprintf.c

# C++ sources that can be compiled in ARM or THUMB mode depending on the global
# setting.
CPPSRC = $(CHCPPSRC) \
				 main.cpp \
				 tinynew.cpp \
				 I2C.cpp \
				 $(PROJLIBS)/Sys/Sys.cpp \
				 Sys_Project.cpp \
				 $(PROJLIBS)/Watchdog/Watchdog.cpp \
				 Watchdog_Project.cpp \
				 $(PROJLIBS)/Os/Os_ChibiOS.cpp \
				 $(PROJLIBS)/Os/Os_Timer.cpp \
			   $(PROJLIBS)/base64/base64.cpp \
			   $(PROJLIBS)/EEPROM/EEPROM.cpp \
				 EEPROM_Project.cpp \
				 $(PROJLIBS)/FixEndian/FixEndian.cpp \
				 $(PROJLIBS)/DbgConsole/DbgConsole.cpp \
				 DbgConsole_Project.cpp \
				 LCD.cpp \
				 Input.cpp \
				 Humid.cpp \
				 ADS1234.cpp \
				 Menu.cpp \
				 NV.cpp

# C sources to be compiled in ARM mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
ACSRC =

# C++ sources to be compiled in ARM mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
ACPPSRC =

# C sources to be compiled in THUMB mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
TCSRC =

# C sources to be compiled in THUMB mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
TCPPSRC =

# List ASM source files here
ASMSRC = $(STARTUPASM) $(PORTASM) $(OSALASM)

INCDIR = $(STARTUPINC) $(PORTINC) $(KERNINC) $(TESTINC) \
         $(OSALINC) $(HALINC) $(PLATFORMINC) $(BOARDINC) \
				 $(CHIBIOS)/os/hal/lib/streams/ \
				 $(CHCPPINC) \
				 $(COMMON)/inc/ \
         $(CHIBIOS)/os/various \
				 $(PROJLIBS)/Os/ \
				 $(PROJLIBS)/Sys/ \
				 $(PROJLIBS)/Watchdog/ \
				 $(PROJLIBS)/EEPROM/ \
				 $(PROJLIBS)/FixEndian/ \
				 $(PROJLIBS)/DbgConsole/ \
				 $(PROJLIBS)/base64/

#
# Project, sources and paths
##############################################################################

##############################################################################
# Compiler settings
#

MCU  = cortex-m0

#TRGT = arm-elf-
TRGT = arm-none-eabi-
CC   = $(TRGT)gcc
CPPC = $(TRGT)g++
# Enable loading with g++ only if you need C++ runtime support.
# NOTE: You can use C++ even without C++ support if you are careful. C++
#       runtime support makes code size explode.
#LD   = $(TRGT)gcc
LD   = $(TRGT)g++
CP   = $(TRGT)objcopy
AS   = $(TRGT)gcc -x assembler-with-cpp
AR   = $(TRGT)ar
OD   = $(TRGT)objdump
SZ   = $(TRGT)size
HEX  = $(CP) -O ihex
BIN  = $(CP) -O binary

# ARM-specific options here
AOPT =

# THUMB-specific options here
TOPT = -mthumb -DTHUMB

# Define C warning options here
CWARN = -Wall -Wextra -Wstrict-prototypes

# Define C++ warning options here
CPPWARN = -Wall -Wextra

#
# Compiler settings
##############################################################################

##############################################################################
# Start of user section
#

# List all user C define here, like -D_DEBUG=1
UDEFS =

# Define ASM defines here
UADEFS =

# List all user directories here
UINCDIR =

# List the user directory to look for the libraries here
ULIBDIR =

# List all user libraries here
ULIBS = -lc -lrdimon

#
# End of user defines
##############################################################################

####
#

#install: all
#	size build/$(PROJECT).elf

#
####

include $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC/rules.mk

