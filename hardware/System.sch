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
LIBS:autokiln-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 6
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
L STM32F070CBT6 U2
U 1 1 5505BC8C
P 6350 2800
F 0 "U2" H 5700 4750 60  0000 C CNN
F 1 "STM32F070CBT6" H 6000 4650 60  0000 C CNN
F 2 "" H 6350 2800 60  0000 C CNN
F 3 "" H 6350 2800 60  0000 C CNN
	1    6350 2800
	1    0    0    -1  
$EndComp
$Comp
L 24LC512 U3
U 1 1 5505BCD0
P 9700 5800
F 0 "U3" H 9550 6250 60  0000 C CNN
F 1 "24LC512" H 9700 6150 60  0000 C CNN
F 2 "" H 9700 5800 60  0000 C CNN
F 3 "" H 9700 5800 60  0000 C CNN
	1    9700 5800
	1    0    0    -1  
$EndComp
Text Notes 6400 850  0    60   ~ 0
MICROCONTROLLER
Text Notes 9500 5200 0    60   ~ 0
EEPROM
Text GLabel 10900 750  2    60   BiDi ~ 0
SDA
Text Label 9000 3300 2    60   ~ 0
DBG_TX
Text Label 9000 3450 2    60   ~ 0
DBG_RX
Text GLabel 10900 600  2    60   Output ~ 0
SCL
Text Label 10550 600  0    60   ~ 0
SCL
Text Label 10550 750  0    60   ~ 0
SDA
Text Label 9000 3650 2    60   ~ 0
SCL
Text Label 9000 3800 2    60   ~ 0
SDA
$Comp
L CONN_01X04 P1
U 1 1 5505C6C3
P 10400 3200
F 0 "P1" H 10400 3450 50  0000 C CNN
F 1 "DEBUG" V 10500 3200 50  0000 C CNN
F 2 "" H 10400 3200 60  0000 C CNN
F 3 "" H 10400 3200 60  0000 C CNN
	1    10400 3200
	1    0    0    -1  
$EndComp
Text Label 9850 3050 0    60   ~ 0
GND
Text Label 9850 3150 0    60   ~ 0
DBG_TX
Text Label 9850 3250 0    60   ~ 0
DBG_RX
NoConn ~ 9850 3350
$Comp
L VCC #PWR17
U 1 1 5505CA3C
P 10450 5500
F 0 "#PWR17" H 10450 5350 60  0001 C CNN
F 1 "VCC" H 10450 5650 60  0000 C CNN
F 2 "" H 10450 5500 60  0000 C CNN
F 3 "" H 10450 5500 60  0000 C CNN
	1    10450 5500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR12
U 1 1 5505CA84
P 9150 6150
F 0 "#PWR12" H 9150 5900 60  0001 C CNN
F 1 "GND" H 9150 6000 60  0000 C CNN
F 2 "" H 9150 6150 60  0000 C CNN
F 3 "" H 9150 6150 60  0000 C CNN
	1    9150 6150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR16
U 1 1 5505CAEC
P 10350 5750
F 0 "#PWR16" H 10350 5500 60  0001 C CNN
F 1 "GND" V 10350 5550 60  0000 C CNN
F 2 "" H 10350 5750 60  0000 C CNN
F 3 "" H 10350 5750 60  0000 C CNN
	1    10350 5750
	0    -1   -1   0   
$EndComp
Text Label 10500 5900 2    60   ~ 0
SCL
Text Label 10500 6050 2    60   ~ 0
SDA
Text Notes 9750 5350 0    60   ~ 0
addr=0x50
$Comp
L VCC #PWR6
U 1 1 5505CE53
P 4800 1050
F 0 "#PWR6" H 4800 900 60  0001 C CNN
F 1 "VCC" H 4800 1200 60  0000 C CNN
F 2 "" H 4800 1050 60  0000 C CNN
F 3 "" H 4800 1050 60  0000 C CNN
	1    4800 1050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR7
