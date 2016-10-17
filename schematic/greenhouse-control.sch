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
LIBS:arduino
LIBS:shield_arduino
LIBS:74xgxx
LIBS:ac-dc
LIBS:actel
LIBS:Altera
LIBS:analog_devices
LIBS:battery_management
LIBS:bbd
LIBS:brooktre
LIBS:cmos_ieee
LIBS:dc-dc
LIBS:diode
LIBS:elec-unifil
LIBS:ESD_Protection
LIBS:ftdi
LIBS:gennum
LIBS:graphic
LIBS:hc11
LIBS:ir
LIBS:Lattice
LIBS:logo
LIBS:maxim
LIBS:microchip_dspic33dsc
LIBS:microchip_pic10mcu
LIBS:microchip_pic12mcu
LIBS:microchip_pic16mcu
LIBS:microchip_pic18mcu
LIBS:microchip_pic32mcu
LIBS:motor_drivers
LIBS:motors
LIBS:msp430
LIBS:nordicsemi
LIBS:nxp_armmcu
LIBS:onsemi
LIBS:Oscillators
LIBS:powerint
LIBS:Power_Management
LIBS:pspice
LIBS:references
LIBS:relays
LIBS:rfcom
LIBS:sensors
LIBS:silabs
LIBS:stm8
LIBS:stm32
LIBS:supertex
LIBS:switches
LIBS:transf
LIBS:ttl_ieee
LIBS:video
LIBS:Worldsemi
LIBS:Xicor
LIBS:Zilog
LIBS:greenhouse-control-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Greenhouse Control"
Date "2016-10-07"
Rev "0.2"
Comp "Michael Langeder"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ARDUINO_NANO SH1
U 1 1 57F73003
P 1975 1775
F 0 "SH1" H 1950 700 60  0000 C CNN
F 1 "ARDUINO_NANO" H 1950 2825 60  0000 C CNN
F 2 "" H 1050 1175 60  0001 C CNN
F 3 "" H 1050 1175 60  0000 C CNN
	1    1975 1775
	1    0    0    -1  
$EndComp
$Comp
L LCD16X2 DS1
U 1 1 57F731F3
P 10250 1225
F 0 "DS1" H 9450 1625 50  0000 C CNN
F 1 "LCD20x4" H 10950 1625 50  0000 C CNN
F 2 "Display:WC1602A" H 10250 1175 50  0000 C CIN
F 3 "" H 10250 1225 50  0000 C CNN
	1    10250 1225
	1    0    0    -1  
$EndComp
$Comp
L PCF8574 U3
U 1 1 57F7327A
P 8900 2800
F 0 "U3" H 8550 3400 50  0000 L CNN
F 1 "PCF8574" H 9000 3400 50  0000 L CNN
F 2 "" H 8900 2800 50  0001 C CNN
F 3 "" H 8900 2800 50  0000 C CNN
	1    8900 2800
	1    0    0    -1  
$EndComp
Text GLabel 8225 3675 0    60   Input ~ 0
GND
Text GLabel 8175 1875 0    60   Input ~ 0
5V
Text GLabel 9600 1825 3    60   Input ~ 0
5V
Text GLabel 9500 2000 3    60   Input ~ 0
GND
Wire Wire Line
	8400 2700 8325 2700
Wire Wire Line
	8325 2700 8325 3675
Wire Wire Line
	8325 2800 8400 2800
Wire Wire Line
	8325 2900 8400 2900
Connection ~ 8325 2800
Wire Wire Line
	8225 3675 8900 3675
Wire Wire Line
	8900 3675 8900 3500
Connection ~ 8325 2900
Connection ~ 8325 3675
Wire Wire Line
	8900 2100 8900 1875
Wire Wire Line
	8900 1875 8175 1875
Wire Wire Line
	9500 2000 9500 1725
Wire Wire Line
	9600 1825 9600 1725
Wire Wire Line
	9800 1725 9800 1900
Wire Wire Line
	9800 1900 10900 1900
Wire Wire Line
	10900 1900 10900 1725
Wire Wire Line
	10800 1725 10800 1900
Connection ~ 10800 1900
Wire Wire Line
	10700 1725 10700 1900
Connection ~ 10700 1900
Wire Wire Line
	10600 1725 10600 1900
Connection ~ 10600 1900
Wire Wire Line
	10500 1725 10500 1900
Connection ~ 10500 1900
Wire Wire Line
	10400 1725 10400 1900
Connection ~ 10400 1900
Wire Wire Line
	10300 2800 10300 1725
Connection ~ 10300 1900
Wire Wire Line
	10200 1725 10200 1900
Connection ~ 10200 1900
Wire Wire Line
	10100 1725 10100 1900
Connection ~ 10100 1900
Wire Wire Line
	10000 1725 10000 1900
Connection ~ 10000 1900
Wire Wire Line
	9900 1725 9900 1900
Connection ~ 9900 1900
Wire Wire Line
	9400 2800 10300 2800
