
/********************************************************************* 
** Program name: AnimalConstants.hpp
** Author: Huy Nguyen <nguyehu6@oregonstate.edu>
** Date: Apr 23, 2019 at 6:07 PM
** Description: Class specification file for AnimalConstants class.
 *              This helper class was designed to create a
 *              lookup table of constant default values and
 *              configurations for Animal class and its derived
 *              classes. It also holds an enum for AnimalTypes, and
 *              a constant for the value zero (0). This header file
 *              defines typedefs to alias the access of these values
 *              more easily.
*********************************************************************/


#ifndef ANIMAL_CONST_HPP
#define ANIMAL_CONST_HPP

#include <string>

class AnimalConstants
{
public:
    static const int ZERO;
    static const int DEFAULTS_SIZE;

    enum AnimalType
    {
        TIGER,
        PENGUIN,
        TURTLE,
        CUSTOM
    };

    struct Animal
    {
        std::string default_name;
        int default_age;
        int default_cost;
        int default_num_babies;
        double default_food_cost_multiplier;
        double default_payoff_percentage;
    };

    static const Animal defaults[];
};


//Make aliases for quick access

//Typedef for easy aliasing in other modules
typedef AnimalConstants::AnimalType AnimalType;

//Alias to constant numbers
const int ZERO = AnimalConstants::ZERO;
const int EXHIBITS_SIZE = AnimalConstants::DEFAULTS_SIZE;

//Alias to Animal Defaults Lookup Table
//const AnimalConstants::Animal *DEFAULTS = AnimalConstants::defaults; //does not work
extern const AnimalConstants::Animal *DEFAULTS;

//Alias to AnimalType enums
const AnimalType TIGER = AnimalConstants::TIGER;
const AnimalType PENGUIN = AnimalConstants::PENGUIN;
const AnimalType TURTLE = AnimalConstants::TURTLE;
const AnimalType CUSTOM = AnimalConstants::CUSTOM;

#endif