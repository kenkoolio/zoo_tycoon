
/********************************************************************* 
** Program name: Turtle.hpp
** Author: Huy Nguyen <nguyehu6@oregonstate.edu>
** Date: Apr 23, 2019 at 10:34 PM
** Description: Class specification file for Turtle class. Turtle
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


#ifndef TURTLE_HPP
#define TURTLE_HPP

#include "Animal.hpp"
#include <string>

class Turtle : public Animal
{
protected:
    std::string name;
    double feeding_cost;

public:

    /********************************************************************
    ** Function: Constructor/default: Sets age of turtle to argument.
     *           Sets name, cost, number of babies, feeding cost, and
     *           payoff with constant default values.
    ** Params:   int age: age of turtle.
     *          default = 0;
    ** Returns: None
    *********************************************************************/
    Turtle(int age = DEFAULTS[TURTLE].default_age);


    /********************************************************************
    ** Function: getName: Returns name of animal.
    ** Params:   None
    ** Returns:  string name: "Turtle"
    *********************************************************************/
    virtual std::string getName() const override;


    /********************************************************************
    ** Function: getFeedingCost: Returns feeding cost of turtle.
    ** Params:   None
    ** Returns:  double feeding_cost.
    *********************************************************************/
    virtual double getFeedingCost() const override;

};

#endif