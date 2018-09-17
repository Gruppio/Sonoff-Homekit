#!/bin/bash

SONOFF_PORT="/dev/cu.wchusbserial1420"
esptool.py \
            -p $SONOFF_PORT \
            --baud 115200 \
            write_flash \
            -fs 8m \
            -fm dout \
            -ff 40m \
            0x0 ./firmware/rboot.bin \
            0x1000 ./firmware/blank_config.bin \
            0x2000 ./firmware/sonoff.bin