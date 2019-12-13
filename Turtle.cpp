
/*********************************************************************
** Program name: Turtle.cpp
** Author: Huy Nguyen <nguyehu6@oregonstate.edu>
** Date: Apr 23, 2019 at 10:34 PM
** Description: Class implementation file for Turtle class. Turtle
 *              class is a derived class of Animal. Turtles represent
 *              a reptile with a large bony shell in which it uses as
 *              a shield to protect itself, or to hide away from
 *              predators. They are typically greenish and brown
 *              animals. They have a $100 purchasing cost, have 10
 *              babies at a time, feeding costs are half that of the
 *              base food cost, and generates 5% of their purchasing
 *              cost as payoff. They inherit all data members and
 *              functions of Animal, with the addition of a string
 *              for their name, "Turtle", and a function to get their
 *              name.
*********************************************************************/


#include "Turtle.hpp"

/********************************************************************
** Function: Constructor/default: Sets age of turtle to argument.
 *           Sets name, cost, number of babies, feeding cost, and
 *           payoff with constant default values.
** Params:   int age: age of turtle.
 *          default = 0;
** Returns: None
*********************************************************************/
Turtle::Turtle(int age)
{
    this->age = age;
    name = DEFAULTS[TURTLE].default_name;
    cost = DEFAULTS[TURTLE].default_cost;
    num_babies = DEFAULTS[TURTLE].default_num_babies;
    feeding_cost = DEFAULTS[TURTLE].default_food_cost_multiplier
                   * getBaseFoodCost();
    payoff = DEFAULTS[TURTLE].default_cost
             * DEFAULTS[TURTLE].default_payoff_percentage;
}


/********************************************************************
** Function: getName: Returns name of animal.
** Params:   None
** Returns:  string name: "Turtle"
*********************************************************************/
std::string Turtle::getName() const
{
    return name;
}


/********************************************************************
** Function: getFeedingCost: Returns feeding cost of turtle.
** Params:   None
** Returns:  double feeding_cost.
*********************************************************************/
double Turtle::getFeedingCost() const
{
    return feeding_cost;
}
