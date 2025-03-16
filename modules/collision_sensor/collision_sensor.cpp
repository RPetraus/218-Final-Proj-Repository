//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "collision_sensor.h"
#include "sirens.h"

//=====[Declaration of private defines]========================================

#define DISTANCE_SENSOR_SAMPLES 10   // Number of samples for averaging
#define COLLISION_ALARM_DISTANCE_CM 4.5  // Collision alert threshold in cm

//=====[Declaration and initialization of public global objects]===============

DigitalOut trigger(D14);  // Trigger pin for ultrasonic sensor
DigitalIn echo(D15);      // Echo pin for ultrasonic sensor

//=====[Declaration and initialization of private global variables]============

float distanceReadingsArray[DISTANCE_SENSOR_SAMPLES]; // Stores distance samples
int distanceSampleIndex = 0; // Index for circular buffer of distance samples

//=====[Declarations (prototypes) of private functions]=========================

static float measureDistance();  // Measures distance using the ultrasonic sensor

//=====[Implementations of public functions]===================================

// Initializes the distance sensor by taking initial readings
void distanceSensorInit() 
{
    for (int i = 0; i < DISTANCE_SENSOR_SAMPLES; i++) {
        distanceUpdate();
    }
}

// Updates the collision sensor and triggers the alarm if necessary
void collisionSensorUpdate() {    
    if (distanceUpdate() < COLLISION_ALARM_DISTANCE_CM) {
        internalSirenStateWrite(ON);  // Activate siren if too close
    } else {
        internalSirenStateWrite(OFF); // Deactivate siren if safe
    }
    sirensUpdate(); // Ensure siren status is updated
}

// Updates the distance measurement and calculates a moving average
float distanceUpdate() {
    distanceReadingsArray[distanceSampleIndex] = measureDistance();
    distanceSampleIndex++;

    if (distanceSampleIndex >= DISTANCE_SENSOR_SAMPLES) {
        distanceSampleIndex = 0;  // Reset index for circular buffer
    }

    float distanceReadingsSum = 0.0;
    for (int i = 0; i < DISTANCE_SENSOR_SAMPLES; i++) {
        distanceReadingsSum += distanceReadingsArray[i]; // Sum all samples
    }

    float averageDistance = distanceReadingsSum / DISTANCE_SENSOR_SAMPLES;
    return averageDistance;
}

//=====[Implementations of private functions]==================================

// Measures distance using an ultrasonic sensor and returns the value in cm
static float measureDistance() {
    trigger = 1;
    wait_us(10);  // Send 10-microsecond pulse
    trigger = 0;

    while (echo == 0);  // Wait for echo signal to start
    Timer timer;
    timer.start();

    while (echo == 1);  // Measure pulse duration
    timer.stop();

    float duration = chrono::duration<float, std::micro>(timer.elapsed_time()).count();

    return (duration * 0.0343f) / 2.0f;  // Convert to
