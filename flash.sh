#!/bin/bash

SONOFF_PORT="/dev/cu.wchusbserial1420"
esptool.py \
            -p $SONOFF_PORT \
            --baud 115200 \
            write_flash \
            -fs 8 \
            -fm dout \
            -ff 40m \
            0x0 ./common/rboot.bin \
            0x1000 ./common/blank_config.bin \
            0x2000 ./homekit_projects/sonoff.bin