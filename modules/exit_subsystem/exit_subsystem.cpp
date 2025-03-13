//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"

#include "exit_subsystem.h"

#include "move_gate.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalIn exitButton(D12);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]=========================

//=====[Implementations of public functions]===================================

void exitSubsystemInit()
{
    exitButton.mode(PullDown);
}

void exitSubsystemUpdate() {
    if (exitButton) {
        openGate();
        delay(5000);
        closeGate();
    }
}

//=====[Implementations of private functions]==================================
