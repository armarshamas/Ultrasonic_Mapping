# SAMNS - Secure Autonomous Mapping and Navigation System

SAMNS is an autonomous mapping and navigation system designed for a range of applications, including robotics, military, and environmental monitoring. It combines hardware components, software algorithms, and secure data communication to provide real-time mapping, obstacle avoidance, and precise positioning.

## Key Components

- **Rover Hardware:** Utilizes Arduino microcontrollers, ultrasonic sensors, servo motors, GPS modules, motor drivers, and an HC12 WiFi module.
- **Software and Algorithms:** Implements obstacle avoidance algorithms, mapping algorithms, and RSA encryption for secure wireless data transmission.
- **Base Station:** Receives, decrypts, and visualizes rover data using the Processing framework.

## How It Works

The SAMNS rover autonomously explores unknown environments while continuously collecting data from ultrasonic sensors and the GPS module. Obstacle avoidance algorithms guide its movement to ensure it avoids collisions. Simultaneously, it records GPS coordinates for accurate positioning.

Data collected by the rover, including mapping data and GPS coordinates, is encrypted using RSA encryption before being transmitted to the base station via the HC12 WiFi module.

The base station, equipped with the corresponding private RSA key, receives the encrypted data, decrypts it, and then uses Processing to visualize the mapping data. This visualization aids in understanding the environment and identifying obstacles or areas of interest.

## Installation and Usage

1. Clone this repository.
2. Upload the Arduino code to the rover's microcontroller.
3. Set up the base station to receive data and run the Processing script for data visualization.

For detailed installation and usage instructions, please refer to the project's documentation.

## License

This project is licensed under the [MIT License].


Feel free to contribute to this project by forking and creating pull requests. If you have any questions or need assistance, please open an issue.
