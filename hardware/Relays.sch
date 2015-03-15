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
Sheet 4 6
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
L RELAY_SPST K1
U 1 1 5505E8C3
P 9300 1400
F 0 "K1" H 9300 1550 50  0000 C CNN
F 1 "12V 250VAC 10A" H 9450 900 50  0000 C CNN
F 2 "" H 9300 1400 60  0000 C CNN
F 3 "" H 9300 1400 60  0000 C CNN
	1    9300 1400
	1    0    0    -1  
$EndComp
$Comp
L RELAY_SPST K2
U 1 1 5505E99E
P 9300 2350
F 0 "K2" H 9300 2500 50  0000 C CNN
F 1 "12V 250VAC 10A" H 9450 1850 50  0000 C CNN
F 2 "" H 9300 2350 60  0000 C CNN
F 3 "" H 9300 2350 60  0000 C CNN
	1    9300 2350
	1    0    0    -1  
$EndComp
$Comp
L RELAY_SPST K3
U 1 1 5505E9D7
P 9300 3300
F 0 "K3" H 9300 3450 50  0000 C CNN
F 1 "12V 250VAC 10A" H 9450 2800 50  0000 C CNN
F 2 "" H 9300 3300 60  0000 C CNN
F 3 "" H 9300 3300 60  0000 C CNN
	1    9300 3300
	1    0    0    -1  
$EndComp
$Comp
L RELAY_SPST K4
U 1 1 5505EA64
P 9300 4250
F 0 "K4" H 9300 4400 50  0000 C CNN
F 1 "12V 250VAC 10A" H 9450 3750 50  0000 C CNN
F 2 "" H 9300 4250 60  0000 C CNN
F 3 "" H 9300 4250 60  0000 C CNN
	1    9300 4250
	1    0    0    -1  
$EndComp
$Comp
L RELAY_SPST K5
U 1 1 5505EACF
P 9300 5200
F 0 "K5" H 9300 5350 50  0000 C CNN
F 1 "12V 250VAC 10A" H 9450 4700 50  0000 C CNN
F 2 "" H 9300 5200 60  0000 C CNN
F 3 "" H 9300 5200 60  0000 C CNN
	1    9300 5200
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P2
U 1 1 5505EFEF
P 10350 1450
F 0 "P2" H 10350 1600 50  0000 C CNN
F 1 "HEATER" H 10350 1300 50  0000 C CNN
F 2 "" H 10350 1450 60  0000 C CNN
F 3 "" H 10350 1450 60  0000 C CNN
	1    10350 1450
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P3
U 1 1 5505F07F
P 10400 2400
F 0 "P3" H 10400 2550 50  0000 C CNN
F 1 "DEHUMIDIFIER" H 10400 2250 50  0000 C CNN
F 2 "" H 10400 2400 60  0000 C CNN
F 3 "" H 10400 2400 60  0000 C CNN
	1    10400 2400
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P4
U 1 1 5505F0F2
P 10400 3350
F 0 "P4" H 10400 3500 50  0000 C CNN
F 1 "FAN" H 10400 3200 50  0000 C CNN
F 2 "" H 10400 3350 60  0000 C CNN
F 3 "" H 10400 3350 60  0000 C CNN
	1    10400 3350
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P5
U 1 1 5505F180
P 10400 4300
F 0 "P5" H 10400 4450 50  0000 C CNN
F 1 "VACUUM" H 10400 4150 50  0000 C CNN
F 2 "" H 10400 4300 60  0000 C CNN
F 3 "" H 10400 4300 60  0000 C CNN
	1    10400 4300
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P6
U 1 1 5505F2A2
P 10450 5250
F 0 "P6" H 10450 5400 50  0000 C CNN
F 1 "CONDITIONER" H 10450 5100 50  0000 C CNN
F 2 "" H 10450 5250 60  0000 C CNN
F 3 "" H 10450 5250 60  0000 C CNN
	1    10450 5250
	1    0    0    -1  
