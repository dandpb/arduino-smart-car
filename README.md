# arduino-smart-car

[![Build Status](https://travis-ci.org/miquelbeltran/arduino-smart-car.svg?branch=master)](https://travis-ci.org/miquelbeltran/arduino-smart-car)

Arduino project for the Elegoo UNO Project Smart Robot Car kit.

## Features

- Autonomous exploration mode using the ultrasonic sensor on top.
- Manual control mode using the provided Android app via Bluetooth.

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

The world map button activates the Exploration Mode. Tapping any of the other directional buttons will deactivate the Exploration Mode.

Some stuff is hardcoded (UUID and Bluetooth device name). The code is not the cleanest but works. 

## Legal Stuff

I have no relationship with Elegoo and I have no economical interest in promoting their hardware products. The code tutorials provided with the kit helped me write this project, however all the code here is mine, therefor I am the author and owner of it.

This project is distributed without warranty, so if your robot explodes or falls from the stairs please don't blame me.

This app is libre software ( GPLv3 ), if you build something cooler for this robot kit, please share it!

```
Copyright (c) 2016, Beltran

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO
THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT
SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE
USE OR PERFORMANCE OF THIS SOFTWARE.
```