U 1 1 5505CE85
P 4800 2350
F 0 "#PWR7" H 4800 2100 60  0001 C CNN
F 1 "GND" H 4800 2200 60  0000 C CNN
F 2 "" H 4800 2350 60  0000 C CNN
F 3 "" H 4800 2350 60  0000 C CNN
	1    4800 2350
	1    0    0    -1  
$EndComp
$Comp
L Crystal X1
U 1 1 5505D167
P 10250 4450
F 0 "X1" V 10200 4650 50  0000 C CNN
F 1 "32kHz" V 10300 4700 50  0000 C CNN
F 2 "" H 10250 4450 60  0000 C CNN
F 3 "" H 10250 4450 60  0000 C CNN
	1    10250 4450
	0    1    1    0   
$EndComp
$Comp
L C C6
U 1 1 5505D356
P 9800 4250
F 0 "C6" V 9900 4350 50  0000 L CNN
F 1 "10pF" V 9900 4000 50  0000 L CNN
F 2 "" H 9838 4100 30  0000 C CNN
F 3 "" H 9800 4250 60  0000 C CNN
	1    9800 4250
	0    -1   1    0   
$EndComp
$Comp
L C C7
U 1 1 5505D710
P 9800 4650
F 0 "C7" V 9900 4750 50  0000 L CNN
F 1 "10pF" V 9900 4400 50  0000 L CNN
F 2 "" H 9838 4500 30  0000 C CNN
F 3 "" H 9800 4650 60  0000 C CNN
	1    9800 4650
	0    -1   1    0   
$EndComp
$Comp
L GND #PWR13
U 1 1 5505D806
P 9550 4800
F 0 "#PWR13" H 9550 4550 60  0001 C CNN
F 1 "GND" H 9550 4650 60  0000 C CNN
F 2 "" H 9550 4800 60  0000 C CNN
F 3 "" H 9550 4800 60  0000 C CNN
	1    9550 4800
	1    0    0    -1  
$EndComp
Text Label 10900 4250 2    60   ~ 0
OSC32_IN
Text Label 10900 4650 2    60   ~ 0
OSC32_OUT
Text Label 4750 2700 0    60   ~ 0
OSC32_IN
Text Label 4750 2850 0    60   ~ 0
OSC32_OUT
Text Notes 10100 4050 0    60   ~ 0
RTC
Text Notes 9900 2850 0    60   ~ 0
DEBUG CONSOLE
$Comp
L 318-ENC130175F-12PS SW4
U 1 1 550685A0
P 5300 7100
F 0 "SW4" H 5300 7500 60  0000 C CNN
F 1 "318-ENC130175F-12PS" H 5300 7400 60  0000 C CNN
F 2 "" H 5300 7500 60  0000 C CNN
F 3 "" H 5300 7500 60  0000 C CNN
	1    5300 7100
	1    0    0    -1  
$EndComp
Text Label 6300 7000 2    60   ~ 0
ENC_B
Text Label 6300 7200 2    60   ~ 0
ENC_C
Text Label 6300 7400 2    60   ~ 0
ENC_A
$Comp
L GND #PWR5
U 1 1 55069BEC
P 4550 7500
F 0 "#PWR5" H 4550 7250 60  0001 C CNN
F 1 "GND" H 4550 7350 60  0000 C CNN
F 2 "" H 4550 7500 60  0000 C CNN
F 3 "" H 4550 7500 60  0000 C CNN
	1    4550 7500
	1    0    0    -1  
$EndComp
Text Label 4000 7000 0    60   ~ 0
ENC_CLICK
Text Notes 5200 6600 0    60   ~ 0
KNOB
$Comp
L CONN_01X06 P2
U 1 1 5506BFB8
P 10600 2000
F 0 "P2" H 10600 2350 50  0000 C CNN
F 1 "SWD" H 10750 2000 50  0000 C CNN
F 2 "" H 10600 2000 60  0000 C CNN
F 3 "" H 10600 2000 60  0000 C CNN
	1    10600 2000
	1    0    0    -1  
