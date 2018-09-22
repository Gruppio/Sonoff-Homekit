# Sonoff Homekit

This firmware makes the **Sonoff WIFI Smart Switch** compatible with **Apple Homekit**!

<img src="images/sonoffonly.png" alt="Sonoff" width="150"/> <img src="images/transparent.png" alt="Sonoff" width="20"/><img src="/images/homekit-badge.svg" alt="Sonoff"/>

### Homekit runs on the Sonoff ! 😳

Unlike other projects on github, this firmware does NOT require anything else in order to work.
It is not based on the Tasmota Fw, you don't need HomeBridge running on a Raspberry-Pi or an MQTT server, a Wi-Fi connection and an Apple Device are enough!

The implementation use Apple provided specifications for developers, so it is a stable and supported software and it will keep working for a long time.

Now you finally can have a HomeKit devices without spending a lot of money!

## Instructions

### Flash the Sonoff
 1) Unplug your sonoff from the power line _(or you can burn your PC)_
 2) Connect your Sonoff to a serial adapter @ 3.3v
 3) Run the `flash.sh` script 

### Add Sonoff to Home app
 1) Connect your iPhone or iPad to the new wifi network `Sonoff Switch-xxx`
 2) Wait for the Captive Portal and select your WiFi network
 3) Insert your WiFi Password
 4) Open the `Home` app
 5) Click the `+` symbol
 6) Click `I don't have the code...`
 7) Select the Sonoff-xxx Switch 
 7.1 If the Sonoff-xxx does not appear on top of the page try to press the sonoff button a couple of times and kill the Home App
 9) Confirm that you want to add the Sonoff
 10) Insert the Password that is `11111111`

Done! 🎉 

## If you like this project please:

<a href="https://www.buymeacoffee.com/gruppio" target="_blank"><img src="images/buymeacoffee.png" alt="Buy Me A Coffee" width="300" ></a>

My supporters will also receive immediately:

* A **Step-by-Step Video Tutorial** that will help you to flash and connect your Sonoff
* All the **Source Code**
* A personal **E-Mail** where you can write to me your Issues
