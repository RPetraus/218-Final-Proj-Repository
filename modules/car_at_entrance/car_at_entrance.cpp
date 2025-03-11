//=====[Libraries]=============================================================

#include "arm_book_lib.h"

#include "car_at_entrance.h"




#include "pc_serial_com.h"

//=====[Declaration of private defines]========================================

#define CAR_PRESENT_LEVEL 70  
#define CAR_NOT_PRESENT_LEVEL 40     
#define LIGHT_SENSOR_SAMPLES 10 

// Global variables
bool carDetected = false;

//=====[Declaration of private data types]=====================================

float lightReadingsArray[LIGHT_SENSOR_SAMPLES];
static int lightSampleIndex = 0;

//=====[Declaration and initialization of public global objects]===============

AnalogIn lightsens(A0);

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void carAtEntranceInit()
{   
    for (int i = 0; i < LIGHT_SENSOR_SAMPLES; i++) {
        lightReadingsArray[i] = 0.0;
        sensorUpdate();
    }
}

bool carIsDetected()
{
    float currentLightLevel = sensorUpdate();

    if (currentLightLevel >= CAR_PRESENT_LEVEL) {
        carDetected = true;  
    } else if (currentLightLevel < CAR_NOT_PRESENT_LEVEL) {
        carDetected = false; 
    }

    return carDetected;
}

/*
bool carIsDetected()
{
    float currentLightLevel = sensorUpdate();

    if (currentLightLevel >= CAR_PRESENT_LEVEL) {
        carDetected = true;  

        // Debug
        char buffer[50];
        sprintf(buffer, "Light level: %.2f\r\n", currentLightLevel);
        pcSerialComStringWrite(buffer);

    } else if (currentLightLevel < CAR_NOT_PRESENT_LEVEL) {
        carDetected = false; 

        // Debug
        char buffer[50];
        sprintf(buffer, "Light level: %.2f\r\n", currentLightLevel);
        pcSerialComStringWrite(buffer);

    }

    return carDetected;
}
*/


float sensorUpdate() 
{
    lightReadingsArray[lightSampleIndex] = lightsens.read();
    lightSampleIndex++;
    
    if (lightSampleIndex >= LIGHT_SENSOR_SAMPLES) {
        lightSampleIndex = 0;
    }

    float lightReadingsSum = 0.0;
    for (int i = 0; i < LIGHT_SENSOR_SAMPLES; i++) {
        lightReadingsSum += lightReadingsArray[i];
    }

    float currentLightLevel = (1.0 - (lightReadingsSum / LIGHT_SENSOR_SAMPLES)) * 100.0;

    return currentLightLevel;
}


/*
float sensorUpdate() 
{
    lightReadingsArray[lightSampleIndex] = lightsens.read();
    lightSampleIndex++;
    
    if (lightSampleIndex >= LIGHT_SENSOR_SAMPLES) {
        lightSampleIndex = 0;
    }

    float lightReadingsSum = 0.0;
    for (int i = 0; i < LIGHT_SENSOR_SAMPLES; i++) {
        lightReadingsSum += lightReadingsArray[i];
    }

    float currentLightLevel = (1.0 - (lightReadingsSum / LIGHT_SENSOR_SAMPLES)) * 100.0;

    // Debug
    char buffer[50];
    sprintf(buffer, "\r\nLight level: %.2f\r\n", currentLightLevel);
    pcSerialComStringWrite(buffer);

    return currentLightLevel;
}
*/


//=====[Implementations of public functions]===================================