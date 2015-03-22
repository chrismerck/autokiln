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
Sheet 3 6
Title "Wood Drying Kiln Controller \"AutoKiln\""
Date "Sat 21 Mar 2015"
Rev "A1"
Comp "Chris Merck"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ADS1234 U4
U 1 1 550D6BB5
P 5450 3750
F 0 "U4" H 5450 5250 60  0000 C CNN
F 1 "ADS1234" H 5450 5150 60  0000 C CNN
F 2 "Housings_SSOP:TSSOP-28_4.4x9.7mm_Pitch0.65mm" H 5450 5250 60  0001 C CNN
F 3 "" H 5450 5250 60  0000 C CNN
	1    5450 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 3750 7750 3750
Wire Wire Line
	7750 3550 7750 3800
$Comp
L +5V #PWR022
U 1 1 550D6C2D
P 7750 3550
F 0 "#PWR022" H 7750 3400 60  0001 C CNN
F 1 "+5V" H 7750 3690 60  0000 C CNN
F 2 "" H 7750 3550 60  0000 C CNN
F 3 "" H 7750 3550 60  0000 C CNN
	1    7750 3550
	1    0    0    -1  
$EndComp
$Comp
L C C11
U 1 1 550D6C42
P 7750 3950
F 0 "C11" H 7775 4050 50  0000 L CNN
F 1 "100nF" H 7775 3850 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 7788 3800 30  0001 C CNN
F 3 "" H 7750 3950 60  0000 C CNN
	1    7750 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 4100 7750 4200
$Comp
L GND #PWR023
U 1 1 550D6C66
P 7750 4200
F 0 "#PWR023" H 7750 3950 60  0001 C CNN
F 1 "GND" H 7750 4050 60  0000 C CNN
F 2 "" H 7750 4200 60  0000 C CNN
F 3 "" H 7750 4200 60  0000 C CNN
	1    7750 4200
	1    0    0    -1  
$EndComp
Connection ~ 7750 3750
$Comp
L C C10
U 1 1 550D6CC1
P 3900 4250
F 0 "C10" H 3925 4350 50  0000 L CNN
F 1 "100nF" H 3925 4150 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 3938 4100 30  0001 C CNN
F 3 "" H 3900 4250 60  0000 C CNN
	1    3900 4250
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3900 4100 3900 4000
Wire Wire Line
	3900 4000 4100 4000
Wire Wire Line
	4100 4000 4100 4150
Wire Wire Line
	4100 4150 4700 4150
Wire Wire Line
	3900 4400 3900 4500
Wire Wire Line
	3900 4500 4100 4500
Wire Wire Line
	4100 4500 4100 4350
Wire Wire Line
	4100 4350 4700 4350
$Comp
L GND #PWR024
U 1 1 550D6DA4
P 6500 3950
F 0 "#PWR024" H 6500 3700 60  0001 C CNN
F 1 "GND" V 6500 3750 60  0000 C CNN
F 2 "" H 6500 3950 60  0000 C CNN
F 3 "" H 6500 3950 60  0000 C CNN
	1    6500 3950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6200 3950 6500 3950
Text Notes 5000 5500 0    60   ~ 0
JOIN AGND WITH DGND\nUNDER ADS1234
Wire Wire Line
	4700 2550 4400 2550
Wire Wire Line
	4400 2550 4400 2400
$Comp
L VCC #PWR025
U 1 1 550D6E23
P 4400 2400
F 0 "#PWR025" H 4400 2250 60  0001 C CNN
F 1 "VCC" H 4400 2550 60  0000 C CNN
F 2 "" H 4400 2400 60  0000 C CNN
F 3 "" H 4400 2400 60  0000 C CNN
	1    4400 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 2750 4700 2750
$Comp
L GND #PWR026
U 1 1 550D6E4F
P 4400 2750
F 0 "#PWR026" H 4400 2500 60  0001 C CNN
F 1 "GND" V 4400 2550 60  0000 C CNN
F 2 "" H 4400 2750 60  0000 C CNN
F 3 "" H 4400 2750 60  0000 C CNN
	1    4400 2750
	0    1    1    0   
$EndComp
Wire Wire Line
	4700 3750 4650 3750
Wire Wire Line
	4700 3950 4650 3950
Text GLabel 4650 3750 0    60   Input ~ 0
ADC_A1
Text GLabel 4650 3950 0    60   Input ~ 0
ADC_A0
Wire Wire Line
	4700 3350 4400 3350
