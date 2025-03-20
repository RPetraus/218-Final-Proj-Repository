//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "car_at_entrance.h"

//=====[Declaration of private defines]========================================

#define CAR_PRESENT_LEVEL 70  ///< Light level threshold for detecting a car
#define CAR_NOT_PRESENT_LEVEL 40 ///< Light level threshold for detecting no car
#define LIGHT_SENSOR_SAMPLES 10 ///< Number of samples for light sensor averaging

//=====[Declaration of private data types]=====================================

static float lightReadingsArray[LIGHT_SENSOR_SAMPLES]; ///< Array to store light sensor readings
static int lightSampleIndex = 0; ///< Index for cycling through the light readings array

//=====[Declaration and initialization of public global objects]===============

AnalogIn lightsens(A0); ///< Analog input object for the light sensor

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static bool carDetected; ///< Boolean variable indicating car presence

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

/**
 * @brief Initializes the car detection system.
 * 
 * This function initializes the light readings array and updates the sensor data.
 */
void carAtEntranceInit()
{   
    for (int i = 0; i < LIGHT_SENSOR_SAMPLES; i++) {
        lightReadingsArray[i] = 0.0;
        sensorUpdate();
    }
}

/**
 * @brief Checks whether a car is detected at the entrance.
 * 
 * @return True if a car is detected, false otherwise.
 */
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

/**
 * @brief Reads and processes the light sensor data.
 * 
 * This function updates the circular buffer of light readings and calculates the average light level.
 * 
 * @return The computed light level as a percentage.
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
