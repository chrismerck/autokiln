EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:custom
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 7
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L NHD-C0220BiZ-FSW-FBW-3VM U?
U 1 1 550679C4
P 2550 2750
F 0 "U?" H 2550 3150 60  0000 C CNN
F 1 "NHD-C0220BiZ-FSW-FBW-3VM" H 2550 3050 60  0000 C CNN
F 2 "" H 2550 3150 60  0000 C CNN
F 3 "" H 2550 3150 60  0000 C CNN
	1    2550 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 3050 3500 3050
Text Label 3500 3050 2    60   ~ 0
SDA
Wire Wire Line
	3100 2850 3500 2850
Text Label 3500 2850 2    60   ~ 0
SCL
Wire Wire Line
	3100 2650 3500 2650
Text Label 3500 2650 2    60   ~ 0
LCD_RST
Wire Wire Line
	3100 3250 3500 3250
$Comp
L GND #PWR?
U 1 1 55067AC6
P 3500 3250
F 0 "#PWR?" H 3500 3000 60  0001 C CNN
F 1 "GND" H 3500 3100 60  0000 C CNN
F 2 "" H 3500 3250 60  0000 C CNN
F 3 "" H 3500 3250 60  0000 C CNN
	1    3500 3250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3100 3450 4000 3450
Wire Wire Line
	4000 3450 4000 3250
$Comp
L VCC #PWR?
U 1 1 55067AEC
P 4000 3250
F 0 "#PWR?" H 4000 3100 60  0001 C CNN
F 1 "VCC" H 4000 3400 60  0000 C CNN
F 2 "" H 4000 3250 60  0000 C CNN
F 3 "" H 4000 3250 60  0000 C CNN
	1    4000 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 3650 3750 3650
$Comp
L C C?
U 1 1 55067B0B
P 3450 3850
F 0 "C?" V 3550 3950 50  0000 L CNN
F 1 "1uF" V 3550 3650 50  0000 L CNN
F 2 "" H 3488 3700 30  0000 C CNN
F 3 "" H 3450 3850 60  0000 C CNN
	1    3450 3850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3100 3850 3300 3850
Wire Wire Line
	3600 3850 3750 3850
Wire Wire Line
	3750 3850 3750 4050
Wire Wire Line
	3750 4050 3100 4050
$Comp
L C C?
U 1 1 55067C36
P 3900 3650
F 0 "C?" V 4000 3750 50  0000 L CNN
F 1 "1uF" V 4000 3450 50  0000 L CNN
F 2 "" H 3938 3500 30  0000 C CNN
F 3 "" H 3900 3650 60  0000 C CNN
	1    3900 3650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4050 3650 4150 3650
Wire Wire Line
	4150 3650 4150 3800
$Comp
L GND #PWR?
U 1 1 55067C8A
P 4150 3800
F 0 "#PWR?" H 4150 3550 60  0001 C CNN
F 1 "GND" H 4150 3650 60  0000 C CNN
F 2 "" H 4150 3800 60  0000 C CNN
F 3 "" H 4150 3800 60  0000 C CNN
	1    4150 3800
	1    0    0    -1  
$EndComp
Text Notes 1150 3100 0    60   ~ 0
What to do with A/K?
Text Notes 2450 2050 0    60   ~ 0
LCD
$EndSCHEMATC
