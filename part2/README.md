# Lab 4 - Part 2

## Group Members

Shaun Fidler, Sydney McLaughlin, Zach Cowan

## Additional Information

In order to get Atlas to work with our program, we had to modify the way that
Atlas builds the C++ services by including an additional WiringPi library.
Specifically, we included wiringPiI2C.h. This header file is included with the 
Atlas WiringPi library and just needed to be added to the template file. This file 
is found at: 
/AtlasThingMiddleware_RPI/Architecture/GeneratedServices/ServiceTemplate/service.tpl

In addition, our Raspberry Pi kit came with an included library to interface with the 
Analog-to-Digital Converter included with our kit. This was necessary to get data from 
the photoresistor, allowing for light level reading. This library was ADCDevice and we 
went through the process of exporting the library components into both our service and the 
included code in the Atlas DDL file. 
