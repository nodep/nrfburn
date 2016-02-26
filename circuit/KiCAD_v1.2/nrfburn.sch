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
LIBS:nrfburn
LIBS:nrfburn-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L ATMEGA88PA-A IC1
U 1 1 556DAF54
P 5600 3400
F 0 "IC1" H 4850 4650 40  0000 L BNN
F 1 "ATMEGA88PA-A" H 6000 2000 40  0000 L BNN
F 2 "nrfburn:TQFP32" H 5600 3400 30  0000 C CIN
F 3 "" H 5600 3400 60  0000 C CNN
	1    5600 3400
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 556DA5DA
P 7350 4350
F 0 "R4" V 7430 4350 40  0000 C CNN
F 1 "10K" V 7357 4351 40  0000 C CNN
F 2 "nrfburn:Resistor_Horizontal_RM10mm" V 7280 4350 30  0001 C CNN
F 3 "" H 7350 4350 30  0000 C CNN
	1    7350 4350
	0    1    1    0   
$EndComp
$Comp
L GND #PWR01
U 1 1 556DA625
P 4600 4800
F 0 "#PWR01" H 4600 4800 30  0001 C CNN
F 1 "GND" H 4600 4730 30  0001 C CNN
F 2 "" H 4600 4800 60  0000 C CNN
F 3 "" H 4600 4800 60  0000 C CNN
	1    4600 4800
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR02
U 1 1 556DA6E4
P 7600 4300
F 0 "#PWR02" H 7600 4260 30  0001 C CNN
F 1 "+3.3V" H 7600 4410 30  0000 C CNN
F 2 "" H 7600 4300 60  0000 C CNN
F 3 "" H 7600 4300 60  0000 C CNN
	1    7600 4300
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR03
U 1 1 556DA834
P 4600 2200
F 0 "#PWR03" H 4600 2160 30  0001 C CNN
F 1 "+3.3V" H 4600 2350 30  0000 C CNN
F 2 "" H 4600 2200 60  0000 C CNN
F 3 "" H 4600 2200 60  0000 C CNN
	1    4600 2200
	1    0    0    -1  
$EndComp
$Comp
L XTAL X1
U 1 1 556DA94B
P 7400 2850
F 0 "X1" H 7400 2975 60  0000 C CNN
F 1 "12MHz" H 7425 2725 60  0000 C CNN
F 2 "nrfburn:Crystal_HC49-U_Vertical" H 7425 2875 60  0001 C CNN
F 3 "" H 7425 2875 60  0000 C CNN
	1    7400 2850
	0    1    1    0   
$EndComp
$Comp
L C C3
U 1 1 556DB37A
P 7800 2700
F 0 "C3" H 7800 2800 40  0000 L CNN
F 1 "18pF" H 7806 2615 40  0000 L CNN
F 2 "nrfburn:c_1206" H 7838 2550 30  0001 C CNN
F 3 "" H 7800 2700 60  0000 C CNN
	1    7800 2700
	0    1    1    0   
$EndComp
$Comp
L C C4
U 1 1 556DB3B9
P 7800 3000
F 0 "C4" H 7800 3100 40  0000 L CNN
F 1 "18pF" H 7806 2915 40  0000 L CNN
F 2 "nrfburn:c_1206" H 7838 2850 30  0001 C CNN
F 3 "" H 7800 3000 60  0000 C CNN
	1    7800 3000
	0    1    1    0   
$EndComp
$Comp
L GND #PWR04
U 1 1 556DB6CF
P 8100 3200
F 0 "#PWR04" H 8100 3200 30  0001 C CNN
F 1 "GND" H 8100 3130 30  0001 C CNN
F 2 "" H 8100 3200 60  0000 C CNN
F 3 "" H 8100 3200 60  0000 C CNN
	1    8100 3200
	1    0    0    -1  
