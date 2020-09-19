#pragma once
#include "Standard.h"
class Griffin :
   public Standard
{
private:
   std::string id;   //Holds the ID of the package
public:
   Griffin();        //Standard constructor, Sets ID to undefined by default
   Griffin(std::string, std::string, std::string, double);  //Constructor used to set name, date, id, and weight
   std::string get_id();   //returns the ID
   void display();         //Displays the stats of the package to the user
};

