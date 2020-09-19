#pragma once
#include "Delivery.h"
class VanishingCabinet :
   public Delivery
{
private:
   std::string id;   //Holds the ID of the vanishing cabinet
public:
   VanishingCabinet();  //Default constructor, sets the ID to undefined
   VanishingCabinet(std::string, std::string, std::string); //Overloaded constructor takes in name, date, id
   std::string get_id();  //Returns the ID of the package
   std::string get_date_scheduled();  //Returns the scheduled delivery date
   void display();  //Displays the stats of the package
   std::string get_sender_name(); //Returns the senders name 

};