$EndComp
$Comp
L LED D2
U 1 1 556DB83A
P 8550 3600
F 0 "D2" H 8550 3700 50  0000 C CNN
F 1 "ERR" H 8550 3500 50  0000 C CNN
F 2 "nrfburn:LED-3MM" H 8550 3600 60  0001 C CNN
F 3 "" H 8550 3600 60  0000 C CNN
	1    8550 3600
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 556DB8E5
P 8350 3800
F 0 "D1" H 8350 3900 50  0000 C CNN
F 1 "PROG" H 8350 3700 50  0000 C CNN
F 2 "nrfburn:LED-3MM" H 8350 3800 60  0001 C CNN
F 3 "" H 8350 3800 60  0000 C CNN
	1    8350 3800
	1    0    0    -1  
$EndComp
$Comp
L LED D3
U 1 1 556DB909
P 8550 4000
F 0 "D3" H 8550 4100 50  0000 C CNN
F 1 "USB" H 8550 3900 50  0000 C CNN
F 2 "nrfburn:LED-3MM" H 8550 4000 60  0001 C CNN
F 3 "" H 8550 4000 60  0000 C CNN
	1    8550 4000
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 556DBC51
P 7900 3600
F 0 "R5" V 7980 3600 40  0000 C CNN
F 1 "1K" V 7907 3601 40  0000 C CNN
F 2 "nrfburn:Resistor_Horizontal_RM10mm" V 7830 3600 30  0001 C CNN
F 3 "" H 7900 3600 30  0000 C CNN
	1    7900 3600
	0    1    1    0   
$EndComp
$Comp
L R R6
U 1 1 556DBCC3
P 7900 3800
F 0 "R6" V 7980 3800 40  0000 C CNN
F 1 "1K" V 7907 3801 40  0000 C CNN
F 2 "nrfburn:Resistor_Horizontal_RM10mm" V 7830 3800 30  0001 C CNN
F 3 "" H 7900 3800 30  0000 C CNN
	1    7900 3800
	0    1    1    0   
$EndComp
$Comp
L R R7
U 1 1 556DBD01
P 7900 4000
F 0 "R7" V 7980 4000 40  0000 C CNN
F 1 "1K" V 7907 4001 40  0000 C CNN
F 2 "nrfburn:Resistor_Horizontal_RM10mm" V 7830 4000 30  0001 C CNN
F 3 "" H 7900 4000 30  0000 C CNN
	1    7900 4000
	0    1    1    0   
$EndComp
$Comp
L GND #PWR05
U 1 1 556DC3CF
P 8850 4150
F 0 "#PWR05" H 8850 4150 30  0001 C CNN
F 1 "GND" H 8850 4080 30  0001 C CNN
F 2 "" H 8850 4150 60  0000 C CNN
F 3 "" H 8850 4150 60  0000 C CNN
	1    8850 4150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 556DB6D4
P 1800 3850
F 0 "#PWR06" H 1800 3850 30  0001 C CNN
F 1 "GND" H 1800 3780 30  0001 C CNN
F 2 "" H 1800 3850 60  0000 C CNN
F 3 "" H 1800 3850 60  0000 C CNN
	1    1800 3850
	1    0    0    -1  
$EndComp
$Comp
L VREG U2
U 1 1 556DBC38
P 2800 2250
F 0 "U2" H 2800 2500 60  0000 C CNN
F 1 "MCP1702" H 2800 2000 60  0000 C CNN
F 2 "nrfburn:SOT23" H 2775 2250 60  0001 C CNN
F 3 "" H 2775 2250 60  0000 C CNN
	1    2800 2250
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 556DC002
P 2300 2550
F 0 "C1" H 2300 2650 40  0000 L CNN
F 1 "1uF" H 2306 2465 40  0000 L CNN
F 2 "nrfburn:c_1206" H 2338 2400 30  0001 C CNN
F 3 "" H 2300 2550 60  0000 C CNN
	1    2300 2550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 556DC0DC
P 2300 2800
F 0 "#PWR07" H 2300 2800 30  0001 C CNN
F 1 "GND" H 2300 2730 30  0001 C CNN
F 2 "" H 2300 2800 60  0000 C CNN
F 3 "" H 2300 2800 60  0000 C CNN
	1    2300 2800
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 556DC240
P 3450 2450
F 0 "C2" H 3450 2550 40  0000 L CNN
F 1 "1uF" H 3456 2365 40  0000 L CNN
F 2 "nrfburn:c_1206" H 3488 2300 30  0001 C CNN
F 3 "" H 3450 2450 60  0000 C CNN
	1    3450 2450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 556DC334
