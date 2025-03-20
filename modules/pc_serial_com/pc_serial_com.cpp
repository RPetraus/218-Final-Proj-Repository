//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "pc_serial_com.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

UnbufferedSerial uartUsb(USBTX, USBRX, 115200);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

/**
 * Sends a string over the serial interface.
 * 
 * This function writes a null-terminated string to the serial interface 
 * using the configured UART communication. It sends the string byte by byte 
 * over the USB serial port.
 *
 * @param str The string to be written to the interface.
 * @return None
 */
void pcSerialComStringWrite( const char* str )
{
    uartUsb.write( str, strlen(str) );
}

/**
 * Reads a single character from the serial interface.
 * 
 * This function waits until a character is received over the serial interface 
 * and then stores it in the provided variable.
 *
 * @param receivedChar A pointer to a variable where the received character will be stored.
 * @return None
 */
void pcSerialComCharRead( char *receivedChar ) {
    uartUsb.read( receivedChar, 1 );
}
