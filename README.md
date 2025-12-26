# Embedded_forklift_robot
Embedded forklift robot integrating DC motor control, ultrasonic sensing, NeoPixel feedback, and a servo actuator. Focuses on power-domain separation, debugging under load, and reliable mixed-signal system design.

# Project description
🚜 Embedded Forklift Robot – Power-Aware Control System
🧠 Project Overview

This project implements an embedded mobile forklift platform with obstacle detection, visual feedback, and a servo-driven lifting mechanism.
Beyond basic motion control, the project focuses on system-level design, power-domain separation, and debugging hardware limitations under load.

The goal was not just to “make it work”, but to design, analyze, and fix a mixed-signal embedded system operating under real power constraints.

🚗 Motion Control (DC Motors)

Differential drive using two DC motors

Motors driven by an L298N H-bridge

Controlled via a joystick:

Forward / backward

Left / right turning

Independent speed control enables smooth steering

📏 Obstacle Detection

An ultrasonic sensor measures distance in front of the robot

Distance data is used for:

Logic decisions

Serial debugging and calibration

Models basic collision-avoidance sensing found in real vehicles

💡 Visual Feedback (NeoPixel)

An 8-LED WS2812B (NeoPixel) strip provides immediate visual feedback of obstacle proximity.

Distance	LEDs	Color
> 20 cm	0	Off
15–20 cm	2	Green
10–15 cm	4	Yellow
5–10 cm	6	Orange
< 5 cm	8	Red

Brightness is intentionally limited to reduce current transients on the logic rail.

🏗️ Forklift Mechanism (Servo Actuator)

A servo motor lifts and lowers the forklift rails

Activated when the joystick is centered and the button is pressed

Direction toggles between up and down

Movement is incremental to reduce mechanical stress

Servo is detached when idle to avoid unnecessary current draw

🔋 Power Architecture & Design Decisions

The final system uses separate power domains to ensure stability and predictability.

Power domains

Logic domain

ESP microcontroller

Ultrasonic sensor

Joystick

NeoPixel strip

Motor domain

DC motors powered via L298N

Actuator domain

Servo motor powered from a dedicated 5V step-down (buck) converter

This separation prevents high-current motor and servo transients from causing logic brownouts or undefined behavior.

Block diagram
9V Battery
   |
   +--> L298N --------> DC Motors
   |
   +--> Buck (5V) ----> Servo

ESP (USB / 5V)
   |
   +--> Sensors
   +--> NeoPixel


All domains share a common ground.

🧪 Debugging & Failure Analysis

During system integration, the servo failed to operate reliably under load.

Observed symptoms

Audible motor noise without output shaft movement

Increased servo temperature

System instability during actuation

Root cause

PP3 battery high internal resistance

L298N onboard 5V regulator not designed for servo current spikes

Voltage sag during servo stall conditions

Solution

Introduced a dedicated 5V power domain using a step-down converter

Shared common ground across all domains

Result: stable and repeatable servo operation under load

This issue was resolved through power analysis, not software changes.

🧪 Testing Results

DC motor control and steering ✔️

Ultrasonic distance measurement ✔️

NeoPixel distance visualization ✔️

🧰 Bill of Materials

ESP-based microcontroller (Jade Nano+ ESP)

L298N H-bridge

2× DC motors

MG90S servo motor

Ultrasonic sensor

Joystick module

WS2812B NeoPixel strip (8 LEDs)

9V PP3 battery

Step-down (buck) converter

ON/OFF switch

3D printed forklift mechanism

📚 Lessons Learned

Current capability matters more than voltage for actuators

Power issues often manifest as software instability

Separating power domains significantly improves reliability

Hardware debugging requires observing symptoms, not guessing causes

Incremental integration simplifies fault isolation

Good embedded design starts with power, not code

🔁 Design Iteration & Improvements

If redesigned:

Replace PP3 battery with Li-ion or NiMH pack

Use a more efficient motor driver (e.g. TB6612FNG)

Add current sensing for motors and servo

Introduce limit switches for closed-loop forklift positioning

Migrate timing-critical logic to hardware (FPGA)

Stable servo operation under load ✔️

No logic resets during combined operation ✔️
