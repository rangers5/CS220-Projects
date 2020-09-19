#include "Standard.h"

Standard::Standard()
{
   weight = 1; //By defualt the weight is 1
}

Standard::Standard(std::string name, std::string date, double weight) : Delivery{ name, date}
{
   this->weight = weight; //Sets the weight and sends name and date to the delivery constructor
}


double Standard::get_weight() //Returns the weight of the package
{
   return weight;
}

std::string Standard::get_date_scheduled()   //Returns the scheduled delivery date of the package
{
   return Delivery::get_date_scheduled();
}

void Standard::display()   //Displays the package stats to the user
{
   std::cout << "The delivery via Standard Shipping sent by " << get_sender_name() << " with weight " << weight << " is schedualed to be delivered on " << get_date_scheduled() << std::endl;
}

std::string Standard::get_sender_name()   //Returns the sender name to the user
{
   return Delivery::get_sender_name();
}
