//=====[#include guards - begin]===============================================

#ifndef _IGNITION_SUBSYSTEM_H_
#define _IGNITION_SUBSYSTEM_H_

//=====[Declaration of public defines]=========================================

#define TIME_INCREMENT_MS 10

//=====[Declaration of public data types]======================================

//=====[Declaration and initialization of public global variables]=============


//=====[Declarations (prototypes) of public functions]=========================

void welcomeMessage();
void errorMessage();

bool debounceIgnition();

void ignitionEnable();
bool ignitionUpdate();

void ignitionSubsystemInit();

//=====[#include guards - end]=================================================

#endif // _IGNITION_SUBSYSTEM_H_