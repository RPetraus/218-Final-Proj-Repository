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

# Success Cases

| Pass Case                          | Description                                                   | Expected Behavior                                              | Status |
|-------------------------------------|---------------------------------------------------------------|----------------------------------------------------------------|--------|
| **Correct Code Entered**            | The user enters the correct code within 3 attempts.            | The gate opens, and the system displays "Welcome!" before closing the gate after 5 seconds. | Pass   |
| **Car Detected with Correct Code** | A car is detected at the entrance, and the correct code is entered within the allowed attempts. | The system grants access, opens the gate, and displays a welcome message. | Pass   |
| **Multiple Incorrect Attempts (3)** | The user enters 3 incorrect codes.                            | After 3 failed attempts, the system triggers a security issue, activates the alarm, and displays "ALARM ACTIVATED!". | Pass   |
| **Successful Gate Operation**      | After entering the correct code, the gate opens and closes as expected. | The gate opens for 5 seconds and then closes. While opening or closing, redLed should be on. While gate is open, greenLed should be on                 | Pass   |
| **Display Updates Correctly**      | The display shows the correct information during each attempt. | The system displays "3 10sec Attempts", the attempt number, and correct status messages ("Welcome!" or "ALARM ACTIVATED!"). | Pass   |
| **Siren Activated After 3 Failures** | After 3 incorrect attempts, the siren activates.              | The siren should be turned on, and the system should display "3 WRONG ATTEMPTS" and "ALARM ACTIVATED!". | Pass   |

| **Car Detected and System Activated** | The system detects a car at the entrance and activates the entrance subsystem. | The entrance system is activated and ready to receive code input. | Pass   |
| **Attempt Number Displayed Correctly** | Each attempt number is displayed correctly on the screen.      | The display shows the current attempt number in the format "Attempt X". | Pass   |



# Fail Cases/Trouble Shooting  

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
