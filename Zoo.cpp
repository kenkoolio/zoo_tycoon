
/*********************************************************************
** Program name: Zoo.cpp
** Author: Huy Nguyen <nguyehu6@oregonstate.edu>
** Date: Apr 24, 2019 at 12:46 AM
** Description: Class implementation file for Zoo class. Zoo class
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


#include "Zoo.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

//Initialize constants
const int Zoo::START_EXHIBIT_SIZE = 10;
const int Zoo::START_BANK_ACCOUNT = 100000;
const int Zoo::FEED_MULTIPLIER_SIZE = 3;
const double Zoo::CHEAP_MULTIPLIER = 0.5;
const double Zoo::GENERIC_MULTIPLIER = 1.0;
const double Zoo::PREMIUM_MULTIPLIER = 2.0;
const std::string Zoo::EVENT_FILE = "event_file.txt";

/********************************************************************
** Function: Constructor/default: Seeds the random number generator,
 *          initializes bank_account, exit_status, tiger_bonus,
 *          todays_feed_type, food_cost_multiplier,
 *          feed_multiplier_lookup, animal_exhibits,
 *          and exhibit_count to proper game starting values.
** Params:  None
** Returns: None
*********************************************************************/
Zoo::Zoo() : bank_account(START_BANK_ACCOUNT), tiger_bonus(ZERO),
                exit_status(false), todays_feed_type(GENERIC)
{
    //Seed random number generator
    MyRandom::seed();

    //Initialize feed_multiplier_lookup array
    feed_multiplier_lookup = new double[FEED_MULTIPLIER_SIZE]
            {CHEAP_MULTIPLIER, GENERIC_MULTIPLIER, PREMIUM_MULTIPLIER};

    //Initialize today's food cost multiplier
    changeFoodCostMultiplier(todays_feed_type);

    //Create all the animal exhibit arrays of size START_EXHIBIT_SIZE
    animal_exhibits = new Animal**[EXHIBITS_SIZE];
    for (int i=ZERO; i<EXHIBITS_SIZE; i++)
    {
        animal_exhibits[i] = new Animal*[START_EXHIBIT_SIZE];

        //Point the pointers to nullptr
        for (int k=ZERO; k<START_EXHIBIT_SIZE; k++)
        {
            animal_exhibits[i][k] = nullptr;
        }
    }

    //Set up exhibit_count array to starting values,
    // all animal counts = 0, capacity = START_EXHIBIT_SIZE = 10
    exhibit_count = new Exhibit[EXHIBITS_SIZE];
    for (int i=ZERO; i<EXHIBITS_SIZE; i++)
    {
        exhibit_count[i].capacity = START_EXHIBIT_SIZE;
        exhibit_count[i].count = ZERO;
    }
}


/********************************************************************
** Function: Destructor: Delete animal_exhibits arrays,
 *           exhibit_count array, and feed_multiplier_lookup array.
 *           Points all pointers to nullptr.
** Params:   None
** Returns:  None
*********************************************************************/
Zoo::~Zoo()
{
    //Delete all animal exhibits
    for (int i=ZERO, p=EXHIBITS_SIZE; i<p; i++)
    {
        for (int k=ZERO, j=exhibit_count[i].count; k<j; k++)
        {
            delete animal_exhibits[i][k];
            animal_exhibits[i][k] = nullptr;
        }
        delete [] animal_exhibits[i];
        animal_exhibits[i] = nullptr;
    }
    delete [] animal_exhibits;
    animal_exhibits = nullptr;

    //Delete exhibit_count array
    delete [] exhibit_count;
    exhibit_count = nullptr;

    //Delete feed_multiplier_lookup array
    delete [] feed_multiplier_lookup;
    feed_multiplier_lookup = nullptr;
}


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
void Zoo::start()
{
    //Welcome message with left-padding
    const int TITLE_PADDING = 20;
    const int HALF_PADDING = 10;
    const char SPACE = char(32);
    const string WELCOME_MSG = string(TITLE_PADDING, SPACE) +
            "Welcome To Your Brand New Zoo!";
    const string EXTRA_CREDIT = string(HALF_PADDING, SPACE) +
            "*** Note: All 3 extra credits are included in this program. ***";

    //Buy animal prompts
    const string BUY_ANIMALS =
            "Please buy your 3 animals to start, you can buy 1 or 2 of each:";
    const string BUY_TIGER = "How many Tigers do you want? ";
    const string BUY_PENGUIN = "How many Penguins do you want? ";
    const string BUY_TURTLE = "How many Turtles do you want? ";

    const int LOWER_BOUND = 1;
    const int UPPER_BOUND = 2;
    const int START_AGE = 1;
    int tiger_count = 0;
    int penguin_count = 0;
    int turtle_count = 0;

    //print welcome and extra credit
    menu.formatPrompt(WELCOME_MSG + "\n\n" + EXTRA_CREDIT);

    //print starting bank account;
    printBank();

    //prompt to buy animals
    cout << endl << BUY_ANIMALS << endl << endl;
    //tiger amount
    cout << BUY_TIGER;
    tiger_count = ValidateInput::validateInteger(LOWER_BOUND, UPPER_BOUND);
    //penguin amount
    cout << BUY_PENGUIN;
    penguin_count = ValidateInput::validateInteger(LOWER_BOUND, UPPER_BOUND);
    //turtle amount
    cout << BUY_TURTLE;
    turtle_count = ValidateInput::validateInteger(LOWER_BOUND, UPPER_BOUND);

    //add tigers
    for (int i=ZERO; i<tiger_count; i++)
    {
        addAnimal(TIGER, START_AGE);
    }

    //add penguins
    for (int i=ZERO; i<penguin_count; i++)
    {
        addAnimal(PENGUIN, START_AGE);
    }

    //add turtles
    for (int i=ZERO; i<turtle_count; i++)
    {
        addAnimal(TURTLE, START_AGE);
    }

    //START THE GAME!!
    runTycoon();

}


