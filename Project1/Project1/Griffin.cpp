#include "Griffin.h"

Griffin::Griffin()
{
   id = "Undefined";  //Sets the ID to undefined if not specified
}

Griffin::Griffin(std::string name, std::string date, std::string id, double weight) : Standard {name, date, weight}
{
   this->id = id;    //Sets ID and the rest of the paramaters to the standard constructor
}

std::string Griffin::get_id()
{
   return id;     //Returns the ID to the user
}

void Griffin::display()    //Virtual function that displays the stats of the package
{
   std::cout << "The delivery via Griffin sent by " << get_sender_name() << " with ID " << id << " is schedualed to be delivered on " << get_date_scheduled() << " with a weight of " << get_weight() << " kg" << std::endl;
}
