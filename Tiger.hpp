
/********************************************************************* 
** Program name: Tiger.hpp
** Author: Huy Nguyen <nguyehu6@oregonstate.edu>
** Date: Apr 23, 2019 at 9:19 PM
** Description: Class specification file for Tiger class. Tiger class
 *              is a derived class of Animal. Tigers represent a
 *              large, predatory species of Cat with red-orange fur,
 *              and large black stripes. Tigers are one of the more
 *              popular exhibits at our Zoo Tycoon simulation. They
 *              have a $10,000 purchasing cost, have one baby at a
 *              time, cost 5 times as much as the base cost to feed,
 *              and generates 20% of their purchasing cost as payoff.
 *              They inherit all data members and functions of Animal,
 *              with the addition of a string for their name, "Tiger",
 *              and a function to get their name.
*********************************************************************/


#ifndef TIGER_HPP
#define TIGER_HPP

#include "Animal.hpp"
#include <string>

class Tiger : public Animal
{
protected:
    std::string name;
    double feeding_cost;

public:

    /********************************************************************
    ** Function: Constructor/default: Sets age of tiger to argument. Sets
     *           name, cost, number of babies, feeding cost, and payoff
     *           with constant default values.
    ** Params:   int age: age of tiger.
     *          default = 0;
    ** Returns: None
    *********************************************************************/
    Tiger(int age = DEFAULTS[TIGER].default_age);


    /********************************************************************
    ** Function: getName: Returns name of animal.
    ** Params:   None
    ** Returns:  string name: "Tiger"
    *********************************************************************/
    virtual std::string getName() const override;


    /********************************************************************
    ** Function: getFeedingCost: Returns feeding cost of tiger.
    ** Params:   None
    ** Returns:  double feeding_cost.
    *********************************************************************/
    virtual double getFeedingCost() const override;

};

#endif