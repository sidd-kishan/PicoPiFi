# A Driverless RNDIS based wifi adapter based on pi pico w to enable usb wifi wlan on Windows on ARM devices like Windows on Raspberry pi 4 that makes use of the default driver of Windows RNDIS drivers
# pico-rndis-use-freerots
A project for rp2040
Use rndis in tinyusb and use freerots to create usb-related tasks.You can also use socket-related interfaces in this project
## Overview
```
        ---------------------------       -------------------------------                     ----------
       |Full USB 12 Mbps rndis link| --->| PI PICO W ( MCU <-SPI-> WIFI) | <--- 54 Mbps----> |2.4 Ghz AP|
        ---------------------------       -------------------------------                     ----------
               |                                                                                  |
               V                                                                                  V
          Raspberry pi (Windows on ARM64)                                                       Client
```

Webserver example that came with TinyUSB slightly modified to run on a Raspberry Pi Pico.
Lets the Pico pretend to be a USB Ethernet device. Runs a webinterface at http://192.168.7.1/

## Build dependencies

On Debian:

```
sudo apt install git build-essential cmake gcc-arm-none-eabi
```

Your Linux distribution does need to provide a recent CMake (3.13+).
If not, compile [CMake from source](https://cmake.org/download/#latest) first.

## Build instructions

```
git clone --depth 1 https://github.com/sidd-kishan/pico-webserver
cd pico-webserver
git submodule update --init
cd pico-sdk
git submodule update --init
cd ..
mkdir -p build
cd build
cmake ..
make -j$(nproc --all)
```

Copy the resulting pico_webserver.uf2 file to the Pico mass storage device manually.
Webserver will be available at http://192.168.7.1/

Content it is serving is in /fs
If you change any files there, run ./regen-fsdata.sh

By default it shows a webpage that led you toggle the Pico's led, and allows you to switch to BOOTSEL mode.
