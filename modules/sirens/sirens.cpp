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
 * @brief Initializes the sirens to the OFF state (inactive).
 * 
 * Both internal and external sirens are set to ON (inactive state) 
 * at the beginning to prevent them from being activated unintentionally.
 */
void sirensInit()
{
    internalSirenPin = ON;  // Internal siren is inactive
    externalSirenPin = ON;  // External siren is inactive
}

/**
 * @brief Reads the current state of the internal siren (ON/OFF).
 * 
 * @return The current state of the internal siren. Returns true if 
 * the siren is on, otherwise false.
 */
bool internalSirenStateRead()
{
    return internalSirenState;
}

/**
 * @brief Reads the current state of the external siren (ON/OFF).
 * 
 * @return The current state of the external siren. Returns true if 
 * the siren is on, otherwise false.
 */
bool externalSirenStateRead()
{
    return externalSirenState;
}

/**
 * @brief Sets the internal siren state (ON/OFF).
 * 
 * @param state The desired state of the internal siren. Pass true 
 * to activate the siren (ON), and false to deactivate it (OFF).
 */
void internalSirenStateWrite(bool state)
{
    internalSirenState = state;
}

/**
 * @brief Sets the external siren state (ON/OFF).
 * 
 * @param state The desired state of the external siren. Pass true 
 * to activate the siren (ON), and false to deactivate it (OFF).
 */
void externalSirenStateWrite(bool state)
{
    externalSirenState = state;
}

/**
 * @brief Updates the physical state of both sirens based on their current state.
 * 
 * This function controls the actual hardware pins for both sirens. If the 
 * internal or external siren is set to ON (active), the corresponding pin 
 * is set to LOW. If the siren is OFF (inactive), the pin is set to HIGH.
 */
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