P 3350 2850
F 0 "#PWR08" H 3350 2850 30  0001 C CNN
F 1 "GND" H 3350 2780 30  0001 C CNN
F 2 "" H 3350 2850 60  0000 C CNN
F 3 "" H 3350 2850 60  0000 C CNN
	1    3350 2850
	1    0    0    -1  
$EndComp
$Comp
L LE1_PRG U5
U 1 1 556EAFE6
P 8900 5000
F 0 "U5" H 8900 4650 60  0000 C CNN
F 1 "LE1_PRG" H 8900 5350 60  0000 C CNN
F 2 "nrfburn:NRF_ICSP_RibbonCable" H 8850 4900 60  0001 C CNN
F 3 "" H 8850 4900 60  0000 C CNN
	1    8900 5000
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 556EB3D0
P 2500 3750
F 0 "R1" V 2580 3750 40  0000 C CNN
F 1 "68R" V 2507 3751 40  0000 C CNN
F 2 "nrfburn:Resistor_Horizontal_RM10mm" V 2430 3750 30  0001 C CNN
F 3 "" H 2500 3750 30  0000 C CNN
	1    2500 3750
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 556EB4F7
P 2700 3550
F 0 "R2" V 2780 3550 40  0000 C CNN
F 1 "68R" V 2707 3551 40  0000 C CNN
F 2 "nrfburn:Resistor_Horizontal_RM10mm" V 2630 3550 30  0001 C CNN
F 3 "" H 2700 3550 30  0000 C CNN
	1    2700 3550
	0    1    1    0   
$EndComp
$Comp
L R R3
U 1 1 556EB585
P 2700 3400
F 0 "R3" V 2780 3400 40  0000 C CNN
F 1 "1K5" V 2707 3401 40  0000 C CNN
F 2 "nrfburn:Resistor_Horizontal_RM10mm" V 2630 3400 30  0001 C CNN
F 3 "" H 2700 3400 30  0000 C CNN
	1    2700 3400
	0    1    1    0   
$EndComp
Text Label 2850 3750 0    60   ~ 0
D+
Text Label 2950 3550 0    60   ~ 0
D-
Text Label 2950 3400 0    60   ~ 0
DPU
Text Label 6650 4100 0    60   ~ 0
D+
Text Label 6650 4200 0    60   ~ 0
D-
Text Label 6650 4300 0    60   ~ 0
DPU
$Comp
L +3.3V #PWR09
U 1 1 556EC399
P 3450 2050
F 0 "#PWR09" H 3450 2010 30  0001 C CNN
F 1 "+3.3V" H 3450 2200 30  0000 C CNN
F 2 "" H 3450 2050 60  0000 C CNN
F 3 "" H 3450 2050 60  0000 C CNN
	1    3450 2050
	1    0    0    -1  
$EndComp
Text Label 6650 2500 0    60   ~ 0
CSN
Text Label 6650 2600 0    60   ~ 0
MOSI
Text Label 6650 2700 0    60   ~ 0
MISO
Text Label 6650 2800 0    60   ~ 0
SCK
Text Label 6650 4400 0    60   ~ 0
PROG
Text Label 6650 3150 0    60   ~ 0
TGT_RST
Text Label 9450 4850 0    60   ~ 0
SCK
Text Label 9450 4950 0    60   ~ 0
MOSI
Text Label 9450 5050 0    60   ~ 0
MISO
Text Label 9450 5150 0    60   ~ 0
CSN
$Comp
L +3.3V #PWR010
U 1 1 556EDF7B
P 8300 4750
F 0 "#PWR010" H 8300 4710 30  0001 C CNN
F 1 "+3.3V" H 8300 4860 30  0000 C CNN
F 2 "" H 8300 4750 60  0000 C CNN
F 3 "" H 8300 4750 60  0000 C CNN
	1    8300 4750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 556EE2EA
