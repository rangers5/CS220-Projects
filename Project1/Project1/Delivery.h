#pragma once
#include <string>
#include <iostream>
class Delivery
{
private:
   std::string sender_name;   //Holds the senders name of the package as a string
   std::string date_scheduled;  //Holds the estimated delivery date of the package (mm/dd/yyyy)
protected:
   std::string get_sender_name();   //Returns the senders name
   std::string get_date_scheduled();  //Returns the estimated delivery date
   void set_sender_name(std::string);  //Sets the senders name
   void set_date_scheduled(std::string); //Sets the date scheduled
   Delivery(); //Default constructor, sets name and date to undefined
   Delivery(std::string, std::string); //Overloaded constructor sets name and date to the parameters passed in
public:
   virtual void display(); //Virtual fuction that displays the package info to the user 
};
