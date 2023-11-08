#include <iostream>
#include <cmath>
#include <cstdlib>
#include <unistd.h>


/*
1. The world is loaded with
    variables:
        altitude_start, altitude_goal, speed_start, speed_goal, fuel and gravity (depending on altitude and planet_mass);
    constants:
        time_count(0.1 sec), planet_mass;
    (player_inputs):
        thrust,
2. The player chooses one of the scenarios (launch_to_orbit_planet, landing_planet);
    - launch_to_orbit_moon: altitude_start: 0, altitude_goal: 150, speed_start: 0,speed_goal: 50,  fuel: 2000, planet_mass: 1;
    - launch_to_orbit_earth: altitude_start: 0, altitude_goal: 150, speed_start: 0,speed_goal: 50, fuel: 2000, planet_mass: 6;
    - landing_moon: altitude_start: 150, altitude_goal: 0, speed_start: 10,speed_goal: <= 2, fuel: 200, planet_mass: 1;
    - landing_earth: altitude_start: 150, altitude_goal: 0, speed_start: 10,speed_goal: <= 2, fuel: 200, planet_mass: 6;

    The according scenario is loaded;
3. Time starts ticking: every round length is equals time_count;
4. Each round consists of a loop:
    -Check for altitude and speed, 
        if current altitute != goal: 
            1) speed is subtracted from alt (alt from previous round - speed from previous round)
            2) current gravity is calculated (gravity constant at new altitude)
            3) speed is altered by gravity (speed + gravity)
            4) the player chooses the thrust, a check is performed to see if the thrust is acceptable:
                if acceptable, then: 
                    thrust gets subtracted from the fuel (fuel - thrust)
                if not, then:
                    thrust gets limited to a set value or remaining fuel - the lower number gets taken;
                
                after that 1/10 thrust gets subtracted from speed (speed - thrust/10)
            5) repeat;
        if current altitute == goal, speed is checked:
            if speed == goal_speed_range then the player wins;
            else the player loses;
5. The game ends;


  To-Do:

    - speed: should be only positive (V)
    - thrust: check for acceptability (V)
    - altitude_goal: full check -> launch_scenario: >= 150; landing_scenario: >= 0 (V)
    - altitude_start: should not be performed before round_1 (V)
    - gravity: needs altitude adjustement (X)
    - floor needed (V)
    - air resistance (V)

    - cleaning code (XXX)
    - including ideas (XXX)
    - 
    - fine tuning the parameters... (VXX)

*/

// Constants
const double time_count = 1;
const double planet_mass_moon = 1; // work in progress...
const double planet_mass_earth = 6; // work in progress...
const double gravity_moon = 1.625; 
const double gravity_earth = 9.81; 



//texts and graphics
std::string graphic_rocket_start = "       |\n      / \\\n     / _ \\\n    |.o '.|\n    |'._.'|\n    |     |\n  ,'|  |  |  |`.\n /  |  |  |  |  \\\n|,-'--|--'-.| t.r.\n";
std::string welcome_text = "Hello, rocketman! Choose a scenario you wanna fly:\n1. Launch to orbit moon\n2. Launch to orbit earth\n3. Landing on moon\n4. Landing on earth\n";