P 8300 5250
F 0 "#PWR011" H 8300 5250 30  0001 C CNN
F 1 "GND" H 8300 5180 30  0001 C CNN
F 2 "" H 8300 5250 60  0000 C CNN
F 3 "" H 8300 5250 60  0000 C CNN
	1    8300 5250
	1    0    0    -1  
$EndComp
Text Label 8000 4950 0    60   ~ 0
PROG
Text Label 8000 5050 0    60   ~ 0
TGT_RST
$Comp
L +5V #PWR012
U 1 1 556EE8ED
P 1800 2150
F 0 "#PWR012" H 1800 2240 20  0001 C CNN
F 1 "+5V" H 1800 2300 30  0000 C CNN
F 2 "" H 1800 2150 60  0000 C CNN
F 3 "" H 1800 2150 60  0000 C CNN
	1    1800 2150
	1    0    0    -1  
$EndComp
$Comp
L AVR-ISP6 U1
U 1 1 556EB488
P 2450 5300
F 0 "U1" H 2450 5500 50  0000 C CNN
F 1 "AVR-ISP6" H 2210 5070 50  0000 L BNN
F 2 "nrfburn:AVR_ISP6" V 1930 5340 50  0001 C CNN
F 3 "" H 2450 5300 60  0000 C CNN
	1    2450 5300
	1    0    0    -1  
$EndComp
Text Label 2800 5300 0    60   ~ 0
MOSI
Text Label 1750 5200 0    60   ~ 0
MISO
Text Label 1750 5300 0    60   ~ 0
SCK
Text Label 1750 5400 0    60   ~ 0
AVR_RST
Text Label 6650 4000 0    60   ~ 0
AVR_TX
$Comp
L LU1_PRG_DNGL U4
U 1 1 556EC793
P 6400 6250
F 0 "U4" H 6400 5800 60  0000 C CNN
F 1 "LU1_PRG_DNGL" V 6650 6250 60  0000 C CNN
F 2 "nrfburn:LU1_PRG_DONGLE" H 6600 6000 60  0001 C CNN
F 3 "" H 6600 6000 60  0000 C CNN
	1    6400 6250
	1    0    0    -1  
$EndComp
$Comp
L LU1_PRG_SPRKFN U3
U 1 1 556EC91F
P 4900 6400
F 0 "U3" H 4900 5800 60  0000 C CNN
F 1 "LU1_PRG_SPRKFN" V 5250 6400 60  0000 C CNN
F 2 "nrfburn:Pin_Header_Straight_1x10" H 4900 6300 60  0001 C CNN
F 3 "" H 4900 6300 60  0000 C CNN
	1    4900 6400
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR013
U 1 1 556ED3C8
P 4300 5350
F 0 "#PWR013" H 4300 5440 20  0001 C CNN
F 1 "+5V" H 4300 5440 30  0000 C CNN
F 2 "" H 4300 5350 60  0000 C CNN
F 3 "" H 4300 5350 60  0000 C CNN
	1    4300 5350
	1    0    0    -1  
$EndComp
Text Label 3950 6050 0    60   ~ 0
PROG
Text Label 3950 6150 0    60   ~ 0
TGT_RST
$Comp
L GND #PWR014
U 1 1 556EDFAE
P 3750 6350
F 0 "#PWR014" H 3750 6350 30  0001 C CNN
F 1 "GND" H 3750 6280 30  0001 C CNN
F 2 "" H 3750 6350 60  0000 C CNN
F 3 "" H 3750 6350 60  0000 C CNN
	1    3750 6350
	1    0    0    -1  
$EndComp
Text Label 3950 6350 0    60   ~ 0
SCK
Text Label 3950 6450 0    60   ~ 0
MOSI
Text Label 3950 6550 0    60   ~ 0
MISO
Text Label 3950 6650 0    60   ~ 0
CSN
Text Label 3950 6750 0    60   ~ 0
DBG1
Text Label 3950 6850 0    60   ~ 0
DBG2
Wire Wire Line
	7600 4300 7600 4350
