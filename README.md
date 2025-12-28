## Smart Garage Automation System

This project demonstrates a smart garage door automation system built using the ATmega16 microcontroller and FreeRTOS. An IR obstacle sensor detects the presence of a vehicle, and a servo motor is used to open and close the garage gate automatically.

FreeRTOS is utilized to separate the sensor monitoring task and the servo control task, allowing clean multitasking and non-blocking delays. Servo control is implemented using Timer1 Fast PWM at 50 Hz, following standard servo motor specifications.

### Features
- Automatic garage door opening and closing
- IR sensor-based vehicle detection
- Servo motor control using PWM (Timer1)
- FreeRTOS task-based architecture
- Efficient task communication using task notifications
- Designed for ATmega16 (low RAM optimized)

### Technologies Used
- ATmega16 Microcontroller
- Embedded C (AVR-GCC)
- FreeRTOS
- IR Obstacle Sensor
- Servo Motor (SG90/MG90)

This project is suitable for academic demonstrations, embedded systems learning, and FreeRTOS practice on AVR microcontrollers.
