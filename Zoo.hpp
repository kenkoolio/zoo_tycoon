
/********************************************************************* 
** Program name: Zoo.hpp
** Author: Huy Nguyen <nguyehu6@oregonstate.edu>
** Date: Apr 24, 2019 at 12:46 AM
** Description: Class specification file for Zoo class. Zoo class
 *              represents a zoo establishment in our Zoo Tycoon game.
 *              A Zoo maintains a collection of animals and allows
 *              visitors to pay an entrance fee to come and observe
 *              the animals. The zoo will house tigers, penguins,
 *              turtles, and other animals. A zoo is a business that
 *              is responsible for its animals, so a zoo is able to
 *              purchase animals, feed the animals, and collect
 *              profits on each animal. Random events can happen every
 *              day, such as an animal gets sick and dies, an animal
 *              gives birth, a boom in zoo attendance, or nothing at
 *              all. Zoo is able to manage its own bank account,
 *              withdraw from the account for purchases, and add to
 *              the account for generated revenue.
*********************************************************************/
//incremental development plan:
// develop up to add animal then test: add all animals, add custom animals, increase exhibit size
// feed all animals and all animals increase in age, calculate profits for all animals
// print out all the information
// random events
// write/read random event messages
// this means type up all the code, and comment out the later stuff to test incrementally


#ifndef ZOO_HPP
#define ZOO_HPP

#include "Menu.hpp"
#include "MyRandom.hpp"
#include "ValidateInput.hpp"
#include "AnimalConstants.hpp"
#include "Animal.hpp"
#include "Tiger.hpp"
#include "Penguin.hpp"
#include "Turtle.hpp"
#include "CustomAnimal.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> //for std::find

class Zoo
{
private:
    //Structures, enums, and constants
    //Keeps track of exhibit capacity and animal count for an exhibit
    struct Exhibit
    {
        int capacity;
        int count;
    };

    enum FeedType {CHEAP, GENERIC, PREMIUM};
    //Random event types
    enum EventType {NOTHING, BOOM, BIRTH, SICKNESS};
    enum ExitReason {QUIT, BANKRUPT};

    //Start exhibit size for all exhibits is 10
    static const int START_EXHIBIT_SIZE;
    //Start bank account for the Zoo is $100,000
    static const int START_BANK_ACCOUNT;
    //Values for feed type multiplier lookup table
    static const int FEED_MULTIPLIER_SIZE;
    static const double CHEAP_MULTIPLIER;
    static const double GENERIC_MULTIPLIER;
    static const double PREMIUM_MULTIPLIER;
    //Text file to write/read today's random event
    static const std::string EVENT_FILE;

    //Variables, and pointers to arrays
    //Pointer to array of pointers to arrays of pointers to Animal objects
    Animal ***animal_exhibits;
    //Pointer to array of Exhibit structures to hold exhibit capacity and animal counts
    Exhibit *exhibit_count;
    Menu menu;
    double bank_account;
    double tiger_bonus;
    double food_cost_multiplier;
    double *feed_multiplier_lookup;
    bool exit_status;
    FeedType todays_feed_type;
    int day_counter;

    //file stream objects
    std::ifstream fileIn;
    std::ofstream fileOut;

public:

    /********************************************************************
    ** Function: Constructor/default: Seeds the random number generator,
     *          initializes bank_account, exit_status, tiger_bonus,
     *          todays_feed_type, food_cost_multiplier,
     *          feed_multiplier_lookup, animal_exhibits,
     *          and exhibit_count to proper game starting values.
    ** Params:  None
    ** Returns: None
    *********************************************************************/
    Zoo();


    /********************************************************************
    ** Function: Destructor: Delete animal_exhibits arrays,
     *           exhibit_count array, and feed_multiplier_lookup array.
     *           Points all pointers to nullptr.
    ** Params:   None
    ** Returns:  None
    *********************************************************************/
    ~Zoo();


    /********************************************************************
    ** Function: Start: Public driver function to run game. Zoo Tycoon
     *                  game's entry point. Welcome's user, display
     *                  starting bank account, prompt user to buy 3
     *                  animals, 1 or 2 of each kind. Create the animals
     *                  and adds them to their exhibits at 1 day old.
     *                  Then calls runTycoon to start the simulation.
     *                  Also prints a note that all 3 extra credits are
     *                  included in this program.
    ** Params:  None
    ** Returns: None
    *********************************************************************/
    void start();

private:

    /********************************************************************
    ** Function: runTycoon: Driver function to run the simulation for
     *              "each day" at the Zoo. Contains a while loop to run
     *              all the tasks necessary in a day of the Zoo Tycoon
     *              business. Says goodbye when user exits.
    ** Params:  None
    ** Returns: None
    *********************************************************************/
    void runTycoon();


    /********************************************************************
    ** Function: beginningOfDay: The tasks at the start of each day of
     *              the Zoo Tycoon.
     *              Tiger_bonus resets.
     *              Animals get older.
     *              Show bank account at start of day.
     *              Ask user for the feed type then feed the animals.
     *              Show bank account after feeding.
    ** Params:  None
    ** Returns: None
    *********************************************************************/
    void beginningOfDay();


    /********************************************************************
    ** Function: midday: The tasks and events that happen during the
     *              middle portion of the day at the Zoo.
     *              A random event happens.
     *              Earnings/profits are calculated for the day.
     *              Show bank account.
     *              Ask user if they want to buy a new animal, then add
     *              animal to the exhibit.
    ** Params:  None
    ** Returns: None
    *********************************************************************/
    void midday();
    
    
    /********************************************************************
    ** Function: endOfDay: The tasks at the end of the day at the Zoo.
     *              Show exhibit count.
     *              Show bank account.
     *              Check if the Zoo is bankrupt, if so the game ends.
     *              Ask user if they want to keep playing, if not then
     *              the game ends.
    ** Params:  None
    ** Returns: None
    *********************************************************************/
    void endOfDay();


    /********************************************************************
    ** Function: randomEvent: Random events happen on a daily basis.
     *              There could be a boom in zoo attendance, an animal
     *              gives birth, an animal gets sick and dies, or nothing
     *              happens at all.
    ** Params:  None
    ** Returns: None
    *********************************************************************/
    void randomEvent();
    
    
    /********************************************************************
    ** Function: draw: Randomly select the random event
     *              (outcomes can depend on food quality).
    ** Params:  None
    ** Returns: int: integer number to denote which random event was
     *              selected.
    *********************************************************************/
    int draw() const;
    
    
    /********************************************************************
    ** Function: nothingHappens: Nothing happened at the Zoo today.
     *              Write to file the event and read from file the event,
     *              then print the event to the user.
    ** Params:   None
    ** Returns:  None
    *********************************************************************/
    void nothingHappens();


    /********************************************************************
    ** Function: boomInAttendance: A boom in zoo attendance happened
     *              today. Calculate random bonus between $250-500 for
     *              each tiger in the exhibit. Set the total bonus to
     *              tiger_bonus. Write to file the event and read from
     *              file the event, then print the event to the user.
    ** Params:  None
    ** Returns: None
    *********************************************************************/
    void boomInAttendance();
    
    
    /********************************************************************
    ** Function: babyIsBorn: A random animal at the Zoo gave birth. Add
     *              all of its babies to the exhibit. If no animals are
     *              old enough to have babies, pick another animal.
     *              If there are no animals in the zoo, pick a
     *              different random event.
    ** Params:  None
    ** Returns: None
    *********************************************************************/
    void babyIsBorn();


    /********************************************************************
    ** Function: pickAnimalToHaveBaby: Randomly selects animal to give
     *              birth, while keeping track of which animal exhibits
     *              are not able to give birth. Recursively calls itself
     *              until it has checked all animals for eligibility.
    ** Params:  vector<AnimalType> &animals_checked: vector of animal
     *              types to keep track of which exhibits have already
     *              been checked.
     *          Animal *& selected_animal: Reference to pointer to an
     *              Animal instance to store the selected animal.
     *          AnimalType &selected_type: Reference to AnimalType
     *              variable to keep track of the type of animal selected.
     *          bool &animal_chosen: Reference to boolean to keep track
     *              if animal has been chosen.
    ** Returns: bool: true if eligible animal was selected, false if no
     *              animals were able to be selected.
    *********************************************************************/
    bool pickAnimalToHaveBaby(std::vector<AnimalType> &animals_checked,
                                Animal *&selected_animal,
                                AnimalType &selected_type,
                                bool &animal_chosen);


    /********************************************************************
    ** Function: giveBirth: An animal of specified type gives birth
     *              according to how many babies their species produces
     *              at a time. Write to file the event and read from
     *              file the event, then print the event to the user.
    ** Params:   AnimalType type: Type of animal to give birth.
     *           const Animal *animal: Pointer to constant eligible
     *           animal object to give birth.
    ** Returns:  None
    *********************************************************************/
    void giveBirth(AnimalType type, const Animal *animal);