Wire Wire Line
	7600 4350 7500 4350
Wire Wire Line
	4700 4400 4600 4400
Wire Wire Line
	4600 4400 4600 4800
Wire Wire Line
	4700 4500 4600 4500
Connection ~ 4600 4500
Wire Wire Line
	4700 4600 4600 4600
Connection ~ 4600 4600
Wire Wire Line
	4600 2200 4600 2600
Wire Wire Line
	4600 2400 4700 2400
Wire Wire Line
	4700 2300 4600 2300
Connection ~ 4600 2300
Wire Wire Line
	4600 2600 4700 2600
Connection ~ 4600 2400
Wire Wire Line
	7150 2700 7650 2700
Wire Wire Line
	6600 3000 7650 3000
Connection ~ 7400 2700
Connection ~ 7400 3000
Wire Wire Line
	7950 2700 8100 2700
Wire Wire Line
	8100 2700 8100 3200
Wire Wire Line
	7950 3000 8100 3000
Connection ~ 8100 3000
Wire Wire Line
	7650 3600 7650 3250
Wire Wire Line
	7550 3350 7550 3800
Wire Wire Line
	7450 3450 7450 4000
Wire Wire Line
	7150 2700 7150 2900
Wire Wire Line
	7150 2900 6600 2900
Wire Wire Line
	8750 3600 8850 3600
Wire Wire Line
	8850 3600 8850 4150
Wire Wire Line
	8550 3800 8850 3800
Connection ~ 8850 3800
Wire Wire Line
	8750 4000 8850 4000
Connection ~ 8850 4000
Wire Wire Line
	2300 2700 2300 2800
Wire Wire Line
	3150 2300 3250 2300
Wire Wire Line
	3250 2300 3250 2750
Wire Wire Line
	3250 2750 3450 2750
Wire Wire Line
	3450 2750 3450 2600
Wire Wire Line
	3350 2750 3350 2850
Connection ~ 3350 2750
Wire Wire Line
	3150 2200 3450 2200
Wire Wire Line
	1700 3550 2550 3550
Wire Wire Line
	2550 3400 2350 3400
Connection ~ 2350 3550
Wire Wire Line
	2650 3750 3250 3750
Wire Wire Line
	2850 3550 3250 3550
Wire Wire Line
	2850 3400 3250 3400
Wire Wire Line
	6600 4100 6900 4100
Wire Wire Line
	6600 4200 6900 4200
Wire Wire Line
	6600 4300 6900 4300
Connection ~ 3450 2200
Wire Wire Line
	6600 2800 6900 2800
Wire Wire Line
	6900 2700 6600 2700
Wire Wire Line
	6600 2600 6900 2600
Wire Wire Line
	6600 2500 6900 2500
Wire Wire Line
	6600 4400 6900 4400
Wire Wire Line
	7650 3250 6600 3250
Wire Wire Line
	7550 3350 6600 3350
Wire Wire Line
	6600 3450 7450 3450
Wire Wire Line
	6600 3150 7050 3150
Wire Wire Line
	9400 5150 9750 5150
Wire Wire Line
	9400 5050 9750 5050
Wire Wire Line
	9400 4950 9750 4950
Wire Wire Line
	9400 4850 9750 4850
Wire Wire Line
	8400 4850 8300 4850
Wire Wire Line
	8300 4850 8300 4750
Wire Wire Line
	8000 4950 8400 4950
Wire Wire Line
	8400 5050 8000 5050
Wire Wire Line
	8400 5150 8300 5150
Wire Wire Line
	8300 5150 8300 5250
Wire Wire Line
	2750 5200 2850 5200
Wire Wire Line
	2850 5200 2850 5100
Wire Wire Line
	2750 5400 2850 5400
Wire Wire Line
	2850 5400 2850 5500
Wire Wire Line
	2750 5300 3000 5300
Wire Wire Line
	2150 5200 1750 5200
Wire Wire Line
	2150 5300 1750 5300
Wire Wire Line
	2150 5400 1750 5400
Wire Wire Line
	6600 4000 6900 4000
