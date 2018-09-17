# Sonoff Homekit

This is a custom made firmware for the sonoff wifi smart switch that makes it compatible with the Apple Homekit!

### Homekit runs on the Sonoff

Unlike other projects on github, this firmware does .NOT. require anything else in order to work, You don't need HomeBridge running on a Raspberry-Pi or an MQTT server, just a Wi-Fi connection and an Apple Device.

The implementation uses Apple provided specifications for developers, so it will keep working for a long time.

## Instructions

### Flashing the Sonoff
 1) Unplug your sonoff from the power line
 2) Connect your Sonoff to a serial adapter @ 3.3v
 3) Run the `flash.sh` script 

### Add Sonoff to Home app
 1) Connect your iPhone or iPad to the new wifi network `Sonoff Switch-xxx`
 2) Wait for the Captive Portal and select your WiFi network
 3) Insert your WiFi Password
 4) Open the `Home` app
 5) Click the `+` symbol
 6) Click `I don't have the code...`
 7) Select the Sonoff Switch
 8) Confirm that you want to add the Sonoff
 9) Insert the Password that is `111111111`

Done! 🎉 

## If you like this project please:

<a href="https://www.buymeacoffee.com/gruppio" target="_blank"><img src="https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png" alt="Buy Me A Coffee" style="height: auto !important;width: auto !important;" ></a>

<style>.bmc-button img{width: 27px !important;margin-bottom: 1px !important;box-shadow: none !important;border: none !important;vertical-align: middle !important;}.bmc-button{line-height: 36px !important;height:37px !important;text-decoration: none !important;display:inline-flex !important;color:#ffffff !important;background-color:#FF813F !important;border-radius: 3px !important;border: 1px solid transparent !important;padding: 0px 9px !important;font-size: 17px !important;letter-spacing:-0.08px !important;box-shadow: 0px 1px 2px rgba(190, 190, 190, 0.5) !important;-webkit-box-shadow: 0px 1px 2px 2px rgba(190, 190, 190, 0.5) !important;margin: 0 auto !important;font-family:'Lato', sans-serif !important;-webkit-box-sizing: border-box !important;box-sizing: border-box !important;-o-transition: 0.3s all linear !important;-webkit-transition: 0.3s all linear !important;-moz-transition: 0.3s all linear !important;-ms-transition: 0.3s all linear !important;transition: 0.3s all linear !important;}.bmc-button:hover, .bmc-button:active, .bmc-button:focus {-webkit-box-shadow: 0px 1px 2px 2px rgba(190, 190, 190, 0.5) !important;text-decoration: none !important;box-shadow: 0px 1px 2px 2px rgba(190, 190, 190, 0.5) !important;opacity: 0.85 !important;color:#ffffff !important;}</style><link href="https://fonts.googleapis.com/css?family=Lato&subset=latin,latin-ext" rel="stylesheet"><a class="bmc-button" target="_blank" href="https://www.buymeacoffee.com/gruppio"><img src="https://www.buymeacoffee.com/assets/img/BMC-btn-logo.svg" alt="Buy me a coffee"><span style="margin-left:5px">Buy me a coffee</span></a>

### If you do so:
I will also send to you:
* A Step-by-Step video tutorial that will help you to flash and connect your Sonoff
* All the source code
* A personal e-mail where you can write to me your Issue