$EndComp
Text Notes 10450 1550 0    60   ~ 0
SWD
$Comp
L VCC #PWR14
U 1 1 5506C4D9
P 9800 1700
F 0 "#PWR14" H 9800 1550 60  0001 C CNN
F 1 "VCC" H 9800 1850 60  0000 C CNN
F 2 "" H 9800 1700 60  0000 C CNN
F 3 "" H 9800 1700 60  0000 C CNN
	1    9800 1700
	1    0    0    -1  
$EndComp
Text Label 9800 1850 0    60   ~ 0
SWCLK
$Comp
L GND #PWR15
U 1 1 5506C66B
P 9800 1950
F 0 "#PWR15" H 9800 1700 60  0001 C CNN
F 1 "GND" H 9800 1800 60  0000 C CNN
F 2 "" H 9800 1950 60  0000 C CNN
F 3 "" H 9800 1950 60  0000 C CNN
	1    9800 1950
	0    1    1    0   
$EndComp
Text Label 9800 2050 0    60   ~ 0
SWDIO
Text Label 9800 2150 0    60   ~ 0
NRST
NoConn ~ 10400 2250
Text Label 9000 2050 2    60   ~ 0
SWCLK
Text Label 9000 1900 2    60   ~ 0
SWDIO
$Comp
L GND #PWR8
U 1 1 5506D1DB
P 5050 3450
F 0 "#PWR8" H 5050 3200 60  0001 C CNN
F 1 "GND" V 5050 3250 60  0000 C CNN
F 2 "" H 5050 3450 60  0000 C CNN
F 3 "" H 5050 3450 60  0000 C CNN
	1    5050 3450
	0    1    1    0   
$EndComp
Text Label 4750 3300 0    60   ~ 0
NRST
Text GLabel 8400 1150 2    60   BiDi ~ 0
HUMID_DATA1
Text GLabel 8400 1300 2    60   BiDi ~ 0
BAROM_SDA
Text GLabel 8400 1450 2    60   BiDi ~ 0
BAROM_SCL
Text GLabel 8450 4100 2    60   BiDi ~ 0
HEATER
Text GLabel 8450 4250 2    60   BiDi ~ 0
DEHUM
Text GLabel 8450 4400 2    60   BiDi ~ 0
FAN
Text GLabel 8450 4550 2    60   BiDi ~ 0
VACUUM
Text GLabel 8450 4700 2    60   BiDi ~ 0
STEAM
Text Label 4750 3650 0    60   ~ 0
LCD_RS
Text Label 9000 2850 2    60   ~ 0
ENC_A
Text Label 9000 3000 2    60   ~ 0
ENC_C
Text Label 9000 3150 2    60   ~ 0
ENC_A
Text Label 9000 2700 2    60   ~ 0
ENC_CLICK
$Comp
L SW_PUSH SW1
U 1 1 5507050B
P 5300 5400
F 0 "SW1" H 5450 5510 50  0000 C CNN
F 1 "MENU" H 5300 5320 50  0000 C CNN
F 2 "" H 5300 5400 60  0000 C CNN
F 3 "" H 5300 5400 60  0000 C CNN
	1    5300 5400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR9
U 1 1 55070909
P 5700 5400
F 0 "#PWR9" H 5700 5150 60  0001 C CNN
F 1 "GND" V 5700 5200 60  0000 C CNN
F 2 "" H 5700 5400 60  0000 C CNN
F 3 "" H 5700 5400 60  0000 C CNN
	1    5700 5400
	0    -1   -1   0   
$EndComp
Text Label 4700 5400 0    60   ~ 0
MENU
$Comp
L SW_PUSH SW2
U 1 1 55070A62
P 5300 5700
F 0 "SW2" H 5450 5810 50  0000 C CNN
F 1 "RESET" H 5300 5620 50  0000 C CNN
F 2 "" H 5300 5700 60  0000 C CNN
F 3 "" H 5300 5700 60  0000 C CNN
	1    5300 5700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR10