/********************************************************************
** Function: runTycoon: Driver function to run the simulation for
 *              "each day" at the Zoo. Contains a while loop to run
 *              all the tasks necessary in a day of the Zoo Tycoon
 *              business. Says goodbye when user exits.
** Params:  None
** Returns: None
*********************************************************************/
void Zoo::runTycoon()
{
    //initialize day counter
    day_counter = 0;
    const string FAREWELL_MSG = "Goodbye!";
    while (!exit_status)
    {
        day_counter++;

        //print day number
        string day_string = "Day # " + std::to_string(day_counter);
        menu.formatPrompt(day_string);

        //the day beings
        beginningOfDay();
        midday();
        endOfDay();
    }

    cout << endl << endl << FAREWELL_MSG << endl << endl;
}


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
void Zoo::beginningOfDay()
{
    //reset tiger bonus
    tiger_bonus = ZERO;

    increaseAnimalsAge();
    printAnimalsAgeIncreased();

    //show bank account before feeding
    printBank();

    //feed animals
    promptForFeedType();
    feedAllAnimals();
    printAnimalsFed();

    //show bank account after feeding
    printBank();
}


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
void Zoo::midday()
{
    //random event occurs
    randomEvent();
    //profits are calculated
    calculateAnimalProfits();
    //show current bank account
    printBank();
    //ask if user wants to buy a new animal
    buyNewAnimal();
}


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
void Zoo::endOfDay()
{
    //show state of all exhibits
    printExhibitCount();
    //show bank account
    printBank();
    //check if user is out of money
    checkIfBankrupt();
    //check if user wants to keep playing
    if (!exit_status)
    {
        promptToKeepPlaying();
    }
}


/********************************************************************
** Function: randomEvent: Random events happen on a daily basis.
 *              There could be a boom in zoo attendance, an animal
 *              gives birth, an animal gets sick and dies, or nothing
 *              happens at all.
** Params:  None
** Returns: None
*********************************************************************/
void Zoo::randomEvent()
{
    int lottery = draw();

    if (lottery == 1)
    {
        nothingHappens();
    }
    else if (lottery == 2)
    {
        boomInAttendance();
    }
    else if (lottery == 3)
    {
        babyIsBorn();
    }
    else if (lottery > 3)
    {
        animalGetsSick();
    }
}


/********************************************************************
** Function: draw: Randomly select the random event
 *              (outcomes can depend on food quality).
** Params:  None
** Returns: int: integer number to denote which random event was
 *              selected.
*********************************************************************/
int Zoo::draw() const
{
    const int LOWER_BOUND = 1;
    int UPPER_BOUND = 4;

    //if feed type is cheap, then animals get a higher chance
    // of getting sick
    if (todays_feed_type == CHEAP)
    {
        UPPER_BOUND = 6;
    }

    return MyRandom::randomInteger(LOWER_BOUND, UPPER_BOUND);
}


/********************************************************************
** Function: nothingHappens: Nothing happened at the Zoo today.
 *              Write to file the event and read from file the event,
 *              then print the event to the user.
** Params:   None
** Returns:  None
*********************************************************************/
void Zoo::nothingHappens()
{
    writeRead(NOTHING);
}


