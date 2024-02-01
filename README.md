# Rocket Game

Welcome to the Rocket Game, a simple C++ console application where players can simulate various space flight scenarios including launches and landings on the Earth and the Moon.

## Game Overview

This game presents a text-based simulation of space flight. The player can choose from different scenarios:
1. Launch to orbit the Moon
2. Launch to orbit the Earth
3. Landing on the Moon
4. Landing on the Earth

Each scenario requires the player to manage fuel, speed, and altitude to successfully complete the mission. The game provides a graphical representation of the rocket and planetary bodies using ASCII art.

## Features

- Text-based user interface
- ASCII graphics for rockets, planets, and space
- Physics-based gameplay involving gravity and air resistance
- Health points (HP) and damage calculation upon crashing
- Replayability with different scenarios and outcomes

## Requirements

To build and run this game, you need a C++ compiler that supports the C++11 standard (or later) and the `unistd.h` header for Unix/Linux systems. If you are using Windows, you may need to modify the code to replace `unistd.h` with the appropriate Windows headers.

## How to Play

1. Compile the game using your preferred C++ compiler. For example, if you're using `g++`, you can compile the game with the following command:
g++ -o rocket_game main.cpp engine.cpp -std=c++11


2. Run the compiled executable:
./rocket_game


3. Follow the on-screen prompts to choose a scenario and control your rocket.

## Controls

- Enter the number of the scenario you want to play.
- When in a scenario, input your desired thrust for each turn.
- After completing a scenario, you can choose to play again.

## Contributing

Feel free to fork this project, make improvements, or customize the game. Contributions are welcome!

## License

This project is open-sourced under the MIT License.

## Acknowledgments

- ASCII art by various artists
- Inspired by classic text-based simulation games

## Disclaimer

This game is a simulation and is for entertainment purposes only. The physics and scenarios are simplified and may not accurately represent real space flight.

## Future Improvements

- [ ] Implement a graphical user interface
- [ ] Add more detailed physics calculations
- [ ] Include additional scenarios and celestial bodies
