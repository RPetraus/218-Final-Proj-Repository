//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "collision_sensor.h"

#include "sirens.h"

//=====[Declaration of private defines]========================================

#define DISTANCE_SENSOR_SAMPLES 10
#define COLLISION_ALARM_DISTANCE_CM 4.5

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalOut trigger(D14);
DigitalIn echo(D15);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

float distanceReadingsArray[DISTANCE_SENSOR_SAMPLES];
int distanceSampleIndex = 0;

//=====[Declarations (prototypes) of private functions]=========================

static float measureDistance();

//=====[Implementations of public functions]===================================

void distanceSensorInit() 
{
    for (int i = 0; i < 10; i++) {
        distanceUpdate();
    }
}

void collisionSensorUpdate() {    
    if (distanceUpdate() < COLLISION_ALARM_DISTANCE_CM) {
        internalSirenStateWrite(ON);
        sirensUpdate();
    } else {
        internalSirenStateWrite(OFF);
        sirensUpdate(); 
    }
}

float distanceUpdate() {
    distanceReadingsArray[distanceSampleIndex] = measureDistance();
    distanceSampleIndex++;

    if (distanceSampleIndex >= DISTANCE_SENSOR_SAMPLES) {
        distanceSampleIndex = 0;
    }

    float distanceReadingsSum = 0.0;
    for (int i = 0; i < DISTANCE_SENSOR_SAMPLES; i++) {
        distanceReadingsSum += distanceReadingsArray[i];
    }

    float averageDistance = distanceReadingsSum / DISTANCE_SENSOR_SAMPLES;

    return averageDistance;
}

//=====[Implementations of private functions]==================================

static float measureDistance() {
    trigger = 1;
    wait_us(10);
    trigger = 0;

    while (echo == 0);
    Timer timer;
    timer.start();

    while (echo == 1);
    timer.stop();

    float duration = chrono::duration<float, std::micro>(timer.elapsed_time()).count();

    return (duration * 0.0343f) / 2.0f;
}
