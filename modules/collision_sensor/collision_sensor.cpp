//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "collision_sensor.h"
#include "sirens.h"

//=====[Declaration of private defines]========================================

#define DISTANCE_SENSOR_SAMPLES 10      ///< Number of samples used for moving average calculation
#define COLLISION_ALARM_DISTANCE_CM 4.5 ///< Collision alert threshold in centimeters

//=====[Declaration and initialization of public global objects]===============

DigitalOut trigger(D14);  ///< Digital output for ultrasonic sensor trigger signal
DigitalIn echo(D15);      ///< Digital input to receive the ultrasonic echo signal

//=====[Declaration and initialization of private global variables]============

float distanceReadingsArray[DISTANCE_SENSOR_SAMPLES]; ///< Circular buffer to store distance measurements
int distanceSampleIndex = 0; ///< Index for managing the circular buffer

//=====[Declarations (prototypes) of private functions]=========================

/**
 * @brief Measures the distance using an ultrasonic sensor.
 * 
 * @return Measured distance in centimeters.
 */
static float measureDistance();

//=====[Implementations of public functions]===================================

/**
 * @brief Initializes the ultrasonic distance sensor by taking initial readings.
 * 
 * This function fills the buffer with initial readings to stabilize measurements.
 */
void distanceSensorInit() 
{
    for (int i = 0; i < DISTANCE_SENSOR_SAMPLES; i++) {
        distanceUpdate();
    }
}

/**
 * @brief Monitors distance readings and triggers the siren if a collision risk is detected.
 * 
 * If the measured distance is below the defined threshold, the siren is activated.
 * Otherwise, the siren is turned off.
 */
void collisionSensorUpdate() 
{    
    if (distanceUpdate() < COLLISION_ALARM_DISTANCE_CM) {
        internalSirenStateWrite(ON);  ///< Activate siren if object is too close
    } else {
        internalSirenStateWrite(OFF); ///< Deactivate siren if safe distance is maintained
    }
    sirensUpdate(); ///< Ensure siren status is updated accordingly
}

/**
 * @brief Updates the distance measurement and computes a moving average.
 * 
 * This function takes a new distance reading, updates the circular buffer, 
 * and calculates the average of the last DISTANCE_SENSOR_SAMPLES measurements.
 * 
 * @return The averaged distance in centimeters.
 */
float distanceUpdate() 
{
    // Store new measurement in the circular buffer
    distanceReadingsArray[distanceSampleIndex] = measureDistance();
    distanceSampleIndex++;

    // Reset index to maintain circular buffer behavior
    if (distanceSampleIndex >= DISTANCE_SENSOR_SAMPLES) {
        distanceSampleIndex = 0;
    }

    // Compute the average of the last DISTANCE_SENSOR_SAMPLES readings
    float distanceReadingsSum = 0.0;
    for (int i = 0; i < DISTANCE_SENSOR_SAMPLES; i++) {
        distanceReadingsSum += distanceReadingsArray[i];
    }

    return distanceReadingsSum / DISTANCE_SENSOR_SAMPLES; ///< Return the averaged distance value
}

//=====[Implementations of private functions]==================================

/**
 * @brief Measures the distance using an ultrasonic sensor.
 * 
 * This function triggers the ultrasonic sensor, measures the time it takes for the echo 
 * signal to return, and calculates the distance based on sound speed in air.
 * 
 * @return The measured distance in centimeters.
 */
static float measureDistance() 
{
    trigger = 1;
    wait_us(10);  ///< Send a 10-microsecond pulse
    trigger = 0;

    while (echo == 0);  ///< Wait for the echo signal to start
    Timer timer;
    timer.start();

    while (echo == 1);  ///< Measure the pulse duration
    timer.stop();

    float duration = chrono::duration<float, std::micro>(timer.elapsed_time()).count();

    return (duration * 0.0343f) / 2.0f; ///< Convert time to distance (cm)
}