$Comp
L GND #PWR027
U 1 1 550D6EE9
P 4400 3350
F 0 "#PWR027" H 4400 3100 60  0001 C CNN
F 1 "GND" V 4400 3150 60  0000 C CNN
F 2 "" H 4400 3350 60  0000 C CNN
F 3 "" H 4400 3350 60  0000 C CNN
	1    4400 3350
	0    1    1    0   
$EndComp
Wire Wire Line
	4700 3550 4400 3550
$Comp
L GND #PWR028
U 1 1 550D6EF6
P 4400 3550
F 0 "#PWR028" H 4400 3300 60  0001 C CNN
F 1 "GND" V 4400 3350 60  0000 C CNN
F 2 "" H 4400 3550 60  0000 C CNN
F 3 "" H 4400 3550 60  0000 C CNN
	1    4400 3550
	0    1    1    0   
$EndComp
Wire Wire Line
	6350 3750 6350 4150
Wire Wire Line
	6350 4150 6200 4150
Connection ~ 6350 3750
Wire Wire Line
	6200 4350 6450 4350
Wire Wire Line
	6450 4350 6450 3950
Connection ~ 6450 3950
Wire Wire Line
	6200 2550 6250 2550
Wire Wire Line
	6200 2750 6250 2750
Text GLabel 6250 2550 2    60   Output ~ 0
ADC_DOUT
Text GLabel 6250 2750 2    60   Output ~ 0
ADC_SCLK
Wire Wire Line
	6200 2950 6250 2950
Text GLabel 6250 2950 2    60   Input ~ 0
ADC_PDWN
Wire Wire Line
	6200 3150 6600 3150
Wire Wire Line
	6200 3550 6600 3550
$Comp
L VCC #PWR029
U 1 1 550D723C
P 6500 3350
F 0 "#PWR029" H 6500 3200 60  0001 C CNN
F 1 "VCC" V 6500 3550 60  0000 C CNN
F 2 "" H 6500 3350 60  0000 C CNN
F 3 "" H 6500 3350 60  0000 C CNN
	1    6500 3350
	0    1    1    0   
$EndComp
Wire Wire Line
	6200 3350 6500 3350
Text Notes 9550 3800 0    60   ~ 0
GAIN = 64 or 128
Wire Wire Line
	4700 2950 4650 2950
Wire Wire Line
	4650 2950 4650 2750
Connection ~ 4650 2750
NoConn ~ 4700 3150
$Comp
L CONN_01X04 P3
U 1 1 550D736C
P 1600 2350
F 0 "P3" H 1600 2600 50  0000 C CNN
F 1 "LOAD CELL 1" H 1950 2350 50  0000 C CNN
F 2 "autokiln:ostoq047151" H 1600 2350 60  0001 C CNN
F 3 "" H 1600 2350 60  0000 C CNN
	1    1600 2350
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1800 2300 2200 2300
Wire Wire Line
	1800 2400 2200 2400
$Comp
L GND #PWR030
U 1 1 550D7644
P 2000 2600
F 0 "#PWR030" H 2000 2350 60  0001 C CNN
F 1 "GND" H 2000 2450 60  0000 C CNN
F 2 "" H 2000 2600 60  0000 C CNN
F 3 "" H 2000 2600 60  0000 C CNN
	1    2000 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 2500 2000 2500
Wire Wire Line
	2000 2500 2000 2600
Wire Wire Line
	2000 2200 1800 2200
Wire Wire Line
	2000 2100 2000 2200
$Comp
L +5V #PWR031
U 1 1 550D76CA
P 2000 2100
F 0 "#PWR031" H 2000 1950 60  0001 C CNN
F 1 "+5V" H 2000 2240 60  0000 C CNN
F 2 "" H 2000 2100 60  0000 C CNN
F 3 "" H 2000 2100 60  0000 C CNN
	1    2000 2100
	1    0    0    -1  
$EndComp
Text Label 2200 2300 2    60   ~ 0
LC1P
Text Label 2200 2400 2    60   ~ 0
LC1N
$Comp
L CONN_01X04 P4
U 1 1 550D777A
P 1600 3400
F 0 "P4" H 1600 3650 50  0000 C CNN
F 1 "LOAD CELL 2" H 1950 3400 50  0000 C CNN
F 2 "autokiln:ostoq047151" H 1600 3400 60  0001 C CNN
F 3 "" H 1600 3400 60  0000 C CNN
	1    1600 3400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1800 3350 2200 3350
Wire Wire Line
	1800 3450 2200 3450