U 1 1 55070A6A
P 5700 5700
F 0 "#PWR10" H 5700 5450 60  0001 C CNN
F 1 "GND" V 5700 5500 60  0000 C CNN
F 2 "" H 5700 5700 60  0000 C CNN
F 3 "" H 5700 5700 60  0000 C CNN
	1    5700 5700
	0    -1   -1   0   
$EndComp
Text Label 4700 5700 0    60   ~ 0
RESET
$Comp
L SW_PUSH SW3
U 1 1 55070B06
P 5300 6000
F 0 "SW3" H 5450 6110 50  0000 C CNN
F 1 "MANUAL" H 5300 5920 50  0000 C CNN
F 2 "" H 5300 6000 60  0000 C CNN
F 3 "" H 5300 6000 60  0000 C CNN
	1    5300 6000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR11
U 1 1 55070B0E
P 5700 6000
F 0 "#PWR11" H 5700 5750 60  0001 C CNN
F 1 "GND" V 5700 5800 60  0000 C CNN
F 2 "" H 5700 6000 60  0000 C CNN
F 3 "" H 5700 6000 60  0000 C CNN
	1    5700 6000
	0    -1   -1   0   
$EndComp
Text Label 4700 6000 0    60   ~ 0
MANUAL
Text Label 5000 2550 0    60   ~ 0
MENU
Text Label 4750 3000 0    60   ~ 0
RESET
Text Label 4750 3150 0    60   ~ 0
MANUAL
Text Notes 5100 5150 0    60   ~ 0
BUTTONS
$Comp
L NHD-0420AZ-FL-YBW-33V3 U1
U 1 1 550C7F12
P 1550 2900
F 0 "U1" H 1550 3300 60  0000 C CNN
F 1 "NHD-0420AZ-FL-YBW-33V3" H 1550 3200 60  0000 C CNN
F 2 "" H 1550 3300 60  0000 C CNN
F 3 "" H 1550 3300 60  0000 C CNN
	1    1550 2900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR1
U 1 1 550C813D
P 2150 2800
F 0 "#PWR1" H 2150 2550 60  0001 C CNN
F 1 "GND" V 2150 2600 60  0000 C CNN
F 2 "" H 2150 2800 60  0000 C CNN
F 3 "" H 2150 2800 60  0000 C CNN
	1    2150 2800
	0    -1   -1   0   
$EndComp
$Comp
L VCC #PWR2
U 1 1 550C8509
P 2550 2850
F 0 "#PWR2" H 2550 2700 60  0001 C CNN
F 1 "VCC" H 2550 3000 60  0000 C CNN
F 2 "" H 2550 2850 60  0000 C CNN
F 3 "" H 2550 2850 60  0000 C CNN
	1    2550 2850
	1    0    0    -1  
$EndComp
$Comp
L POT RV1
U 1 1 550C8A80
P 2850 3200
F 0 "RV1" V 2850 3050 50  0000 C CNN
F 1 "10K" H 2850 3200 50  0000 C CNN
F 2 "" H 2850 3200 60  0000 C CNN
F 3 "" H 2850 3200 60  0000 C CNN
	1    2850 3200
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR3
U 1 1 550C8C93
P 2850 3550
F 0 "#PWR3" H 2850 3300 60  0001 C CNN
F 1 "GND" H 2850 3400 60  0000 C CNN
F 2 "" H 2850 3550 60  0000 C CNN
F 3 "" H 2850 3550 60  0000 C CNN
	1    2850 3550
	1    0    0    -1  
$EndComp
Text Label 2100 3400 0    60   ~ 0
LCD_RS
Text Label 2100 3600 0    60   ~ 0
LCD_RW
Text Label 2100 3800 0    60   ~ 0
LCD_E
NoConn ~ 2000 4000
NoConn ~ 2000 4200
NoConn ~ 2000 4400
NoConn ~ 2000 4600
Text Label 2100 4800 0    60   ~ 0
LCD_DB4
Text Label 2100 5000 0    60   ~ 0
LCD_DB5
Text Label 2100 5200 0    60   ~ 0
LCD_DB6
Text Label 2100 5400 0    60   ~ 0
LCD_DB7
$Comp
L R R1
U 1 1 550C989C
P 2350 5800
F 0 "R1" V 2430 5800 50  0000 C CNN
F 1 "3" V 2350 5800 50  0000 C CNN
F 2 "" V 2280 5800 30  0000 C CNN
F 3 "" H 2350 5800 30  0000 C CNN
	1    2350 5800
	0    1    1    0   