    /********************************************************************
    ** Function: animalGetsSick: A random animal in the Zoo became sick.
     *              There's a slim chance they might make it, possibly
     *              depending today's feed type. If today's feed type
     *              was premium, there's a 50/50 chance the animal would
     *              get sick, or another random event is chosen. If the
     *              feed type was not premium, then the animal dies.
    ** Params:  None
    ** Returns: None
    *********************************************************************/
    void animalGetsSick();


    /********************************************************************
    ** Function: animalDies: Randomly select an animal that will get
     *              "sick" and die. Remove one animal of that type from
     *              the exhibit. Checks if exhibit has any animals of
     *              that type, if there are no animals in that exhibit,
     *              pick another animal type. If there are no animals
     *              left in the Zoo, pick another random event.
    ** Params:  None
    ** Returns: None
    *********************************************************************/
    void animalDies();


    /********************************************************************
    ** Function: checkAnimalsCount: Helper function. Randomly loops
     *              through animal exhibits to find eligible animals to
     *              either give birth or get sick and die. Keeps track of
     *              which exhibits have been checked, and if an eligible
     *              animal has been found.
    ** Params:  vector<AnimalType> &animals_checked: Reference to vector
     *              of animal types to keep track of which animal
     *              exhibits have already been checked, as to prevent
     *              infinite loops due to random selection of animals.
     *          AnimalType &selected_type: Reference to AnimalType
     *              variable denoting which animal type was randomly
     *              selected.
     *          bool &animal_chosen: Reference to boolean variable
     *              denoting if an eligible animal has been chosen.
    ** Returns: None
    *********************************************************************/
    void checkAnimalsCount(std::vector<AnimalType> &animals_checked,
                            AnimalType &selected_type,
                            bool &animal_chosen);


    /********************************************************************
    ** Function: pickRandomAnimal: Helper function that randomly picks
     *              an animal type. Pick a random number
     *              between 0 to animal exhibit count - 1.
    ** Params:  None
    ** Returns: int: randomly chosen number static_casted into AnimalType.
     *              i.e. randomly chosen animal type.
    *********************************************************************/
    AnimalType pickRandomAnimal() const;


    /********************************************************************
    ** Function: removeAnimal: Randomly selects an animal from a specific
     *              exhibit passed as an argument. Deletes randomly
     *              selected animal in the exhibit. Shifts the rest of
     *              the animal pointers in the animal's exhibit array
     *              down to fill in the space of the deleted animal.
     *              Deletes the pointer of the last animal in the exhibit,
     *              because it is now duplicated (set the last pointer
     *              to nullptr). Decreases exhibit count of that animal
     *              by 1. Write to file the event and read from
     *              file the event, then print the event to the user.
    ** Params:  AnimalType selected_type: Type of animal to remove.
    ** Returns: None
    *********************************************************************/
    void removeAnimal(AnimalType selected_type);


    /********************************************************************
    ** Function: addAnimal: Adds a new animal to the exhibit by creating
     *              a new animal, adds them to the exhibit, subtracts
     *              their cost from the bank, then prints out a message
     *              saying that a new animal has been added.
    ** Params:   AnimalType type: type of animal to add.
     *           Int age: age of animal to be added.
     *              Default = 0;
     *           Bool isBirth: boolean to denote if animal was added
     *              by birth, if true, does not subtract the animal's
     *              cost from the bank.
     *              Default = false.
    ** Returns: None
    *********************************************************************/
    void addAnimal(AnimalType type, int age = ZERO, bool isBirth = false);


    /********************************************************************
    ** Function: addAnimal(overloaded): Overloaded version of addAnimal
     *              specifically for creating new custom animals. Adds a
     *              new animal to the exhibit by creating a new animal,
     *              adds them to the exhibit, subtracts their cost from
     *              the bank, then prints out a message saying a new
     *              animal has been added.
    ** Params:  AnimalType type: type of animal to add.
     *          Int age: age of animal to be added.
     *          const string& name: name of animal.
     *          Int cost: cost of animal.
     *          Int num_babies: number of babies the animal produces.
     *          Int feeding_cost: cost to feed animal.
     *          Int payoff: profit generated by animal.
     *          Bool isBirth: boolean to denote if animal was added
     *              by birth, if true, does not subtract the animal's
     *              cost from the bank.
     *              Default = false.
    ** Returns: None
    *********************************************************************/
    void addAnimal(AnimalType type, int age, const std::string &name,
                    int cost, int num_babies, int feeding_cost,
                        int payoff, bool isBirth = false);


