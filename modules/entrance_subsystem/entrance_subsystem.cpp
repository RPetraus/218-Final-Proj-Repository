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
    if (carIsDetected() && !securityIssue) {
        bool correctCode = false;
        int incorrectAttempts = 0;
        int attemptNumber = 1;

        displayCharPositionWrite(0, 0);
        displayStringWrite("3 10sec Attempts");

        while (incorrectAttempts < 3 && !correctCode) {
            showAttempt(attemptNumber);

            if (isCodeCorrect()) {
                displayCharPositionWrite(0, 0);
                displayStringWrite("Welcome!        ");
                displayCharPositionWrite(0, 1);
                displayStringWrite("                ");
                correctCode = true;
                openGate();
                delay(5000);
                closeGate();
            } else {
                incorrectAttempts++;
                attemptNumber++;
            }
        }

        displayCharPositionWrite(0, 0);
        displayStringWrite("Welcome!        ");
        displayCharPositionWrite(0, 1);
        displayStringWrite("                ");

        for (int i = 0; i < 10; i++) {
            sensorUpdate();
        }

        if (!correctCode && carIsDetected()) {
            securityIssue = true;
            externalSirenStateWrite(ON);
            sirensUpdate();

            displayCharPositionWrite(0, 0);
            displayStringWrite("3 WRONG ATTEMPTS");

            displayCharPositionWrite(0, 1);
            displayStringWrite("ALARM ACTIVATED!");
        }
    }
}

//=====[Implementations of private functions]==================================

void showAttempt(int attemptNumber) {
    displayCharPositionWrite(0, 1);

    char attemptMessage[20];
    snprintf(attemptMessage, sizeof(attemptMessage), "Attempt %d:      ", attemptNumber);

    displayStringWrite(attemptMessage);
}