$EndComp
Text Notes 750  5650 0    60   ~ 0
Backlight\n300mA, 3.0V
Text Notes 1150 2350 0    60   ~ 0
20x4 Character LCD
Text Label 4750 3800 0    60   ~ 0
LCD_RW
Text Label 4750 3950 0    60   ~ 0
LCD_E
Text Label 4750 4250 0    60   ~ 0
LCD_DB4
Text Label 4750 4400 0    60   ~ 0
LCD_DB5
Text Label 4750 4550 0    60   ~ 0
LCD_DB6
Text Label 4750 4700 0    60   ~ 0
LCD_DB7
Text GLabel 8450 1600 2    60   Output ~ 0
ADC_A1
Text GLabel 8450 1750 2    60   Output ~ 0
ADC_A0
Text GLabel 8500 2400 2    60   Input ~ 0
ADC_DOUT
Text GLabel 8500 2550 2    60   Input ~ 0
ADC_SCLK
Text GLabel 8450 3950 2    60   Output ~ 0
ADC_PDWN
Text GLabel 8450 2200 2    60   BiDi ~ 0
HUMID_DATA2
$Comp
L C C5
U 1 1 550DB5DB
P 4600 1350
F 0 "C5" H 4700 1450 50  0000 L CNN
F 1 "100nF" H 4700 1250 50  0000 L CNN
F 2 "" H 4638 1200 30  0000 C CNN
F 3 "" H 4600 1350 60  0000 C CNN
	1    4600 1350
	-1   0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 550DB77E
P 4150 1350
F 0 "C3" H 4250 1450 50  0000 L CNN
F 1 "100nF" H 4250 1250 50  0000 L CNN
F 2 "" H 4188 1200 30  0000 C CNN
F 3 "" H 4150 1350 60  0000 C CNN
	1    4150 1350
	-1   0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 550DB7BA
P 3700 1350
F 0 "C2" H 3800 1450 50  0000 L CNN
F 1 "100nF" H 3800 1250 50  0000 L CNN
F 2 "" H 3738 1200 30  0000 C CNN
F 3 "" H 3700 1350 60  0000 C CNN
	1    3700 1350
	-1   0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 550DB80D
P 3300 1350
F 0 "C1" H 3400 1450 50  0000 L CNN
F 1 "100nF" H 3400 1250 50  0000 L CNN
F 2 "" H 3338 1200 30  0000 C CNN
F 3 "" H 3300 1350 60  0000 C CNN
	1    3300 1350
	-1   0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 550DBB74
P 4500 1950
F 0 "C4" H 4600 2050 50  0000 L CNN
F 1 "4u7" H 4600 1850 50  0000 L CNN
F 2 "" H 4538 1800 30  0000 C CNN
F 3 "" H 4500 1950 60  0000 C CNN
	1    4500 1950
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8300 3650 9000 3650
Wire Wire Line
	8300 3800 9000 3800
Wire Wire Line
	8300 3450 9000 3450
Wire Wire Line
	8300 3300 9000 3300
Wire Wire Line
	10900 600  10550 600 
Wire Wire Line
	10900 750  10550 750 
Wire Wire Line
	10200 3050 9850 3050
Wire Wire Line
	10200 3150 9850 3150
Wire Wire Line
	9850 3250 10200 3250
Wire Wire Line
	9850 3350 10200 3350
Wire Wire Line
	10250 5600 10900 5600
Wire Wire Line
	10450 5600 10450 5500
Wire Wire Line
	9150 5600 9150 6150
Connection ~ 9150 5750
Connection ~ 9150 5900
Connection ~ 9150 6050
Wire Wire Line
	10250 5750 10350 5750
