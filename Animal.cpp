
/*********************************************************************
** Program name: Animal.cpp
** Author: Huy Nguyen <nguyehu6@oregonstate.edu>
** Date: Apr 23, 2019 at 8:49 PM
** Description: Class implementation file for Animal class. Animal
 *              class represents an animal of the Kingdom Animalia,
 *              that will live in a Zoo in our Zoo Tycoon game. All
 *              animals have an age, cost, number of babies each
 *              animal produces at a time, base food cost, and
 *              profitable payoff. Animal class functions include
 *              getting its age, cost, number of babies, base food
 *              cost, payoff, incrementing its age, and determine if
 *              they are an adult. This is an abstract base class.
*********************************************************************/


#include "Animal.hpp"

//Initialize base_food_cost constant to 10
const int Animal::base_food_cost = 10;

/********************************************************************
** Function: Constructor/default: Initializes age, cost, num_babies,
 *          and payoff to 0, if they are not passed as arguments.
** Params:   int age: age of animal
 *           int cost: purchase cost of animal
 *           int num_babies: number of babies this animal produces.
 *           double payoff: profit this animal generates.
 *           defaults for all = 0;
** Returns:  None
*********************************************************************/
Animal::Animal(int age, int cost, int num_babies, double payoff)
    : age(age), cost(cost), num_babies(num_babies), payoff(payoff)
{}


/********************************************************************
** Function: Destructor: Need to declare a virtual desctructor since
 *              Animal class is abstract.
** Params:   None
** Returns:  None
*********************************************************************/
Animal::~Animal()
{}


/********************************************************************
** Function: incrementAge: Increases age of animal by 1.
** Params:   None
** Returns:  None
*********************************************************************/
void Animal::incrementAge()
{
    age++;
}


/********************************************************************
** Function: isAdult: Returns true if age is 3 or more,
 *          false otherwise.
** Params:   None
** Returns:  Boolean: True if age is 3 or greater, false otherwise.
*********************************************************************/
bool Animal::isAdult() const
{
    return age > 2;
}


/********************************************************************
** Function: getAge: Returns age of animal.
** Params:   None
** Returns:  int age.
*********************************************************************/
int Animal::getAge() const
{
    return age;
}


/********************************************************************
** Function: getCost: Returns cost of animal.
** Params:   None
** Returns:  int cost.
*********************************************************************/
int Animal::getCost() const
{
    return cost;
}


/********************************************************************
** Function: getNumBabies: Returns num_babies of animal.
** Params:   None
** Returns:  int num_babies.
*********************************************************************/
int Animal::getNumBabies() const
{
    return num_babies;
}


/********************************************************************
** Function: getBaseFoodCost: Returns base_food_cost of animal.
** Params:   None
** Returns:  int base_food_cost.
*********************************************************************/
int Animal::getBaseFoodCost() const
{
    return base_food_cost;
}


/********************************************************************
** Function: getPayoff: Returns payoff percentage of animal.
** Params:   None
** Returns:  double payoff.
*********************************************************************/
double Animal::getPayoff() const
{
    return payoff;
}
