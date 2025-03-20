//=====[Libraries]=============================================================

#include "mbed.h"
#include "code.h"
#include "pc_serial_com.h"
#include "matrix_keypad.h"
#include "display.h"
#include "stdio.h"

//=====[Declaration of private defines]========================================

#define CODE_LENGTH 6  ///< Defines the required length of the security code

//=====[Declaration and initialization of public global variables]=============

int codeSequence[CODE_LENGTH] = {1, 1, 1, 1, 1, 1};  ///< Default security code

//=====[Declaration and initialization of private global variables]============

static int codeLetterNum;  ///< Stores the number of entered code digits

//=====[Declarations (prototypes) of private functions]========================

/**
 * @brief Captures user input from the keypad and validates it.
 * 
 * @return Pointer to the dynamically allocated array containing the entered code.
 */
static int* inputCode();

//=====[Implementations of public functions]===================================

/**
 * @brief Resets the security code with user input validation.
 * 
 * This function allows the user to enter a new security code, confirms it by re-entering,
 * and updates the stored code if both entries match.
 */
void resetCode() {
    pcSerialComStringWrite("\r\n\r\nPlease enter a new code sequence.\r\n");
    pcSerialComStringWrite("The allowable length of the sequence is 6.\r\n");
    pcSerialComStringWrite("The sequence may include any of:\r\n");
    pcSerialComStringWrite("'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'\r\n\r\n");
    pcSerialComStringWrite("To cancel, press 'C'.\r\n");

    int tempCode[CODE_LENGTH];
    char receivedChar;

    while (true) {
        pcSerialComStringWrite("Enter the new code: ");
        
        // Collect new code sequence from user input
        for (int i = 0; i < CODE_LENGTH; i++) {
            do {
                pcSerialComCharRead(&receivedChar);

                if (receivedChar == 'C' || receivedChar == 'c') {
                    pcSerialComStringWrite("\r\nCode reset cancelled.\r\n");
                    return;
                }

                if (receivedChar >= '0' && receivedChar <= '9') {
                    tempCode[i] = receivedChar - '0';
                    pcSerialComStringWrite("*");  // Masking user input
                    break;
                } else {
                    pcSerialComStringWrite("\r\nInvalid input! Please enter a digit (0-9).\r\n");
                    pcSerialComStringWrite("Current sequence: ");
                    for (int j = 0; j < i; j++) {
                        pcSerialComStringWrite("*");
                    }
                }
            } while (true);
        }

        pcSerialComStringWrite("\r\nRe-enter the code to confirm: ");

        // Confirm new code by re-entering
        bool match = true;
        for (int i = 0; i < CODE_LENGTH; i++) {
            do {
                pcSerialComCharRead(&receivedChar);

                if (receivedChar == 'C' || receivedChar == 'c') {
                    pcSerialComStringWrite("\r\nCode reset cancelled.\r\n");
                    return;
                }

                if (receivedChar >= '0' && receivedChar <= '9') {
                    if (tempCode[i] != receivedChar - '0') {
                        match = false;
                    }
                    pcSerialComStringWrite("*");  // Masking input
                    break;
                } else {
                    pcSerialComStringWrite("\r\nInvalid input! Please enter a digit (0-9).\r\n");
                    pcSerialComStringWrite("Current sequence: ");
                    for (int j = 0; j < i; j++) {
                        pcSerialComStringWrite("*");
                    }
                }
            } while (true);
        }

        // Set the new code if both entries match
        if (match) {
            for (int i = 0; i < CODE_LENGTH; i++) {
                codeSequence[i] = tempCode[i];
            }
            pcSerialComStringWrite("\r\nNew code set successfully!\r\n\r\n");
            break;
        } else {
            pcSerialComStringWrite("\r\nError: The codes did not match! Please try again.\r\n\r\n");
        }
    }
}

/**
 * @brief Compares user-entered code with the stored security code.
 * 
 * @return True if the entered code matches the stored code, false otherwise.
 */
bool isCodeCorrect() {
    int* inputtedCode = inputCode(); 

    for (int i = 0; i < CODE_LENGTH; i++) {
        if (inputtedCode[i] != codeSequence[i]) {
            return false;
        }
    }
    return true;
}

//=====[Implementations of private functions]==================================

/**
 * @brief Captures user input from the keypad and validates it.
 * 
 * This function reads keypad inputs until a full code is entered or a timeout occurs.
 * It dynamically allocates memory for the inputted code, which must be manually deallocated.
 * 
 * @return Pointer to the dynamically allocated array containing the entered code.
 */
static int* inputCode() {
    int* inputtedCode = new int[CODE_LENGTH];  ///< Dynamically allocated memory for storing code input
    char keyReleased;
    bool codeComplete = false;
    int codeIndex = 0;
    int displayPosition = 10;  ///< Position on LCD to display input
    char keyReleasedStr[2];
    keyReleasedStr[1] = '\0';
    
    Timer timer;
    timer.start();
    
    chrono::milliseconds timeout(10000);  ///< Timeout for input entry (10 seconds)
    
    while (!codeComplete) {
        keyReleased = matrixKeypadUpdate();  ///< Get keypad input

        if (timer.elapsed_time() >= timeout) {  ///< Check if timeout has occurred
            break;
        }

        if (keyReleased != '\0') {
            if (keyReleased >= '0' && keyReleased <= '9') {
                if (codeIndex < CODE_LENGTH) {
                    inputtedCode[codeIndex] = keyReleased - '0';
                    keyReleasedStr[0] = keyReleased;
                    displayCharPositionWrite(displayPosition, 1);  ///< Update LCD display
                    displayStringWrite(keyReleasedStr);
                    codeIndex++;
                    displayPosition++;
                    if (codeIndex == CODE_LENGTH) {
                        codeComplete = true;  ///< Code entry complete
                    }
                }
            }
        }
    }
    return inputtedCode;
}
