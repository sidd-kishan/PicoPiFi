# Driverless RNDIS USB WIFI Dongle
A Driverless RNDIS based wifi adapter based on pi pico w to enable usb wifi wlan on Windows on ARM devices like Windows on Raspberry pi 4 that makes use of the default driver of Windows RNDIS drivers


## 3 Steps connect to Wifi with PicoPiFi
### 1) Download the UF2 firmware and index.html
### 2) Upload Firmware to pi pico w
### 3) Open the index.html locally or navigate to https://sidd-kishan.github.io/PicoPiFi/ to control the wifi adapter

![image](https://github.com/sidd-kishan/PicoPiFi/assets/1007208/29d206ca-cc51-4f08-8696-4dd7b14d2b2d)




## Overview
```
        ---------------------------       -------------------------------                     ----------
       |Full USB 12 Mbps rndis link| --->| PI PICO W ( MCU <-SPI-> WIFI) | <--- 54 Mbps----> |2.4 Ghz AP|
        ---------------------------       -------------------------------                     ----------
               |                                                                                  |
               V                                                                                  V
          Raspberry pi (Windows on ARM64)                                                       Client
```

A RNDIS example that came with CherryUSB slightly modified to run on a Raspberry Pi Pico.
Lets the Pico pretend to be a USB Ethernet device and CDC port to manage the device. 

## Build dependencies

On Debian:

```
sudo apt install git build-essential cmake gcc-arm-none-eabi
```

Your Linux distribution does need to provide a recent CMake (3.13+).
If not, compile [CMake from source](https://cmake.org/download/#latest) first.

## Build instructions

```
git clone --depth 1 https://github.com/sidd-kishan/PicoPiFi
cd PicoPiFi
git submodule update --init
cd pico-sdk
git submodule update --init
cd lib/
git submodule update --remote
cd ..
cd ..
cp -R rp2040/ CherryUSB/port/
rm -rf build/
mkdir -p build/
cd build
cmake ..
make -j$(nproc --all)
```

Copy the resulting PicoPiFi.uf2 file to the Pico mass storage device manually.
