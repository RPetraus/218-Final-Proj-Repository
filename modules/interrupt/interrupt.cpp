//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "interrupt.h"

#include "code.h"
#include "collision_sensor.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

/**
 * Interrupt pin for the code reset button.
 * Triggered when the button is pressed to initiate a reset process.
 */
InterruptIn codeResetButton(D13);  

/**
 * Ticker object for collision sensor update.
 * Used to trigger the collision sensor update at regular intervals.
 */
Ticker collisionTicker;          

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]=========================

/**
 * Handles the code reset button press event.
 * This function is called when the reset button is pressed.
 */
static void codeResetButtonPressed();  

//=====[Implementations of public functions]===================================

/**
 * Initializes interrupt for the code reset button.
 * Configures the button to pull-down mode and attaches the interrupt handler
 * to trigger when the button is pressed (falling edge).
 */
void codeResetButtonInterrupt() {
    codeResetButton.mode(PullDown);  // Set button to pull-down mode
    codeResetButton.fall(&codeResetButtonPressed);  // Trigger when button is pressed
}

/**
 * Initializes the collision sensor interrupt with a 10ms interval.
 * Configures a ticker object to regularly trigger the collision sensor update.
 */
void collisionSensorInterrupt() {
    collisionTicker.attach(&collisionSensorUpdate, 10ms);  // Attach update function to ticker
}

//=====[Implementations of private functions]==================================

/**
 * Handles the code reset button press event.
 * 
 * Disables the interrupt temporarily, waits for debouncing, and then triggers
 * the reset code function. After the reset process, the interrupt is re-enabled.
 */
static void codeResetButtonPressed() {
    codeResetButton.fall(NULL);  // Disable the interrupt temporarily

    wait_us(100000);  // Debounce wait

    resetCode();  // Call the reset code function to initiate the reset process

    codeResetButton.fall(&codeResetButtonPressed);  // Re-enable interrupt after processing
}
