//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "matrix_keypad.h"
#include "mbed.h"

#include "parking_system.h"

#include "move_gate.h"
#include "pc_serial_com.h"
#include "user_display.h"
#include "sirens.h"
#include "code.h"
#include "car_at_entrance.h"

//=====[Declaration of private defines]========================================

#define UPDATE_TIME_MS                 10

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

/**
* Initializes the smart car system by initializing the subsystems
*/
void parkingSystemInit()
{
    pcSerialComInit(); // should not be initialized elsewhere

    sirensInit(); // should not be initialized elsewhere

    matrixKeypadInit(UPDATE_TIME_MS); // should not be initialized elsewhere

    userDisplayInit(); // should not be initialized elsewhere

    moveGateInit(); // should not be initialized elsewhere

    carAtEntranceInit(); // should not be initialized elsewhere

    resetCode(); // holds code; need to give code to move on

    inputCode();
}


void parkingSystemUpdate()
{
    carAtEntranceUpdate();
    
    openGate();
    delay(3000);
    closeGate();
    delay(3000);
    
    delay(SYSTEM_TIME_INCREMENT_MS);
}

//=====[Implementations of private functions]==================================