//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "code.h"

/*
#include "collision_sensor.h"
#include "sirens.h"
*/



//#include "pc_serial_com.h" // for debugging

//=====[Declaration of private defines]========================================

//#define COLLISION_ALARM_DISTANCE_CM 4.5

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

InterruptIn codeResetButton(D13);

/*
DigitalOut trigger(D14);
InterruptIn echo(D15);

Ticker distanceTicker;
Timer timer;
*/

//=====[Declaration of external public global variables]=======================

/*
volatile float measuredDistance = 0.0;
volatile bool measurementReady = false;
*/

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]=========================

static void codeResetButtonPressed();

/*
static void echoRise();
static void echoFall();
static void startMeasurement();
*/

//=====[Implementations of public functions]===================================

void codeResetButtonInterrupt() {
    codeResetButton.mode(PullDown);
    codeResetButton.fall(&codeResetButtonPressed);
}

/*
void collisionSensorInterrupt() {
    echo.rise(&echoRise);
    echo.fall(&echoFall);
    distanceTicker.attach(&startMeasurement, 100ms);
}
*/

/*
void checkCollisionInterrupt() {
    if (measurementReady) {
        measurementReady = false; // Reset flag

        // Print the measured distance
        char distanceStr[100];
        sprintf(distanceStr, "measurement made: measurement is %.2f cm\r\n", measuredDistance);
        pcSerialComStringWrite(distanceStr); // Send to serial monitor

        if (measuredDistance < COLLISION_ALARM_DISTANCE_CM) {
            internalSirenStateWrite(ON);
        } else {
            internalSirenStateWrite(OFF);
        }

        sirensUpdate();
    }
}
*/



//=====[Implementations of private functions]==================================

static void codeResetButtonPressed() {
    resetCode();
}

/*








//
static void startMeasurement() {
    trigger = 1;
    wait_us(10);
    trigger = 0;
}


static void echoRise() {
    timer.reset();
    timer.start();
    //pcSerialComStringWrite("Echo rise detected\r\n"); // Debugging output
}

static void echoFall() {
    timer.stop();
    float duration = chrono::duration<float, std::micro>(timer.elapsed_time()).count();
    //measuredDistance = (duration * 0.0343f) / 2.0f; // Convert to cm
    
    // Debug print to check the calculated distance
    char distanceStr[100];
    sprintf(distanceStr, "Calculated distance: %.2f cm\r\n", duration);
    pcSerialComStringWrite(distanceStr);

    if (measuredDistance < COLLISION_ALARM_DISTANCE_CM) {
        internalSirenStateWrite(ON);
    } else {
        internalSirenStateWrite(OFF);
    }

    //sirensUpdate();
}
//*/