/********************************************************************
** Function: boomInAttendance: A boom in zoo attendance happened
 *              today. Calculate random bonus between $250-500 for
 *              each tiger in the exhibit. Set the total bonus to
 *              tiger_bonus. Write to file the event and read from
 *              file the event, then print the event to the user.
** Params:  None
** Returns: None
*********************************************************************/
void Zoo::boomInAttendance()
{
    const int LOWER_BOUND = 250;
    const int UPPER_BOUND = 500;
    int todays_bonus = MyRandom::randomInteger(LOWER_BOUND, UPPER_BOUND);
    int total_tigers = exhibit_count[TIGER].count;
    tiger_bonus = todays_bonus * total_tigers;
    writeRead(BOOM, nullptr, todays_bonus);
}


/********************************************************************
** Function: babyIsBorn: A random animal at the Zoo gave birth. Add
 *              all of its babies to the exhibit. If no animals are
 *              old enough to have babies, pick another animal.
 *              If there are no animals in the zoo, pick a
 *              different random event.
** Params:  None
** Returns: None
*********************************************************************/
void Zoo::babyIsBorn()
{
    //passing these variables by reference
    AnimalType selected_type;
    Animal *selected_animal = nullptr;
    vector<AnimalType> animals_checked;
    bool animal_chosen = false;

    //pick random animal and check for quantity and age
    if (pickAnimalToHaveBaby(animals_checked,
            selected_animal, selected_type, animal_chosen))
    {
        //if successfully found animal that is old enough
        giveBirth(selected_type, selected_animal);
    }
    else
    {
        //no eligible animals found, pick another random event
        randomEvent();
    }
}


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
bool Zoo::pickAnimalToHaveBaby(vector<AnimalType> &animals_checked,
                                  Animal *&selected_animal,
                                  AnimalType &selected_type,
                                  bool &animal_chosen)
{
    //reset animal_chosen flag
    animal_chosen = false;

    //base case, if all animals already checked return false
    // for no eligible animals found
    if (animals_checked.size() == static_cast<unsigned>(EXHIBITS_SIZE))
    {
        return animal_chosen;
    }

    //pick random animal and check quantity of exhibit
    checkAnimalsCount(animals_checked, selected_type, animal_chosen);

    if (animal_chosen)
    {
        //random exhibit chosen that has at least 1 animal
        //check if any animals in exhibit are old enough
        for (int i=ZERO, k=exhibit_count[selected_type].count; i<k; i++)
        {
            if (animal_exhibits[selected_type][i]->isAdult())
            {
                //found an adult animal in selected exhibit
                // return the pointer of that animal
                selected_animal = animal_exhibits[selected_type][i];
                return animal_chosen;
            }
        }
        //no animals were old enough, recursively call pick animal
        // to have baby to pick another animal
        pickAnimalToHaveBaby(animals_checked, selected_animal,
                selected_type, animal_chosen);
    }

    //zoo must not have any animals, returns false
    return animal_chosen;
}


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
void Zoo::giveBirth(AnimalType type, const Animal *animal)
{
    //write/read status message that animal has given birth
    writeRead(BIRTH, animal);

    //loop for how many babies this animal produces
    for (int i=ZERO, k=animal->getNumBabies(); i<k; i++)
    {
        if (type == CUSTOM)
        {
            //make custom animal babies, passing in custom traits
            addAnimal(type, ZERO, animal->getName(),
                    animal->getCost(), animal->getNumBabies(),
                    animal->getFeedingCost(), animal->getPayoff(), true);
        }
        else
        {
            //make normal animal
            addAnimal(type, ZERO, true);
        }
    }
}


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
void Zoo::animalGetsSick()
{
    const int LOWER_BOUND = 1;
    const int UPPER_BOUND = 2;

    if (todays_feed_type == PREMIUM)
    {
        //50/50 chance an animal gets sick
        int lottery = MyRandom::randomInteger(LOWER_BOUND, UPPER_BOUND);
        if (lottery == 1)
        {
            //lucky day, pick another random event
            randomEvent();
        }
        else if (lottery == 2)
        {
            //unlucky for animals, one dies
            animalDies();
        }
    }
    else
    {
        animalDies();
    }
}


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
void Zoo::animalDies()
{
    //passing these variables by reference
    vector<AnimalType> animals_checked;
    AnimalType selected_type;
    bool animal_chosen = false;

    //pick a random animal, and check if exhibit has any of that type
    checkAnimalsCount(animals_checked, selected_type, animal_chosen);

    if (animal_chosen)
    {
        //one unlucky animal dies, remove them from the exhibit
        removeAnimal(selected_type);
    }
    else
    {
        //the zoo must not have any animals, another random event happens
        randomEvent();
    }
}


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
void Zoo::checkAnimalsCount(vector<AnimalType> &animals_checked,
                               AnimalType &selected_type,
                               bool &animal_chosen)
{
    do
    {
        selected_type = pickRandomAnimal();

        //if exhibit has any animals, that exhibit is eligible
        if (exhibit_count[selected_type].count > 0)
        {
            animal_chosen = true;
        }

        //check if randomly selected animal exhibit has already been
        // checked.
        // Search for selected animal in vector.
        if (std::find(animals_checked.begin(), animals_checked.end(),
                selected_type) == animals_checked.end())
        {
            //selected animal has not been checked yet, update
            // animals_checked vector
            animals_checked.push_back(selected_type);
        }

    } while (!animal_chosen && animals_checked.size() != static_cast<unsigned>(EXHIBITS_SIZE));
}


