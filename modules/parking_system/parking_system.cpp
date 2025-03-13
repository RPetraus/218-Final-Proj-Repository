//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "matrix_keypad.h"
#include "mbed.h"

#include "parking_system.h"

#include "sirens.h"
#include "display.h"
#include "pc_serial_com.h"
#include "code.h"
#include "move_gate.h"
#include "car_at_entrance.h"
#include "entrance_subsystem.h"
#include "exit_subsystem.h"
#include "collision_sensor.h"
#include "interrupt.h"

//=====[Declaration of private defines]========================================

#define UPDATE_TIME_MS                 10

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void parkingSystemInit()
{     
    sirensInit();

    displayInit();

    matrixKeypadInit(UPDATE_TIME_MS);

    moveGateInit();
    
    carAtEntranceInit();

    entranceSubsystemInit();

    exitSubsystemInit();

    distanceSensorInit();

    codeResetButtonInterrupt();

    collisionSensorInterrupt();
}


void parkingSystemUpdate()
{
    entranceSubsystemUpdate();

    exitSubsystemUpdate();
    
    delay(SYSTEM_TIME_INCREMENT_MS);
}

//=====[Implementations of private functions]==================================
