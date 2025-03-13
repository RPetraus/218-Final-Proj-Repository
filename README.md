# Automated Luxury Underground Parking System

Ryan Petrauskas and Brandon Mori

# Project Description
Luxury underground parking in heavily populated urban areas like Manhattan demands enhanced security, convenience, and safety for vehicle owners. Existing parking systems often lack sufficient access control and collision prevention mechanisms, increasing the risk of unauthorized access and potential accidents within parking spaces. This creates a need for a more secure and user-friendly solution that provides peace of mind while ensuring efficient vehicle management.


We propose an automated underground parking system designed to enhance security, safety, and user convenience. The system utilizes an LDR sensor to detect vehicle presence at the entrance gate, which can be unlocked using a matrix keypad for secure code-based access. LED indicators (red and green) inside the parking area guide the driver on when it is safe to enter. At the same time, an ultrasonic distance sensor helps prevent collisions by triggering a buzzer alert when the vehicle is too close to the wall. For a seamless exit, an exit button opens the gate, allowing the driver to back out safely. Additionally, a button inside the parking spot enables the driver to change the matrix keypad code, with updates displayed on the serial monitor for enhanced security control.


# System Components  

| Component                     | Description                                                         |
|-------------------------------|---------------------------------------------------------------------|
| **Microcontroller**           | STM32 Nucleo – the core controller for the system              |
| **Matrix Keypad**             | Used for secure code-based entry                               |
| **LDR Sensor**                | Detects vehicle presence at the entrance and parking spot      |
| **Ultrasonic Sensor**         | Measures distance to prevent collisions                          |
| **2x Buzzer**                 | One for collision warning, one for security alert               |
| **Indicator LEDs**            | Blue LED to show engine on and Green LED to show ignition enabled   |
| **2x LED**                    | Red LED indicates gate movement; Green LED signals safe entry         |
| **LCD Display**               | Displays system messages |
| **Positional Servo**          | Controls gate movement by lifting and lowering it                      |


# Fail Cases  

| Fail Case                         | Description                                                   | Solution                                                       |
|------------------------------------|---------------------------------------------------------------|---------------------------------------------------------------|
| **Wrong Code Entered**             | The user enters an incorrect code for access.                 | The system allows 3 attempts before triggering a security issue. |
| **Security Issue Triggered**      | After 3 incorrect attempts, a security issue is flagged.      | An alarm is triggered (external siren is activated) and the display shows "ALARM ACTIVATED!" |
| **Car Not Detected**              | The system fails to detect the car at the entrance.            | Ensure proper sensor functionality and that the car is within detection range. |
| **Gate Fails to Open**             | The gate fails to open after the correct code is entered.     | Verify motor functions and ensure gate opening command (`openGate()`) is being executed correctly. |
| **Display Failure**                | The display shows incorrect or no message during operation.   | Check the display wiring and ensure correct positioning in the `displayCharPositionWrite` and `displayStringWrite` calls. |
| **Code Check Failure**             | The code check (`isCodeCorrect()`) fails but should succeed.  | Debug the `isCodeCorrect()` function for issues with code validation. |
| **Timing Issues**                  | The timing for 10 seconds for attempts might be incorrect.    | Ensure the delay functions and timing conditions are set correctly for each attempt. |
| **Siren Not Triggered**            | The external siren doesn't activate after failed attempts.    | Check the siren control logic (`externalSirenStateWrite(ON)`) and the `sirensUpdate()` function. |
| **Incorrect Sensor Update**        | The sensors fail to update correctly after the 3 failed attempts. | Ensure that the `sensorUpdate()` function works properly and is called the expected number of times (10). |

# Intermittent Delay Time Modes  

| Mode       | Potentiometer Range | Behavior                            |
|------------|---------------------|-------------------------------------|
| **LONG**   | >= 0.66             | 8-second delay between wiper sweeps |
| **MEDIUM** | 0.66 - 0.33         | 6-second delay between wiper sweeps |
| **SHORT**  | < 0.33              | 3-second delay between wiper sweeps |

# Testing Results  

| Subsystem                   | Specification                                                                  | Results  | 
|-----------------------------|--------------------------------------------------------------------------------|----------|
| **Ignition System**         | Enable engine start when both seats are occupied and seatbelts fastened        |  Pass    |
|                             | Welcome driver when seated                                                     |  Pass    |
|                             | Display appropriate error messages when ignition is inhibited                  |  Pass    |
|                             | Allows for multiple attempts to start engine                                   |  Pass    |
|                             | Keep the engine running even if seat belts are unfastened or occupants leave   |  Pass    |
|                             | Stop the engine when the ignition button is pressed and released               |  Pass    |
| **Windshield Wiper System** | Wipers run in HI, LO, INT, or OFF when engine is running                       |  Pass    |
|                             | In INT mode, delay time is correct based on chosen mode (SHORT, MED, LONG)     |  Pass    |
|                             | Selected mode is displayed, including selection of delay time                  |  Pass    |
|                             | Wipers turn off if engine turns off                                            |  Pass    |
|                             | Wipers complete cycle and return to 0 degrees if engine is turned off          |  Pass    |
|                             | Wipers complete cycle and return to 0 degrees if wipers are turned off         |  Pass    |
|                             | Wipers remain stationary if engine is turned off while hesitating in INT mode  |  Pass    |
|                             | Wipers remain stationary if wipers are turned off while hesitating in INT mode |  Pass    |