/********************************************************************
** Function: pickRandomAnimal: Helper function that randomly picks
 *              an animal type. Pick a random number
 *              between 0 to animal exhibit count - 1.
** Params:  None
** Returns: int: randomly chosen number static_casted into AnimalType.
 *              i.e. randomly chosen animal type.
*********************************************************************/
AnimalType Zoo::pickRandomAnimal() const
{
    return static_cast<AnimalType>
            (MyRandom::randomInteger(ZERO, EXHIBITS_SIZE-1));
}


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
void Zoo::removeAnimal(AnimalType selected_type)
{
    //temporary animal pointer
    Animal *temp_animal;

    //randomly select an animal from exhibit
    int animal_index =
            MyRandom::randomInteger(ZERO, exhibit_count[selected_type].count-1);

    //point temp animal pointer to selected animal
    temp_animal = animal_exhibits[selected_type][animal_index];

    //shift all animals in exhibit array from selected animal
    // down one except for last one, this removes them from the exhibit,
    // and fills the gap
    for (int i=animal_index, k=exhibit_count[selected_type].count-1; i<k; i++)
    {
        //copy the pointer to the right over to current pointer
        animal_exhibits[selected_type][i] = animal_exhibits[selected_type][i+1];
    }

    //delete pointer at the end of exhibit array because it is now
    // a duplicate. point to nullptr
    animal_exhibits[selected_type][exhibit_count[selected_type].count-1] = nullptr;

    //decrease exhibit count of animal type by 1
    exhibit_count[selected_type].count--;

    //write/read status message that an animal got sick and died
    writeRead(SICKNESS, temp_animal);

    //deallocate dead animal
    delete temp_animal;
    temp_animal = nullptr;
}


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
void Zoo::addAnimal(AnimalType type, int age, bool isBirth)
{
    //make a new animal
    Animal *new_animal = makeAnimal(type, age);

    //add animal to the exhibit
    addToExhibit(type, new_animal);

    //If animal was bought, and not birthed
    //subtract cost of animal from bank
    if (!isBirth)
    {
        subFromBank(new_animal->getCost());
    }

    //print to screen that a new animal was added
    printAnimalAdded(new_animal);
}

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
void Zoo::addAnimal(AnimalType type, int age, const std::string &name,
                       int cost, int num_babies, int feeding_cost,
                       int payoff, bool isBirth)
{
    //make new custom animal
    Animal *new_animal =
            makeAnimal(type, age, name, cost, num_babies, feeding_cost, payoff);

    //add animal to exhibit
    addToExhibit(type, new_animal);

    //If animal was bought, and not birthed
    //subtract cost of animal from bank
    if (!isBirth)
    {
        subFromBank(new_animal->getCost());
    }

    //print to screen that a new animal was added
    printAnimalAdded(new_animal);
}


/********************************************************************
** Function: makeAnimal: Creates a new animal of specified type at
 *              specified age. Tigers, penguins, or turtles only.
** Params:   AnimalType type: type of animal to be created.
 *           Int age: age of animal to be created.
** Returns:  Animal *: pointer to new animal created.
*********************************************************************/
Animal *Zoo::makeAnimal(AnimalType type, int age)
{
    Animal *new_animal = nullptr;

    switch(type)
    {
        case TIGER:
            new_animal = new Tiger(age);
            break;
        case PENGUIN:
            new_animal = new Penguin(age);
            break;
        case TURTLE:
            new_animal = new Turtle(age);
            break;
        case CUSTOM:
            break;  //should never reach here
    }

    return new_animal;
}


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
Animal *Zoo::makeAnimal(AnimalType type, int age, const std::string &name,
                           int cost, int num_babies, int feeding_cost,
                           int payoff)
{
    Animal *new_animal = new CustomAnimal(name, age, cost, num_babies,
                            feeding_cost, payoff);

    return new_animal;
}


