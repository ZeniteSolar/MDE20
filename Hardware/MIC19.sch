EESchema Schematic File Version 4
LIBS:MIC19-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 6
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 3175 1925 1350 1250
U 5AABFC1B
F0 "CANBUS" 60
F1 "canbus.sch" 60
F2 "SI" I L 3175 2225 60 
F3 "SO" O L 3175 2125 60 
F4 "CS" I L 3175 2325 60 
F5 "SCK" I L 3175 2025 60 
F6 "INT" O L 3175 2425 60 
F7 "GND" O R 4525 2075 60 
F8 "VCC" I R 4525 1975 60 
F9 "CAN_H" B R 4525 2175 60 
F10 "CAN_L" B R 4525 2275 60 
$EndSheet
$Sheet
S 4875 875  1050 500 
U 5AACFFEF
F0 "POWER SUPPLY" 60
F1 "supplies.sch" 60
F2 "GND" O R 5925 1175 60 
F3 "+5V_OUT" O L 4875 1175 60 
F4 "+18V_IN" I R 5925 1075 60 
$EndSheet
$Sheet
S 6525 1025 600  450 
U 5AAD16DD
F0 "CANBUS CONN" 60
F1 "canbus_connector.sch" 60
F2 "CAN_H" B L 6525 1275 60 
F3 "CAN_L" B L 6525 1375 60 
F4 "CAN_18V" O L 6525 1075 60 
F5 "CAN_GND" B L 6525 1175 60 
$EndSheet
Wire Wire Line
	3175 2425 2625 2425
Wire Wire Line
	3175 2325 2625 2325
Wire Wire Line
	3175 2125 2625 2125
Wire Wire Line
	3175 2025 2625 2025
Wire Wire Line
	2625 2225 3175 2225
Text Label 2775 2225 0    60   ~ 0
MOSI
Text Label 2775 2125 0    60   ~ 0
MISO
Text Label 2775 2025 0    60   ~ 0
SCK
Wire Wire Line
	6525 1075 5925 1075
Wire Wire Line
	5925 1175 6125 1175
Wire Wire Line
	6525 1275 6225 1275
Wire Wire Line
	6225 1275 6225 2175
Wire Wire Line
	6225 2175 4525 2175
Wire Wire Line
	4525 2275 6325 2275
Wire Wire Line
	6325 2275 6325 1375
Wire Wire Line
	6325 1375 6525 1375
Wire Wire Line
	6125 1175 6125 2075
Wire Wire Line
	6125 2075 5025 2075
Connection ~ 6125 1175
Wire Wire Line
	4875 1175 4675 1175
Wire Wire Line
	4675 1175 4675 1725
Wire Wire Line
	4675 1975 4525 1975
Wire Wire Line
	4725 2075 4725 2475
Connection ~ 4725 2075
Wire Wire Line
	4725 2075 4525 2075
Wire Wire Line
	4525 1625 4525 1725
Wire Wire Line
	4525 1725 4675 1725
Connection ~ 4675 1725
Wire Wire Line
	4675 1725 4675 1975
$Comp
L Mechanical:MountingHole H104
U 1 1 5BE9AF15
P 6150 7625
F 0 "H104" H 6250 7675 50  0000 L CNN
F 1 "MountingHole" H 6250 7625 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 6150 7625 50  0001 C CNN
F 3 "~" H 6150 7625 50  0001 C CNN
	1    6150 7625
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H103
U 1 1 5BE9BC53
P 6150 7425
F 0 "H103" H 6250 7475 50  0000 L CNN
F 1 "MountingHole" H 6250 7425 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 6150 7425 50  0001 C CNN
F 3 "~" H 6150 7425 50  0001 C CNN
	1    6150 7425
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H102
U 1 1 5BE9BC79
P 6150 7225
F 0 "H102" H 6250 7275 50  0000 L CNN
F 1 "MountingHole" H 6250 7225 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 6150 7225 50  0001 C CNN
F 3 "~" H 6150 7225 50  0001 C CNN
	1    6150 7225
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H101
U 1 1 5BE9BC9F
P 6150 7025
F 0 "H101" H 6250 7075 50  0000 L CNN
F 1 "MountingHole" H 6250 7025 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 6150 7025 50  0001 C CNN
F 3 "~" H 6150 7025 50  0001 C CNN
	1    6150 7025
	1    0    0    -1  
$EndComp
Wire Wire Line
	6125 1175 6525 1175