Wire Wire Line
	9550 2400 9550 3100
Wire Wire Line
	9550 2400 9400 2400
Wire Wire Line
	9400 2500 9550 2500
Connection ~ 9550 2500
Wire Wire Line
	9400 2600 9550 2600
Connection ~ 9550 2600
Wire Wire Line
	9400 2700 9550 2700
Connection ~ 9550 2700
Connection ~ 9550 2800
Wire Wire Line
	9550 2900 9400 2900
Wire Wire Line
	9400 3000 9550 3000
Connection ~ 9550 2900
Wire Wire Line
	9550 3100 9400 3100
Connection ~ 9550 3000
Text GLabel 8200 2400 0    60   BiDi ~ 0
I2C_SCL
Text GLabel 8200 2500 0    60   BiDi ~ 0
I2C_SDA
Wire Wire Line
	8400 2400 8200 2400
Wire Wire Line
	8400 2500 8200 2500
Text GLabel 2825 2050 2    60   BiDi ~ 0
I2C_SCL
Text GLabel 2825 1925 2    60   BiDi ~ 0
I2C_SDA
Wire Wire Line
	2825 1925 2625 1925
Wire Wire Line
	2625 2050 2825 2050
Text GLabel 2825 925  2    60   Input ~ 0
12V
Wire Wire Line
	2825 925  2625 925 
Text GLabel 2825 1300 2    60   Input ~ 0
5V
Text GLabel 2825 1050 2    60   Input ~ 0
GND
Text GLabel 1125 1300 0    60   Input ~ 0
GND
Wire Wire Line
	2625 1050 2825 1050
Wire Wire Line
	2825 1300 2625 1300
Wire Wire Line
	1325 1300 1125 1300
Text GLabel 2825 1425 2    60   Input ~ 0
SENSE_A0
Text GLabel 2825 1550 2    60   Input ~ 0
SENSE_A1
Text GLabel 2825 1675 2    60   Input ~ 0
SENSE_A2
Text GLabel 2825 1800 2    60   Input ~ 0
SENSE_A3
Wire Wire Line
	2625 1425 2825 1425
Wire Wire Line
	2625 1550 2825 1550
Wire Wire Line
	2625 1675 2825 1675
Wire Wire Line
	2625 1800 2825 1800
Text GLabel 2825 2175 2    60   Input ~ 0
SENSE_A6
Text GLabel 2825 2300 2    60   Input ~ 0
SENSE_A7
Wire Wire Line
	2625 2175 2825 2175
Wire Wire Line
	2625 2300 2825 2300
Text GLabel 1125 2675 0    60   Input ~ 0
PIN_D12
Wire Wire Line
	1325 2675 1125 2675
Text GLabel 1100 2050 0    60   Input ~ 0
TRIGGER
Text GLabel 1100 2175 0    60   Input ~ 0
ECHO
Wire Wire Line
	1325 2050 1100 2050
Wire Wire Line
	1325 2175 1100 2175
$Comp
L BC547 Q1
U 1 1 57F75C9B
P 5150 1425
F 0 "Q1" H 5350 1500 50  0000 L CNN
F 1 "BC547" H 5350 1425 50  0000 L CNN
F 2 "TO-92" H 5350 1350 50  0000 L CIN
F 3 "" H 5150 1425 50  0000 L CNN
	1    5150 1425
	1    0    0    -1  
$EndComp
Text GLabel 3950 825  0    60   Input ~ 0
5V
$Comp
L R R2
U 1 1 57F75E89
P 5250 1000
F 0 "R2" V 5330 1000 50  0000 C CNN
F 1 "10" V 5250 1000 50  0000 C CNN
F 2 "" V 5180 1000 50  0001 C CNN
F 3 "" H 5250 1000 50  0000 C CNN
	1    5250 1000
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 57F75F1A
P 4675 1425
F 0 "R1" V 4755 1425 50  0000 C CNN
F 1 "1k" V 4675 1425 50  0000 C CNN
F 2 "" V 4605 1425 50  0001 C CNN
F 3 "" H 4675 1425 50  0000 C CNN
	1    4675 1425
	0    1    1    0   
$EndComp
$Comp
L R R_soil1
U 1 1 57F760D7
P 4250 1425
F 0 "R_soil1" V 4330 1425 50  0000 C CNN
F 1 "SOIL" V 4250 1425 50  0000 C CNN
F 2 "" V 4180 1425 50  0001 C CNN
F 3 "" H 4250 1425 50  0000 C CNN
	1    4250 1425
	0    1    1    0   
$EndComp
Wire Wire Line
	3950 825  5250 825 
Wire Wire Line
	4050 825  4050 1425
Wire Wire Line
	4050 1425 4100 1425
Wire Wire Line
	4400 1425 4525 1425
Wire Wire Line
	4825 1425 4950 1425
Wire Wire Line
	5250 1150 5250 1225