/********************************************************************
** Function: addToExhibit: Adds new animal pointer into their exhibit
 *              array. If exhibit is at capacity, increase the
 *              exhibit size. Increase exhibit animal count by 1.
** Params:   AnimalType type: type of animal.
 *           Animal *&animal_ptr: Reference to pointer to
 *              Animal to be added to exhibit.
** Returns:  None
*********************************************************************/
void Zoo::addToExhibit(AnimalType type, Animal *&animal_ptr)
{
    //check if exhibit is at capacity, if so increase capacity
    if (exhibit_count[type].count == exhibit_count[type].capacity)
    {
        increaseExhibit(type);
    }

    //add animal pointer to animal exhibit at the next open index
    animal_exhibits[type][exhibit_count[type].count] = animal_ptr;

    //increase exhibit count by 1
    exhibit_count[type].count++;
}


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
void Zoo::increaseExhibit(AnimalType type)
{
    //exhibit size will increase by 10
    int new_array_size = exhibit_count[type].capacity + START_EXHIBIT_SIZE;

    //create new array for exhibit with new size
    Animal **new_array = new Animal*[new_array_size];

    //initialize all the new pointers to nullptr
    for (int i=ZERO, k=new_array_size; i<k; i++)
    {
        new_array[i] = nullptr;
    }

    //copy animal pointers of old array into new array
    for (int i=ZERO, k=exhibit_count[type].capacity; i<k; i++)
    {
        new_array[i] = animal_exhibits[type][i];
    }

    //delete old animal exhibit array
    delete [] animal_exhibits[type];

    //set animal exhibit pointer to new array
    animal_exhibits[type] = new_array;

    //pointer new array to nullptr
    new_array = nullptr;

    //set new exhibit capacity
    exhibit_count[type].capacity = new_array_size;
}


/********************************************************************
** Function: increaseAnimalsAge: Increases age of all animals in the
 *              Zoo by 1 day.
** Params:   None
** Returns:  None
*********************************************************************/
void Zoo::increaseAnimalsAge()
{
    for (int i=ZERO, k=EXHIBITS_SIZE; i<k; i++)
    {
        for (int j=ZERO, p=exhibit_count[i].count; j<p; j++)
        {
            //increase animal's age by 1
            animal_exhibits[i][j]->incrementAge();
        }
    }
}


/********************************************************************
** Function: feedAllAnimals: Feeds all the animals in the Zoo.
 *              Subtracts their feeding cost times food cost
 *              multiplier, which is dependent on today's feed type,
 *              from the bank account.
** Params:   None
** Returns:  None
*********************************************************************/
void Zoo::feedAllAnimals()
{
    for (int i=ZERO, k=EXHIBITS_SIZE; i<k; i++)
    {
        for (int j=ZERO, p=exhibit_count[i].count; j<p; j++)
        {
            //subtract animal's feeding cost times food cost multiplier
            // from bank account
            subFromBank
            (food_cost_multiplier * animal_exhibits[i][j]->getFeedingCost());
        }
    }
}


/********************************************************************
** Function: calculateAnimalProfits: Loops through the exhibits and
 *              adds all animal's payoffs to the bank, including
 *              today's tiger bonus.
** Params:   None
** Returns:  None
*********************************************************************/
void Zoo::calculateAnimalProfits()
{
    int total_profit = 0;

    for (int i=ZERO, k=EXHIBITS_SIZE; i<k; i++)
    {
        for (int j=ZERO, p=exhibit_count[i].count; j<p; j++)
        {
            //add animal's payoff to total profit
            total_profit += animal_exhibits[i][j]->getPayoff();
        }
    }

    //add tiger bonus to total profit
    total_profit += tiger_bonus;

    //add total profit to bank account
    addToBank(total_profit);

    //print message that today's profits have been calculated
    printTodaysProfits(total_profit);
}


/********************************************************************
** Function: printAnimalAdded: Prints out a message that a new
 *              animal was added to the exhibit.
** Params:   const Animal *animal: Pointer to constant animal object.
** Returns:  None
*********************************************************************/
void Zoo::printAnimalAdded(const Animal *animal) const
{
    //create string message
    string message;
    message += "A new "
                + animal->getName()
                + " was added to the exhibit. ";
    message += "It is only "
                + std::to_string(animal->getAge())
                + " days old.";

    //print message to screen
    menu.formatPrompt(message);
}


