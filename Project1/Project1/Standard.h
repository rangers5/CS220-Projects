#pragma once
#include "Delivery.h"
class Standard :
   public Delivery
{
private:
   double weight; //Holds the weight of the package
protected:
   Standard();    //Default constructor, sets the weight to 1 by default
   Standard(std::string, std::string, double); //Overloaded constructor takes in name, date, weight
public:
   double get_weight(); //Returns the weight
   std::string get_date_scheduled();   //Returns the date scheduled
   void display();      //Displays the package info to the user
   std::string get_sender_name();   //Returns the sender name
};

