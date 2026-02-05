# Room Security and Automation 
**Course:** Digital Logic Design (Semester 2)
**Tools Used:** Multisim (Circuit Simulation)

##  Project Overview
A smart room system designed to integrate security and automation features. The project focuses on creating a secure environment through password-based access control while optimizing energy efficiency with automated appliance management.

##  Key Features
* **5-Bit Binary Digital Lock:** Secure entry system utilizing XNOR logic for password validation.
* **Intrusion Alarm System:** Triggers an alarm after 3 incorrect password attempts or if motion is detected while the door is unauthorized.
* **Automated Lighting:** PIR-based occupancy detection to automatically turn lights on/off.
* **Temperature Control:** Integrated temperature sensing to activate ventilation or cooling when thresholds are exceeded.
* **Visual Status Display:** A DCD_HEX display to show system status (e.g., "OPEN" or "WRONG").

##  Components & Logic
* **Logic Gates (AND, XNOR):** Used for 5-bit binary password validation.
* **JK Flip-Flops:** Implemented to count and limit incorrect password attempts.
* **Sensors:** PIR Motion Sensor, Light Dependent Resistor (LDR), and Temperature Sensors.
* **Outputs:** Alarms (Buzzer/Siren) and Probe Lights to simulate automated appliances.

##  Project Files
* **[DLD-Project-Report.pdf](./DLDProject-Report.pdf):** Full technical documentation and circuit diagrams.
* **Simulation Folder:** Contains Multisim circuit files for different scenarios (Password verification, Motion detection, etc.).

