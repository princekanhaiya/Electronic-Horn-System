# Electronic Horn System[📣](https://www.ti.com/lit/an/slva563/slva563.pdf?ts=1653760961598&ref_url=https%253A%252F%252Fwww.google.com%252F) 
This document describes the development of an electronic horn (E-Horn) for an automotive application. The E-Horn developed is for 4 wheeler applications but can be easily tweaked for 2 wheeler automotive applications.
The design has been proven for 1 million cycles of Power ON and OFF for the required sound level (110 dB).

## Purpose ##
- [**Mechanical horns**](https://drive.google.com/file/d/1Wpg6y5j7gNXZ7x0dmo2y9Jh2PzMjeUDC/view?usp=sharing) have a typical `lifetime of 2 years` and `low cost`. The most common reason for failure of mechanical horns has been the [**burning of the coil**](https://www.team-bhp.com/forum/technical-stuff/251273-erratic-behavior-cars-horn.html) because of high current.
- In addition, mechanical switches may develop carbon contact issues due to frequent switching.
- To address this issues and increase the lifetime of the horn, a precise frequency control is needed. 
- To generate a `precise frequency` we chose the `AVR family` MCU with precise clocking source for the MCU. The low-cost target was met using the Value Line series of AVR.
- A temperature sensor is used to monitor coil tmeprature.
- To power up the MCU, a very reliable TI TPS79801 voltage regulator of 3.3 V was used. The TPS79801-Q1 has a wide input range up to 50 V, which suits 12-V automotive batteries as far as input transients.
- The thermal management of the volatage regulator is supported by thermal PAD under the chip.

## Schematic Diagram

![plot](https://embed.creately.com/Pa2FC4PgWFw?type=svg)

## Working Principle ##
[Watch](https://www.youtube.com/watch?v=ApRdXy28Qag) youTube video to understand mechanical horn in details

## Code Structure ##
 * [Electronic Horn System]()
    * [include](/include/)
      * [GPIO.h](/include/GPIO.h)
      * [ADC.h](/include/ADC.h)
      * [PWM.h](/include/PWM.h)
      * [LCD.h](/include/LCD.h)
   * [source](/source/)
      * [main.c](/source/main.c)
      * [GPIO.c](/source/GPIO.c)
      * [PWM.c](/source/PWM.c)
      * [ADC.c](/source/ADC.c)
      * [ISRs.c](/source/ISRs.c)
      * [LCD.c](/source/LCD.c)         
   * [bin](/bin/)
   * [obj](/obj/)
   * [README.md](/README.md)

## Must Read ##
Followings point shall be checked before the start of simulation
- All the buttons label are mentioned below the button and shall be in off condition.
- Status of the simulaion can be seen on `LCD screen`
- Analog value(`Temperature sensor`) only get updated when intrrupt buttons are pressed.
- Horn will blow only when horn button is pressed and it doesnot depends engine button at any time after powering app the module.
- Potentiometer is used instead of `temperature sensor`.
- As there is not seperate hardware/filter is used for buttons so software debouncing is used
- Callibration is only possisble when engine is OFF.

## License ##

This library is distributed under the BSD-style license found in the [LICENSE](./LICENSE)
file.