Wire Wire Line
	4300 5950 4400 5950
Wire Wire Line
	4300 5600 4300 5950
Wire Wire Line
	4300 5750 6000 5750
Wire Wire Line
	6000 5750 6000 5950
Wire Wire Line
	6000 5950 6100 5950
Wire Wire Line
	4150 5500 4300 5500
Wire Wire Line
	4300 5500 4300 5350
Wire Wire Line
	4150 5600 4300 5600
Connection ~ 4300 5750
Wire Wire Line
	4400 6050 3900 6050
Wire Wire Line
	4400 6150 3900 6150
Wire Wire Line
	4400 6250 3750 6250
Wire Wire Line
	3750 6250 3750 6350
Wire Wire Line
	4400 6350 3900 6350
Wire Wire Line
	4400 6450 3900 6450
Wire Wire Line
	4400 6550 3900 6550
Wire Wire Line
	4400 6650 3900 6650
Wire Wire Line
	3650 6750 4400 6750
Wire Wire Line
	3650 6850 4400 6850
Wire Wire Line
	6100 6050 5800 6050
Wire Wire Line
	5800 6150 6100 6150
Wire Wire Line
	6100 6250 5800 6250
Wire Wire Line
	5800 6350 6100 6350
Wire Wire Line
	6100 6450 5800 6450
Wire Wire Line
	5800 6550 6100 6550
Text Label 5800 6050 0    60   ~ 0
PROG
Text Label 5800 6150 0    60   ~ 0
SCK
Text Label 5800 6250 0    60   ~ 0
MOSI
Text Label 5800 6350 0    60   ~ 0
MISO
Text Label 5800 6450 0    60   ~ 0
CSN
$Comp
L GND #PWR015
U 1 1 556EEC40
P 5800 6650
F 0 "#PWR015" H 5800 6650 30  0001 C CNN
F 1 "GND" H 5800 6580 30  0001 C CNN
F 2 "" H 5800 6650 60  0000 C CNN
F 3 "" H 5800 6650 60  0000 C CNN
	1    5800 6650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 6550 5800 6650
$Comp
L DBG U6
U 1 1 556EF41F
P 9100 1450
F 0 "U6" H 9125 1225 60  0000 C CNN
F 1 "DBG_LU1" H 9125 1675 60  0000 C CNN
F 2 "nrfburn:Pin_Header_Straight_1x03" H 9075 1450 60  0001 C CNN
F 3 "" H 9075 1450 60  0000 C CNN
	1    9100 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 1550 8800 1550
Wire Wire Line
	8800 1550 8800 1650
Wire Wire Line
	8900 1450 8350 1450
Wire Wire Line
	8350 1450 8350 1400
$Comp
L +3.3V #PWR016
U 1 1 556EF8AA
P 8350 1400
F 0 "#PWR016" H 8350 1360 30  0001 C CNN
F 1 "+3.3V" H 8350 1510 30  0000 C CNN
F 2 "" H 8350 1400 60  0000 C CNN
F 3 "" H 8350 1400 60  0000 C CNN
	1    8350 1400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 556EF9A5
P 8800 1650
F 0 "#PWR017" H 8800 1650 30  0001 C CNN
F 1 "GND" H 8800 1580 30  0001 C CNN
F 2 "" H 8800 1650 60  0000 C CNN
F 3 "" H 8800 1650 60  0000 C CNN
	1    8800 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 1350 8500 1350
Wire Wire Line
	8750 2600 8650 2600
Wire Wire Line
	8650 2600 8650 2700
$Comp
L GND #PWR018
U 1 1 556F0DED
P 8650 2700
F 0 "#PWR018" H 8650 2700 30  0001 C CNN
F 1 "GND" H 8650 2630 30  0001 C CNN
F 2 "" H 8650 2700 60  0000 C CNN
F 3 "" H 8650 2700 60  0000 C CNN
	1    8650 2700
	-1   0    0    -1  