$EndComp
NoConn ~ 9700 1350
NoConn ~ 9700 2300
NoConn ~ 9700 3250
NoConn ~ 9700 4200
NoConn ~ 9700 5150
Text Notes 9250 1000 0    60   ~ 0
RELAYS\n(Omron G5LE-1)
$Comp
L LED D4
U 1 1 5505FD54
P 6450 2150
F 0 "D4" V 6350 2250 50  0000 C CNN
F 1 "12V LED" V 6550 2350 50  0000 C CNN
F 2 "" H 6450 2150 60  0000 C CNN
F 3 "" H 6450 2150 60  0000 C CNN
	1    6450 2150
	0    1    1    0   
$EndComp
$Comp
L +12V #PWR07
U 1 1 550604B0
P 6450 1800
F 0 "#PWR07" H 6450 1650 60  0001 C CNN
F 1 "+12V" H 6450 1940 60  0000 C CNN
F 2 "" H 6450 1800 60  0000 C CNN
F 3 "" H 6450 1800 60  0000 C CNN
	1    6450 1800
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR08
U 1 1 55061014
P 8800 1150
F 0 "#PWR08" H 8800 1000 60  0001 C CNN
F 1 "+12V" H 8800 1290 60  0000 C CNN
F 2 "" H 8800 1150 60  0000 C CNN
F 3 "" H 8800 1150 60  0000 C CNN
	1    8800 1150
	1    0    0    -1  
$EndComp
Text Label 8100 1750 0    60   ~ 0
HEATER_COIL
Text Label 8100 2700 0    60   ~ 0
DEHUM_COIL
Wire Wire Line
	8900 1450 8900 1150
Wire Wire Line
	8900 1150 10150 1150
Wire Wire Line
	10150 1150 10150 1400
Wire Wire Line
	9700 1550 10150 1550
Wire Wire Line
	10150 1550 10150 1500
Wire Wire Line
	8900 2400 8900 2100
Wire Wire Line
	8900 2100 10200 2100
Wire Wire Line
	10200 2100 10200 2350
Wire Wire Line
	9700 2500 10200 2500
Wire Wire Line
	10200 2500 10200 2450
Wire Wire Line
	8900 3050 8900 3350
Wire Wire Line
	8900 3050 10200 3050
Wire Wire Line
	10200 3050 10200 3300
Wire Wire Line
	10200 3400 9700 3400
Wire Wire Line
	9700 3400 9700 3450
Wire Wire Line
	8900 4300 8900 4000
Wire Wire Line
	8900 4000 10200 4000
Wire Wire Line
	10200 4000 10200 4250
Wire Wire Line
	9700 4400 10200 4400
Wire Wire Line
	10200 4400 10200 4350
Wire Wire Line
	9700 5350 10250 5350
Wire Wire Line
	10250 5350 10250 5300
Wire Wire Line
	8900 5250 8900 4950
Wire Wire Line
	8900 4950 10250 4950
Wire Wire Line
	10250 4950 10250 5200
Wire Wire Line
	6450 1800 6450 1950
Wire Wire Line
	6450 2350 6450 2400
Wire Wire Line
	6450 2400 7200 2400
Wire Wire Line
	8800 1150 8800 1650
Wire Wire Line
	8800 1650 8800 2600
Wire Wire Line
	8800 2600 8800 3550
Wire Wire Line
	8800 3550 8800 4500
Wire Wire Line
	8800 4500 8800 5450
Wire Wire Line
	8800 1650 8900 1650
Wire Wire Line
	8800 2600 8900 2600
Connection ~ 8800 1650
Wire Wire Line
	8800 3550 8900 3550
Connection ~ 8800 2600
Wire Wire Line
	8800 4500 8900 4500
Connection ~ 8800 3550
Wire Wire Line
	8800 5450 8900 5450
Connection ~ 8800 4500
Wire Wire Line
	8100 1750 8900 1750
Wire Wire Line
	8100 2700 8900 2700
Wire Wire Line
	8900 3650 8100 3650
Text Label 8100 3650 0    60   ~ 0
FAN_COIL
Wire Wire Line
	8900 4600 8100 4600
