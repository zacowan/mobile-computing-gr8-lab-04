#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <iostream>

using namespace std;

int main(){
    int cmd = 0x84;
    wiringPiSetup();
    int _fd = wiringPiI2CSetup(0x4b); 
    int chn = 0;
    wiringPiI2CWrite(_fd, cmd|(((chn<<2 | chn>>1)&0x07)<<4));
    return wiringPiI2CRead(_fd);