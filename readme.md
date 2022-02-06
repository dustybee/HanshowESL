
# Hanshow Stellar series Firmware

This firmware is currently work in progress. It's for you to play with if you want. There is no guarantee of any functionality.

#####Requirements: 
* [Make](https://www.gnu.org/software/make/)
* [Python](https://www.python.org/downloads/)
* A command line

#####Build

Clone the repo
```
git clone https://github.com/dustybee/HanshowESL.git
```

Change directory to Firmware/src
```
cd HanshowESL/Firmware/src
```

Build the project with Make
```
make all
```

The build bin file will be available in the `Firmware` directory.

Flash the firmware to the ESL via [this handy web-based flasher](https://atc1441.github.io/ATC_TLSR_Paper_UART_Flasher.html)!

---

# Hanshow RF Protocol

See [Hanshow RF Protocol](/Hanshow%20RF%20Protocol/readme.md)