$Comp
L power:GND #PWR0103
U 1 1 5BE8F87F
P 4725 2475
F 0 "#PWR0103" H 4725 2225 50  0001 C CNN
F 1 "GND" H 4775 2275 50  0000 C CNN
F 2 "" H 4725 2475 50  0001 C CNN
F 3 "" H 4725 2475 50  0001 C CNN
	1    4725 2475
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0105
U 1 1 5BE8FCAE
P 4525 1625
F 0 "#PWR0105" H 4525 1475 50  0001 C CNN
F 1 "+5V" H 4575 1825 50  0000 C CNN
F 2 "" H 4525 1625 50  0001 C CNN
F 3 "" H 4525 1625 50  0001 C CNN
	1    4525 1625
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0104
U 1 1 5C9032F1
P 1325 1725
F 0 "#PWR0104" H 1325 1575 50  0001 C CNN
F 1 "+5V" H 1375 1925 50  0000 C CNN
F 2 "" H 1325 1725 50  0001 C CNN
F 3 "" H 1325 1725 50  0001 C CNN
	1    1325 1725
	1    0    0    -1  
$EndComp
Wire Wire Line
	1325 1725 1325 1825
Wire Wire Line
	1325 1825 1475 1825
$Comp
L power:GND #PWR0106
U 1 1 5C9038CC
P 1325 2075
F 0 "#PWR0106" H 1325 1825 50  0001 C CNN
F 1 "GND" H 1375 1875 50  0000 C CNN
F 2 "" H 1325 2075 50  0001 C CNN
F 3 "" H 1325 2075 50  0001 C CNN
	1    1325 2075
	1    0    0    -1  
$EndComp
Wire Wire Line
	1325 2075 1325 2025
Wire Wire Line
	1325 2025 1475 2025
$Sheet
S 3175 3425 1350 1600
U 5CDB3009
F0 "Conectores" 50
F1 "Conectores.sch" 50
F2 "VCC" I R 4525 3500 50 
F3 "GND" I R 4525 3575 50 
F4 "ENGINE_VEL" I L 3175 3500 50 
F5 "ENGINE_ACEL" I L 3175 3625 50 
F6 "MPPT_POT" I L 3175 3750 50 
F7 "SW_PUMP1_ON" I L 3175 3875 50 
F8 "SW_PUMP2_ON" I L 3175 4000 50 
F9 "SW_PUMP3_ON" I L 3175 4125 50 
F10 "SW_BOAT_ON" I L 3175 4250 50 
F11 "SW_ENGINE_ON" I L 3175 4375 50 
F12 "SW_MPPT_ON" I L 3175 4500 50 
F13 "SW_DMS" I L 3175 4625 50 
F14 "SW_EMERGENCIA" I L 3175 4750 50 
$EndSheet
$Sheet
S 1475 1525 1150 3500
U 5AACA401
F0 "MCU" 60
F1 "atmega328p.sch" 60
F2 "SPI_MISO" I R 2625 2125 60 
F3 "SPI_MOSI" O R 2625 2225 60 
F4 "MCP_INT" I R 2625 2425 60 
F5 "VCC" I L 1475 1825 60 
F6 "GND" O L 1475 2025 60 
F7 "SPI_SCK" O R 2625 2025 50 
F8 "MCP_SS" O R 2625 2325 50 
F9 "ENGINE_VEL" I R 2625 3500 50 
F10 "ENGINE_ACEL" I R 2625 3625 50 
F11 "MPPT_POT" I R 2625 3750 50 
F12 "SW_PUMP1_ON" I R 2625 3875 50 
F13 "SW_PUMP2_ON" I R 2625 4000 50 
F14 "SW_PUMP3_ON" I R 2625 4125 50 
F15 "SW_BOAT_ON" I R 2625 4250 50 
F16 "SW_ENGINE_ON" I R 2625 4375 50 
F17 "SW_MPPT_ON" I R 2625 4500 50 
F18 "SW_DMS" I R 2625 4625 50 
F19 "SW_EMERGENCIA" I R 2625 4750 50 
$EndSheet
Wire Wire Line
	2625 4750 3175 4750
Wire Wire Line
	2625 4625 3175 4625
Wire Wire Line
	2625 4500 3175 4500
Wire Wire Line
	2625 4375 3175 4375
Wire Wire Line
	2625 4250 3175 4250
Wire Wire Line
	2625 4125 3175 4125
Wire Wire Line
	2625 4000 3175 4000
Wire Wire Line
	2625 3875 3175 3875
Wire Wire Line
	2625 3500 3175 3500
Wire Wire Line
	2625 3625 3175 3625
Wire Wire Line
	2625 3750 3175 3750
Wire Wire Line
	4525 3500 4950 3500
Wire Wire Line
	4525 3575 5025 3575
Wire Wire Line
	5025 3575 5025 2075
Connection ~ 5025 2075
Wire Wire Line
	4725 2075 5025 2075
Wire Wire Line
	4675 1975 4950 1975
Wire Wire Line
	4950 1975 4950 3500
Connection ~ 4675 1975
$EndSCHEMATC
