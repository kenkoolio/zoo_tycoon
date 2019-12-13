
/*********************************************************************
** Program name: Tiger.cpp
** Author: Huy Nguyen <nguyehu6@oregonstate.edu>
** Date: Apr 23, 2019 at 9:19 PM
** Description: Class implementation file for Tiger class. Tiger class
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


#include "Tiger.hpp"

/********************************************************************
** Function: Constructor/default: Sets age of tiger to argument. Sets
 *           name, cost, number of babies with constant default
 *           values. Feeding cost and payoff are calculated with
 *           default multipliers and base costs.
** Params:   int age: age of tiger.
 *          default = 0;
** Returns: None
*********************************************************************/
Tiger::Tiger(int age)
{
    this->age = age;
    name = DEFAULTS[TIGER].default_name;
    cost = DEFAULTS[TIGER].default_cost;
    num_babies = DEFAULTS[TIGER].default_num_babies;
    feeding_cost = DEFAULTS[TIGER].default_food_cost_multiplier
                    * getBaseFoodCost();
    payoff = DEFAULTS[TIGER].default_cost
            * DEFAULTS[TIGER].default_payoff_percentage;
}


/********************************************************************
** Function: getName: Returns name of animal.
** Params:   None
** Returns:  string name: "Tiger"
*********************************************************************/
std::string Tiger::getName() const
{
    return name;
}


/********************************************************************
** Function: getFeedingCost: Returns feeding cost of tiger.
** Params:   None
** Returns:  double feeding_cost.
*********************************************************************/
double Tiger::getFeedingCost() const
{
    return feeding_cost;
}