    /********************************************************************
    ** Function: makeAnimal: Creates a new animal of specified type at
     *              specified age. Tigers, penguins, or turtles only.
    ** Params:   AnimalType type: type of animal to be created.
     *           Int age: age of animal to be created.
    ** Returns:  Animal *: pointer to new animal created.
    *********************************************************************/
    Animal *makeAnimal(AnimalType type, int age);


    /********************************************************************
    ** Function: makeAnimal(overloaded): Overloaded version of makeAnimal
     *              specifically for creating a new custom animal.
     *              Creates a new animal of specified type at specified
     *              age.
    ** Params:   AnimalType type: type of animal to be created.
     *           Int age: age of animal to be created.
     *           const string& name: name of animal.
     *           Int cost: cost of animal.
     *           Int num_babies: number of babies the animal produces.
     *           Int feeding_cost: cost to feed animal.
     *           Int payoff: profit generated by animal.
    ** Returns:  Animal *: pointer to new custom animal created.
    *********************************************************************/
    Animal *makeAnimal(AnimalType type, int age, const std::string &name,
                        int cost, int num_babies, int feeding_cost,
                            int payoff);
    

    /********************************************************************
    ** Function: addToExhibit: Adds new animal pointer into their exhibit
     *              array. If exhibit is at capacity, increase the
     *              exhibit size. Increase exhibit animal count by 1.
    ** Params:   AnimalType type: type of animal.
     *           Animal *&animal_ptr: Reference to pointer to
     *              Animal to be added to exhibit.
    ** Returns:  None
    *********************************************************************/
    void addToExhibit(AnimalType type, Animal *&animal_ptr);


    /********************************************************************
    ** Function: increaseExhibit: Increases exhibit capacity by a factor
     *              of START_EXHIBIT_SIZE. All exhibits will be increased
     *              by a size of 10 at a time. Creates a new dynamically
     *              allocated array of animal pointers, copies the old
     *              array over, deletes the old array, and points the
     *              old array pointer to the new array. Sets the exhibit
     *              capacity to the new value.
    ** Params:   AnimalType type: type of exhibit to increase capacity.
    ** Returns:  None
    *********************************************************************/
    void increaseExhibit(AnimalType type);


    /********************************************************************
    ** Function: increaseAnimalsAge: Increases age of all animals in the
     *              Zoo by 1 day.
    ** Params:   None
    ** Returns:  None
    *********************************************************************/
    void increaseAnimalsAge();


    /********************************************************************
    ** Function: feedAllAnimals: Feeds all the animals in the Zoo.
     *              Subtracts their feeding cost times food cost
     *              multiplier, which is dependent on today's feed type,
     *              from the bank account.
    ** Params:   None
    ** Returns:  None
    *********************************************************************/
    void feedAllAnimals();


    /********************************************************************
    ** Function: calculateAnimalProfits: Loops through the exhibits and
     *              adds all animal's payoffs to the bank, including
     *              today's tiger bonus.
    ** Params:   None
    ** Returns:  None
    *********************************************************************/
    void calculateAnimalProfits();


    /********************************************************************
    ** Function: printAnimalAdded: Prints out a message that a new
     *              animal was added to the exhibit.
    ** Params:   const Animal *animal: Pointer to constant animal object.
    ** Returns:  None
    *********************************************************************/
    void printAnimalAdded(const Animal *animal) const;


    /********************************************************************
    ** Function: printAnimalsAgeIncreased: Prints out message that all
     *              animals age increased by 1 day.
    ** Params:   None
    ** Returns:  None
    *********************************************************************/
    void printAnimalsAgeIncreased() const;


    /********************************************************************
    ** Function: printAnimalsFed: Prints out message that all animals
     *              have been fed.
    ** Params:   None
    ** Returns:  None
    *********************************************************************/
    void printAnimalsFed() const;


    /********************************************************************
    ** Function: printTodaysProfits: Prints out message that today's
     *              profits have been calculated.
    ** Params:   Int profits: today's total profits.
    ** Returns:  None
    *********************************************************************/
    void printTodaysProfits(int profits) const;


