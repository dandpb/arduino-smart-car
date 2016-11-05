# arduino-smart-car

[![Build Status](https://travis-ci.org/miquelbeltran/arduino-smart-car.svg?branch=master)](https://travis-ci.org/miquelbeltran/arduino-smart-car)

Arduino project for the Elegoo UNO Project Smart Robot Car kit.

## Setup

1. Install PlatformIO.
2. Build with `make`
3. Upload to robot with `make upload`

## Working Environment

I don't use Arduino IDE, rather I just write code with Vim.

There's also a Makefile that handles all the PlatformIO commands.

I use the following tools to make my life easier:

- a.vim
- clang-format

The `.clang-format` is also included in the project.

## Android App

There's an Android project to control the robot via a bluetooth app.

You can move the car back/forward/left/right and control the board LED.

Some stuff is hardcoded (UUID and Bluetooth device name). The code is not the cleanest but works. 

## Legal Stuff

I have no relationship with Elegoo and I have no economical interest in promoting their hardware products. The code tutorials provided with the kit helped me write this project, however all the code here present is mine.

This project is distributed without warranty, so if your robot explodes or falls from the stairs please don't blame me.

There's no license attached, but if you do something cooler, please share it.
