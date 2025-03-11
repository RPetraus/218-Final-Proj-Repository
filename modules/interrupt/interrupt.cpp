//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "interrupt.h"

#include "code.h"
#include "distance_sensor.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

InterruptIn codeResetButton(D13);

Ticker collisionTicker;

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]=========================

static void codeResetButtonPressed();

//=====[Implementations of public functions]===================================

void codeResetButtonInterrupt() {
    codeResetButton.mode(PullDown);
    codeResetButton.fall(&codeResetButtonPressed);
}

void collisionSensorInterrupt() {
    collisionTicker.attach(&collisionSensorUpdate, 10ms);
}

//=====[Implementations of private functions]==================================

static void codeResetButtonPressed() {
    codeResetButton.fall(NULL);

    wait_us(100000); 

    resetCode();

    codeResetButton.fall(&codeResetButtonPressed);
}
