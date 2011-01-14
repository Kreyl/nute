EESchema Schematic File Version 2  date 17/08/2010 11:56:39
LIBS:Atmel_kl
LIBS:Connectors_kl
LIBS:power
LIBS:Power_kl
LIBS:Tittar_kl
LIBS:Transistors_kl
LIBS:CalmaLite-cache
EELAYER 24  0
EELAYER END
$Descr A4 11700 8267
Sheet 1 1
Title ""
Date "17 aug 2010"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Connection ~ 3600 2300
Wire Wire Line
	3600 2300 4100 2300
Wire Wire Line
	4100 2300 4100 2500
Wire Wire Line
	4100 2500 4550 2500
Wire Wire Line
	3600 2200 3600 2350
Wire Wire Line
	2250 3650 2250 3700
Wire Wire Line
	2250 2400 2250 2250
Wire Wire Line
	6250 2500 6900 2500
Wire Wire Line
	6250 2600 6400 2600
Connection ~ 6350 2400
Wire Wire Line
	6350 2400 6350 2300
Wire Wire Line
	4550 2700 4550 2850
Wire Wire Line
	6250 2400 6450 2400
Wire Wire Line
	6350 1900 6350 1800
Wire Wire Line
	6900 2600 7000 2600
Wire Wire Line
	7400 2600 7550 2600
Wire Wire Line
	2250 2850 2250 3000
Wire Wire Line
	3600 1550 3600 1700
Wire Wire Line
	3600 2750 3600 2850
$Comp
L +BATT #PWR?
U 1 1 4C6A4028
P 3600 1550
F 0 "#PWR?" H 3600 1510 30  0001 C CNN
F 1 "+BATT" H 3680 1580 30  0000 C CNN
	1    3600 1550
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR?
U 1 1 4C6A401E
P 3600 2850
F 0 "#PWR?" H 3690 2830 30  0001 C CNN
F 1 "GND" H 3600 2770 30  0001 C CNN
	1    3600 2850
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 4C6A4014
P 3600 1950
F 0 "R?" V 3680 1950 50  0000 C CNN
F 1 "10k" V 3600 1950 50  0000 C CNN
	1    3600 1950
	1    0    0    -1  
$EndComp
$Comp
L PHOTO Q?
U 1 1 4C6A3FFC
P 3550 2550
F 0 "Q?" H 3750 2600 60  0000 C CNN
F 1 "PHOTO" H 3800 2500 60  0000 C CNN
	1    3550 2550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 4C6A3F17
P 2250 3700
F 0 "#PWR?" H 2340 3680 30  0001 C CNN
F 1 "GND" H 2250 3620 30  0001 C CNN
	1    2250 3700
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 XL?
U 1 1 4C6A3EE3
P 2250 3450
F 0 "XL?" V 2200 3460 40  0000 C CNN
F 1 "CONN_1" V 2260 3470 40  0000 C CNN
	1    2250 3450
	0    -1   -1   0   
$EndComp
NoConn ~ 4550 2400
NoConn ~ 4550 2600
NoConn ~ 6250 2700
$Comp
L +BATT #PWR2
U 1 1 4C585A57
P 2250 2250
F 0 "#PWR2" H 2250 2200 20  0001 C CNN
F 1 "+BATT" H 2310 2290 30  0000 C CNN
	1    2250 2250
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR6
U 1 1 4C585A53
P 2250 3000
F 0 "#PWR6" H 2340 2980 30  0001 C CNN
F 1 "GND" H 2250 2920 30  0001 C CNN
	1    2250 3000
	1    0    0    -1  
$EndComp
$Comp
L BAT B1
U 1 1 4C585A4A
P 2250 2600
F 0 "B1" H 2400 2800 60  0000 C CNN
F 1 "BAT" H 2000 2800 60  0000 C CNN
	1    2250 2600
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 XL1
U 1 1 4C585A14
P 6900 2300
F 0 "XL1" V 6850 2310 40  0000 C CNN
F 1 "CONN_1" V 6910 2320 40  0000 C CNN
	1    6900 2300
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR5
U 1 1 4C585A02
P 4550 2850
F 0 "#PWR5" H 4640 2830 30  0001 C CNN
F 1 "GND" H 4550 2770 30  0001 C CNN
	1    4550 2850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR1
U 1 1 4C5859FD
P 6350 1800
F 0 "#PWR1" H 6440 1780 30  0001 C CNN
F 1 "GND" H 6350 1720 30  0001 C CNN
	1    6350 1800
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 4C5859F3
P 6350 2100
F 0 "C1" H 6400 2200 50  0000 L CNN
F 1 "0.1u" H 6400 2000 50  0000 L CNN
	1    6350 2100
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR3
U 1 1 4C5859BF
P 6450 2400
F 0 "#PWR3" H 6450 2350 20  0001 C CNN
F 1 "+BATT" H 6510 2440 30  0000 C CNN
	1    6450 2400
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR4
U 1 1 4C5859BA
P 7550 2600
F 0 "#PWR4" H 7550 2550 20  0001 C CNN
F 1 "+BATT" H 7610 2640 30  0000 C CNN
	1    7550 2600
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 4C5859A8
P 6650 2600
F 0 "R1" V 6730 2600 50  0000 C CNN
F 1 "12" V 6650 2600 50  0000 C CNN
	1    6650 2600
	0    1    1    0   
$EndComp
$Comp
L LED D1
U 1 1 4C585997
P 7200 2600
F 0 "D1" H 7300 2740 50  0000 C CNN
F 1 "LED" H 7120 2740 50  0000 C CNN
	1    7200 2600
	-1   0    0    1   
$EndComp
$Comp
L ATTINY45 DD1
U 1 1 4C58597E
P 5400 2600
F 0 "DD1" H 4950 2950 60  0000 C CNN
F 1 "ATTINY45" H 5700 2950 60  0000 C CNN
	1    5400 2600
	1    0    0    -1  
$EndComp
$EndSCHEMATC
