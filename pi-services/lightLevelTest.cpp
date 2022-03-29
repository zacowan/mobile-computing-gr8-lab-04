#include <wiringPi.h>
#include <ADCDevice.hpp>
#include <softPwm.h>
#include <iostream>

using namespace std;

ADCDevice *adc;


int main(){
    adc = new ADCDevice();
    if(adc->detectI2C(0x4b)){
        delete adc;
        adc = new ADS7830();
    }else{
        cout << "No I2C" << endl;
    }

    wiringPiSetup();
    
    while(true){
        int value = adc->analogRead(0);
        float voltage = (float)value / 255.0 * 3.3;
        cout << "Current Voltage --> " << voltage << endl;
        delay(100);
    }
}