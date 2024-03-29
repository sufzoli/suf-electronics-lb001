EESchema Schematic File Version 2
LIBS:suf
LIBS:conn
LIBS:device
LIBS:power
LIBS:transistors
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
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
LIBS:DISPLAY-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "5 nov 2013"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L 7SEGMENT_CC_4D U2
U 1 1 52696DDA
P 4850 1950
F 0 "U2" H 4500 2150 60  0000 C CNN
F 1 "HDSP-B09G" H 5050 2150 60  0000 C CNN
F 2 "HDSP-B0XG" H 4850 1950 60  0001 C CNN
F 3 "~" H 4850 1950 60  0000 C CNN
	1    4850 1950
	1    0    0    -1  
$EndComp
$Comp
L ULN2003A U1
U 1 1 52696E56
P 4200 3550
F 0 "U1" H 3950 4100 70  0000 C CNN
F 1 "ULN2003A" H 4300 2950 70  0000 C CNN
F 2 "DIP-16__300" H 4200 3550 60  0001 C CNN
F 3 "" H 4200 3550 60  0000 C CNN
	1    4200 3550
	0    -1   -1   0   
$EndComp
$Comp
L MCP23017 U3
U 1 1 52696E65
P 6000 3650
F 0 "U3" H 5800 4500 60  0000 C CNN
F 1 "MCP23017" H 6000 2800 60  0000 C CNN
F 2 "DIP-28__300" H 6000 3650 60  0001 C CNN
F 3 "~" H 6000 3650 60  0000 C CNN
	1    6000 3650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4500 2375 3850 2375
Wire Wire Line
	3850 2375 3850 3050
Wire Wire Line
	4550 2375 4550 2400
Wire Wire Line
	4550 2400 3950 2400
Wire Wire Line
	3950 2400 3950 3050
Wire Wire Line
	4600 2375 4600 2425
Wire Wire Line
	4600 2425 4050 2425
Wire Wire Line
	4050 2425 4050 3050
Wire Wire Line
	4150 2450 4150 3050
Wire Wire Line
	4150 2450 4650 2450
Wire Wire Line
	4650 2450 4650 2375
Wire Wire Line
	5200 2375 5950 2375
Wire Wire Line
	5150 2375 5150 2400
Wire Wire Line
	5150 2400 5850 2400
Wire Wire Line
	5100 2375 5100 2425
Wire Wire Line
	5100 2425 5750 2425
Wire Wire Line
	5050 2375 5050 2450
Wire Wire Line
	5050 2450 5650 2450
Wire Wire Line
	5000 2375 5000 2475
Wire Wire Line
	5000 2475 5550 2475
Wire Wire Line
	4950 2375 4950 2500
Wire Wire Line
	4950 2500 5450 2500
Wire Wire Line
	4900 2375 4900 2525
Wire Wire Line
	4900 2525 5350 2525
Wire Wire Line
	4850 2375 4850 2550
Wire Wire Line
	4850 2550 5250 2550
$Comp
L R R1
U 1 1 526986B4
P 5250 2850
F 0 "R1" H 5425 2825 40  0000 C CNN
F 1 "68" H 5075 2800 40  0000 C CNN
F 2 "R4" H 5250 2850 60  0001 C CNN
F 3 "~" H 5250 2850 60  0000 C CNN
	1    5250 2850
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 526986C3
P 5350 2850
F 0 "R2" H 5525 2825 40  0000 C CNN
F 1 "68" H 5175 2800 40  0000 C CNN
F 2 "R4" H 5350 2850 60  0001 C CNN
F 3 "~" H 5350 2850 60  0000 C CNN
	1    5350 2850
	0    1    1    0   
$EndComp
$Comp
L R R3
U 1 1 526986D0
P 5450 2850
F 0 "R3" H 5625 2825 40  0000 C CNN
F 1 "68" H 5275 2800 40  0000 C CNN
F 2 "R4" H 5450 2850 60  0001 C CNN
F 3 "~" H 5450 2850 60  0000 C CNN
	1    5450 2850
	0    1    1    0   
$EndComp
$Comp
L R R4
U 1 1 526986D6
P 5550 2850
F 0 "R4" H 5725 2825 40  0000 C CNN
F 1 "68" H 5375 2800 40  0000 C CNN
F 2 "R4" H 5550 2850 60  0001 C CNN
F 3 "~" H 5550 2850 60  0000 C CNN
	1    5550 2850
	0    1    1    0   
$EndComp
$Comp
L R R5
U 1 1 526986DC
P 5650 2850
F 0 "R5" H 5825 2825 40  0000 C CNN
F 1 "68" H 5475 2800 40  0000 C CNN
F 2 "R4" H 5650 2850 60  0001 C CNN
F 3 "~" H 5650 2850 60  0000 C CNN
	1    5650 2850
	0    1    1    0   
$EndComp
$Comp
L R R6
U 1 1 526986E2
P 5750 2850
F 0 "R6" H 5925 2825 40  0000 C CNN
F 1 "68" H 5575 2800 40  0000 C CNN
F 2 "R4" H 5750 2850 60  0001 C CNN
F 3 "~" H 5750 2850 60  0000 C CNN
	1    5750 2850
	0    1    1    0   
