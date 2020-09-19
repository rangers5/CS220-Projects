#include "Owl.h"

Owl::Owl()
{
   id = "Undefined"; //Sets the default ID to undefined
}

Owl::Owl(std::string name, std::string date, std::string id, double weight) : Standard{ name, date, weight }
{
   this->id = id;    //Sets the ID to the value given, the rest sent to the standard constructor
}

std::string Owl::get_id()  //Returns the ID 
{
   return id;
}

void Owl::display()  //Displays the package stats to the user
{
   std::cout << "The delivery via Owl sent by " << get_sender_name() << " with ID " << id << " is schedualed to be delivered on " << get_date_scheduled()  << " with a weight of " << get_weight() << " kg"<< std::endl;
}
