#!/bin/bash

##
# Start a GDB Debug Session to GSN-STM32
#  using ARM-USB-TINY-H / OpenOCD (already started).
##

ATTACH=0
FLASH=0

options='af'
while getopts $options option
do
  case $option in
    a )   ATTACH=1;;
    f )   FLASH=1;;
    * )   ;;
  esac
done

shift $(($OPTIND -1))

if [ "$ATTACH" = 0 ]; then
  if [ "$FLASH" = 0 ]; then
    echo "Usage: debug [-a | -f]"
    echo "  -a = attach to running image"
    echo "  -f = flash new image"
    exit
  fi
fi

# configuration for Application
PROJECT=autokiln-app
FIRST_PAGE=0
LAST_PAGE=63
HEXFILE=build/$PROJECT.hex


echo "***"
echo "PROJECT=$PROJECT"
echo "HEXFILE=$HEXFILE"
echo "***"

# ensure latest hex available
#  (make independently looks at .current-image)
make || exit 1

killall st-util

# try to reprogram
echo "**** Reset board now! ****"
false
while [ $? -ne 0 ]; do
  sleep 1
  ~/src/stlink/st-flash --reset erase
done
echo "**** Success! ****"

# start programmer driver
~/src/stlink/st-util &

# Configure GDB
rm .gdbinit
# connect to st-util
echo "target ext :4242" >> .gdbinit
if [ "$FLASH" = 1 ]; then
  echo "load" >> .gdbinit
  echo "continue" >> .gdbinit
fi

# launch GNU debugger
arm-none-eabi-gdb build/$PROJECT.elf

# use '-' command in gdb to go graphical
# we don't use -tui switch because if there are
#  startup errors we want to see them on the console