$EndComp
$Comp
L R R7
U 1 1 526986E8
P 5850 2850
F 0 "R7" H 6025 2825 40  0000 C CNN
F 1 "68" H 5675 2800 40  0000 C CNN
F 2 "R4" H 5850 2850 60  0001 C CNN
F 3 "~" H 5850 2850 60  0000 C CNN
	1    5850 2850
	0    1    1    0   
$EndComp
$Comp
L R R8
U 1 1 526986EE
P 5950 2850
F 0 "R8" H 6125 2825 40  0000 C CNN
F 1 "68" H 5775 2800 40  0000 C CNN
F 2 "R4" H 5950 2850 60  0001 C CNN
F 3 "~" H 5950 2850 60  0000 C CNN
	1    5950 2850
	0    1    1    0   
$EndComp
Wire Wire Line
	5250 2550 5250 2650
Wire Wire Line
	5350 2525 5350 2650
Wire Wire Line
	5450 2500 5450 2650
Wire Wire Line
	5550 2475 5550 2650
Wire Wire Line
	5650 2450 5650 2650
Wire Wire Line
	5750 2425 5750 2650
Wire Wire Line
	5850 2400 5850 2650
Wire Wire Line
	5950 2375 5950 2650
Wire Wire Line
	5250 3050 5250 3100
Wire Wire Line
	5350 3050 5350 3100
Wire Wire Line
	5450 3050 5450 3100
Wire Wire Line
	5550 3050 5550 3100
Wire Wire Line
	5650 3050 5650 3100
Wire Wire Line
	5750 3050 5750 3100
Wire Wire Line
	5850 3050 5850 3100
Wire Wire Line
	5950 3050 5950 3100
Wire Wire Line
	6350 3100 6350 3050
Wire Wire Line
	6350 3050 6900 3050
Wire Wire Line
	6900 3050 6900 4250
Wire Wire Line
	6900 4250 4150 4250
Wire Wire Line
	4150 4250 4150 4050
Wire Wire Line
	4050 4050 4050 4275
Wire Wire Line
	4050 4275 6925 4275
Wire Wire Line
	6925 4275 6925 3025
Wire Wire Line
	6925 3025 6250 3025
Wire Wire Line
	6250 3025 6250 3100
Wire Wire Line
	6150 3100 6150 3000
Wire Wire Line
	6150 3000 6950 3000
Wire Wire Line
	6950 3000 6950 4300
Wire Wire Line
	6950 4300 3950 4300
Wire Wire Line
	3950 4300 3950 4050
Wire Wire Line
	3850 4050 3850 4325
Wire Wire Line
	3850 4325 6975 4325
Wire Wire Line
	6975 4325 6975 2975
Wire Wire Line
	6975 2975 6050 2975
Wire Wire Line
	6050 2975 6050 3100
$Comp
L GND #PWR01
U 1 1 5269E2CA
P 5350 4475
F 0 "#PWR01" H 5350 4475 30  0001 C CNN
F 1 "GND" H 5350 4405 30  0001 C CNN
F 2 "" H 5350 4475 60  0000 C CNN
F 3 "" H 5350 4475 60  0000 C CNN
	1    5350 4475
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 4200 5350 4475
$Comp
L GND #PWR02
U 1 1 5269E367
P 5850 4475
F 0 "#PWR02" H 5850 4475 30  0001 C CNN
F 1 "GND" H 5850 4405 30  0001 C CNN
F 2 "" H 5850 4475 60  0000 C CNN
F 3 "" H 5850 4475 60  0000 C CNN
	1    5850 4475
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 4200 5950 4200
Connection ~ 5850 4200
Wire Wire Line
	5850 4200 5850 4475
$Comp
L VCC #PWR03
U 1 1 5269E46D
P 5050 4200
F 0 "#PWR03" H 5050 4300 30  0001 C CNN
F 1 "VCC" H 5050 4300 30  0000 C CNN
F 2 "" H 5050 4200 60  0000 C CNN
F 3 "" H 5050 4200 60  0000 C CNN
	1    5050 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 4200 5050 4200
$Comp
L VCC #PWR04
U 1 1 5269E4FB
P 6450 4200
F 0 "#PWR04" H 6450 4300 30  0001 C CNN
F 1 "VCC" H 6450 4300 30  0000 C CNN
F 2 "" H 6450 4200 60  0000 C CNN
F 3 "" H 6450 4200 60  0000 C CNN
	1    6450 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 4200 6450 4200
$Comp
L CONN_4 J1
U 1 1 5275D3B7
P 8100 3400
F 0 "J1" V 8050 3400 50  0000 C CNN
F 1 "IO" V 8150 3400 50  0000 C CNN
F 2 "HDR-4" H 8100 3400 60  0001 C CNN
F 3 "" H 8100 3400 60  0000 C CNN
	1    8100 3400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 5275D3C6
