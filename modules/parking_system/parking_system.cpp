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

/**
 * @brief Initializes the parking system by setting up all necessary subsystems.
 * 
 * This function performs the initialization of all the modules needed for the 
 * parking system to function properly, including the sirens, display, keypad, 
 * gate movement, entrance and exit subsystems, and sensors.
 */
void parkingSystemInit()
{     
    sirensInit();                    ///< Initializes the sirens system.
    displayInit();                   ///< Initializes the display system.
    matrixKeypadInit(UPDATE_TIME_MS);///< Initializes the keypad matrix with a defined update time.
    moveGateInit();                  ///< Initializes the gate movement system.
    carAtEntranceInit();             ///< Initializes the car detection at the entrance.
    entranceSubsystemInit();         ///< Initializes the entrance subsystem for vehicle entry control.
    exitSubsystemInit();             ///< Initializes the exit subsystem for vehicle exit control.
    distanceSensorInit();            ///< Initializes the distance sensor for collision prevention.
    codeResetButtonInterrupt();      ///< Sets up the interrupt for the code reset button.
    collisionSensorInterrupt();      ///< Sets up the interrupt for collision sensor events.
}

/**
 * @brief Updates the state of the parking system.
 * 
 * This function updates the entrance and exit subsystems, handling the logic 
 * for vehicle entry and exit. It also handles periodic delays to manage 
 * the system's timing.
 */
void parkingSystemUpdate()
{
    entranceSubsystemUpdate();       ///< Updates the entrance subsystem for vehicle entry.
    exitSubsystemUpdate();           ///< Updates the exit subsystem for vehicle exit.
    
    delay(SYSTEM_TIME_INCREMENT_MS); ///< Delays to maintain the system time increment.
}

//=====[Implementations of private functions]==================================
