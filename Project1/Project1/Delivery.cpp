#include "Delivery.h"

Delivery::Delivery()  //Default constructor sets variables to undefined by default
{
   sender_name = "Undefined";
   date_scheduled = "Undefined";
}

Delivery::Delivery(std::string name, std::string date) //Overloaded constructor sets sender_name and date_scheduled to parameters
{
   sender_name = name;
   date_scheduled = date;
}

std::string Delivery::get_sender_name()  //Returns the senders name
{
   return sender_name;
}

std::string Delivery::get_date_scheduled()  //returns the date scheduled
{
   return date_scheduled;
}

void Delivery::set_sender_name(std::string name)  //Sets the sender's name of the package to the parameter
{
   sender_name = name;
   return;
}

void Delivery::set_date_scheduled(std::string date)  //Sets the estimated delivery date of the package to the parameter
{
   date_scheduled = date;
   return;
}

void Delivery::display()  //Displays the stats of the package
{
   std::cout << "The sender of the package is " << sender_name << " with a scheduled delivery date of " << date_scheduled << std::endl;
}