$Comp
L GND #PWR032
U 1 1 550D7782
P 2000 3650
F 0 "#PWR032" H 2000 3400 60  0001 C CNN
F 1 "GND" H 2000 3500 60  0000 C CNN
F 2 "" H 2000 3650 60  0000 C CNN
F 3 "" H 2000 3650 60  0000 C CNN
	1    2000 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 3550 2000 3550
Wire Wire Line
	2000 3550 2000 3650
Wire Wire Line
	2000 3250 1800 3250
Wire Wire Line
	2000 3150 2000 3250
$Comp
L +5V #PWR033
U 1 1 550D778C
P 2000 3150
F 0 "#PWR033" H 2000 3000 60  0001 C CNN
F 1 "+5V" H 2000 3290 60  0000 C CNN
F 2 "" H 2000 3150 60  0000 C CNN
F 3 "" H 2000 3150 60  0000 C CNN
	1    2000 3150
	1    0    0    -1  
$EndComp
Text Label 2200 3350 2    60   ~ 0
LC2P
Text Label 2200 3450 2    60   ~ 0
LC2N
$Comp
L CONN_01X04 P5
U 1 1 550D78A9
P 1600 4450
F 0 "P5" H 1600 4700 50  0000 C CNN
F 1 "LOAD CELL 3" H 1950 4450 50  0000 C CNN
F 2 "autokiln:ostoq047151" H 1600 4450 60  0001 C CNN
F 3 "" H 1600 4450 60  0000 C CNN
	1    1600 4450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1800 4400 2200 4400
Wire Wire Line
	1800 4500 2200 4500
$Comp
L GND #PWR034
U 1 1 550D78B1
P 2000 4700
F 0 "#PWR034" H 2000 4450 60  0001 C CNN
F 1 "GND" H 2000 4550 60  0000 C CNN
F 2 "" H 2000 4700 60  0000 C CNN
F 3 "" H 2000 4700 60  0000 C CNN
	1    2000 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 4600 2000 4600
Wire Wire Line
	2000 4600 2000 4700
Wire Wire Line
	2000 4300 1800 4300
Wire Wire Line
	2000 4200 2000 4300
$Comp
L +5V #PWR035
U 1 1 550D78BB
P 2000 4200
F 0 "#PWR035" H 2000 4050 60  0001 C CNN
F 1 "+5V" H 2000 4340 60  0000 C CNN
F 2 "" H 2000 4200 60  0000 C CNN
F 3 "" H 2000 4200 60  0000 C CNN
	1    2000 4200
	1    0    0    -1  
$EndComp
Text Label 2200 4400 2    60   ~ 0
LC3P
Text Label 2200 4500 2    60   ~ 0
LC3N
$Comp
L CONN_01X04 P6
U 1 1 550D78C3
P 1600 5500
F 0 "P6" H 1600 5750 50  0000 C CNN
F 1 "LOAD CELL 4" H 1950 5500 50  0000 C CNN
F 2 "autokiln:ostoq047151" H 1600 5500 60  0001 C CNN
F 3 "" H 1600 5500 60  0000 C CNN
	1    1600 5500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1800 5450 2200 5450
Wire Wire Line
	1800 5550 2200 5550
$Comp
L GND #PWR036
U 1 1 550D78CB
P 2000 5750
F 0 "#PWR036" H 2000 5500 60  0001 C CNN
F 1 "GND" H 2000 5600 60  0000 C CNN
F 2 "" H 2000 5750 60  0000 C CNN
F 3 "" H 2000 5750 60  0000 C CNN
	1    2000 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 5650 2000 5650
Wire Wire Line
	2000 5650 2000 5750
Wire Wire Line
	2000 5350 1800 5350
Wire Wire Line
	2000 5250 2000 5350
$Comp
L +5V #PWR037
U 1 1 550D78D5
P 2000 5250
F 0 "#PWR037" H 2000 5100 60  0001 C CNN
F 1 "+5V" H 2000 5390 60  0000 C CNN
F 2 "" H 2000 5250 60  0000 C CNN
F 3 "" H 2000 5250 60  0000 C CNN
	1    2000 5250
	1    0    0    -1  
$EndComp
Text Label 2200 5450 2    60   ~ 0
LC4P
Text Label 2200 5550 2    60   ~ 0
LC4N
Text Notes 1250 1700 0    60   ~ 0
LOAD CELL CONNECTORS\n
Text Notes 4900 1850 0    60   ~ 0
LOAD CELL AMPLIFIER / ADC
Wire Wire Line
	4700 4550 4300 4550
Wire Wire Line
	4700 4750 4300 4750