Text Label 8100 4600 0    60   ~ 0
VACUUM_COIL
Wire Wire Line
	8900 5550 8100 5550
Text Label 8100 5550 0    60   ~ 0
STEAM_COIL
Text Label 7200 2400 2    60   ~ 0
DEHUM_COIL
$Comp
L ULQ2003 U3
U 1 1 55062CD9
P 2750 4350
F 0 "U3" H 2100 6300 60  0000 C CNN
F 1 "ULQ2003" H 2200 6200 60  0000 C CNN
F 2 "" H 2750 3650 60  0000 C CNN
F 3 "" H 2750 3650 60  0000 C CNN
	1    2750 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 3400 2850 3400
Wire Wire Line
	2950 2400 2950 3400
$Comp
L +12V #PWR09
U 1 1 55062EC6
P 2950 2400
F 0 "#PWR09" H 2950 2250 60  0001 C CNN
F 1 "+12V" H 2950 2540 60  0000 C CNN
F 2 "" H 2950 2400 60  0000 C CNN
F 3 "" H 2950 2400 60  0000 C CNN
	1    2950 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 2700 3700 2700
Text Label 3700 2700 2    60   ~ 0
HEATER_COIL
Wire Wire Line
	2850 2800 3700 2800
Text Label 3700 2800 2    60   ~ 0
DEHUM_COIL
Wire Wire Line
	2850 2900 3700 2900
Text Label 3700 2900 2    60   ~ 0
FAN_COIL
Wire Wire Line
	2850 3000 3700 3000
Text Label 3700 3000 2    60   ~ 0
VACUUM_COIL
Wire Wire Line
	2850 3100 3700 3100
Text Label 3700 3100 2    60   ~ 0
STEAM_COIL
Wire Wire Line
	1700 2700 850  2700
Wire Wire Line
	1700 2800 850  2800
Wire Wire Line
	1700 2900 850  2900
Wire Wire Line
	1700 3000 850  3000
Wire Wire Line
	1700 3100 850  3100
NoConn ~ 1700 3200
NoConn ~ 1700 3300
NoConn ~ 2850 3200
NoConn ~ 2850 3300
Wire Wire Line
	1700 3400 1650 3400
Wire Wire Line
	1650 3400 1650 3450
$Comp
L GND #PWR010
U 1 1 55063B3D
P 1650 3450
F 0 "#PWR010" H 1650 3200 60  0001 C CNN
F 1 "GND" H 1650 3300 60  0000 C CNN
F 2 "" H 1650 3450 60  0000 C CNN
F 3 "" H 1650 3450 60  0000 C CNN
	1    1650 3450
	1    0    0    -1  
$EndComp
Text Notes 1950 2200 0    60   ~ 0
RELAY DRIVER
Text Notes 5500 1150 0    60   ~ 0
RELAY INDICATORS
$Comp
L LED D5
U 1 1 55063F04
P 6450 3500
F 0 "D5" V 6350 3600 50  0000 C CNN
F 1 "12V LED" V 6550 3700 50  0000 C CNN
F 2 "" H 6450 3500 60  0000 C CNN
F 3 "" H 6450 3500 60  0000 C CNN
	1    6450 3500
	0    1    1    0   
$EndComp
$Comp
L +12V #PWR011
U 1 1 55063F10
P 6450 3150
F 0 "#PWR011" H 6450 3000 60  0001 C CNN
F 1 "+12V" H 6450 3290 60  0000 C CNN
F 2 "" H 6450 3150 60  0000 C CNN
F 3 "" H 6450 3150 60  0000 C CNN
	1    6450 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 3150 6450 3300
Wire Wire Line
	6450 3700 6450 3750
Wire Wire Line
	6450 3750 7200 3750
Text Label 7200 3750 2    60   ~ 0
VACUUM_COIL
$Comp
L LED D1
U 1 1 5506407D
P 5300 2150
F 0 "D1" V 5200 2250 50  0000 C CNN
F 1 "12V LED" V 5400 2350 50  0000 C CNN
F 2 "" H 5300 2150 60  0000 C CNN
F 3 "" H 5300 2150 60  0000 C CNN
	1    5300 2150
	0    1    1    0   