Wire Wire Line
	10250 5900 10500 5900
Wire Wire Line
	10250 6050 10500 6050
Wire Wire Line
	3300 1150 5300 1150
Wire Wire Line
	4800 1150 4800 1050
Wire Wire Line
	5300 1300 4800 1300
Wire Wire Line
	4800 1300 4800 2350
Wire Wire Line
	4500 2200 5300 2200
Connection ~ 4800 2200
Wire Wire Line
	5300 1900 4800 1900
Connection ~ 4800 1900
Wire Wire Line
	3300 1600 5300 1600
Connection ~ 4800 1600
Wire Wire Line
	4500 1750 5300 1750
Wire Wire Line
	5050 1150 5050 2350
Connection ~ 5050 1150
Wire Wire Line
	5300 1450 5050 1450
Connection ~ 5050 1450
Wire Wire Line
	5050 2050 5300 2050
Connection ~ 5050 1750
Wire Wire Line
	5050 2350 5300 2350
Connection ~ 5050 2050
Wire Wire Line
	10250 4300 10250 4250
Connection ~ 10250 4250
Wire Wire Line
	9950 4650 10900 4650
Wire Wire Line
	10250 4650 10250 4600
Wire Wire Line
	9950 4250 10900 4250
Wire Wire Line
	9650 4250 9550 4250
Wire Wire Line
	9550 4250 9550 4800
Wire Wire Line
	9550 4650 9650 4650
Connection ~ 9550 4650
Connection ~ 10250 4650
Wire Wire Line
	4750 2700 5300 2700
Wire Wire Line
	4750 2850 5300 2850
Wire Wire Line
	5950 7000 6300 7000
Wire Wire Line
	5950 7200 6300 7200
Wire Wire Line
	5950 7400 6300 7400
Wire Wire Line
	4650 7400 4550 7400
Wire Wire Line
	4550 7400 4550 7500
Wire Wire Line
	4650 7000 4000 7000
Wire Wire Line
	10400 1750 9800 1750
Wire Wire Line
	9800 1750 9800 1700
Wire Wire Line
	10400 1850 9800 1850
Wire Wire Line
	10400 1950 9800 1950
Wire Wire Line
	10400 2050 9800 2050
Wire Wire Line
	10400 2150 9800 2150
Wire Wire Line
	8300 2050 9000 2050
Wire Wire Line
	8300 1900 9000 1900
Wire Wire Line
	5300 3450 5050 3450
Wire Wire Line
	5300 3300 4750 3300
Wire Wire Line
	8300 1150 8400 1150
Wire Wire Line
	8300 1300 8400 1300
Wire Wire Line
	8300 1450 8400 1450
Wire Wire Line
	5300 4400 4750 4400
Wire Wire Line
	5300 4700 4750 4700
Wire Wire Line
	5300 4550 4750 4550
Wire Wire Line
	5300 4100 4750 4100
Wire Wire Line
	5300 4250 4750 4250
Wire Wire Line
	5300 3800 4750 3800
Wire Wire Line
	5300 3950 4750 3950
Wire Wire Line
	5300 3650 4750 3650
Wire Wire Line
	8300 2850 9000 2850
Wire Wire Line
	8300 3000 9000 3000
Wire Wire Line
	8300 3150 9000 3150
Wire Wire Line
	8300 4100 8450 4100
Wire Wire Line
	8300 4250 8450 4250
Wire Wire Line
	8300 4400 8450 4400
Wire Wire Line
	8300 4550 8450 4550
Wire Wire Line
	8300 4700 8450 4700
Wire Wire Line
	8300 2700 9000 2700
Wire Wire Line
	5600 5400 5700 5400
Wire Wire Line
	4700 5400 5000 5400
Wire Wire Line
	5600 5700 5700 5700
Wire Wire Line
	4700 5700 5000 5700
Wire Wire Line
	5600 6000 5700 6000
Wire Wire Line
	4700 6000 5000 6000