/********************************************************************
** Function: printAnimalsAgeIncreased: Prints out message that all
 *              animals age increased by 1 day.
** Params:   None
** Returns:  None
*********************************************************************/
void Zoo::printAnimalsAgeIncreased() const
{
    const string MESSAGE = "All animals are one day older.";

    menu.formatPrompt(MESSAGE);
}


/********************************************************************
** Function: printAnimalsFed: Prints out message that all animals
 *              have been fed.
** Params:   None
** Returns:  None
*********************************************************************/
void Zoo::printAnimalsFed() const
{
    const string MESSAGE = "All animals have been fed! :3";

    menu.formatPrompt(MESSAGE);
}


/********************************************************************
** Function: printTodaysProfits: Prints out message that today's
 *              profits have been calculated.
** Params:   Int profits: today's total profits.
** Returns:  None
*********************************************************************/
void Zoo::printTodaysProfits(int profits) const
{
    //create string message
    string message;
    message += "Your zoo made a killing today.. ";
    message += "you earned $"
                + std::to_string(profits)
                + " in total profit..";

    menu.formatPrompt(message);
}


/********************************************************************
** Function: buyNewAnimal: Prompt the user if they want to buy a new
 *              animal at the end of the day. Then create the new
 *              animal if they choose to do so.
** Params:   None
** Returns:  None
*********************************************************************/
void Zoo::buyNewAnimal()
{
    const string ANIMAL_LIST[] =
            {"Tiger", "Penguin", "Turtle", "New animal (*extra credit*)"};
    const int ANIMAL_LIST_SIZE = 4;
    const int ADULT_AGE = 3;
    int confirmation;

    //ask user if they want to buy a new animal
    const string BUY_ANIMAL_PROMPT = "Do you want to buy a new animal?";
    confirmation = menu.confirm(BUY_ANIMAL_PROMPT);

    if (confirmation == Menu::YES)
    {
        //show user a list of animals to choose from.
        // Subtract 1 to account for zero-based index.
        const string CHOOSE_ANIMAL_PROMPT = "Choose an animal";
        AnimalType animal_selection =
                static_cast<AnimalType>
                (menu.chooseOne(ANIMAL_LIST,
                                ANIMAL_LIST_SIZE,
                                CHOOSE_ANIMAL_PROMPT)-1);

        //if user wants to buy a new custom animal
        if (animal_selection == CUSTOM)
        {
            buyCustomAnimal();
        }
        //else user wants to buy a normal animal
        else
        {
            addAnimal(animal_selection, ADULT_AGE);
        }
    }
}


/********************************************************************
** Function: buyCustomAnimal: If the user has chosen to make a new
 *              animal. Prompt them for the animal's traits then
 *              create the new custom animal.
** Params:   None
** Returns:  None
*********************************************************************/
void Zoo::buyCustomAnimal()
{
    const int ADULT_AGE = 3;

    //constants to prompt for animal traits
    const string ANIMAL_TRAIT_PROMPTS[] =
            {"What is the name of your new animal? ",
             "What is the cost of your new animal? ",
             "What is the number of babies your new animal produces? ",
             "What is the feeding cost of your new animal? ",
             "What is the payoff of your new animal? "};
    const int NAME_INDEX = 0;
    const int COST_INDEX = 1;
    const int NUM_BABIES_INDEX = 2;
    const int FEED_COST_INDEX = 3;
    const int PAYOFF_INDEX = 4;

    //range values for animal traits
    const int LOWER_RANGE = 0;
    const int UPPER_RANGE = 1;
    const int COST_RANGE[] = {100, 10000};
    const int NUM_BABIES_RANGE[] = {1, 10};
    const int FEED_COST_RANGE[] = {10, 100};
    const int PAYOFF_RANGE[] = {100, 2000};

    //variables to hold user input for animal traits
    string name;
    int cost;
    int num_babies;
    int feeding_cost;
    int payoff;

    //prompt for name
    menu.printBorder();
    cout << endl;
    cout << ANIMAL_TRAIT_PROMPTS[NAME_INDEX];
    getline(cin, name);
    menu.printBorder();

    //prompt for cost
    cost = menu.promptForInteger
            (ANIMAL_TRAIT_PROMPTS[COST_INDEX],
                    COST_RANGE[LOWER_RANGE], COST_RANGE[UPPER_RANGE]);

    //prompt for number of babies
    num_babies = menu.promptForInteger
            (ANIMAL_TRAIT_PROMPTS[NUM_BABIES_INDEX],
             NUM_BABIES_RANGE[LOWER_RANGE], NUM_BABIES_RANGE[UPPER_RANGE]);

    //prompt for feeding cost
    feeding_cost = menu.promptForInteger
            (ANIMAL_TRAIT_PROMPTS[FEED_COST_INDEX],
             FEED_COST_RANGE[LOWER_RANGE], FEED_COST_RANGE[UPPER_RANGE]);

    //prompt for payoff
    payoff = menu.promptForInteger
            (ANIMAL_TRAIT_PROMPTS[PAYOFF_INDEX],
             PAYOFF_RANGE[LOWER_RANGE], PAYOFF_RANGE[UPPER_RANGE]);

    //add the new custom animal
    addAnimal(CUSTOM, ADULT_AGE, name, cost, num_babies, feeding_cost, payoff);
}


