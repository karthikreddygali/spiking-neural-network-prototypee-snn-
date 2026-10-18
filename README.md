# spiking-neural-network-prototypee-snn-
A hardware-based spiking neural network for event-driven hand gesture recognition, using IR sensors, Arduino, and Python.
# NeuroPulse — NSS (Neuron Spiking System)

## 1. Project Overview

**NeuroPulse** is a low-cost, Arduino-based hardware prototype inspired by Spiking Neural Networks (SNNs) and neuromorphic computing. It demonstrates how sensor inputs can trigger different output responses in a system inspired by the event-driven behaviour of biological neurons.

The prototype uses three infrared (IR) sensors to detect objects or interruptions, an Arduino to process sensor states, four LEDs to display output patterns, and a buzzer to provide an audible response.

## 2. Aim of the Project

The main aim of NeuroPulse is to develop a simple hardware system that demonstrates sensor-driven, spike-like responses using affordable electronic components.

The project introduces the fundamental ideas behind event-driven computing and neuromorphic systems, in which responses are generated based on input events.

## 3. Components Required

- Arduino Uno
- 3 IR sensor modules
- 4 LEDs
- Current-limiting resistors for the LEDs
- 1 buzzer
- Breadboard and jumper wires
- USB cable and computer

## 4. Working Principle

The system operates in the following sequence:

1. **Input detection:** Three IR sensors detect objects or changes in their detection states.
2. **Signal processing:** The Arduino reads the sensor outputs and determines how many sensors are active.
3. **Output generation:** Based on the number of active sensors, the Arduino produces the corresponding LED output pattern.
4. **Spike-like indication:** A blinking LED represents a spike or firing event for demonstration purposes.
5. **Audible feedback:** The buzzer provides an additional output response according to the programmed logic.

The system demonstrates how multiple sensor inputs can be converted into observable output events.

## 5. System Architecture

IR Sensors → Arduino → Sensor-State Processing → LED Patterns and Buzzer

The Arduino acts as the central controller, connecting the input sensors to the output indicators.

## 6. Connection to Neuromorphic Computing

Biological neurons communicate through electrical spikes. Spiking Neural Networks model aspects of this behaviour by representing information through discrete firing events over time.

NeuroPulse is inspired by this concept. The blinking LED provides a visual representation of a spike-like event, while the sensor states determine the system's output response.

**Note:** A blinking LED alone does not constitute a complete Spiking Neural Network. Implementing a formal neuron model, such as a Leaky Integrate-and-Fire (LIF) neuron, with membrane-potential integration, threshold detection, and reset behaviour would be a potential extension of this prototype.

## 7. Applications

- Educational demonstrations of event-driven systems
- Sensor-based interactive electronics
- Basic embedded-system experiments
- Introduction to neuromorphic engineering
- A starting point for future spiking-neuron hardware experiments

## 8. Future Improvements

- Implement a software-based or hardware-based spiking-neuron model.
- Record and analyse sensor-event timestamps.
- Develop communication between multiple simulated neurons.
- Display spike events and sensor activity on a computer.
- Measure response time and power consumption experimentally.
- Explore integration with a Python-based neural-network model.

## 9. Technologies Used

- Arduino C/C++
- Python (for the associated Python component)
- Infrared sensing
- Embedded systems
- Neuromorphic computing concepts

The exact role of the Python program depends on its implementation and how it interacts with the hardware.

## 10. Conclusion

NeuroPulse is an educational hardware prototype that combines infrared sensing, Arduino-based processing, LED patterns, and audible feedback. It provides a practical starting point for exploring event-driven responses and the concepts behind neuromorphic computing.

The project can be extended toward more advanced spiking-neuron models and hardware–software integration.

## Project Status

**Status:** Hardware prototype

The project is intended for educational and experimental purposes. Performance measurements and neural-network capabilities should be reported only after they have been implemented and tested.

## Author

Developed as an electronics and neuromorphic-computing learning project.
