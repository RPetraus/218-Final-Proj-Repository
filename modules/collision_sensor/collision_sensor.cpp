//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "collision_sensor.h"

#include "sirens.h"




//#include "pc_serial_com.h"

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

static float distanceUpdate();
static float measureDistance();

//=====[Implementations of public functions]===================================


void collisionSensorInit() 
{
    for (int i = 0; i < 10; i++) {
        distanceUpdate();
    }
}

/*
void collisionSensorInit() 
{
    pcSerialComStringWrite("\r\n\r\n\r\n\r\n\r\n");
    
    for (int i = 0; i < 10; i++) {
        distanceUpdate();
    }

    pcSerialComStringWrite("\r\n\r\n\r\n\r\n\r\n");
}
*/







void collisionSensorUpdate() {    
    if (distanceUpdate() < COLLISION_ALARM_DISTANCE_CM) {
        internalSirenStateWrite(ON);
        sirensUpdate();
    } else {
        internalSirenStateWrite(OFF);
        sirensUpdate(); 
    }
}









//=====[Implementations of private functions]==================================

static float distanceUpdate() {
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




/*
static float distanceUpdate() {
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

    // for debugging
    char distanceStr[100] = "";
    sprintf ( distanceStr, "Distance: %.2f cm\r\n", averageDistance );
    pcSerialComStringWrite( distanceStr );


    return averageDistance;
}
*/













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
    float distance_cm = (duration * 0.0343f) / 2.0f;
    
    return distance_cm;
}