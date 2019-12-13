
/*********************************************************************
** Program name: ValidateInput.hpp
** Author: Huy Nguyen <nguyehu6@oregonstate.edu>
** Date: Apr 02, 2019 at 7:59 PM
** Description: Class implementation file for ValidateInput.
 *              ValidateInput class has static methods for input
 *              validation. Validate input by choosing corresponding
 *              static method for integer, float, double, character, string.
 *              Call static methods directly from class name and
 *              input arguments.
 *              Currently only supports integer validation,
 *              others will be added eventually.
*********************************************************************/


#ifndef VALIDATE_INPUT_HPP
#define VALIDATE_INPUT_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <limits>

class ValidateInput
{
public:

    /********************************************************************
    ** Function: validateInteger: validates user input to ensure it is
     *           an integer. Rejects floats.
    ** Params:   None
    ** Returns:  int: valid user integer input
    *********************************************************************/
    static int validateInteger();


    /********************************************************************
    ** Function: validateInteger validates user input to ensure
     *           it is an integer within specified range. Rejects
     *           floating point numbers.
    ** Params:   int range_start: starting value of valid numeric range
     *           int range_end:   ending value of valid numeric range
    ** Returns:  int: valid user integer input
    *********************************************************************/
    static int validateInteger(int range_start, int range_end);


    /********************************************************************
    ** Function: validateInteger: validates user input to ensure
     *           it is an integer within list of valid choices. Rejects
     *           floating point numbers.
    ** Params:   const int * choices: pointer to array of valid integer choices
     *           int size: size of array
    ** Returns:  int: valid user integer input
    *********************************************************************/
    static int validateInteger(const int *, int size);
};

#endif