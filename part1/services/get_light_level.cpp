#include "get_light_level.h"

/**
 * @brief Get the current light level from the Photoresistor
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