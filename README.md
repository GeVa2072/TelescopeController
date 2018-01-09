# Telescope Controller
This project aims to drive equatorial mount for Telescope or camera.
## Hardware
The hardware is base on Arduino, for now Nano 168 may be move to bigger.
For clock and position we use Ublox-NEO-6M-GPS-Module
![GPS Module](https://ae01.alicdn.com/kf/HTB1Vv.DhBcHL1JjSZJiq6AKcpXa6/1-Set-NEO-6M-Module-GPS-GY-GPS6MV2-NEO6MV2-Buit-dans-EEPROM-APM2-5-Antenne-3.jpg_640x640.jpg)

For Communication with the user we use a LCD display moduel 1602-16x2-HD44780-Character-LCD-Display-Module
![LCD Module](https://ae01.alicdn.com/kf/HTB1gkXpQpXXXXb0XXXXq6xXFXXXF/2-Pcs-Lot-LCD1602-1602-LCD-cran-HD44780-Caract-re-LCD-Affichage-Jaune-Blacklight-TFT-16X2.jpg_640x640.jpg)

For Driving motor a Big Easy Driver
![Driver](https://ae01.alicdn.com/kf/HTB19P3Vlr_I8KJjy1Xaq6zsxpXaP/WAVGAT-2A-phase-3D-Imprimante-Grand-Facile-bord-du-Pilote-v1-2-A4988-moteur-pas-pas.jpg_640x640.jpg)

A Motor 35HM27-0554 with 400 steps resolution 0.9° 
![Motor](https://ae01.alicdn.com/kf/HTB1O6EELXXXXXcWXFXXq6xXFXXXL/35HM27-0554-0-9-degr-s-2-Phase-NEMA14-hybride-moteur-pas-pas-35mm-12-v.jpg_640x640.jpg)

And a flexible plum to connect 5mm motor axe with equatorial mount 6mm.
![Plum](https://ae01.alicdn.com/kf/HTB1eraaa.o09KJjSZFDq6z9npXa2/LUPULLEY-3-PCS-Flexible-Plum-Accouplement-5mm-to10mm-Al-sage-Diagramme-6-6-35-7-89.jpg_640x640.jpg)

## Software
Software are build over module:
### Coordinates
First part is for managing Coordinates and converting it.
### Sideral Time
Convert UTC time to Sideral time depending of longitude and latitude. 
### LX200 Protocol 
Arduino emulate an LX200 protocol to communicate with must common astronomy software able to drive mount. 
