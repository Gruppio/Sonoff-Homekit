#!/bin/bash

SONOFF_PORT="/dev/cu.wchusbserial14310"

esptool.py \
            -p $SONOFF_PORT \
            --baud 115200 \
            erase_flash