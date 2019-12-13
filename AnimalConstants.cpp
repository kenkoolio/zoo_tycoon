
/*********************************************************************
** Program name: AnimalConstants.cpp
** Author: Huy Nguyen <nguyehu6@oregonstate.edu>
** Date: Apr 23, 2019 at 6:07 PM
** Description: Class implementation file for AnimalConstants class.
 *              This helper class was designed to create a
 *              lookup table of constant default values and
 *              configurations for Animal class and its derived
 *              classes. It also holds an enum for AnimalTypes, and
 *              a constant for the value zero (0). This header file
 *              defines typedefs to alias the access of these values
 *              more easily.
*********************************************************************/


#include "AnimalConstants.hpp"

//Initialize static constants
const int AnimalConstants::ZERO = 0;
const int AnimalConstants::DEFAULTS_SIZE = 4;

//Initialize alias to defaults array
const AnimalConstants::Animal *DEFAULTS = AnimalConstants::defaults;

//Initialize Animal Defaults Lookup Table:
//  Default name, age, cost, num babies, food cost multiplier, payoff percentage
const AnimalConstants::Animal
AnimalConstants::defaults[AnimalConstants::DEFAULTS_SIZE] =
                {
                    {"Tiger", 0, 10000, 1, 5, 0.2},
                    {"Penguin", 0, 1000, 5, 1, 0.1},
                    {"Turtle", 0, 100, 10, 0.5, 0.05},
                    {"", 0, 0, 0, 0.0, 0.0}                 //Custom animal
                };