std::string graphic_space = "Space\n\n .              +   .                .   . .     .  .\n                   .                    .       .     *\n  .       *                        . . . .  .   .  + .\n            \"You Are Here\"            .   .  +  . . .\n.                 |             .  .   .    .    . .\n                  |           .     .     . +.    +  .\n                 \\|/            .       .   . .\n        . .       V          .    * . . .  .  +   .\n           +      .           .   .      +\n                            .       . +  .+. .\n  .                      .     . + .  . .     .      .\n           .      .    .     . .   . . .        ! /\n      *             .    . .  +    .  .       - O -\n          .     .    .  +   . .  *  .       . / |\n               . + .  .  .  .. +  .\n.      .  .  .  *   .  *  . +..  .            *\n .      .   . .   .   .   . .  +   .    .            +\n";
std::string graphic_landed = "                     _  _     ____________.--.\n                  |\\|_|//_.-\"\" .'    \\   /|  |\n                  |.-\"\"\"-.|   /       \\_/ |  |\n                  \\  ||  /| __\\_____________ |\n                  _\\_||_/_| .-\"\"            \"\"-.  __\n                .' '.    \\//                    \".\\n                ||   '. >()_                     |()<\n                ||__.-' |/\\ \\                    |/\\\n                   |   / \"|  \\__________________/.\"\"\n                  /   //  | / \\ \"-.__________/  /\\\n               ___|__/_|__|/___\\___\".______//__/__\\\n              /|\\     [____________] \\__/         |\\n             //\\ \\     |  |=====| |   /\\\\         |\\\\\n            // |\\ \\    |  |=====| |   | \\\\        | \\\\        ____...____....----\n          .//__| \\ \\   |  |=====| |   | |\\\\       |--\\---\"\"\"\"     .            ..\n_____....-//___|  \\_\\  |  |=====| |   |_|_\\\\      |___\\\\    .                 ...'\n .      .//-.__|_______|__|_____|_|_____[__\\\\_____|__.-\\      .     .    ...::\n        //        //        /          \\ `-_\\\\/         \\\\          .....:::\n  -... //     .  / /       /____________\\    \\\\       .  \\ \\     .            .\n      //   .. .-/_/-.                 .       \\\\        .-\\_\\-.                 .\n     / /      '-----'           .             \\ \\      '._____.'         .\n  .-/_/-.         .                          .-\\_\\-.                          ...\n '._____.'                            .     '._____.'                       .....\n        .                                                             ...... ..\n    .            .                  .                        .\n   ...                    .                      .                       .      .\n        ....     .                       .                    ....\n            ......           . ..                       ......'\n             .......             '...              ....\n                                   ''''''      .              .\n";
std::string graphic_crashed = "     ________________________________         \n/                                \"-_          \n/      .  |  .                       \\          \n/      : \\ | / :                       \\         \n/        '-___-'                         \\      \n/_________________________________________ \\      \n     _______| |________________________--\"\"-L \n    /       F J                              \\ \n   /       F   J                              L\n  /      :'     ':                            F\n /        '-___-'                            / \n/_________________________________________--\n";
std::string graphic_planet_moon = "                        .                          +\n           +                                                    .\n                                     ___       .\n     .                        _.--\"~~ __\"-.\n                           ,-\"     .-~  ~\"-\\              .\n              .          .^       /       ( )      .\n                    +   {_.---._ /         ~\n                        /    .  Y                            .\n                       /      \\_j                      +\n        .             Y     ( --l__\n                      |            \"-.                   .\n                      |      (___     \\\n              .       |        .)~-.__/             .           .\n                      l        _)\n     .                 \\      \"l\n         +              \\       \\\n                         \\       ^.\n             .            ^.       \"-.                    .\n                            \"-._      ~-.___,\n                      .         \"--.._____.^\n       .                                         .\n                            ->Moon<-\n";
std::string graphic_planet_earth = "o               .        ___---___                    .                   \n       .              .--\\        --.     .     .         .                 \n                    ./.;_.\\     __/~ \\.                                     \n                   /;  / `-'  __\\    . \\                                    \n .        .       / ,--'     / .   .;   \\        |                         \n                 | .|       /       __   |      -O-       .                 \n                |__/    __ |  . ;   \\ | . |      |                         \n                |      /  \\\\_    . ;| \\___|                                \n   .    o       |      \\  .~\\\\___,--'     |           .                      \n                 |     | . ; ~~~~\\_    __|                                    \n    |             \\    \\   .  .  ; \\  /_/   .                                \n   -O-        .    \\   /         . |  ~/                  .                    \n    |    .          ~\\ \\   .      /  /~          o                        \n  .                   ~--___ ; ___--~                                       \n                 .          ---         .              -JT                   \n";


// replay function
bool askForReplay() 
{
    char choice;
    std::cout << "Do you want to play again? (Y/N): ";
    std::cin >> choice;
    return (choice == 'Y' || choice == 'y');
}

// display: start of the game
void displayScenarioParameters(double altitude_start, double altitude_goal, double speed_start, double speed_goal, double fuel, double planet_mass, std::string planet, std::string graphic_planet) 
{
    std::cout << graphic_planet;
    std::cout << "\nScenario Parameters:\n";
    std::cout << "Planet: " << planet << "\n";   
    //std::cout << "Starting Altitude: " << altitude_start << " meters\n";
    std::cout << "Target Altitude: " << altitude_goal << " meters\n";
    //std::cout << "Starting Speed: " << speed_start << " m/s\n";
    std::cout << "TARGET SPEED: " << speed_goal << " m/s\n";
    //std::cout << "Fuel: " << fuel << " litres\n";
    //std::cout << "Planet Mass: " << planet_mass << "\n";
}

