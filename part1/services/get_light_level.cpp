#include "get_light_level.h"

/**
 * @brief Get the current light level from the Photoresistor
 * 
 * Entity: LightSensor_1
 * Service Description: 
 * This service interfaces directly with the photoresistor, copying out functionality 
 * from the ADCDevice Library that is included with our RPi Kit. It first sets 
 * up the photoresistor to communicate through a Analog to Digital Converter, 
 * reading input from the channel "A0". This integer result read in from this device 
 * is the current light level found in the room. 
 * 
 * As the light level increases, the integer read in decreases. 
 * 
 * For the purposes of our main program, when the light level falls < 50, this is 
 * considered a HIGH amount of light. When it is instead > 50, we consider it a LOW 
 * amount of light.
 *
 * @return int read in from the sensor
 */
int getLightLevel(){
    int cmd = 0x84;
    wiringPiSetup();
    int _fd = wiringPiI2CSetup(0x4b); 
    int chn = 0;
    wiringPiI2CWrite(_fd, cmd|(((chn<<2 | chn>>1)&0x07)<<4));
    return wiringPiI2CRead(_fd);
}