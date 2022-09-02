#include "Domain.h"
#include <sstream>
#include <Windows.h>
#include <shellapi.h>
#include <iostream>

Event::Event() : title{ "" }, description{ "" }, date{ "" }, time{ "" }, numberOfPeople{ 0 }, link{ "" } {}

Event::Event(const std::string& title, const std::string& description, const std::string& date, const std::string& time,
    int numberOfPeople, const std::string& link) : title{ title }, description{ description }, date{ date }, time{ time }, numberOfPeople{ numberOfPeople }, link{ link } {}

std::string Event::toString()
{
    std::ostringstream  eventToPrint;

    eventToPrint << " > Event Title: " << this->title << "\n";
    eventToPrint << " > Description : " << this->description << "\n";
    eventToPrint << " > Date  : " << this->date << "\n";
    eventToPrint << " > Time: " << this->time << "\n";
    eventToPrint << " > Number of People: " << this->numberOfPeople << "\n";
    eventToPrint << " > Link: " << this->link << "\n";

    return eventToPrint.str();
}

std::vector<std::string> Event::tokenize(const std::string& str, char separator)
{
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, separator))
        result.push_back(token);
    return result;
}

// example of line in file
// carrer fest,career event in cluj-napoca,29/10/2022,10:30,5000,https://www.targuldecariere.ro/cluj-global
std::istream& operator>>(std::istream& is, Event& e)
{
    if (is.eof())
        is.setstate(std::ios_base::failbit); // operator bool returns true for eof => enforce false to terminate the loop
    else
    {
        std::string line;
        getline(is, line);
        std::vector<std::string> tokens = e.tokenize(line, ',');
        if (tokens.size() != 6)
            return is;
        e.setTitle(tokens.at(0));
        e.setDescription(tokens.at(1));
        e.setDate(tokens.at(2));
        e.setTime(tokens.at(3));
        e.setNumberOfPeople(stoi(tokens.at(4)));
        e.setLink(tokens.at(5));
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Event& e)
{
    os << e.getTitle() << "," << e.getDescription() << "," << e.getDate() << "," << e.getTime() << "," << e.getNumberOfPeople() << "," << e.getLink() << "\n";
    return os;
}