// logic...
void runScenario(double altitude_start, double altitude_goal, double speed_start, double speed_goal, double fuel, double planet_mass, bool launch) 
{
    double altitude = altitude_start;
    double speed = speed_start;
    double time = 0;
    double hp = 100;
    double mass_rocket = 3;
    double energy;

    // HP START
    
    // while game is running
    while ((launch == true && altitude <= altitude_goal && hp >= 0) || (launch == false && altitude >= altitude_goal && hp >= 0))
    {
        double gravity = (planet_mass == planet_mass_moon) ? gravity_moon : gravity_earth;
        double air_resist = 1/( 1 + 1/((abs(speed))/13000) + (speed*speed)/300000);
        double thrust;
        time++;

        std::cout << "---------------" << std::endl;
        std::cout << "Second: " << time << std::endl;
        std::cout << "Current altitude: " << altitude << " meters\n";
        std::cout << "Air_resistence_coefficient: " << air_resist << " \n";
        std::cout << "Current speed: " << abs(speed) << " m/s";
        if ( speed > 0)                     
        { 
            std::cout << " [DOWN]\n";       // FLIGHT INDICATOR DOWN
        } 
        else 
        {
            std::cout <<" [UP]\n";          // FLIGHT INDICATOR UP
        }
        std::cout << "Fuel left: " << fuel <<  " litres\n";
        std::cout << "Health: " << hp <<  " \n";
        std::cout << "Enter thrust: ";
        if ( fuel > 0 && altitude > 0)
            {
            std::cin >> thrust;
            }
            else if (fuel != 0 && altitude == 0)
            {
            std::cin >> thrust;
            }
            else
            {
            std::cout << thrust << std::endl;
            thrust = 0;
            std::cout.flush();
            usleep(200000);
            }
        std::cout << "---------------" << std::endl;

        //floor check
        if  ( altitude <= 0)
            {
            altitude = 0;
            speed = 0;
            }
            else if ( altitude > 0 )
            {
            speed = speed * air_resist + gravity * time_count;
            }

        //throttle and fuel control
        if  ( thrust <= fuel && thrust >= 0) 
            {
            fuel -= thrust;
            } 
            else if ( thrust > fuel )
            {
            thrust = fuel;
            fuel -= thrust;
            }
            else 
            {
            thrust = 0;
            }

        speed = speed * air_resist - (thrust / 3.0) * time_count;
        altitude -= speed;


        //Damage Check
        if (altitude <= 0 && abs(speed) > 0)
            {
            energy = abs(speed) * mass_rocket;
            hp-= energy;
            }

    }



    //display: game ending
    std::cout << "x.X. Game Over X.x. after " << time + 1 << " seconds." << std::endl;
    //std::cout << "Current altitude: " << altitude << " meters\n";
    std::cout << "End speed: " << abs(speed) << " m/s\n";
    std::cout << "Fuel left: " << fuel <<  " litres\n";
    std::cout << "Health: " << hp <<  " \n";
    std::cout << "---------------" << std::endl;
    std::cout << "" << std::endl;

    //check for game-ending conditions
    if (hp <= 0 )
    {
        std::cout << graphic_crashed;
        std::cout << "" << std::endl;
        std::cout << "You Crashed!" << std::endl;
    }
    else if (launch == true && abs(speed) >= speed_goal || launch == false && hp > 0) 
    {
        if (altitude > 0) 
        {
        std::cout << graphic_space;    
        }
        else
        {
        std::cout << graphic_landed; 
        }
        std::cout << "" << std::endl;
        std::cout << "You won!" << std::endl;
    }
    
    else     
    {
        std::cout << "" << std::endl;
        std::cout << "Too slow..." << std::endl;
    }
}

// programm
int main() 
{
    bool replay = true;

    while (replay == true)
    {
    int scenario;

    std::cout << graphic_rocket_start << welcome_text;
    std::cin >> scenario;

    double altitude_start, altitude_goal, speed_start, speed_goal, fuel, planet_mass;
    std::string planet, graphic_planet;
    bool launch;

    switch (scenario) 
    {
        case 1:
            planet = "moon";
            graphic_planet = graphic_planet_moon;
            altitude_start = 0;
            altitude_goal = 5000;
            speed_start = 0;
            speed_goal = 100;
            fuel = 4000;
            planet_mass = planet_mass_moon;
            launch = true;
            break;
        case 2:
            planet = "earth";
            graphic_planet = graphic_planet_earth;
            altitude_start = 0;
            altitude_goal = 5000;
            speed_start = 0;
            speed_goal = 100;
            fuel = 4400;
            planet_mass = planet_mass_earth;
            launch = true;
            break;
        case 3:
            planet = "moon";
            graphic_planet = graphic_planet_moon;
            altitude_start = 900;
            altitude_goal = 0;
            speed_start = 100;
            speed_goal = 2;
            fuel = 250;
            planet_mass = planet_mass_moon;
            launch = false;
            break;
        case 4:
            planet = "earth";
            graphic_planet = graphic_planet_earth;
            altitude_start = 900;
            altitude_goal = 0;
            speed_start = 100;
            speed_goal = 2;
            fuel = 350;
            planet_mass = planet_mass_earth;
            launch = false;
            break;
        default:
            std::cout << "Invalid scenario choice." << std::endl;
            return 0;
    }

    displayScenarioParameters(altitude_start, altitude_goal, speed_start, speed_goal, fuel, planet_mass, planet, graphic_planet);
    runScenario(altitude_start, altitude_goal, speed_start, speed_goal, fuel, planet_mass, launch);
    
    replay = askForReplay();
    
    }
    return 0;
}


/*
Ideas:



DMG_Modell:
rocket_mass = 2
rocket_hp = 100
energy = rocket_mass * speed
rocket_hp = rocket_hp - energy
if 0 -> dead
*/