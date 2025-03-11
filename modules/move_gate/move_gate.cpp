//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "move_gate.h"

//=====[Declaration of private defines]========================================

#define GATE_LOW                             0.065
#define GATE_HIGH                            0.02
#define PERIOD                               0.02
#define MOTOR_DELAY_MS                       25

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalOut greenLED(D10);
DigitalOut redLED(D11);
PwmOut servo(PF_9);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]=========================

//=====[Implementations of public functions]===================================

void moveGateInit() {
    greenLED = OFF;
    redLED = OFF;
    servo.period(PERIOD);
    servo.write(GATE_LOW);
}

void openGate() {
    redLED = ON;
    for (int i = 0; i < 250; i++) {
        servo.write(GATE_LOW + ((GATE_HIGH - GATE_LOW) / 250) * i);
        delay(MOTOR_DELAY_MS);
    }
    redLED = OFF;
    greenLED = ON;
}

void closeGate() {    
    greenLED = OFF;
    redLED = ON;
    for (int i = 0; i < 250; i++) {
        servo.write(GATE_HIGH - ((GATE_HIGH - GATE_LOW) / 250) * i);
        delay(MOTOR_DELAY_MS);
    }
    redLED = OFF;
}

//=====[Implementations of private functions]==================================