#include "VanishingCabinet.h"

VanishingCabinet::VanishingCabinet()
{
   id = "Undefined"; //Default constructor sets ID to undefined
}

VanishingCabinet::VanishingCabinet(std::string name, std::string date, std::string id) : Delivery{name, date}
{
   this->id = id; //Overloaded constructor sets ID and sends date and name to Delivery constructor
}

std::string VanishingCabinet::get_id() //Returns the ID of the package
{
   return id;  
}

std::string VanishingCabinet::get_date_scheduled() //Returns the date of the scheduled delivery
{
   return Delivery::get_date_scheduled();
}

void VanishingCabinet::display()  //Displays the stats of the current package
{
   std::cout << "The delivery via Vanishing Cabinet sent by " << get_sender_name() << " with ID " << id << " is schedualed to be delivered on " << get_date_scheduled() << std::endl;
}

std::string VanishingCabinet::get_sender_name() //Returns the senders name of the package
{
   return Delivery::get_sender_name();
}
