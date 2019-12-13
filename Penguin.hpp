
/*********************************************************************
** Program name: Penguin.hpp
** Author: Huy Nguyen <nguyehu6@oregonstate.edu>
** Date: Apr 23, 2019 at 10:21 PM
** Description: Class specification file for Penguin class. Penguin
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


#ifndef PENGUIN_HPP
#define PENGUIN_HPP

#include "Animal.hpp"
#include <string>

class Penguin : public Animal
{
protected:
    std::string name;
    double feeding_cost;

public:

    /********************************************************************
    ** Function: Constructor/default: Sets age of penguin to argument.
     *           Sets name, cost, number of babies, feeding cost, and
     *           payoff with constant default values.
    ** Params:   int age: age of penguin.
     *          default = 0;
    ** Returns: None
    *********************************************************************/
    Penguin(int age = DEFAULTS[PENGUIN].default_age);


    /********************************************************************
    ** Function: getName: Returns name of animal.
    ** Params:   None
    ** Returns:  string name: "Penguin"
    *********************************************************************/
    virtual std::string getName() const override;


    /********************************************************************
    ** Function: getFeedingCost: Returns feeding cost of penguin.
    ** Params:   None
    ** Returns:  double feeding_cost.
    *********************************************************************/
    virtual double getFeedingCost() const override;

};

#endif