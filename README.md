# mbed_os_nfc_shield
MBed PN532 NFC shield app with LoRaWAN

PN532 connections:

| PN532 | MBed |
|-------|------|
|MOSI | p5 (mosi)|
|MISO | p6 (miso)|
|CLK | p7 (sck)|
|SS | p17 |
|IRQ | p18 (connected but not used) |
|5V (not 3V) | Vout (3V3) |
| GND | GND |

## Quick build and deploy

Execute this inside project dir

```shell
rm -f ./BUILD/LPC1768/GCC_ARM/mbed_os_nfc_shield.bin ; mbed compile && cp ./BUILD/LPC1768/GCC_ARM/mbed_os_nfc_shield.bin /media/$(whoami)/MBED && sudo sync
```
