
/*********************************************************************
** Program name: CustomAnimal.hpp
** Author: Huy Nguyen <nguyehu6@oregonstate.edu>
** Date: Apr 24, 2019 at 12:08 AM
** Description: Class specification file for CustomAnimal class.
 *              CustomAnimal is a derived class of Animal. It allows
 *              the user to create a custom animal in the Zoo Tycoon
 *              simulation. The user will determine the animal's
 *              purchase cost, number of babies, feeding costs, and
 *              payoff. They inherit all data members and functions
 *              of Animal, with the addition of a string for their
 *              name, and a function to get their name.
*********************************************************************/


#ifndef CUSTOM_ANIMAL_HPP
#define CUSTOM_ANIMAL_HPP

#include "Animal.hpp"
#include <string>

class CustomAnimal : public Animal
{
protected:
    std::string name;
    double feeding_cost;

public:
    /********************************************************************
    ** Function: Constructor/default: Sets age, name, cost, number of
     *           babies, feeding cost, and payoff of animal to arguments.
     *           Defaults to default values if no arguments passed in.
    ** Params:  string name: name of custom animal.
     *              default = empty string "".
     *          int age: age of animal.
     *              default = 0;
     *          int cost: cost of animal.
     *              default = 0;
     *          int num_babies: number of babies animal makes.
     *              default = 0;
     *          double feeding_cost: cost to feed animal.
     *              default = 0;
     *          double payoff: profit animal generates.
     *              default = 0;
    ** Returns: None
    *********************************************************************/
    CustomAnimal(std::string name = DEFAULTS[CUSTOM].default_name,
                int age = DEFAULTS[CUSTOM].default_age,
                int cost = DEFAULTS[CUSTOM].default_cost,
                int num_babies = DEFAULTS[CUSTOM].default_num_babies,
                double feeding_cost = DEFAULTS[CUSTOM].default_food_cost_multiplier,
                double payoff = DEFAULTS[CUSTOM].default_payoff_percentage);


    /********************************************************************
    ** Function: getName: Returns name of animal.
    ** Params:   None
    ** Returns:  string name: Custom Animal's name
    *********************************************************************/
    virtual std::string getName() const override;


    /********************************************************************
    ** Function: getFeedingCost: Returns feeding cost of animal.
    ** Params:   None
    ** Returns:  double feeding_cost.
    *********************************************************************/
    virtual double getFeedingCost() const override;
};

#endif
