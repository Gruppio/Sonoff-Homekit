#!/bin/bash

POWERON_STATE="ON" # Change this to "OFF" if you want that your Sonoff will be OFF when powered 

SONOFF_PORT="/dev/cu.wchusbserial14310"

esptool.py \
            -p $SONOFF_PORT \
            --baud 115200 \
            write_flash \
            -fs 1MB \
            -fm dout \
            -ff 40m \
            0x0 ./firmware/rboot.bin \
            0x1000 ./firmware/blank_config.bin \
            0x2000 ./firmware/Sonoff_$POWERON_STATE.bin