$EndComp
$Comp
L +3.3V #PWR019
U 1 1 556F0E2C
P 8400 2500
F 0 "#PWR019" H 8400 2460 30  0001 C CNN
F 1 "+3.3V" H 8400 2610 30  0000 C CNN
F 2 "" H 8400 2500 60  0000 C CNN
F 3 "" H 8400 2500 60  0000 C CNN
	1    8400 2500
	0    -1   1    0   
$EndComp
Wire Wire Line
	6600 2300 8750 2300
Wire Wire Line
	6600 2400 8750 2400
Text Label 8700 2300 2    60   ~ 0
SWDIO
Text Label 8700 2400 2    60   ~ 0
SWCLK
Wire Wire Line
	8750 2500 8400 2500
$Comp
L +3.3V #PWR020
U 1 1 556EF82A
P 2850 5100
F 0 "#PWR020" H 2850 5060 30  0001 C CNN
F 1 "+3.3V" H 2850 5210 30  0000 C CNN
F 2 "" H 2850 5100 60  0000 C CNN
F 3 "" H 2850 5100 60  0000 C CNN
	1    2850 5100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR021
U 1 1 556EFA09
P 2850 5500
F 0 "#PWR021" H 2850 5500 30  0001 C CNN
F 1 "GND" H 2850 5430 30  0001 C CNN
F 2 "" H 2850 5500 60  0000 C CNN
F 3 "" H 2850 5500 60  0000 C CNN
	1    2850 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 3750 7150 3750
Wire Wire Line
	7150 3750 7150 4350
Wire Wire Line
	7150 4350 7200 4350
Text Label 6650 3750 0    60   ~ 0
AVR_RST
Wire Wire Line
	7650 3600 7750 3600
Wire Wire Line
	7550 3800 7750 3800
Wire Wire Line
	7450 4000 7750 4000
Wire Wire Line
	8050 3600 8350 3600
Wire Wire Line
	8150 3800 8050 3800
Wire Wire Line
	8050 4000 8350 4000
Text Label 8550 1350 0    60   ~ 0
MISO
$Comp
L DBG U7
U 1 1 556F16EC
P 7500 1450
F 0 "U7" H 7525 1225 60  0000 C CNN
F 1 "DBG_AVR" H 7525 1675 60  0000 C CNN
F 2 "nrfburn:Pin_Header_Straight_1x03" H 7475 1450 60  0001 C CNN
F 3 "" H 7475 1450 60  0000 C CNN
	1    7500 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 1450 6650 1450
Wire Wire Line
	6650 1450 6650 1400
Wire Wire Line
	7300 1550 7200 1550
Wire Wire Line
	7200 1550 7200 1650
$Comp
L +3.3V #PWR022
U 1 1 556F219D
P 6650 1400
F 0 "#PWR022" H 6650 1360 30  0001 C CNN
F 1 "+3.3V" H 6650 1510 30  0000 C CNN
F 2 "" H 6650 1400 60  0000 C CNN
F 3 "" H 6650 1400 60  0000 C CNN
	1    6650 1400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR023
U 1 1 556F22E0
P 7200 1650
F 0 "#PWR023" H 7200 1650 30  0001 C CNN
F 1 "GND" H 7200 1580 30  0001 C CNN
F 2 "" H 7200 1650 60  0000 C CNN
F 3 "" H 7200 1650 60  0000 C CNN
	1    7200 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 1350 6850 1350
Text Label 6850 1350 0    60   ~ 0
AVR_TX
$Comp
L PINH_01X02 P1
U 1 1 5571856D
P 3950 5550
F 0 "P1" H 3950 5700 50  0000 C CNN
F 1 "PWR_5V" V 4050 5550 50  0000 C CNN
F 2 "nrfburn:Pin_Header_Straight_1x02" H 3950 5550 60  0001 C CNN
F 3 "" H 3950 5550 60  0000 C CNN
	1    3950 5550
	-1   0    0    1   
$EndComp
$Comp
L PINH_01X04 P3
U 1 1 5571897A
P 8950 2450
F 0 "P3" H 8950 2700 50  0000 C CNN
F 1 "SWD" V 9050 2450 50  0000 C CNN
F 2 "nrfburn:Pin_Header_Straight_1x04" H 8950 2450 60  0001 C CNN
F 3 "" H 8950 2450 60  0000 C CNN
	1    8950 2450
	1    0    0    1   