Wire Wire Line
	5000 2550 5300 2550
Wire Wire Line
	4750 3000 5300 3000
Wire Wire Line
	4750 3150 5300 3150
Wire Wire Line
	2000 2800 2150 2800
Wire Wire Line
	2550 3000 2000 3000
Wire Wire Line
	2550 2850 2550 3000
Wire Wire Line
	2000 3200 2700 3200
Wire Wire Line
	2850 2950 2550 2950
Connection ~ 2550 2950
Wire Wire Line
	2850 3450 2850 3550
Wire Wire Line
	2000 3400 2550 3400
Wire Wire Line
	2000 3600 2550 3600
Wire Wire Line
	2000 3800 2550 3800
Wire Wire Line
	2000 4800 2550 4800
Wire Wire Line
	2000 5000 2550 5000
Wire Wire Line
	2000 5200 2550 5200
Wire Wire Line
	2000 5400 2550 5400
Wire Wire Line
	2000 5800 2200 5800
Wire Wire Line
	2500 5800 2650 5800
Wire Wire Line
	8300 3950 8450 3950
Wire Wire Line
	8300 1600 8450 1600
Wire Wire Line
	8450 1750 8300 1750
Wire Wire Line
	8300 2400 8500 2400
Wire Wire Line
	8300 2550 8500 2550
Wire Wire Line
	8300 2200 8450 2200
Wire Wire Line
	3300 1200 3300 1150
Connection ~ 4800 1150
Wire Wire Line
	3700 1200 3700 1150
Connection ~ 3700 1150
Wire Wire Line
	4150 1200 4150 1150
Connection ~ 4150 1150
Wire Wire Line
	4600 1200 4600 1150
Connection ~ 4600 1150
Wire Wire Line
	3300 1500 3300 1600
Wire Wire Line
	3700 1500 3700 1600
Connection ~ 3700 1600
Wire Wire Line
	4150 1500 4150 1600
Connection ~ 4150 1600
Wire Wire Line
	4600 1500 4600 1600
Connection ~ 4600 1600
Wire Wire Line
	4500 1800 4500 1750
Wire Wire Line
	4500 2100 4500 2200
$Comp
L C C8
U 1 1 550DD56E
P 10900 5850
F 0 "C8" H 10925 5950 50  0000 L CNN
F 1 "100nF" H 10925 5750 50  0000 L CNN
F 2 "" H 10938 5700 30  0000 C CNN
F 3 "" H 10900 5850 60  0000 C CNN
	1    10900 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	10900 5600 10900 5700
Connection ~ 10450 5600
Wire Wire Line
	10900 6000 10900 6050
$Comp
L GND #PWR18
U 1 1 550DD807
P 10900 6050
F 0 "#PWR18" H 10900 5800 60  0001 C CNN
F 1 "GND" H 10900 5900 60  0000 C CNN
F 2 "" H 10900 6050 60  0000 C CNN
F 3 "" H 10900 6050 60  0000 C CNN
	1    10900 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 5600 2900 5600
Wire Wire Line
	2900 5600 2900 5500
$Comp
L +5V #PWR4
U 1 1 550DE56C
P 2900 5500
F 0 "#PWR4" H 2900 5350 60  0001 C CNN
F 1 "+5V" H 2900 5640 60  0000 C CNN
F 2 "" H 2900 5500 60  0000 C CNN
F 3 "" H 2900 5500 60  0000 C CNN
	1    2900 5500
	1    0    0    -1  
$EndComp
Text GLabel 4750 4100 0    60   Output ~ 0
LCD_BKL_EN
Text GLabel 2650 5800 2    60   Input ~ 0
LCD_BKL_NEG
Text Notes 2150 6050 0    60   ~ 0
thruhole
Text Notes 1700 6500 0    60   ~ 0
Backlight Current Limit:\n5V - 1.2V (V_CE_SAT) = 3.8V\n3.8V - 3.0V (V_BKL) = 0.8V\n0.8V = 300mA * 2.66 ohm
$EndSCHEMATC
