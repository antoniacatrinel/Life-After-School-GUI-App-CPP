#pragma once

#include "Exceptions.h"
#include <vector>
#include "Domain.h"

class Validator {
public:
    /// <summary>
    /// Validates the user command
    /// </summary>
    static void validateUserCommand(std::string& input);

    /// <summary>
    /// Validates the all fields of an event
    /// </summary>
    static void validateEvent(const Event& e);

    /// <summary>
    /// Validates the title and date of an event
    /// </summary>
    static void validateTitleDate(const std::string& title, const std::string& date);

    /// <summary>
    /// Validates the event date
    /// </summary>
    static void validateEventDate(const std::string& date);
    
    /// <summary>
    /// Validates the event time
    /// </summary>
    static void validateEventTime(const std::string& time);

    /// <summary>
    /// Validates the date by day, month and year
    /// </summary>
    static void validateDate(std::string& day, std::string& month, std::string& year);
    
    /// <summary>
    /// Validates the time in hours and minutes
    /// </summary>
    static void validateTime(std::string& hour, std::string& minutes);

    /// <summary>
    /// Validates the event title
    /// </summary>
    static void validateEventTitle(const std::string& title);

    /// <summary>
    /// Validates the event description
    /// </summary>
    static void validateEventDescription(const std::string& description);

    /// <summary>
    /// Validates the event day
    /// </summary>
    static void validateEventDay(const std::string& day);

    /// <summary>
    /// Validates the event month
    /// </summary>
    static void validateEventMonth(const std::string& month);

    /// <summary>
    /// Validates the event year
    /// </summary>
    static void validateEventYear(const std::string& year);

    /// <summary>
    /// Validates the event time hour
    /// </summary>
    static void validateEventHour(const std::string& hour);

    /// <summary>
    /// Validates the event time minutes
    /// </summary>
    static void validateEventMinutes(const std::string& minutes);

    /// <summary>
    /// Validates the event number of people
    /// </summary>
    static void validateEventNrOfPeople(const int& numberOfPeople);

    /// <summary>
    /// Validates the event link
    /// </summary>
    static void validateEventLink(const std::string& link);

    /// <summary>
    /// Checks if input is integer
    /// </summary>
    static int isInteger(const std::string& s);
};