$EndComp
$Comp
L +12V #PWR012
U 1 1 55064089
P 5300 1800
F 0 "#PWR012" H 5300 1650 60  0001 C CNN
F 1 "+12V" H 5300 1940 60  0000 C CNN
F 2 "" H 5300 1800 60  0000 C CNN
F 3 "" H 5300 1800 60  0000 C CNN
	1    5300 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 1800 5300 1950
Wire Wire Line
	5300 2350 5300 2400
Wire Wire Line
	5300 2400 6050 2400
Text Label 5500 2400 0    60   ~ 0
HEATER_COIL
$Comp
L LED D2
U 1 1 55064094
P 5300 3500
F 0 "D2" V 5200 3600 50  0000 C CNN
F 1 "12V LED" V 5400 3700 50  0000 C CNN
F 2 "" H 5300 3500 60  0000 C CNN
F 3 "" H 5300 3500 60  0000 C CNN
	1    5300 3500
	0    1    1    0   
$EndComp
$Comp
L +12V #PWR013
U 1 1 550640A0
P 5300 3150
F 0 "#PWR013" H 5300 3000 60  0001 C CNN
F 1 "+12V" H 5300 3290 60  0000 C CNN
F 2 "" H 5300 3150 60  0000 C CNN
F 3 "" H 5300 3150 60  0000 C CNN
	1    5300 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 3150 5300 3300
Wire Wire Line
	5300 3700 5300 3750
Wire Wire Line
	5300 3750 6050 3750
Text Label 6050 3750 2    60   ~ 0
FAN_COIL
$Comp
L LED D3
U 1 1 55064167
P 5300 4900
F 0 "D3" V 5200 5000 50  0000 C CNN
F 1 "12V LED" V 5400 5100 50  0000 C CNN
F 2 "" H 5300 4900 60  0000 C CNN
F 3 "" H 5300 4900 60  0000 C CNN
	1    5300 4900
	0    1    1    0   
$EndComp
$Comp
L +12V #PWR014
U 1 1 55064173
P 5300 4550
F 0 "#PWR014" H 5300 4400 60  0001 C CNN
F 1 "+12V" H 5300 4690 60  0000 C CNN
F 2 "" H 5300 4550 60  0000 C CNN
F 3 "" H 5300 4550 60  0000 C CNN
	1    5300 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 4550 5300 4700
Wire Wire Line
	5300 5100 5300 5150
Wire Wire Line
	5300 5150 6050 5150
Text Label 6050 5150 2    60   ~ 0
STEAM_COIL
Text Label 850  3100 0    60   ~ 0
STEAM
Text Label 850  3000 0    60   ~ 0
VACUUM
Text Label 850  2900 0    60   ~ 0
FAN
Text Label 850  2800 0    60   ~ 0
DEHUM
Text Label 850  2700 0    60   ~ 0
HEATER
Wire Wire Line
	1800 750  950  750 
Wire Wire Line
	1800 900  950  900 
Wire Wire Line
	1800 1050 950  1050
Wire Wire Line
	1800 1200 950  1200
Wire Wire Line
	1800 1350 950  1350
Text Label 950  1350 0    60   ~ 0
STEAM
Text Label 950  1200 0    60   ~ 0
VACUUM
Text Label 950  1050 0    60   ~ 0
FAN
Text Label 950  900  0    60   ~ 0
DEHUM
Text Label 950  750  0    60   ~ 0
HEATER
Text GLabel 1800 750  2    60   BiDi ~ 0
HEATER
Text GLabel 1800 900  2    60   BiDi ~ 0
DEHUM
Text GLabel 1800 1050 2    60   BiDi ~ 0
FAN
Text GLabel 1800 1200 2    60   BiDi ~ 0
VACUUM
Text GLabel 1800 1350 2    60   BiDi ~ 0
STEAM
$EndSCHEMATC