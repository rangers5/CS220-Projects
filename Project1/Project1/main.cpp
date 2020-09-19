//Import all the classes for this project
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include "Delivery.h"
#include "Owl.h"
#include "Griffin.h"
#include "VanishingCabinet.h"
#include "Standard.h"
#include <fstream>

//Prototypes
std::string getFileName();
void newDelivery(std::vector<VanishingCabinet*> &vanishingList, std::vector<Owl*> &owlList, std::vector<Griffin*> &griffinList);
bool verifyDate(std::string date);
std::string generateVanishingCabinetId();
std::string generateOwlId();
std::string generateGriffinId();
void removeDelivery(std::vector<VanishingCabinet*>& vanishingList, std::vector<Owl*>& owlList, std::vector<Griffin*>& griffinList);
void saveDeliveryToFile(std::vector<VanishingCabinet*>& vanishingList, std::vector<Owl*>& owlList, std::vector<Griffin*>& griffinList);
void loadDeliveryFromFile(std::vector<VanishingCabinet*>& vanishingList, std::vector<Owl*>& owlList, std::vector<Griffin*>& griffinList);
void displayAllDeliveries(std::vector<VanishingCabinet*>& vanishingList, std::vector<Owl*>& owlList, std::vector<Griffin*>& griffinList);
void displayDeliveryByType(std::vector<VanishingCabinet*>& vanishingList, std::vector<Owl*>& owlList, std::vector<Griffin*>& griffinList);
unsigned short getChoice();
void displayChoices();
bool isNumber(char c);
int computeMaxDay(int month, int year);
bool isLeapYear(int year);
char getDeliveryChoice();
int selectDelivery(size_t size);

int main() {
   //Variables
   std::vector<VanishingCabinet *> vanishingList;    //A vector holding all of the VanishingCabinets
   std::vector<Owl *> owlList;                       //A vector holding all of the Owls
   std::vector<Griffin *> griffinList;               //A vector holding all of the Griffins
   unsigned short userChoice;                        //Holds the users choice of action

   //Startup Sequence
   //Seed the random number generator for Id generation
   srand(time(NULL));
   //Set cout to display 2 decimal places
   std::cout.setf(std::ios::fixed);
   std::cout.precision(2);

   //Main Loop
   do
   {
      userChoice = getChoice();                 //Gets the user's menu choice
      switch (userChoice)
      {
      case 1:                                   //Schedule a new delivery
         newDelivery(vanishingList, owlList, griffinList);
         break;
      case 2:                                   //Remove a Delivery
         removeDelivery(vanishingList, owlList, griffinList);
         break;
      case 3:                                   //Load Deliveries from a file
         loadDeliveryFromFile(vanishingList, owlList, griffinList);
         break;
      case 4:                                   //Save Deliveries to a file
         saveDeliveryToFile(vanishingList, owlList, griffinList);
         break;
      case 5:                                   //Print all Deliveries
         displayAllDeliveries(vanishingList, owlList, griffinList);
         break;
      case 6:                                   //Print Deliveries by type
         displayDeliveryByType(vanishingList, owlList, griffinList);
         break;
      case 7:                                   //Exit the program
         std::cout << "Exiting the program...\n";
         break;
      }
   } while (userChoice != 7);

   //After the user selects exit, do through the list of deliveries and delete all the values that were created
   for (VanishingCabinet* v : vanishingList)
   {
      delete v;
   }

   for (Owl* o : owlList)
   {
      delete o;
   }

   for (Griffin* g : griffinList)
   {
      delete g;
   }

   //Resize the vector to zero
   owlList.clear();
   griffinList.clear();
   vanishingList.clear();

   return 0;
}


unsigned short getChoice()                      //Gets the user's menu choice and verifies that it is a valid choice
{
   unsigned short userChoice;                   //Stores the user's choice to return
   const unsigned short MAX_CHOICES = 7;        //Constant that stores the number of menu choices
   do                                           //Loop to verify the user entered a valid choice
   {
      displayChoices();
      std::cout << "Enter the number of the action you want to do: ";
      std::cin >> userChoice;
   } while (userChoice < 1 || userChoice > MAX_CHOICES);
   return userChoice;
}

void displayChoices()                           //Function that displays the main menu to the user
{
   std::cout << "Main Menu: \n";
   std::cout << "    1. Schedule a new delivery \n";
   std::cout << "    2. Remove a delivery \n";
   std::cout << "    3. Load deliveries from a file \n";
   std::cout << "    4. Save deliveries to a file\n";
   std::cout << "    5. Print all scheduled deliveries\n";
   std::cout << "    6. Print deliveries by type\n";
   std::cout << "    7. Quit\n";

}