Wire Wire Line
	5250 825  5250 850 
Connection ~ 4050 825 
Text GLabel 3950 1700 0    60   Input ~ 0
GND
Wire Wire Line
	5250 1625 5250 1700
Wire Wire Line
	5250 1700 3950 1700
Text GLabel 5400 1175 2    60   Input ~ 0
SENSE_A0
Wire Wire Line
	5400 1175 5250 1175
Connection ~ 5250 1175
Text GLabel 1125 1550 0    60   Input ~ 0
SIG_FAN
Text GLabel 1125 1675 0    60   Input ~ 0
SIG_PUMP1
Wire Wire Line
	1325 1550 1125 1550
Wire Wire Line
	1325 1675 1125 1675
$Comp
L ULN2003 U1
U 1 1 57F788A0
P 2175 4225
F 0 "U1" H 2175 4325 50  0000 C CNN
F 1 "ULN2003" H 2175 4125 50  0000 C CNN
F 2 "" H 2175 4225 50  0001 C CNN
F 3 "" H 2175 4225 50  0000 C CNN
	1    2175 4225
	1    0    0    -1  
$EndComp
Text GLabel 1300 3825 0    60   Input ~ 0
SIG_FAN
Text GLabel 1300 4025 0    60   Input ~ 0
SIG_PUMP1
Wire Wire Line
	1325 3825 1525 3825
Wire Wire Line
	1450 3825 1450 3925
Wire Wire Line
	1450 3925 1525 3925
Connection ~ 1450 3825
Wire Wire Line
	1300 4025 1525 4025
Wire Wire Line
	1525 4125 1450 4125
Wire Wire Line
	1450 4125 1450 4025
Connection ~ 1450 4025
Text GLabel 4025 3250 2    60   Input ~ 0
12V
$Comp
L INDUCTOR L_FAN1
U 1 1 57F7906A
P 3300 3825
F 0 "L_FAN1" V 3250 3825 50  0000 C CNN
F 1 "INDUCTOR" V 3400 3825 50  0001 C CNN
F 2 "" H 3300 3825 50  0001 C CNN
F 3 "" H 3300 3825 50  0000 C CNN
	1    3300 3825
	0    1    1    0   
$EndComp
$Comp
L INDUCTOR L_PUMP1
U 1 1 57F79157
P 3300 4025
F 0 "L_PUMP1" V 3250 4025 50  0000 C CNN
F 1 "INDUCTOR" V 3400 4025 50  0001 C CNN
F 2 "" H 3300 4025 50  0001 C CNN
F 3 "" H 3300 4025 50  0000 C CNN
	1    3300 4025
	0    1    1    0   
$EndComp
Wire Wire Line
	2825 3825 3000 3825
Wire Wire Line
	2825 3925 2900 3925
Wire Wire Line
	2900 3925 2900 3825
Connection ~ 2900 3825
Wire Wire Line
	2825 4025 3000 4025
Wire Wire Line
	2825 4125 2900 4125
Wire Wire Line
	2900 4125 2900 4025
Connection ~ 2900 4025
Wire Wire Line
	3850 4025 3600 4025
Wire Wire Line
	3850 3250 3850 4025
Wire Wire Line
	3850 3250 4025 3250
Wire Wire Line
	3600 3825 3850 3825
Connection ~ 3850 3825
Text GLabel 3000 4625 2    60   Input ~ 0
GND
Wire Wire Line
	3000 4625 2825 4625
Text GLabel 1100 2300 0    60   Input ~ 0
DHTxx-DATA
$Comp
L DHT11 U2
U 1 1 580486E4
P 7100 925
F 0 "U2" H 7250 1175 50  0000 C CNN
F 1 "DHT11" H 7200 675 50  0000 C CNN
F 2 "" H 7250 1175 50  0001 C CNN
F 3 "" H 7250 1175 50  0000 C CNN
	1    7100 925 
	0    1    1    0   
$EndComp
Text GLabel 6650 825  0    60   Input ~ 0
GND
Text GLabel 6975 1400 0    60   Input ~ 0
DHTxx-DATA
Text GLabel 7850 825  2    60   Input ~ 0
5V
Wire Wire Line
	6650 825  6800 825 
Wire Wire Line
	7100 1225 7100 1400
Wire Wire Line
	6975 1400 7575 1400
Wire Wire Line
	7400 825  7850 825 
$Comp
L R R3
U 1 1 5804BC34
P 7575 1100
F 0 "R3" V 7655 1100 50  0000 C CNN
F 1 "10k" V 7575 1100 50  0000 C CNN
F 2 "" V 7505 1100 50  0001 C CNN
F 3 "" H 7575 1100 50  0000 C CNN
	1    7575 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7575 950  7575 825 
Connection ~ 7575 825 
Wire Wire Line
	7575 1400 7575 1250
Connection ~ 7100 1400
Wire Wire Line
	1325 2300 1100 2300
$EndSCHEMATC
