#include <iostream>
#include <cmath>
#include <cstdlib>
#include <unistd.h>

#include "include/engine.cpp"


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
        floor(altitude, speed, air_resist);

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