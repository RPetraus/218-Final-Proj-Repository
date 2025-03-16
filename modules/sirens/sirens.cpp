//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "sirens.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalOut internalSirenPin(PE_10);  // Pin controlling internal siren
DigitalOut externalSirenPin(PE_12);  // Pin controlling external siren

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static bool internalSirenState = OFF;  // Current state of internal siren (ON/OFF)
static bool externalSirenState = OFF;  // Current state of external siren (ON/OFF)

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

/**
* Initializes the sirens to not output
* Both internal and external sirens are set to ON (inactive state)
*/
void sirensInit()
{
    internalSirenPin = ON;  // Internal siren is inactive
    externalSirenPin = ON;  // External siren is inactive
}
 

// Reads the current state of the internal siren (ON/OFF)
bool internalSirenStateRead()
{
    return internalSirenState;
}

// Reads the current state of the external siren (ON/OFF)
bool externalSirenStateRead()
{
    return externalSirenState;
}

// Sets the internal siren state (ON/OFF)
void internalSirenStateWrite(bool state)
{
    internalSirenState = state;
}

// Sets the external siren state (ON/OFF)
void externalSirenStateWrite(bool state)
{
    externalSirenState = state;
}

// Updates the physical state of both sirens based on their current state
void sirensUpdate() {
    if (internalSirenState) {
        internalSirenPin = OFF;  // Internal siren is ON (active)
    } else {
        internalSirenPin = ON;   // Internal siren is OFF (inactive)
    }
    
    if (externalSirenState) {
        externalSirenPin = OFF;  // External siren is ON (active)
    } else {
        externalSirenPin = ON;   // External siren is OFF (inactive)
    }
}

//=====[Implementations of private functions]==================================