void newDelivery(std::vector<VanishingCabinet*>& vanishingList, std::vector<Owl*>& owlList, std::vector<Griffin*>& griffinList)
{
   //Variables
   std::string name;
   std::string date;
   std::string id;
   char type;
   double weight;

   //Get the sender name
   std::cout << "Who is sending the package?" << std::endl;
   std::cin.ignore();
   std::getline(std::cin, name);

   //Get and verify the date
   do
   {
      std::cout << "Enter the estimated delivery date (mm-dd-yyyy): \n";
      std::cin >> date;
   } while (!verifyDate(date));

   //Get the delivery type
   do 
   {
      std::cout << "Enter s for standard delivery or v for vanishing cabinet: ";
      std::cin >> type;
      type = std::tolower(type);
   } while (type != 'v' && type != 's');

   //Generate the delivery for vanishing Cabinet type
   if (type == 'v')
   {
      id = generateVanishingCabinetId();
      VanishingCabinet* v = new VanishingCabinet(name, date, id);
      vanishingList.push_back(v);
      return;
   }
   else
   {
      //Check the weight to see if it is an Owl or a Griffin
      do
      {
         std::cout << "Enter the weight of the package in kilograms: \n";
         std::cin >> weight;
      } while (weight <= 0);
      if (weight <= 1.58)
      {
         id = generateOwlId();
         Owl* o = new Owl(name, date, id, weight);
         owlList.push_back(o);
         return;
      }
      else 
      {
         id = generateGriffinId();
         Griffin* g = new Griffin(name, date, id, weight);
         griffinList.push_back(g);
         return;
      }
   }
}


bool verifyDate(std::string date)               //Takes a date in the form "mm-dd-yyyy" and verifes that it is valid
{
   //Variables
   int day;
   int month;
   int year;

   if (date.length() != 10)                     //Check to see if the string is the correct length
   {
      std::cout << "The string entered is of wrong length, make sure to use preceding zeros! \n";
      return false;
   }

   for (int i = 0; i < 10; i++)                 //Check to see if the string is of proper format
   {
      if (i == 2 || i == 5)                     //Checks to see if there is a dash in the proper spot
      {
         if (date.at(i) != '-')
         {
            std::cout << "The string entered has a dash in the wrong place \n";
            return false;
         }
      }
      else                                      //Checks to see if there is a number in the proper spot
      {
         if (!isNumber(date.at(i)))
         {
            std::cout << "The string entered is missing a number \n";
            return false;
         }
      }
   }

   try
   {                                        //Deconstruct the string and convert to int, catches error if stoi fails (this "should" never fail with previous checks but just in case)
      month = std::stoi(date.substr(0, 2));
      day = std::stoi(date.substr(3, 2));
      year = std::stoi(date.substr(6, 4));
   }
   catch (std::exception e)
   {
      std::cout << "Unknown characters found in the string, make sure it follows the proper format \n";
      return false;
   }
 
   if (year <= 0)                               //Checks to see if it is a valid year
   {
      return false;
   }

   if (month < 1 || month > 12)                 //Checks to see if the month is valid
   {
      return false;
   }

   if (day < 1 || day > computeMaxDay(month, year)) //Checks to see if the day is valid
   {
      return false;
   }

   return true;
}
bool isNumber(char c)                           //Returns true or false dependent on if the given character is one of the following: 0123456789
{
   if (c < 48 || c > 57)
   {
      return false;
   }
   return true;
}
int computeMaxDay(int month, int year)          //Will return the number of days in the given month and year
{
   int maxDay;
   switch (month)
   {
   //Months with 31 days
   case 1:
   case 3:
   case 5:
   case 7:
   case 8:
   case 10:
   case 12:
      maxDay = 31;
      break;
   //Months with 30 days
   case 4:
   case 6:
   case 9:
   case 11:
      maxDay = 30;
      break;
   //Checks Febuary to see if it is a leap year or not
   case 2:
      if (isLeapYear(year))
      {
         maxDay = 29;
      }
      else
      {
         maxDay = 28;
      }
      break;
   }
   return maxDay;
}

bool isLeapYear(int year)                    //Returns true or false depending on if the given year is a leap year
{
   if (year % 4 != 0)
      return false;

   if (year % 100 != 0)
      return true;

   if (year % 400 != 0)
      return false;

   return true;
}

std::string generateVanishingCabinetId()        //Returns a string in the form "XXXXXXXX-XXXXXXXX"
{
   std::string id = "";                         //Start with a blank string

   for (int i = 1; i <= 8; i++)                 //Generate the first 8 digits
   {
      id += std::to_string(rand() % 10);
   }

   id += "-";                                   //Add the dash to the middle of the ID

   for (int i = 1; i <= 8; i++)                 //Generate the last 8 digits
   {
      id += std::to_string(rand() % 10);
   }

   return id;
}

