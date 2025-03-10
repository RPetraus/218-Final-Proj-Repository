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

static bool securityIssue = false;

//=====[Declarations (prototypes) of private functions]=========================

static void showAttempt(int attemptNumber);

//=====[Implementations of public functions]===================================

void entranceSubsystemInit()
{
    displayCharPositionWrite ( 0,0 );
    displayStringWrite( "Welcome!        " );
}

void entranceSubsystemUpdate() {
    int attemptNumber = 1;

    for ( int i = 0; i < 10; i++ ) {
        carIsDetected();
    }

    while (carIsDetected() && !securityIssue) {
        bool correctCode = false;
        int incorrectAttempts = 0;

        displayCharPositionWrite(0, 0);
        displayStringWrite("3 10sec Attempts");

        while (incorrectAttempts < 3 && !correctCode) {
            showAttempt(attemptNumber);

            if (isCodeCorrect()) {
                correctCode = true;
                openGate();
                delay(5000);
                closeGate();
            } else {
                incorrectAttempts++;
                attemptNumber++;
            }
        }

        for (int i = 0; i < 10; i++) {
            carIsDetected();
        }

        if (!carIsDetected()) {
            break;
        }

        if (!correctCode) {
            displayCharPositionWrite(0, 0);
            displayStringWrite("3 WRONG ATTEMPTS");

            displayCharPositionWrite(0, 1);
            displayStringWrite("ALARM ACTIVATED!");
            
            securityIssue = true;
            externalSirenStateWrite(ON);
            sirensUpdate();
        }
    }

    if (!securityIssue) {
        displayCharPositionWrite(0, 0);
        displayStringWrite("Welcome!        ");
        displayCharPositionWrite(0, 1);
        displayStringWrite("                ");
    }
}

/*
void entranceSubsystemUpdate() {
    int attemptNumber = 1;  // Start with the first attempt

    while (carIsDetected() && !securityIssue) {  // Loop runs while car is detected
        pcSerialComStringWrite("Car Detected\r\n");
        bool correctCode = false;
        int incorrectAttempts = 0;

        // Display message indicating the user has 10 seconds to input the correct code
        displayCharPositionWrite(0, 0);  // Set position to the first line
        displayStringWrite("3 10sec Attempts");  // Inform user they have 10 seconds to input the code

        // Try checking the code three times
        while (incorrectAttempts < 3 && !correctCode) {
            showAttempt(attemptNumber);  // Display the current attempt number on the first line

            if (isCodeCorrect()) {  // If the code is correct
                correctCode = true;
                openGate();
                delay(5000);  // Wait for 5 seconds with the gate open
                closeGate();
            } else {
                incorrectAttempts++;  // Increment incorrect attempts
                attemptNumber++;  // Increment the attempt number for each failed attempt
            }
        }

        for (int i = 0; i < 10; i++) {
            carIsDetected();  // Call the function, but don't use its result here
        }

        if (!carIsDetected()) {  // If no car is detected, exit the loop
            break;
        }

        if (!correctCode) {  // If the code was never correct
            // Update the display with a more precise message about failed attempts
            displayCharPositionWrite(0, 0);  // Set position to the second line
            displayStringWrite("3 WRONG ATTEMPTS");  // Inform about 3 wrong tries

            displayCharPositionWrite(0, 1);  // Set position to the second line
            displayStringWrite("ALARM ACTIVATED!");  // Alert that the alarm is triggered
            
            securityIssue = true;
            externalSirenStateWrite(ON);
            sirensUpdate();
            pcSerialComStringWrite("Alarm should be going off");
        }
    }

    if (!securityIssue) {
        pcSerialComStringWrite("No Car Detected\r\n");
        displayCharPositionWrite(0, 0);
        displayStringWrite("Welcome!        ");
        displayCharPositionWrite(0, 1);
        displayStringWrite("                ");
    }
}
*/

//=====[Implementations of private functions]==================================

void showAttempt(int attemptNumber) {
    displayCharPositionWrite(0, 1);

    char attemptMessage[20];
    snprintf(attemptMessage, sizeof(attemptMessage), "Attempt %d:      ", attemptNumber);

    displayStringWrite(attemptMessage);
}

/*
void showAttempt(int attemptNumber) {
    // Set the display to the first line
    displayCharPositionWrite(0, 1);

    // Create a string for the attempt message
    char attemptMessage[20];
    snprintf(attemptMessage, sizeof(attemptMessage), "Attempt %d:      ", attemptNumber);

    // Display the attempt message
    displayStringWrite(attemptMessage);
*/