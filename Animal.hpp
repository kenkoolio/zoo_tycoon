
/********************************************************************* 
** Program name: Animal.hpp
** Author: Huy Nguyen <nguyehu6@oregonstate.edu>
** Date: Apr 23, 2019 at 8:49 PM
** Description: Class specification file for Animal class. Animal
 *              class represents an animal of the Kingdom Animalia,
 *              that will live in a Zoo in our Zoo Tycoon game. All
 *              animals have an age, cost, number of babies each
 *              animal produces at a time, base food cost, and
 *              profitable payoff. Animal class functions include
 *              getting its age, cost, number of babies, base food
 *              cost, payoff, incrementing its age, and determine if
 *              they are an adult. This is an abstract base class.
*********************************************************************/


#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "AnimalConstants.hpp"
#include <string>

class Animal
{
protected:
    int age;
    int cost;
    int num_babies;
    double payoff;
    static const int base_food_cost;

public:

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
    Animal(int age = ZERO, int cost = ZERO,
            int num_babies = ZERO, double payoff = ZERO);


    /********************************************************************
    ** Function: Destructor: Need to declare a virtual desctructor since
     *              Animal class is abstract.
    ** Params:   None
    ** Returns:  None
    *********************************************************************/
    virtual ~Animal();


    /********************************************************************
    ** Function: incrementAge: Increases age of animal by 1.
    ** Params:   None
    ** Returns:  None
    *********************************************************************/
    void incrementAge();


    /********************************************************************
    ** Function: isAdult: Returns true if age is 3 or more,
     *          false otherwise.
    ** Params:   None
    ** Returns:  Boolean: True if age is 3 or greater, false otherwise.
    *********************************************************************/
    bool isAdult() const;


    /********************************************************************
    ** Function: getAge: Returns age of animal.
    ** Params:   None
    ** Returns:  int age.
    *********************************************************************/
    int getAge() const;


    /********************************************************************
    ** Function: getCost: Returns cost of animal.
    ** Params:   None
    ** Returns:  int cost.
    *********************************************************************/
    int getCost() const;


    /********************************************************************
    ** Function: getNumBabies: Returns num_babies of animal.
    ** Params:   None
    ** Returns:  int num_babies.
    *********************************************************************/
    int getNumBabies() const;


    /********************************************************************
    ** Function: getBaseFoodCost: Returns base_food_cost of animal.
    ** Params:   None
    ** Returns:  int base_food_cost.
    *********************************************************************/
    int getBaseFoodCost() const;


    /********************************************************************
    ** Function: getPayoff: Returns payoff percentage of animal.
    ** Params:   None
    ** Returns:  double payoff.
    *********************************************************************/
    double getPayoff() const;


    /********************************************************************
    ** Function: getName: Returns name of animal. Pure virtual function.
    ** Params:   None
    ** Returns:  string name: name of animal.
    *********************************************************************/
    virtual std::string getName() const = 0;


    /********************************************************************
    ** Function: getFeedingCost: Returns feeding cost of animal. Pure
     *              virtual function.
    ** Params:   None
    ** Returns:  double feeding_cost.
    *********************************************************************/
    virtual double getFeedingCost() const = 0;

};

#endif