std::string generateOwlId()                     //returns a string in the form "oXXX"
{
   std::string id = "o";                        //Start with the preceding o

   for (int i = 1; i <= 3; i++)                 //Generate the last 3 digits
   {
      id += std::to_string(rand() % 10);
   }

   return id;
}

std::string generateGriffinId()                 //returns a string in the form "gXXXXXXX"
{
   std::string id = "g";                        //Start with a preceding g

   for (int i = 1; i <= 7; i++)                 //Generate the last 7 digits
   {
      id += std::to_string(rand() % 10);
   }

   return id;
}

void removeDelivery(std::vector<VanishingCabinet*> &vanishingList, std::vector<Owl*> &owlList, std::vector<Griffin*> &griffinList)  //Removes a selected delivery from the delivery lists
{
   char type = getDeliveryChoice();          //Gets to see what type of delivery the user wants to remove
   int selection;                            //The users choice of what item to remove
   switch (type)
   {
   case 'o':
      for (unsigned int i = 0; i < owlList.size(); i++)     //displays all deliveryies for owl type
      {
         std::cout << i + 1 << ". ";
         owlList[i]->display();  
      }

      selection = selectDelivery(owlList.size());           //Gets the users choice on what to remove
      delete owlList[selection];                            //Deletes the selected delivery from memory
      owlList.erase(owlList.begin() + selection);           //Shrinks the size of the vector

      break;
   case 'g':
      for (unsigned int i = 0; i < griffinList.size(); i++)    //Displays all griffin deliveries
      {
         std::cout << i + 1 << ". ";
         griffinList[i]->display();
      }

      selection = selectDelivery(griffinList.size());           //Gets the users choice on what to remove
      delete griffinList[selection];                            //Deletes the selected delivery from memory
      griffinList.erase(griffinList.begin() + selection);       //Shrinks the size of the vector

      break;
   case 'v':
      for (unsigned int i = 0; i < vanishingList.size(); i++)   //Displays all vanishingCabinet Deliveries
      {
         std::cout << i + 1 << ". ";
         vanishingList[i]->display();
      }

      selection = selectDelivery(vanishingList.size());           //Gets the users choice on what to remove
      delete vanishingList[selection];                            //Deletes the selected delivery from memory
      vanishingList.erase(vanishingList.begin() + selection);     //Shrinks the size of the vector

      break;
   }
}

void saveDeliveryToFile(std::vector<VanishingCabinet*> &vanishingList, std::vector<Owl*> &owlList, std::vector<Griffin*> &griffinList)    //Saves the lists of deliveries to a file
{
   std::ofstream output;      //Create an output string to store our data

   try                        //Attempt to open the file, returns to main if it fails
   {
      output.open(getFileName());
   }
   catch (std::exception e)
   {
      std::cout << "Error opening the file, returning to main menu... \n";
      return;
   }

   output.flush();            //Clear the save file of any old save data

   //Save all the delivery data in modified csv format with a end keyword at the end of the file
   for (unsigned int i = 0; i < owlList.size(); i++)
   {
      output << "o," << owlList[i]->get_sender_name() << ',' << owlList[i]->get_date_scheduled() << ',' << owlList[i]->get_id() << ',' << owlList[i]->get_weight() << '\n';
   }

   for (unsigned int i = 0; i < griffinList.size(); i++)
   {
      output << "g," << griffinList[i]->get_sender_name() << ',' << griffinList[i]->get_date_scheduled() << ',' << griffinList[i]->get_id() << ',' << griffinList[i]->get_weight() << '\n';
   }

   for (unsigned int i = 0; i < vanishingList.size(); i++)
   {
      output << "v," << vanishingList[i]->get_sender_name() << ',' << vanishingList[i]->get_date_scheduled() << ',' << vanishingList[i]->get_id() << '\n';
   }

   output << "end";        //Add the word end to the file to not have to deal with removing the last \n when working with eof

   output.close();         //Close the file
}

