# AC Energy Meter Simulation (Proteus & Arduino)

## 📖 Project Overview
This project simulates a digital AC Energy Meter using Proteus 8/9 and an Arduino Uno. It measures real-time Voltage, Current, Power, and Energy consumption of an AC load.

## ⚡ How It Works
1. **Current Sensing:** A 1Ω shunt resistor is placed in series with the load. The Arduino reads the differential voltage across it (A0 and A1) to calculate current using Ohm's Law.
2. **Voltage Sensing:** A voltage divider scales down the 12V AC source, and a DC bias circuit shifts the signal to a safe 0V-5V range for the Arduino's ADC (Pin A2).
3. **RMS Calculation:** The firmware samples the AC sine wave 100 times per cycle, removes the DC bias, and calculates the True RMS values for accurate power measurement.

## ️ Components Used
- Microcontroller: Arduino Uno
- Display: 16x2 LCD (LM016L)
- AC Source: 12V, 50Hz (VSINE)
- Sensors: 1Ω Shunt Resistor, 10kΩ Voltage Divider Network

## 📸 Simulation Results
![Schematic](Images/schematic.png)
![Running Simulation](Images/simulation_running.png)

##  How to Run
1. Open `Schematic/EnergyMeter.pdsprj` in Proteus.
2. Load the `Firmware/EnergyMeter.hex` file into the Arduino component.
3. Press Play to start the simulation.