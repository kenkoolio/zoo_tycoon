
/*********************************************************************
** Program name: CustomAnimal.cpp
** Author: Huy Nguyen <nguyehu6@oregonstate.edu>
** Date: Apr 24, 2019 at 12:08 AM
** Description: Class implementation file for CustomAnimal class.
 *              CustomAnimal is a derived class of Animal. It allows
 *              the user to create a custom animal in the Zoo Tycoon
 *              simulation. The user will determine the animal's
 *              purchase cost, number of babies, feeding costs, and
 *              payoff. They inherit all data members and functions
 *              of Animal, with the addition of a string for their
 *              name, and a function to get their name.
*********************************************************************/


#include "CustomAnimal.hpp"

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
CustomAnimal::CustomAnimal(std::string name, int age, int cost, int num_babies,
                double feeding_cost, double payoff)
{
    this->name = name;
    this->age = age;
    this->cost = cost;
    this->num_babies = num_babies;
    this->feeding_cost = feeding_cost;
    this->payoff = payoff;
}


/********************************************************************
** Function: getName: Returns name of animal.
** Params:   None
** Returns:  string name: Custom Animal's name
*********************************************************************/
std::string CustomAnimal::getName() const
{
    return name;
}


/********************************************************************
** Function: getFeedingCost: Returns feeding cost of animal.
** Params:   None
** Returns:  double feeding_cost.
*********************************************************************/
double CustomAnimal::getFeedingCost() const
{
    return feeding_cost;
}
