
/*********************************************************************
** Program name: Penguin.cpp
** Author: Huy Nguyen <nguyehu6@oregonstate.edu>
** Date: Apr 23, 2019 at 10:21 PM
** Description: Class implementation file for Penguin class. Penguin
 *              class is a derived class of Animal. Penguins
 *              represent an aquatic, flightless bird that can
 *              typically be found in cold climates. They are
 *              typically white feathered, with black wings and head.
 *              They have a $1,000 purchasing cost, have 5 babies at
 *              a time, have the same feeding cost as the base food
 *              cost, and generate 10% of their purchasing cost as
 *              payoff. They inherit all data members and functions
 *              of Animal, with the addition of a string for their
 *              name, "Penguin", and a function to get their name.
*********************************************************************/


#include "Penguin.hpp"

/********************************************************************
** Function: Constructor/default: Sets age of penguin to argument.
 *           Sets name, cost, number of babies, feeding cost, and
 *           payoff with constant default values.
** Params:   int age: age of penguin.
 *          default = 0;
** Returns: None
*********************************************************************/
Penguin::Penguin(int age)
{
    this->age = age;
    name = DEFAULTS[PENGUIN].default_name;
    cost = DEFAULTS[PENGUIN].default_cost;
    num_babies = DEFAULTS[PENGUIN].default_num_babies;
    feeding_cost = DEFAULTS[PENGUIN].default_food_cost_multiplier
                   * getBaseFoodCost();
    payoff = DEFAULTS[PENGUIN].default_cost
            * DEFAULTS[PENGUIN].default_payoff_percentage;
}


/********************************************************************
** Function: getName: Returns name of animal.
** Params:   None
** Returns:  string name: "Penguin"
*********************************************************************/
std::string Penguin::getName() const
{
    return name;
}


/********************************************************************
** Function: getFeedingCost: Returns feeding cost of penguin.
** Params:   None
** Returns:  double feeding_cost.
*********************************************************************/
double Penguin::getFeedingCost() const
{
    return feeding_cost;
}
