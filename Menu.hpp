
/********************************************************************* 
** Program name: Menu.hpp
** Author: Huy Nguyen <nguyehu6@oregonstate.edu>
** Date: Apr 07, 2019 at 6:10 PM
** Description: Class specification file for Menu class. Menu class
 *              is a helper class that provides functions to prompt
 *              users for inputs or selections from a list of options
 *              passed as arguments. Menu objects can present a start
 *              menu, play again menu, a menu to choose one option
 *              from a list, and prompt users to enter an integer
 *              value with a message string provided as an argument,
 *              along with the range of acceptable integers.
*********************************************************************/


#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include "MyRandom.hpp"
#include "ValidateInput.hpp"

class Menu
{
public:
    enum Confirmation {YES = 1, NO};

    //Menu default constants
    static const int START_VALUE_DEFAULT;
    static const int QUIT_VALUE_DEFAULT;
    static const int PLAY_AGAIN_VALUE_DEFAULT;
    static const int START_MENU_SIZE;

private:
    std::string programName;
    int startValue;
    int quitValue;
    int playAgainValue;
    const int startMenuSize;
public:

    /********************************************************************
    ** Function: Default constructor - Sets program name to empty string
     *           and default values for startValue, quitvalue,
     *           playAgainValue, and startMenuSize.
    ** Params:   None
    ** Returns:  None
    *********************************************************************/
    Menu();


    /********************************************************************
    ** Function: Constructor - Sets program name to argument passed in
     *           and values for startValue, quitvalue,
     *           playAgainValue, and constant startMenuSize.
    ** Params:   const string &name - name to be set as program name.
     *           int startValue - value for start choice.
     *           int quitValue - value for quit choice.
     *           int playAgainValue - value for play again choice.
    ** Returns:  None
    *********************************************************************/
    Menu(const std::string &, int startValue=START_VALUE_DEFAULT,
            int quitValue=QUIT_VALUE_DEFAULT,
            int playAgainValue=PLAY_AGAIN_VALUE_DEFAULT);


    /********************************************************************
    ** Function: setName - Sets program name for the menu with argument.
    ** Params:   const string &name - name to be set as program name.
    ** Returns:  None
    *********************************************************************/
    void setName(const std::string &);


    /********************************************************************
    ** Function: setStartValue - sets startValue.
    ** Params:   int value - value to set to startValue.
    ** Returns:  None
    *********************************************************************/
    void setStartValue(int);


    /********************************************************************
    ** Function: setQuitValue - sets quitValue.
    ** Params:   int value - value to set to quitValue.
    ** Returns:  None
    *********************************************************************/
    void setQuitValue(int);


    /********************************************************************
    ** Function: setPlayAgainValue - sets playAgainValue.
    ** Params:   int value - value to set to playAgainValue.
    ** Returns:  None
    *********************************************************************/
    void setPlayAgainValue(int);


    /********************************************************************
    ** Function: getName returns the name of the program for the menu.
    ** Params:   None
    ** Returns:  string name - program name.
    *********************************************************************/
    std::string getName() const;


    /********************************************************************
    ** Function: getStartValue - returns startValue.
    ** Params:   None
    ** Returns:  int - startValue.
    *********************************************************************/
    int getStartValue() const;


    /********************************************************************
    ** Function: getQuitValue - returns quitValue.
    ** Params:   None
    ** Returns:  int - quitValue.
    *********************************************************************/
    int getQuitValue() const;


    /********************************************************************
    ** Function: getPlayAgainValue - returns playAgainValue.
    ** Params:   None
    ** Returns:  int - playAgainValue.
    *********************************************************************/
    int getPlayAgainValue() const;


    /********************************************************************
    ** Function: getStartMenuSize - returns startMenuSize.
    ** Params:   None
    ** Returns:  int - startMenuSize.
    *********************************************************************/
    int getStartMenuSize() const;


    /********************************************************************
    ** Function: start prints out menu with 2 options - start and quit.
    ** Params:   None
    ** Returns:  int - the user's menu selection.
    *********************************************************************/
    int start() const;


    /********************************************************************
    ** Function: play prints out menu with 2 options - play game and quit.
     *           This is an alternative to start().
    ** Params:   None
    ** Returns:  int - the user's menu selection.
    *********************************************************************/
    int play() const;


    /********************************************************************
    ** Function: playAgain prints out menu with 2 options - play again
     *           and quit.
    ** Params:  None
    ** Returns: int - the user's menu selection.
    *********************************************************************/
    int playAgain() const;


    /********************************************************************
    ** Function: chooseOne - takes a string array of options to be
     *           presented to the user to select one option.
    ** Params:   const string * choices - string array of options for
     *           user to choose.
     *           int size - size of the array.
     *           const string & message - message prompt. Default = empty.
     *           bool include_random - flag if choices includes an option
     *           to randomly select one of the other choices. The random
     *           choice must be last in the list of choices.
     *           Default = false.
     *           bool is_seeded - flag denoting if srand() has already been
     *           seeded. Default = false.
    ** Returns:  int - the user's selection.
    *********************************************************************/
    int chooseOne(const std::string *, int size,
            const std::string &message = "", bool include_random = false,
            bool is_seeded = false) const;


    /********************************************************************
    ** Function: promptForInteger - prompts user with provided message
     *           string and acceptable integer range for a number.
    ** Params:   const string &message - the message string to prompt user.
     *           int range_start - start of valid range.
     *           int range_end - end of valid range.
    ** Returns:  int - user's input
    *********************************************************************/
    int promptForInteger(const std::string &message,
            int range_start, int range_end) const;


    /********************************************************************
    ** Function: confirm: prints out argument message, then prompts
     *           user for confirmation. If no message string is passed
     *           as an argument, then it will skip straight to the menu.
     *           Prints Yes/No menu.
     *           1 for Yes, 2 for No. Validates user input.
    ** Params:   const string &message: prompt message preceding menu.
     *           Default = empty string "".
    ** Returns: Int: user's selection.
    *********************************************************************/
    int confirm(const std::string & = "") const;


    /********************************************************************
    ** Function: formatPrompt: prints prompt message formatted to match
     *           other menu prompts.
    ** Params:   const string &message: prompt message to print out.
    ** Returns:  None
    *********************************************************************/
    void formatPrompt(const std::string &message) const;


    /********************************************************************
    ** Function: printBorder: prints a top/bottom border for menus and
     *           prompts. Includes top and bottom padding.
    ** Params:   None
    ** Returns:  None
    *********************************************************************/
    void printBorder() const;

};

#endif
