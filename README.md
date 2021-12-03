[![Codacy Badge](https://app.codacy.com/project/badge/Grade/1fdaea3601294141986a528b28a874e5)](https://www.codacy.com/gh/praba2499/M2-Embedded_UltrasonicRadar/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=praba2499/M2-Embedded_UltrasonicRadar&amp;utm_campaign=Badge_Grade)

[![Codacy Badge](https://api.codiga.io/project/30313/status/svg)](https://app.codiga.io/public/project/30313/M2-Embedded_UltrasonicRadar/dashboard)
[![Codacy Badge](https://api.codiga.io/project/30313/score/svg)](https://app.codiga.io/public/project/30313/M2-Embedded_UltrasonicRadar/dashboard)

[![Code Quality - Static Code - Cppcheck](https://github.com/praba2499/M2-Embedded_UltrasonicRadar/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/praba2499/M2-Embedded_UltrasonicRadar/actions/workflows/c-cpp.yml)











Ultrasonic sensor
================

Introduction
------------
Interfacing an ultrasonic sensor to measure the distance to objects in(cm) and displaying the distance on 2x16 LCD using ATmega328 with the AVR toolchain.

Hardware
--------
* AVR ATmega328 microcontroller.
* Uspasp programmer
* Ultrasonic sensor (HC-SR04)
* 2x16 LCD

Distance Calculation
--------
Sound velocity =   343.00 m/s = 34300 cm/s

Distance of Object (in cm)
                        = (Sound velocity * TIMER Value) / 2

                        = (34300 * TIMER Value) / 2

                        = 17150  * Timer Value

we have selected internal 8 MHz oscillator frequency for ATmega328, with No-presale for timer frequency. Then time to execute 1 instruction is 0.125 us
So, timer gets incremented after 0.125 us time elapse.

                 = 17150 x (TIMER value) x 0.125 x 10^-6 cm

                 = 0.125 x (TIMER value)/58.30 cm

                 = (TIMER value) / 466.47 cm

Circuit
--------
![ultrasonic](circuit/ultrasonic.PNG)

Installation
------------
You will need to have the AVR toolchain installed on your system. This includes:
* avr-gcc
* avr-libc
* avrdude