void loadDeliveryFromFile(std::vector<VanishingCabinet*> &vanishingList, std::vector<Owl*> &owlList, std::vector<Griffin*> &griffinList)
{
   std::ifstream input;          //The input file the user selects
   std::string deliveryString;   //Each line of the current opened file
   std::string id;               //The id retrieved from each line
   std::string name;             //The name retrieved from each line
   std::string date;             //The date recieved from each line
   double weight;                //The weight recieved from each line
   size_t stringPosStart;        //the location of the first character in the current piece of data it is reading
   size_t stringPosEnd;          //the location of the ending comma in the current data it is reading

   //Attempt to open the given file, return if it fails to open
   try
   {
      input.open(getFileName());
   }
   catch (std::exception e)
   {
      std::cout << "Error opening the file, returning to main menu... \n";
      return;
   }

   //Loop through the whole file
   while (!input.eof())
   {
      std::getline(input, deliveryString); //Get the current line of the file
      if (deliveryString == "end")  //Checks for the end keyword and breaks from the loop if it finds it
      {
         break;
      }

      //Gets the info from each line of the data, starting from character 2 as we compare against the first character manually later
      stringPosStart = 2;
      stringPosEnd = deliveryString.find(',', stringPosStart);        //Gets the location of the second comma
      name = deliveryString.substr(stringPosStart, stringPosEnd - stringPosStart); //Gets the name from the file
      stringPosStart = stringPosEnd + 1;                              //Sets the new starting location
      stringPosEnd = deliveryString.find(',', stringPosStart);        //Sets the new ending location for the substring
      date = deliveryString.substr(stringPosStart, stringPosEnd - stringPosStart); //Gets the date from the save data

      if (deliveryString.at(0) != 'v')       //Checks to see if the line will have a weight attribute
      {
         stringPosStart = stringPosEnd + 1;                                           //Sets the new starting location
         stringPosEnd = deliveryString.find(',', stringPosStart);                     //Sets the new ending location for the substring
         id = deliveryString.substr(stringPosStart, stringPosEnd - stringPosStart);   //Gets the ID from the save data
         stringPosStart = stringPosEnd + 1;                                           //Sets the new starting location
         stringPosEnd = deliveryString.size();                                        //Gets the end of the string
         weight = stod(deliveryString.substr(stringPosStart, stringPosEnd - stringPosStart));      //Gets the weight from the save data

         //Checks the first letter of the line to see what class to create
         if (deliveryString.at(0) == 'g')
         {
            Griffin* g = new Griffin(name, date, id, weight);
            griffinList.push_back(g);
         }
         else
         {
            Owl* o = new Owl(name, date, id, weight);
            owlList.push_back(o);
         }

      }
      else   //If it does not have a weight attribute, it is a vanishing cabinet
      {
         stringPosStart = stringPosEnd + 2;                                           //Sets the new starting location
         stringPosEnd = deliveryString.size();                                        //Sets the new ending location for the substring
         id = deliveryString.substr(stringPosStart, stringPosEnd - stringPosStart);                //Gets the id from the save data
         VanishingCabinet* v = new VanishingCabinet(name, date, id);
         vanishingList.push_back(v);
      }
   }

   input.close();   //Close the file
}

void displayAllDeliveries(std::vector<VanishingCabinet*>& vanishingList, std::vector<Owl*>& owlList, std::vector<Griffin*>& griffinList)  //Displays all deliveries in the vectors
{
   //Iterate through the vector and display each part
   for (unsigned int i = 0; i < vanishingList.size(); i++)
   {
      vanishingList[i]->display();
   }

   for (unsigned int i = 0; i < owlList.size(); i++)
   {
      owlList[i]->display();
   }

   for (unsigned int i = 0; i < griffinList.size(); i++)
   {
      griffinList[i]->display();
   }
}

void displayDeliveryByType(std::vector<VanishingCabinet*>& vanishingList, std::vector<Owl*>& owlList, std::vector<Griffin*>& griffinList) //Displays the selected delivery type
{
   char type = getDeliveryChoice(); //Gets the users selection on what deliveries to display

   //Check the character and display the selected choice
   if (type == 'v')
   {
      //Iterate through the vector and display
      for (unsigned int i = 0; i < vanishingList.size(); i++)
      {
         vanishingList[i]->display();
      }
   }
   else
   {
      if (type == 'o')
      {
         //Iterate through the vector and display
         for (unsigned int i = 0; i < owlList.size(); i++)
         {
            owlList[i]->display();
         }
      }
      else
      {
         //Iterate through the vector and display
         for (unsigned int i = 0; i < griffinList.size(); i++)
         {
            griffinList[i]->display();
         }
      }
   }
}
char getDeliveryChoice()      //Returns the character of the users desired delivery choice
{
   char type;  //Holds the user's choice

   //Get the user input and verify that it is a valid choice
   do
   {
      std::cout << "Choose one of the following characters for the delivery type you want to display/remove: \n" <<
         "v for Vanishing Cabinet \n" << "g for Griffin\n" << "o for Owl\n";
      std::cin >> type;
      type = std::tolower(type);    //Makes sure the value is lowercase
   } while (type != 'v' && type != 'g' && type != 'o');

   return type;
}

int selectDelivery(size_t size)     //Takes in the size of the vector for checking and asks the user what delivery he wants to remove, and returns its position in the vector
{
   int choice;    //Holds the users choice

   //Checks to see if the user entered a valid input
   do
   {
      std::cout << "Select the delivery you would like to remove: ";
      std::cin >> choice;
   } while (choice < 1 || choice > static_cast<int>(size));
   return choice - 1;
}

std::string getFileName()     //Asks and returns a file name to open/close from the user
{
   std::string name;
   std::cout << "Enter the name of the file: ";
   std::cin >> name;
   return name;
}