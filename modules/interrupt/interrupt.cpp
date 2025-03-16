//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "interrupt.h"
#include "code.h"
#include "collision_sensor.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

InterruptIn codeResetButton(D13);  // Interrupt pin for code reset button
Ticker collisionTicker;           // Ticker object for collision sensor update

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]=========================

static void codeResetButtonPressed();  // Function called when the reset button is pressed

//=====[Implementations of public functions]===================================

// Initializes interrupt for the code reset button
void codeResetButtonInterrupt() {
    codeResetButton.mode(PullDown);  // Set button to pull-down mode
    codeResetButton.fall(&codeResetButtonPressed);  // Trigger when button is pressed
}

// Initializes the collision sensor interrupt with a 10ms interval
void collisionSensorInterrupt() {
    collisionTicker.attach(&collisionSensorUpdate, 10ms);  // Attach update function to ticker
}

//=====[Implementations of private functions]==================================

// Handles the code reset button press event
static void codeResetButtonPressed() {
    codeResetButton.fall(NULL);  // Disable the interrupt temporarily

    wait_us(100000);  // Debounce wait

    resetCode();  // Call the reset code function to initiate the reset process

    codeResetButton.fall(&codeResetButtonPressed);  // Re-enable interrupt after processing
}
