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

static bool securityIssue = false;  ///< Tracks if there is a security issue (e.g., failed attempts)

//=====[Declarations (prototypes) of private functions]=========================

/**
 * @brief Helper function to display the current attempt number on the display.
 * 
 * This function is called to update the display with the current attempt number 
 * during the process of code entry by the car at the entrance.
 * 
 * @param attemptNumber The current attempt number.
 */
static void showAttempt(int attemptNumber);  

//=====[Implementations of public functions]===================================

/**
 * @brief Initializes the entrance subsystem and displays a welcome message.
 * 
 * This function is responsible for initializing the entrance subsystem. It sets
 * the display cursor to the starting position and shows a welcome message to
 * the user when the system is initialized.
 */
void entranceSubsystemInit()
{
    displayCharPositionWrite(0, 0);           // Set cursor to position (0, 0)
    displayStringWrite("Welcome!        ");    // Display welcome message
}

/**
 * @brief Updates the entrance subsystem logic, including code entry and gate control.
 * 
 * This function handles the logic for code entry attempts when a car is detected.
 * The driver has 3 attempts to enter the correct code. If the code is correct, 
 * the gate will open for 5 seconds. If the code is incorrect after 3 attempts, 
 * a security issue is flagged.
 * 
 * @note The entrance subsystem is responsible for controlling the display and gate.
 */
void entranceSubsystemUpdate() {
    if (carIsDetected() && !securityIssue) {  ///< Check if car is detected and no security issue
        bool correctCode = false;             ///< Flag to track if code entered is correct
        int incorrectAttempts = 0;            ///< Counter for incorrect attempts
        int attemptNumber = 1;                ///< Tracks the number of attempts

        displayCharPositionWrite(0, 0);       // Set cursor to position (0, 0)
        displayStringWrite("3 10sec Attempts");  // Display number of attempts allowed

        // Attempt code entry, up to 3 times
        while (incorrectAttempts < 3 && !correctCode) {
            showAttempt(attemptNumber);       ///< Display the current attempt number

            // Check if the code entered is correct
            if (isCodeCorrect()) {
                displayCharPositionWrite(0, 0); 
                displayStringWrite("Welcome!        "); // Display welcome message after correct code
                displayCharPositionWrite(0, 1);
                displayStringWrite("                "); // Clear the second line after success

                correctCode = true;            // Mark as correct code
                openGate();                    // Open the gate
                delay(5000);                   // Keep the gate open for 5 seconds
                closeGate();                   // Close the gate after 5 seconds
            } else {
                incorrectAttempts++;          // Increment the incorrect attempt counter
                attemptNumber++;               // Increment the attempt number
                displayCharPositionWrite(0, 1); // Move cursor to the second line
                displayStringWrite("Wrong code!    "); // Display error message on incorrect entry
                delay(1000);                   // Wait for a second before the next attempt
            }
        }

        // If 3 incorrect attempts are made, trigger a security issue
        if (incorrectAttempts >= 3) {
            securityIssue = true;              // Flag a security issue
            activateSirens();                  // Activate sirens as a security measure
            displayCharPositionWrite(0, 0);
            displayStringWrite("Security Issue! "); // Display security issue message
        }
    }
}

/**
 * @brief Displays the current attempt number on the display.
 * 
 * This helper function is used within the entrance subsystem to display the 
 * current attempt number on the first line of the display.
 * 
 * @param attemptNumber The current attempt number to display.
 */
static void showAttempt(int attemptNumber) {
    displayCharPositionWrite(0, 1);  // Set cursor to position (0, 1)
    char attemptMessage[16];          // Buffer to hold the message
    sprintf(attemptMessage, "Attempt: %d", attemptNumber);  // Format the attempt message
    displayStringWrite(attemptMessage);  // Display the formatted attempt number
}