/********************************************************************
** Function: promptForFeedType: Prompts user for the kind of feed
 *              type they want to use today. Set's today's feed type
 *              and food cost multiplier.
** Params:   None
** Returns:  None
*********************************************************************/
void Zoo::promptForFeedType()
{
    //constants for feed type prompt
    const string MESSAGE = "What type of feed do you want to use today?";
    const string FEED_CHOICES[] = {"Cheap", "Generic", "Premium"};
    const int FEED_CHOICES_SIZE = 3;

    //prompt user for todays feed type
    // and set it to global todays_feed_type.
    // Subtract 1 to account for zero-based index.
    todays_feed_type = static_cast<FeedType>
            (menu.chooseOne(FEED_CHOICES, FEED_CHOICES_SIZE, MESSAGE)-1);

    //change todays food cost multiplier
    changeFoodCostMultiplier(todays_feed_type);
}


/********************************************************************
** Function: changeFoodCostMultiplier: Changes the food cost
 *              multiplier used to calculate total feeding cost for
 *              the day.
** Params:   FeedType type: feed type to be used today.
** Returns:  None
*********************************************************************/
void Zoo::changeFoodCostMultiplier(FeedType type)
{
    food_cost_multiplier = feed_multiplier_lookup[type];
}


/********************************************************************
** Function: addToBank: Adds amount passed as argument to the Zoo's
 *              bank account.
** Params:   double amount: amount of $ to add to the bank.
** Returns:  None
*********************************************************************/
void Zoo::addToBank(double amount)
{
    bank_account += amount;
}


/********************************************************************
** Function: subFromBank: Subtracts amount passed as argument to
 *              the Zoo's bank account.
** Params:   double amount: amount of $ to subtract from bank.
** Returns:  None
*********************************************************************/
void Zoo::subFromBank(double amount)
{
    bank_account -= amount;
}


/********************************************************************
** Function: printBank: Prints bank account amount to user.
** Params:   None
** Returns:  None
*********************************************************************/
void Zoo::printBank() const
{
    string message = "Bank account: $";

    menu.printBorder();
    cout << endl;

    cout << std::fixed << std::showpoint << std::setprecision(2)
            << message << bank_account << endl;

    menu.printBorder();
}


/********************************************************************
** Function: isBankrupt: Determines if the Zoo is bankrupt or not.
 *              Returns a boolean true if bankrupt, or false if not
 *              bankrupt yet.
** Params:   None
** Returns:  boolean: true if bank account is less than 1, false
 *              otherwise.
*********************************************************************/
bool Zoo::isBankrupt() const
{
    return bank_account < 1;
}


/********************************************************************
** Function: checkIfBankrupt: Checks if Zoo is bankrupt, if so, this
 *              function ends the game.
** Params:   None
** Returns:  None
*********************************************************************/
void Zoo::checkIfBankrupt()
{
    if (isBankrupt())
    {
        //if user is out of money,
        // call game over with global day counter
        gameOver(day_counter, BANKRUPT);
    }
}


/********************************************************************
** Function: promptToKeepPlaying: Ask user if they want to continue
 *              playing or quit the game. If they choose to quit,
 *              this function ends the game.
** Params:   None
** Returns:  None
*********************************************************************/
void Zoo::promptToKeepPlaying()
{
    const string MESSAGE = "Do you want to keep playing?";
    int confirmation = menu.confirm(MESSAGE);
    if (confirmation == Menu::NO)
    {
        //if user chooses to not play any more,
        // call game over with global day counter
        gameOver(day_counter, QUIT);
    }
}


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
void Zoo::gameOver(int day_counter, ExitReason reason)
{
    //output messages
    const string GAME_OVER_MSG = "Game Over";
    const string DAYS_OPENED_MSG =
            "Number of days opened: " + std::to_string(day_counter);
    const string WHAT_HAPPENED_TO_ANIMALS =
            "All the animals were released and went on a rampage in the city.";

    string exit_reason;
    if (reason == BANKRUPT)
    {
        exit_reason = "Because you went bankrupt.";
    }
    else if (reason == QUIT)
    {
        exit_reason = "Because you gave up.";
    }

    //print game over message and number of days in business
    menu.printBorder();
    cout << endl;

    cout << GAME_OVER_MSG << endl;
    cout << DAYS_OPENED_MSG << endl;

    menu.printBorder();

    //print ending status of animal exhibit
    printExhibitCount();

    //print ending bank account
    printBank();

    //print what happened to the animals and the reason for exit
    menu.printBorder();
    cout << endl;

    cout << WHAT_HAPPENED_TO_ANIMALS << endl;
    cout << exit_reason << endl;
    menu.printBorder();

    //set exit status to true to end the game
    exit_status = true;
}


