//=====[Libraries]=============================================================

#include "mbed.h"

#include "code.h"

#include "pc_serial_com.h"
#include "matrix_keypad.h"
#include "display.h"

#include "stdio.h"

//=====[Declaration of private defines]========================================

#define CODE_LENGTH 6

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

int codeSequence[CODE_LENGTH] = {1, 1, 1, 1, 1, 1};

//=====[Declaration and initialization of private global variables]============

static int codeLetterNum;

//=====[Declarations (prototypes) of private functions]========================

static int* inputCode();

//=====[Implementations of public functions]===================================

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
        
        for (int i = 0; i < CODE_LENGTH; i++) {
            do {
                pcSerialComCharRead(&receivedChar);

                if (receivedChar == 'C' || receivedChar == 'c') {
                    pcSerialComStringWrite("\r\nCode reset cancelled.\r\n");
                    return;
                }

                if (receivedChar >= '0' && receivedChar <= '9') {
                    tempCode[i] = receivedChar - '0';
                    pcSerialComStringWrite("*");
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
                    pcSerialComStringWrite("*");
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

static int* inputCode() {
    static int inputtedCode[CODE_LENGTH];
    char keyReleased;
    bool codeComplete = false;
    int codeIndex = 0;
    int displayPosition = 10;
    char keyReleasedStr[2];
    keyReleasedStr[1] = '\0';
    
    Timer timer;
    timer.start();
    
    chrono::milliseconds timeout(10000);
    
    while (!codeComplete) {
        keyReleased = matrixKeypadUpdate();

        if (timer.elapsed_time() >= timeout) {
            break;
        }

        if (keyReleased != '\0') {
            if (keyReleased >= '0' && keyReleased <= '9') {
                if (codeIndex < CODE_LENGTH) {
                    inputtedCode[codeIndex] = keyReleased - '0';

                    keyReleasedStr[0] = keyReleased;
                    displayCharPositionWrite(displayPosition, 1);
                    displayStringWrite(keyReleasedStr);

                    codeIndex++;
                    displayPosition++;

                    if (codeIndex == CODE_LENGTH) {
                        codeIndex = 0;
                        codeComplete = true;
                    }
                }
            }
        }
    }

    return inputtedCode;
}

/*
static int* inputCode() {
    pcSerialComStringWrite("\r\nPlease enter the code sequence: ");
    
    static int inputtedCode[CODE_LENGTH];
    char keyReleased;
    bool codeComplete = false;
    int codeIndex = 0;
    int displayPosition = 10;
    char keyReleasedStr[2];
    keyReleasedStr[1] = '\0';
    
    Timer timer;
    timer.start();
    
    chrono::milliseconds timeout(10000);
    
    while (!codeComplete) {
        keyReleased = matrixKeypadUpdate();

        if (timer.elapsed_time() >= timeout) {
            break;
        }

        if (keyReleased != '\0') {
            if (keyReleased >= '0' && keyReleased <= '9') {
                if (codeIndex < CODE_LENGTH) {
                    inputtedCode[codeIndex] = keyReleased - '0';

                    pcSerialComStringWrite("*");

                    keyReleasedStr[0] = keyReleased;
                    displayCharPositionWrite(displayPosition, 1);
                    displayStringWrite(keyReleasedStr);

                    codeIndex++;
                    displayPosition++;

                    if (codeIndex == CODE_LENGTH) {
                        codeIndex = 0;
                        codeComplete = true;
                    }
                }
            }
        }
    }

    return inputtedCode;
}
*/