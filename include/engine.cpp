#pragma once

#include <iostream>


double altitude_start, altitude_goal, speed_start, speed_goal, fuel, planet_mass;
std::string planet, graphic_planet;
bool launch;

const double time_count = 1;
const double planet_mass_moon = 1; // work in progress...
const double planet_mass_earth = 6; // work in progress...
const double gravity_moon = 1.625; 
const double gravity_earth = 9.81; 


double altitude = altitude_start;
double speed = speed_start;


double gravity = (planet_mass == planet_mass_moon) ? gravity_moon : gravity_earth;
double air_resist = 1/( 1 + 1/((abs(speed))/13000) + (speed*speed)/300000);
double thrust;




double floor(altitude, speed, air_resist)
{        
    

    if  ( altitude <= 0)
            {
            altitude = 0;
            speed = 0;
            }
            else if ( altitude > 0 )
            {
            speed = speed * air_resist + gravity * time_count;
            }


    return 0;
}

