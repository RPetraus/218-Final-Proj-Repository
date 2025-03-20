//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "exit_subsystem.h"

#include "move_gate.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

/**
 * Digital input for detecting the exit button state.
 * This pin is used to check if the user has pressed the button to trigger the gate opening.
 */
DigitalIn exitButton(D12);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]=========================

//=====[Implementations of public functions]===================================

/**
 * Initializes the exit subsystem by setting the exit button pin mode.
 * This function configures the exitButton pin (D12) to use a pull-down resistor,
 * ensuring the pin reads LOW by default when the button is not pressed.
 */
void exitSubsystemInit()
{
    exitButton.mode(PullDown);  // Set the button to pull-down mode
}

/**
 * Monitors the exit button and controls the gate based on its state.
 * If the exit button is pressed (HIGH state), the gate will open, 
 * stay open for 5 seconds, and then close.
 */
void exitSubsystemUpdate() {
    if (exitButton) {  // If the exit button is pressed
        openGate();     // Open the gate
        delay(5000);    // Wait for 5 seconds
        closeGate();    // Close the gate
    }
}

//=====[Implementations of private functions]==================================
