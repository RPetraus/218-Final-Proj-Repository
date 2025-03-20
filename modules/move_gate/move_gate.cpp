//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "move_gate.h"

//=====[Declaration of private defines]========================================

#define GATE_LOW                             0.065    // PWM value for gate closed
#define GATE_HIGH                            0.02     // PWM value for gate open
#define PERIOD                               0.02     // PWM period for servo motor
#define MOTOR_DELAY_MS                       25      // Delay between motor movements

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

/**
 * Green LED indicating that the gate is open.
 */
DigitalOut greenLED(D10);   // Green LED indicating gate open

/**
 * Red LED indicating that the gate is closed.
 */
DigitalOut redLED(D11);     // Red LED indicating gate closed

/**
 * PWM output used to control the gate servo.
 */
PwmOut servo(PF_9);         // PWM output to control the gate servo

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]=========================

//=====[Implementations of public functions]===================================

/**
 * Initializes the gate system by setting LED states and servo parameters.
 * This function configures the initial state of the gate (closed), turns off LEDs, 
 * and sets up the PWM parameters for controlling the servo motor.
 */
void moveGateInit() {
    greenLED = OFF;           // Turn off green LED (gate closed)
    redLED = OFF;             // Turn off red LED (gate closed)
    servo.period(PERIOD);     // Set PWM period for servo
    servo.write(GATE_LOW);    // Set servo to gate closed position
}

/**
 * Opens the gate by gradually increasing the servo position.
 * This function moves the servo motor from the closed position to the open position, 
 * turning on the red LED during the movement and the green LED when fully open.
 */
void openGate() {
    redLED = ON;              // Turn on red LED (gate is moving)
    for (int i = 0; i < 250; i++) {
        servo.write(GATE_LOW + ((GATE_HIGH - GATE_LOW) / 250) * i);  // Gradually open gate
        delay(MOTOR_DELAY_MS);  // Wait before next movement
    }
    redLED = OFF;             // Turn off red LED (gate fully open)
    greenLED = ON;            // Turn on green LED (gate open)
}

/**
 * Closes the gate by gradually decreasing the servo position.
 * This function moves the servo motor from the open position to the closed position, 
 * turning on the green LED during the movement and the red LED when fully closed.
 */
void closeGate() {    
    greenLED = OFF;           // Turn off green LED (gate is moving)
    redLED = ON;              // Turn on red LED (gate is closing)
    for (int i = 0; i < 250; i++) {
        servo.write(GATE_HIGH - ((GATE_HIGH - GATE_LOW) / 250) * i);  // Gradually close gate
        delay(MOTOR_DELAY_MS);  // Wait before next movement
    }
    redLED = OFF;             // Turn off red LED (gate fully closed)
}

//=====[Implementations of private functions]==================================