    /********************************************************************
    ** Function: buyNewAnimal: Prompt the user if they want to buy a new
     *              animal at the end of the day. Then create the new
     *              animal if they choose to do so.
    ** Params:   None
    ** Returns:  None
    *********************************************************************/
    void buyNewAnimal();
    
    
    /********************************************************************
    ** Function: buyCustomAnimal: If the user has chosen to make a new
     *              animal. Prompt them for the animal's traits then
     *              create the new custom animal.
    ** Params:   None
    ** Returns:  None
    *********************************************************************/
    void buyCustomAnimal();
    
    
    /********************************************************************
    ** Function: promptForFeedType: Prompts user for the kind of feed
     *              type they want to use today. Set's today's feed type
     *              and food cost multiplier.
    ** Params:   None
    ** Returns:  None
    *********************************************************************/
    void promptForFeedType();


    /********************************************************************
    ** Function: changeFoodCostMultiplier: Changes the food cost
     *              multiplier used to calculate total feeding cost for
     *              the day.
    ** Params:   FeedType type: feed type to be used today.
    ** Returns:  None
    *********************************************************************/
    void changeFoodCostMultiplier(FeedType type);
    
    
    /********************************************************************
    ** Function: addToBank: Adds amount passed as argument to the Zoo's
     *              bank account.
    ** Params:   double amount: amount of $ to add to the bank.
    ** Returns:  None
    *********************************************************************/
    void addToBank(double amount);


    /********************************************************************
    ** Function: subFromBank: Subtracts amount passed as argument to
     *              the Zoo's bank account.
    ** Params:   double amount: amount of $ to subtract from bank.
    ** Returns:  None
    *********************************************************************/
    void subFromBank(double amount);


    /********************************************************************
    ** Function: printBank: Prints bank account amount to user.
    ** Params:   None
    ** Returns:  None
    *********************************************************************/
    void printBank() const;


    /********************************************************************
    ** Function: isBankrupt: Determines if the Zoo is bankrupt or not.
     *              Returns a boolean true if bankrupt, or false if not
     *              bankrupt yet.
    ** Params:   None
    ** Returns:  boolean: true if bank account is less than 1, false
     *              otherwise.
    *********************************************************************/
    bool isBankrupt() const;


    /********************************************************************
    ** Function: checkIfBankrupt: Checks if Zoo is bankrupt, if so, this
     *              function ends the game.
    ** Params:   None
    ** Returns:  None
    *********************************************************************/
    void checkIfBankrupt();


    /********************************************************************
    ** Function: promptToKeepPlaying: Ask user if they want to continue
     *              playing or quit the game. If they choose to quit,
     *              this function ends the game.
    ** Params:   None
    ** Returns:  None
    *********************************************************************/
    void promptToKeepPlaying();


    /********************************************************************
    ** Function: gameOver: Tells user the game is over, their stats at
     *              the end of the game, what happened to the animals,
     *              and the reason why the game is over. End's game
     *              by setting exit_status to true;
    ** Params:   Int day_counter: the number of day's the Zoo was in
     *              business.
     *           ExitReason reason: Reason the game is ending.
    ** Returns:  None
    *********************************************************************/
    void gameOver(int day_counter, ExitReason reason);


    /********************************************************************
    ** Function: printExhibitCount: Prints the current status of each
     *              exhibit, the count of the animals and the exhibit's
     *              capacity.
    ** Params:   None
    ** Returns:  None
    *********************************************************************/
    void printExhibitCount() const;
    
    
    /********************************************************************
    ** Function: writeRead: Formats an event message string. Write the
     *              event to a file. Reads the event from the file, then
     *              prints the event to the screen.
    ** Params:   EventType event: the random event that occured.
     *              const Animal *animal: pointer to constant animal
     *              object that event happened to.
     *              Default = nullptr.
     *           int todays_bonus: today's tiger bonus per tiger.
     *              Default = 0;
    ** Returns:  None
    *********************************************************************/
    void writeRead(EventType event, const Animal *animal = nullptr,
                    int todays_bonus = ZERO);


    /********************************************************************
    ** Function: writeMessage: Writes a message of a random event to an
     *              output file.
    ** Params:   const string &message: string message stating what event
     *              happened today.
    ** Returns:  None
    *********************************************************************/
    void writeMessage(const std::string &message);
    
    
    /********************************************************************
    ** Function: readMessage: Reads a message from random event file and
     *              prints it to screen.
    ** Params:   None
    ** Returns:  None
    *********************************************************************/
    void readMessage();

};

#endif