/********************************************************************
** Function: printExhibitCount: Prints the current status of each
 *              exhibit, the count of the animals and the exhibit's
 *              capacity.
** Params:   None
** Returns:  None
*********************************************************************/
void Zoo::printExhibitCount() const
{
    const string CAPACITY = "Capacity: ";
    const string COUNT = "Count: ";

    menu.printBorder();
    cout << endl;

    cout << "Animal exhibit count" << endl << endl;

    //tiger exhibit
    cout << "Tiger exhibit:" << endl;
    cout << CAPACITY << exhibit_count[TIGER].capacity << endl;
    cout << COUNT << exhibit_count[TIGER].count << endl;
    cout << endl;

    //penguin exhibit
    cout << "Penguin exhibit:" << endl;
    cout << CAPACITY << exhibit_count[PENGUIN].capacity << endl;
    cout << COUNT << exhibit_count[PENGUIN].count << endl;
    cout << endl;

    //turtle exhibit
    cout << "Turtle exhibit:" << endl;
    cout << CAPACITY << exhibit_count[TURTLE].capacity << endl;
    cout << COUNT << exhibit_count[TURTLE].count << endl;
    cout << endl;

    //new animals exhibit
    cout << "New animals exhibit:" << endl;
    cout << CAPACITY << exhibit_count[CUSTOM].capacity << endl;
    cout << COUNT << exhibit_count[CUSTOM].count << endl;

    menu.printBorder();
}


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
void Zoo::writeRead(EventType event, const Animal *animal, int todays_bonus)
{
    std::ostringstream sstream; //used to format dollar amounts
    string message;

    //make event message string based on today's events
    switch(event)
    {
        case NOTHING:
            message = "Today.. nothing happened at the zoo..";
            break;
        case BOOM:
            sstream << std::fixed << std::showpoint << std::setprecision(2);

            sstream << "Today.. a boom in zoo attendance occurred..";

            if (tiger_bonus > 0)
            {
                sstream << " you earned $";
                sstream << todays_bonus;
                sstream << " per tiger for a total of $";
                sstream << tiger_bonus;
                sstream << " extra profit.. people really love tigers.. :v";
            }
            else
            {
                //there are no tigers in the zoo to generate a bonus
                sstream << " too bad you dont have any tigers :v";
            }

            message = sstream.str();
            break;
        case BIRTH:
            message = "Today.. a(n) ";
            message += animal->getName();
            message += " had ";
            message += std::to_string(animal->getNumBabies());
            message += " babies..";
            break;
        case SICKNESS:
            message = "Today.. a(n) ";
            message += animal->getName();
            message += " died from illness at the age of ";
            message += std::to_string(animal->getAge());
            message += ".. the zoo mourns its loss..";
            break;
    }

    //write message to file
    writeMessage(message);

    //read message from file to screen
    readMessage();
}


/********************************************************************
** Function: writeMessage: Writes a message of a random event to an
 *              output file.
** Params:   const string &message: string message stating what event
 *              happened today.
** Returns:  None
*********************************************************************/
void Zoo::writeMessage(const std::string &message)
{
    //open output file stream
    fileOut.open(EVENT_FILE);

    if (fileOut)
    {
        //write message to file
        fileOut << message;

        //close output file stream
        fileOut.close();
    }
}


/********************************************************************
** Function: readMessage: Reads a message from random event file and
 *              prints it to screen.
** Params:   None
** Returns:  None
*********************************************************************/
void Zoo::readMessage()
{
    string message;

    //open input file for reading
    fileIn.open(EVENT_FILE);

    if (fileIn)
    {
        //read file message into message variable
        getline(fileIn, message);

        //print message to screen
        menu.formatPrompt(message);

        //close input file stream
        fileIn.close();
    }
}
