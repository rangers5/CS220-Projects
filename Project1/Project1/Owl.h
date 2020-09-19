#pragma once
#include "Standard.h"
class Owl :
   public Standard
{
private:
   std::string id;   //holds the ID of the package as a string
public:
   Owl();            //Default constructor, sets ID to undefined
   Owl(std::string, std::string, std::string, double);   //Overloaded constructor, sets name, date, ID, and weight
   std::string get_id();   //Returns the ID
   void display();   //Displays the package stats to the user
};