$EndComp
$Comp
L R R9
U 1 1 55718483
P 2750 6950
F 0 "R9" V 2830 6950 40  0000 C CNN
F 1 "1K" V 2757 6951 40  0000 C CNN
F 2 "nrfburn:Resistor_Horizontal_RM10mm" V 2680 6950 30  0001 C CNN
F 3 "" H 2750 6950 30  0000 C CNN
	1    2750 6950
	0    1    1    0   
$EndComp
$Comp
L LED D4
U 1 1 5571865C
P 3250 6650
F 0 "D4" H 3250 6750 50  0000 C CNN
F 1 "DBG1" H 3250 6550 50  0000 C CNN
F 2 "nrfburn:LED-3MM" H 3250 6650 60  0001 C CNN
F 3 "" H 3250 6650 60  0000 C CNN
	1    3250 6650
	-1   0    0    1   
$EndComp
$Comp
L LED D5
U 1 1 557187D4
P 3250 6950
F 0 "D5" H 3250 7050 50  0000 C CNN
F 1 "DBG2" H 3250 6850 50  0000 C CNN
F 2 "nrfburn:LED-3MM" H 3250 6950 60  0001 C CNN
F 3 "" H 3250 6950 60  0000 C CNN
	1    3250 6950
	-1   0    0    1   
$EndComp
$Comp
L R R8
U 1 1 55718830
P 2750 6650
F 0 "R8" V 2830 6650 40  0000 C CNN
F 1 "1K" V 2757 6651 40  0000 C CNN
F 2 "nrfburn:Resistor_Horizontal_RM10mm" V 2680 6650 30  0001 C CNN
F 3 "" H 2750 6650 30  0000 C CNN
	1    2750 6650
	0    1    1    0   
$EndComp
Wire Wire Line
	3650 6750 3650 6650
Wire Wire Line
	3650 6650 3450 6650
Wire Wire Line
	3450 6950 3650 6950
Wire Wire Line
	3650 6950 3650 6850
Wire Wire Line
	2900 6650 3050 6650
Wire Wire Line
	3050 6950 2900 6950
Wire Wire Line
	2600 6650 2400 6650
Wire Wire Line
	2400 6650 2400 7050
Wire Wire Line
	2400 6950 2600 6950
$Comp
L GND #PWR024
U 1 1 55719087
P 2400 7050
F 0 "#PWR024" H 2400 7050 30  0001 C CNN
F 1 "GND" H 2400 6980 30  0001 C CNN
F 2 "" H 2400 7050 60  0000 C CNN
F 3 "" H 2400 7050 60  0000 C CNN
	1    2400 7050
	1    0    0    -1  
$EndComp
Connection ~ 2400 6950
NoConn ~ 1300 3950
Wire Wire Line
	2100 3750 2350 3750
Wire Wire Line
	2350 3400 2350 3550
Wire Wire Line
	3450 2050 3450 2300
Wire Wire Line
	1700 3650 2100 3650
Wire Wire Line
	2100 3650 2100 3750
Wire Wire Line
	1700 3750 1800 3750
Wire Wire Line
	1800 3750 1800 3850
Wire Wire Line
	1800 3450 1700 3450
Wire Wire Line
	1800 2150 1800 3450
Wire Wire Line
	1800 2200 2500 2200
Wire Wire Line
	2300 2200 2300 2400
Connection ~ 1800 2200
Connection ~ 2300 2200
$Comp
L USB_B P2
U 1 1 56A0A32A
P 1400 3650
F 0 "P2" H 1600 3450 50  0000 C CNN
F 1 "USB_B" H 1350 3850 50  0000 C CNN
F 2 "nrfburn:USB_B_loc" V 1350 3550 50  0001 C CNN
F 3 "" V 1350 3550 50  0000 C CNN
	1    1400 3650
	0    -1   1    0   
$EndComp
$EndSCHEMATC
