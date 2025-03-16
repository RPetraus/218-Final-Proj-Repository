//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "entrance_subsystem.h"

#include "car_at_entrance.h"
#include "code.h"
#include "sirens.h"
#include "move_gate.h"
#include "display.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static bool securityIssue = false;  // Tracks if there is a security issue (e.g., failed attempts)

//=====[Declarations (prototypes) of private functions]=========================

static void showAttempt(int attemptNumber);  // Helper function to display attempt number

//=====[Implementations of public functions]===================================

// Initializes the entrance subsystem, displaying the welcome message
void entranceSubsystemInit()
{
    displayCharPositionWrite(0, 0);           // Set cursor to position (0, 0)
    displayStringWrite("Welcome!        ");    // Display welcome message
}

// Updates the entrance subsystem logic (handles code entry and gate control)
void entranceSubsystemUpdate() {
    if (carIsDetected() && !securityIssue) {  // Check if car is detected and no security issue
        bool correctCode = false;             // Flag for correct code entry
        int incorrectAttempts = 0;            // Counter for incorrect attempts
        int attemptNumber = 1;                // Tracks the number of attempts

        displayCharPositionWrite(0, 0);       // Set cursor to position (0, 0)
        displayStringWrite("3 10sec Attempts");  // Display the number of attempts

        // Attempt code entry, up to 3 times
        while (incorrectAttempts < 3 && !correctCode) {
            showAttempt(attemptNumber);       // Display the current attempt number

            // Check if the code entered is correct
            if (isCodeCorrect()) {
                displayCharPositionWrite(0, 0);
                displayStringWrite("Welcome!        "); // Display welcome message
                displayCharPositionWrite(0, 1);
                displayStringWrite("                "); // Clear the second line

                correctCode = true;            // Mark as correct code
                openGate();                    // Open the gate
                delay(5000);                   // Keep the gate open for 5 seconds
                closeGate();                   // Close the gate after 5 seconds
            } else {
