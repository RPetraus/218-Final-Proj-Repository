# Automated Luxury Parking System

Ryan Petrauskas and Brandon Mori

PROJECT DESCRIPTION
Luxury underground parking in high-end areas like Manhattan demands enhanced security, convenience, and safety for vehicle owners. Existing parking systems often lack sufficient access control and collision prevention mechanisms, increasing the risk of unauthorized access and potential accidents within parking spaces. This creates a need for a more secure and user-friendly solution that provides peace of mind while ensuring efficient vehicle management.


We propose an automated underground parking system designed to enhance security, safety, and user convenience. The system utilizes an LDR sensor to detect vehicle presence at the entrance gate, which can be unlocked using a matrix keypad for secure code-based access. LED indicators (red and green) inside the parking area guide the driver on when it is safe to enter. Once inside, an ultrasonic distance sensor helps prevent collisions by triggering a buzzer alert when the vehicle is too close to the wall. For a seamless exit, an exit button opens the gate, allowing the driver to back out safely. Additionally, a button inside the parking spot enables the driver to change the matrix keypad code, with updates displayed on the serial monitor for enhanced security control.


# System Components  

| Component                     | Description                                                         |
|-------------------------------|---------------------------------------------------------------------|
| **Driver Seat Sensor**        | Push button to detect if the driver seat is occupied                |
| **Passenger Seat Sensor**     | Push button to detect if the passenger seat is occupied             |
| **Driver Seatbelt Sensor**    | Toggle switch to check if the driver's seatbelt is fastened         |
| **Passenger Seatbelt Sensor** | Toggle switch to check if the driver's seatbelt is fastened         |
| **Ignition Button**           | Push Button on NUCLEO board to turn engine on or off                |
| **Indicator LEDs**            | Blue LED to show engine on and Green LED to show ignition enabled   |
| **Wiper Mode Selector**       | Potentiometer that selects wiper modes: HI, LO, INT, OFF            |
| **Int Delay Selector**        | Potentiometer that selects delay time in int mode: SHORT, MED, LONG |
| **LCD Display**               | Displays the current wiper mode and delay time chosen by user       |
| **Windshield Wiper Motor**    | Positional Servo that simulates windshield wiper movement           |
| **Siren**                     | Sounds when try to start the engine when system is not ready        |
| **Windshield Wiper**          | Pencil                                                              |

# Wiper Modes  

| Mode    | Potentiometer Range | Behavior                                                  |
|---------|---------------------|-----------------------------------------------------------|
| **HI**  | >= 0.75             | Wipers move at high speed                                 |
| **LO**  | 0.50 - 0.75         | Wipers move at low speed                                  |
| **INT** | 0.25 - 0.50         | Wipers move at low speed, with given delay between sweeps |
| **OFF** | < 0.25              | Wipers do not move and remain stationary                  |

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




