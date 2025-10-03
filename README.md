# RoboCup Junior Soccer Open Robot

## About the Project
This project is dedicated to the development of an autonomous robot for the **RoboCup Junior Soccer Open** competition.  
The robot is capable of localizing itself on the field, dribbling the ball, performing kicks, and executing game strategies without human intervention.

<img width="607" height="682" alt="Main veiw" src="https://github.com/user-attachments/assets/f32a006e-98e6-438e-98dd-4e3a92f0438d" />


## Key Features
- **Modular electronics** — motherboard divided into independent modules for easy repair and upgrades.  
- **Omni-directional drive** — 4 brushless motors with encoders and omni-wheels provide high maneuverability.  
- **Screw-type dribbler** — dual screw-shaped rollers center the ball for stable control.  
- **Solenoid kicker** — adjustable kick power via capacitor selection.  
- **Optical system** — Raspberry Pi camera + hyperbolic mirror for full field view and localization.  
- **Flexible chassis** — single-piece shell that is easy to remove for maintenance.  

## Mechanics
- **Drive system**: aluminum frame with 4 motor-wheels, compact layout to leave space for the dribbler.  
- **Dribbler**: silicone dual-screw roller with linear suspension for smooth ball reception.  
- **Kicker**: electromagnetic solenoid with variable strike force.  
- **Optics**: camera with a custom-designed mirror providing 360° vision for ball and goal detection.  
- **Power system**: removable 18650 Li-ion battery pack with balancing and protection circuits.  

## Electronics
- Mainboard with Atmega2560, Raspberry Pi Compute Module 4, and CAN interface.  
- Power module with kick control and voltage converters (16→5V, 16→48V).  
- Line sensor board with 16 IR sensors arranged in a circle for precise positioning.  

## Software
- **Low-level (C++)** — motor control via CAN, line sensors processing, odometry.  
- **High-level (Python + OpenCV)** — computer vision, localization, strategy, and decision making.  

## Results
The project delivered a fully assembled and tested autonomous robot that meets the RoboCup Junior Soccer Open regulations.  
The robot is competition-ready and demonstrates:  
- high maneuverability,  
- reliable ball control,  
- effective kicking and scoring.  

---