Text Label 4300 4550 0    60   ~ 0
LC1P
Text Label 4300 4750 0    60   ~ 0
LC1N
Wire Wire Line
	4700 4950 4300 4950
Wire Wire Line
	4700 5150 4300 5150
Text Label 4300 4950 0    60   ~ 0
LC3P
Text Label 4300 5150 0    60   ~ 0
LC3N
Wire Wire Line
	6200 4550 6600 4550
Wire Wire Line
	6200 4750 6600 4750
Text Label 6600 4550 2    60   ~ 0
LC2P
Text Label 6600 4750 2    60   ~ 0
LC2N
Wire Wire Line
	6200 4950 6600 4950
Wire Wire Line
	6200 5150 6600 5150
Text Label 6600 4950 2    60   ~ 0
LC4P
Text Label 6600 5150 2    60   ~ 0
LC4N
Text Label 6600 3550 2    60   ~ 0
GAIN0
Wire Wire Line
	9500 3300 9900 3300
Text Label 9500 3300 0    60   ~ 0
GAIN0
$Comp
L CONN_01X03 J1
U 1 1 550D83CF
P 10100 3300
F 0 "J1" H 10100 3500 50  0000 C CNN
F 1 "GAIN JUMPER" H 10400 3300 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 10100 3300 60  0001 C CNN
F 3 "" H 10100 3300 60  0000 C CNN
	1    10100 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9900 3200 9800 3200
Wire Wire Line
	9800 3200 9800 3100
Wire Wire Line
	9900 3400 9800 3400
Wire Wire Line
	9800 3400 9800 3450
$Comp
L VCC #PWR038
U 1 1 550D84D9
P 9800 3100
F 0 "#PWR038" H 9800 2950 60  0001 C CNN
F 1 "VCC" H 9800 3250 60  0000 C CNN
F 2 "" H 9800 3100 60  0000 C CNN
F 3 "" H 9800 3100 60  0000 C CNN
	1    9800 3100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR039
U 1 1 550D8533
P 9800 3450
F 0 "#PWR039" H 9800 3200 60  0001 C CNN
F 1 "GND" H 9800 3300 60  0000 C CNN
F 2 "" H 9800 3450 60  0000 C CNN
F 3 "" H 9800 3450 60  0000 C CNN
	1    9800 3450
	1    0    0    -1  
$EndComp
Text Label 6600 3150 2    60   ~ 0
SPEED
Text Notes 9450 5250 0    60   ~ 0
SPEED = 10SPS or 80SPS
Wire Wire Line
	9500 4750 9900 4750
Text Label 9500 4750 0    60   ~ 0
SPEED
$Comp
L CONN_01X03 J2
U 1 1 550D8785
P 10100 4750
F 0 "J2" H 10100 4950 50  0000 C CNN
F 1 "SPEED JUMPER" H 10500 4750 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 10100 4750 60  0001 C CNN
F 3 "" H 10100 4750 60  0000 C CNN
	1    10100 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9900 4650 9800 4650
Wire Wire Line
	9800 4650 9800 4550
Wire Wire Line
	9900 4850 9800 4850
Wire Wire Line
	9800 4850 9800 4900
$Comp
L VCC #PWR040
U 1 1 550D878F
P 9800 4550
F 0 "#PWR040" H 9800 4400 60  0001 C CNN
F 1 "VCC" H 9800 4700 60  0000 C CNN
F 2 "" H 9800 4550 60  0000 C CNN
F 3 "" H 9800 4550 60  0000 C CNN
	1    9800 4550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR041
U 1 1 550D8795
P 9800 4900
F 0 "#PWR041" H 9800 4650 60  0001 C CNN
F 1 "GND" H 9800 4750 60  0000 C CNN
F 2 "" H 9800 4900 60  0000 C CNN
F 3 "" H 9800 4900 60  0000 C CNN
	1    9800 4900
	1    0    0    -1  
$EndComp
$Comp
L C C9
U 1 1 550DC6FB
P 3750 2700
F 0 "C9" H 3775 2800 50  0000 L CNN
F 1 "100nF" H 3775 2600 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 3788 2550 30  0001 C CNN
F 3 "" H 3750 2700 60  0000 C CNN
	1    3750 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 2550 3750 2500
Wire Wire Line
	3750 2500 4400 2500
Connection ~ 4400 2500
Wire Wire Line
	3750 2850 3750 2900
Wire Wire Line
	3750 2900 4450 2900
Wire Wire Line
	4450 2900 4450 2750
Connection ~ 4450 2750
$EndSCHEMATC
