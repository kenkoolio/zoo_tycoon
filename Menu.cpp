
/*********************************************************************
** Program name: Menu.cpp
** Author: Huy Nguyen <nguyehu6@oregonstate.edu>
** Date: Apr 07, 2019 at 6:10 PM
** Description: Class implementation file for Menu class. Menu class
 *              is a helper class that provides functions to prompt
 *              users for inputs or selections from a list of options
 *              passed as arguments. Menu objects can present a start
 *              menu, play again menu, a menu to choose one option
 *              from a list, and prompt users to enter an integer
 *              value with a message string provided as an argument,
 *              along with the range of acceptable integers.
*********************************************************************/
// TODO: Validation: Start and Quit values can not be the same value

#include "Menu.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;

//Initialize menu default constants
const int Menu::START_VALUE_DEFAULT = 1;
const int Menu::QUIT_VALUE_DEFAULT = 2;
const int Menu::PLAY_AGAIN_VALUE_DEFAULT = 1;
const int Menu::START_MENU_SIZE = 2;

/********************************************************************
** Function: Default constructor - Sets program name to empty string
 *           and default values for startValue, quitvalue,
 *           playAgainValue, and startMenuSize.
** Params:   None
** Returns:  None
*********************************************************************/
Menu::Menu()
: programName(""), startValue(START_VALUE_DEFAULT),
quitValue(QUIT_VALUE_DEFAULT), playAgainValue(PLAY_AGAIN_VALUE_DEFAULT),
startMenuSize(START_MENU_SIZE)
{}


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
Menu::Menu(const string &name, int startValue, int quitValue,
        int playAgainValue)
: programName(name), startValue(startValue), quitValue(quitValue),
playAgainValue(playAgainValue), startMenuSize(START_MENU_SIZE)
{}


/********************************************************************
** Function: setName - Sets program name for the menu with argument.
** Params:   const string &name - name to be set as program name.
** Returns:  None
*********************************************************************/
void Menu::setName(const string &name)
{
    programName = name;
}


/********************************************************************
** Function: setStartValue - sets startValue.
** Params:   int value - value to set to startValue.
** Returns:  None
*********************************************************************/
void Menu::setStartValue(int value)
{
    startValue = value;
}


/********************************************************************
** Function: setQuitValue - sets quitValue.
** Params:   int value - value to set to quitValue.
** Returns:  None
*********************************************************************/
void Menu::setQuitValue(int value)
{
    quitValue = value;
}


/********************************************************************
** Function: setPlayAgainValue - sets playAgainValue.
** Params:   int value - value to set to playAgainValue.
** Returns:  None
*********************************************************************/
void Menu::setPlayAgainValue(int value)
{
    playAgainValue = value;
}


/********************************************************************
** Function: getName returns the name of the program for the menu.
** Params:   None
** Returns:  string name - program name.
*********************************************************************/
string Menu::getName() const
{
    return programName;
}


/********************************************************************
** Function: getStartValue - returns startValue.
** Params:   None
** Returns:  int - startValue.
*********************************************************************/
int Menu::getStartValue() const
{
    return startValue;
}


/********************************************************************
** Function: getQuitValue - returns quitValue.
** Params:   None
** Returns:  int - quitValue.
*********************************************************************/
int Menu::getQuitValue() const
{
    return quitValue;
}


/********************************************************************
** Function: getPlayAgainValue - returns playAgainValue.
** Params:   None
** Returns:  int - playAgainValue.
*********************************************************************/
int Menu::getPlayAgainValue() const
{
    return playAgainValue;
}


/********************************************************************
** Function: getStartMenuSize - returns startMenuSize.
** Params:   None
** Returns:  int - startMenuSize.
*********************************************************************/
int Menu::getStartMenuSize() const
{
    return startMenuSize;
}


/********************************************************************
** Function: start prints out menu with 2 options - start and quit.
** Params:   None
** Returns:  int - the user's menu selection.
*********************************************************************/
int Menu::start() const
{
    printBorder();
    cout << endl;

    cout << startValue << ": Start " << programName << endl;
    cout << quitValue << ": Quit " << endl;

    printBorder();

    int choices[] = {startValue, quitValue};

    return ValidateInput::validateInteger(choices, startMenuSize);
}


/********************************************************************
** Function: play prints out menu with 2 options - play game and quit.
 *           This is an alternative to start().
** Params:   None
** Returns:  int - the user's menu selection.
*********************************************************************/
int Menu::play() const
{
    printBorder();
    cout << endl;

    cout << startValue << ": Play game" << endl;
    cout << quitValue << ": Exit game" << endl;

    printBorder();

    int choices[] = {startValue, quitValue};

    return ValidateInput::validateInteger(choices, startMenuSize);
}


/********************************************************************
** Function: playAgain prints out menu with 2 options - play again
 *           and quit.
** Params:  None
** Returns: int - the user's menu selection.
*********************************************************************/
int Menu::playAgain() const
{
    printBorder();
    cout << endl;

    cout << "Do you want to play again?" << endl << endl;
    cout << playAgainValue << ": Play again" << endl;
    cout << quitValue << ": Quit " << endl;

    printBorder();

    int choices[] = {playAgainValue, quitValue};

    return ValidateInput::validateInteger(choices, startMenuSize);
}


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
int Menu::chooseOne(const string * choices, int size,
        const string &message, bool include_random, bool is_seeded) const
{
    printBorder();
    cout << endl;

    if (message.length())
    {
        cout << message << endl << endl;
    }

    for (int i=0; i<size; i++)
    {
        cout << i+1 << ": " << choices[i] << endl;
    }

    printBorder();

    int selection = ValidateInput::validateInteger(START_VALUE_DEFAULT, size);

    //If choices include an option for random selection and the user
    //selected the last choice which is the option to do random
    if (include_random && selection == size)
    {
        if (!is_seeded)
        {
            MyRandom::seed();
        }
        selection = MyRandom::randomInteger(START_VALUE_DEFAULT, size-1);
    }

    return selection;
}


/********************************************************************
** Function: promptForInteger - prompts user with provided message
 *           string and acceptable integer range for a number.
** Params:   const string &message - the message string to prompt user.
 *           int range_start - start of valid range.
 *           int range_end - end of valid range.
** Returns:  int - user's input
*********************************************************************/
int Menu::promptForInteger(const string &message,
        int range_start, int range_end) const
{
    printBorder();
    cout << endl;

    cout << message << endl;

    printBorder();
    return ValidateInput::validateInteger(range_start, range_end);
}


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
int Menu::confirm(const string &message) const
{
    printBorder();
    cout << endl;

    if (message.length())
    {
        cout << message << endl << endl;
    }
    cout << YES << ": Yes" << endl;
    cout << NO  << ": No"  << endl;

    printBorder();
    return ValidateInput::validateInteger(YES, NO);
}


/********************************************************************
** Function: formatPrompt: prints prompt message formatted to match
 *           other menu prompts.
** Params:   const string &message: prompt message to print out.
** Returns:  None
*********************************************************************/
void Menu::formatPrompt(const string &message) const
{
    printBorder();

    cout << endl;
    cout << message << endl;

    printBorder();
}


/********************************************************************
** Function: printBorder: prints a top/bottom border for menus and
 *           prompts. Includes top and bottom padding.
** Params:   None
** Returns:  None
*********************************************************************/
void Menu::printBorder() const
{
    const int borderSize = 80;
    const char borderWall = '=';
    const char borderCorner = '@';
    cout << endl << borderCorner << string(borderSize, borderWall)
            << borderCorner << endl;
}