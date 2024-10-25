#!/usr/bin/env python
import RPi.GPIO as GPIO, time, os, sys
#Settings
OUT_MOTOR = 21       #Motor output pin
GPIO.setmode(GPIO.BCM)
GPIO.setup(OUT_MOTOR, GPIO.OUT)
while True:
    GPIO.output(OUT_MOTOR, True)
    Time.Sleep(5)
    GPIO.output(OUT_MOTOR, False)
