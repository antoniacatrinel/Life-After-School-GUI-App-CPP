#include "Validation.h"
#include <algorithm>
#include <string>

void Validator::validateEvent(const Event& e)
{
    std::string exception = "";
    try {
        validateEventTitle(e.getTitle());
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
        exception += "\n";
    }
    try {
        validateEventDescription(e.getDescription());
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
        exception += "\n";
    }
    try {
        validateEventDate(e.getDate());
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
        exception += "\n";
    }
    try {
        validateEventTime(e.getTime());
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
        exception += "\n";
    }
    try {
        validateEventNrOfPeople(e.getNumberOfPeople());
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
        exception += "\n";
    }
    try {
        validateEventLink(e.getLink());
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
    }
    if (exception != "")
        throw ValidatorException(exception);

}

void Validator::validateUserCommand(std::string& input)
{
    if (input.length() == 0)
        throw ValidatorException("  Input error: command cannot be empty!");
    else
    {
        input.erase(remove(input.begin(), input.end(), ' '), input.end());
        transform(input.begin(), input.end(), input.begin(), ::tolower);
    }
}

void Validator::validateEventTitle(const std::string& title)
{
    if (title.length() == 0)
        throw ValidatorException("  Input error: title of event cannot be empty!");
}

void Validator::validateEventDescription(const std::string& description)
{
    if (description.length() == 0)
        throw ValidatorException("  Input error: description of event cannot be empty!");
}

void Validator::validateEventDay(const std::string& day)
{
    if (day.length() == 0)
        throw ValidatorException("  Input error: day of event cannot be empty!");

    int isint = Validator::isInteger(day);
    if (isint == -1)
        throw ValidatorException("  Input error: day of event must be an integer between 1 and 30!");

    int dayy = stoi(day);
    if (dayy < 1 || dayy > 30)
        throw ValidatorException("  Input error: day of event must be an integer between 1 and 30!");
}

void Validator::validateEventMonth(const std::string& month)
{
    if (month.length() == 0)
        throw ValidatorException("  Input error: month of event cannot be empty!");

    int isint = Validator::isInteger(month);
    if (isint == -1)
        throw ValidatorException("  Input error: month of event must be an integer between 1 and 12!");

    int monthh = stoi(month);
    if (monthh < 0 || monthh > 12)
        throw ValidatorException("  Input error: month of event must be an integer between 1 and 12!");
}

void Validator::validateEventYear(const std::string& year)
{
    if (year.length() == 0)
        throw ValidatorException("  Input error: year of event cannot be empty!");

    int isint = Validator::isInteger(year);
    if (isint == -1)
        throw ValidatorException("  Input error: year of event must be an integer between 2000 and 2100!");

    int yearr = stoi(year);
    if (yearr < 2000 || yearr > 2100)
        throw ValidatorException("  Input error: year of event must be an integer between 2000 and 2100!");
}

void Validator::validateEventHour(const std::string& hour)
{
    if (hour.length() == 0)
        throw ValidatorException("  Input error: hour of event cannot be empty!");

    int isint = Validator::isInteger(hour);
    if (isint == -1)
        throw ValidatorException("  Input error: hour of event must be an integer between 0 and 23!");

    int hourr = stoi(hour);
    if (hourr < 0 || hourr > 23)
        throw ValidatorException("  Input error: hour of event must be an integer between 0 and 23!");
}

void Validator::validateEventMinutes(const std::string& minutes)
{
    if (minutes.length() == 0)
        throw ValidatorException("  Input error: minutes of event cannot be empty!");

    int isint = Validator::isInteger(minutes);
    if (isint == -1)
        throw ValidatorException("  Input error: minutes of event must be an integer between 0 and 59!");

    int minutess = stoi(minutes);
    if (minutess < 0 || minutess > 59)
        throw ValidatorException("  Input error: minutes of event must be an integer between 0 and 59!");
}

void Validator::validateEventNrOfPeople(const int& numberOfPeople)
{
    if (numberOfPeople == -32768)
        throw ValidatorException("  Input error: number of people attending the event cannot be empty!");

    if (numberOfPeople < 0)
        throw ValidatorException("  Input error: number of people attending the event must be a positive integer!");
}

void Validator::validateEventLink(const std::string& link)
{
    if (link.length() == 0)
        throw ValidatorException("  Input error: title of event cannot be empty!");
}

int Validator::isInteger(const std::string& s)
{
    int i;
    for (i = 0; i < s.length(); i++)
    {
        if (i == 0 && isdigit(s[i]) == false && s[i] == '-')
            continue;
        if (isdigit(s[i]) == false)
            return -1;
    }

    return stoi(s);
}

void Validator::validateTitleDate(const std::string& title, const std::string& date)
{
    std::string exception = "";
    try {
        validateEventTitle(title);
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
        exception += "\n";
    }
    try {
        validateEventDate(date);
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
        exception += "\n";
    }
    if (exception != "")
        throw ValidatorException(exception);
}

void Validator::validateEventDate(const std::string& date)
{
    std::string exception = "";

    char* p;
    char str[11] = "";
    strcpy(str, date.c_str());
    p = strtok(str, "/");
    int counter = 0, val = 0;
    while (p)
    {
        counter++;
        val = atoi(p);
        if (counter == 1)
        {
            if (val < 1 || val > 30)
                exception += "  Input error: day of event must be an integer between 1 and 30!";
        }
        else
            if (counter == 2)
            {
                if (val < 0 || val > 12)
                    exception += "  Input error: month of event must be an integer between 1 and 12!";
            }
            else
                if (counter == 3)
                {
                    if (val < 2000 || val > 2100)
                        exception += "  Input error: year of event must be an integer between 2000 and 2100!";
                }
                else
                    exception += "  Input error: invalid date format!";
        p = strtok(nullptr, "/");
    }
    if (exception != "")
        throw ValidatorException(exception);
}

void Validator::validateEventTime(const std::string& time)
{
    std::string exception = "";

    char* p;
    char str[11] = "";
    strcpy(str, time.c_str());
    p = strtok(str, ":");
    int counter = 0, val = 0;
    while (p)
    {
        counter++;
        val = atoi(p);
        if (counter == 1)
        {
            if (val < 0 || val > 23)
                exception += "  Input error: hour of event must be an integer between 0 and 23!";
        }
        else
            if (counter == 2)
            {
                if (val < 0 || val > 59)
                    exception += "  Input error: minutes of event must be an integer between 0 and 59!";
            }
            else
                exception += "  Input error: invalid time format!";
        p = strtok(nullptr, ":");
    }
    if (exception != "")
        throw ValidatorException(exception);
}

void Validator::validateDate(std::string& day, std::string& month, std::string& year)
{
    std::string exception = "";
    try {
        validateEventDay(day);
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
        exception += "\n";
    }
    try {
        validateEventMonth(month);
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
        exception += "\n";
    }
    try {
        validateEventYear(year);
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
    }
    if (exception != "")
        throw ValidatorException(exception);
}

void Validator::validateTime(std::string& hour, std::string& minutes)
{
    std::string exception = "";
    try {
        validateEventHour(hour);
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
        exception += "\n";
    }
    try {
        validateEventMinutes(minutes);
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
        exception += "\n";
    }

    if (exception != "")
        throw ValidatorException(exception);
}