P 7650 3650
F 0 "#PWR05" H 7650 3650 30  0001 C CNN
F 1 "GND" H 7650 3580 30  0001 C CNN
F 2 "" H 7650 3650 60  0000 C CNN
F 3 "" H 7650 3650 60  0000 C CNN
	1    7650 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 3350 7650 3350
Wire Wire Line
	7650 3350 7650 3650
$Comp
L VCC #PWR06
U 1 1 5275D41A
P 7650 3050
F 0 "#PWR06" H 7650 3150 30  0001 C CNN
F 1 "VCC" H 7650 3150 30  0000 C CNN
F 2 "" H 7650 3050 60  0000 C CNN
F 3 "" H 7650 3050 60  0000 C CNN
	1    7650 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 3250 7650 3250
Wire Wire Line
	7650 3250 7650 3050
Wire Wire Line
	5650 4200 5650 4350
Wire Wire Line
	5650 4350 7000 4350
Wire Wire Line
	7000 4350 7000 3450
Wire Wire Line
	7000 3450 7750 3450
Wire Wire Line
	7750 3550 7025 3550
Wire Wire Line
	7025 3550 7025 4375
Wire Wire Line
	7025 4375 5550 4375
Wire Wire Line
	5550 4375 5550 4200
$Comp
L SW_PUSH SW4
U 1 1 52761E18
P 7300 1900
F 0 "SW4" H 7450 2010 50  0000 C CNN
F 1 "SW_PUSH" H 7300 1820 50  0000 C CNN
F 2 "SW_PUSH_SMALL" H 7300 1900 60  0001 C CNN
F 3 "" H 7300 1900 60  0000 C CNN
	1    7300 1900
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW3
U 1 1 52761E7A
P 7300 2150
F 0 "SW3" H 7450 2260 50  0000 C CNN
F 1 "SW_PUSH" H 7300 2070 50  0000 C CNN
F 2 "SW_PUSH_SMALL" H 7300 2150 60  0001 C CNN
F 3 "" H 7300 2150 60  0000 C CNN
	1    7300 2150
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW2
U 1 1 52761E89
P 7300 2400
F 0 "SW2" H 7450 2510 50  0000 C CNN
F 1 "SW_PUSH" H 7300 2320 50  0000 C CNN
F 2 "SW_PUSH_SMALL" H 7300 2400 60  0001 C CNN
F 3 "" H 7300 2400 60  0000 C CNN
	1    7300 2400
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW1
U 1 1 52761E98
P 7300 2650
F 0 "SW1" H 7450 2760 50  0000 C CNN
F 1 "SW_PUSH" H 7300 2570 50  0000 C CNN
F 2 "SW_PUSH_SMALL" H 7300 2650 60  0001 C CNN
F 3 "" H 7300 2650 60  0000 C CNN
	1    7300 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 3100 6750 2650
Wire Wire Line
	6750 2650 7000 2650
Wire Wire Line
	7000 2400 6650 2400
Wire Wire Line
	6650 2400 6650 3100
Wire Wire Line
	7000 2150 6550 2150
Wire Wire Line
	6550 2150 6550 3100
Wire Wire Line
	7000 1900 6450 1900
Wire Wire Line
	6450 1900 6450 3100
Wire Wire Line
	7600 1900 7650 1900
Wire Wire Line
	7650 1900 7650 2750
Wire Wire Line
	7650 2650 7600 2650
Wire Wire Line
	7600 2400 7650 2400
Connection ~ 7650 2400
Wire Wire Line
	7600 2150 7650 2150
Connection ~ 7650 2150
$Comp
L GND #PWR07
U 1 1 52769C19
P 7650 2750
F 0 "#PWR07" H 7650 2750 30  0001 C CNN
F 1 "GND" H 7650 2680 30  0001 C CNN
F 2 "" H 7650 2750 60  0000 C CNN
F 3 "" H 7650 2750 60  0000 C CNN
	1    7650 2750
	1    0    0    -1  
$EndComp
Connection ~ 7650 2650
$Comp
L GND #PWR08
U 1 1 52797EE5
P 8100 2700
F 0 "#PWR08" H 8100 2700 30  0001 C CNN
F 1 "GND" H 8100 2630 30  0001 C CNN
F 2 "" H 8100 2700 60  0000 C CNN
F 3 "" H 8100 2700 60  0000 C CNN
	1    8100 2700
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR09
U 1 1 52797EF4
P 8100 2050
F 0 "#PWR09" H 8100 2150 30  0001 C CNN
F 1 "VCC" H 8100 2150 30  0000 C CNN
F 2 "" H 8100 2050 60  0000 C CNN
F 3 "" H 8100 2050 60  0000 C CNN
	1    8100 2050
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 52797F03
P 8100 2350
F 0 "C1" H 8100 2200 40  0000 C CNN
F 1 "100nF" H 8100 2500 40  0000 C CNN
F 2 "C1" H 8100 2350 60  0001 C CNN
F 3 "~" H 8100 2350 60  0000 C CNN
	1    8100 2350
	0    1    1    0   
$EndComp
Wire Wire Line
	8100 2050 8100 2250
Wire Wire Line
	8100 2450 8100 2700
$EndSCHEMATC
