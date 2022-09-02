#pragma once

#include <string>
#include <vector>
#include <iostream>

class Event {

private:
    std::string title;
    std::string description;
    std::string date;
    std::string time;
    int numberOfPeople;
    std::string link;

public:
    /// <summary>
    /// Default constructor for Event class
    /// </summary>
    Event();

    /// <summary>
    /// Copy constructor for Event class
    /// </summary>
    /// <param name="title">title of the event</param>
    /// <param name="description">description of the event</param>
    /// <param name="date">date of the event</param>
    /// <param name="time">title of the event</param>
    /// <param name="numberOfPeople">number of people attending the event</param>
    /// <param name="link">link to the event</param>
    Event(const std::string& title, const std::string& description, const std::string& date, const std::string& time, int numberOfPeople, const std::string& link);

    /// <summary>
    /// Returns the title of an event
    /// </summary>
    std::string getTitle() const { return this->title; }

    /// <summary>
    /// Returns the description of an event
    /// </summary>
    std::string getDescription() const { return this->description; }

    /// <summary>
    /// Returns the date of an event
    /// </summary>
    std::string getDate() const { return this->date; }

    /// <summary>
    /// Returns the time of an event
    /// </summary>
    std::string getTime() const { return this->time; }

    /// <summary>
    /// Returns the number of people attending an event
    /// </summary>
    int getNumberOfPeople() const { return this->numberOfPeople; }

    /// <summary>
    /// Returns the link to an event
    /// </summary>
    std::string getLink() const { return this->link; }

    /// <summary>
    /// Sets the title of an event
    /// </summary>
    void setTitle(const std::string& newTitle) { this->title = newTitle; }

    /// <summary>
    /// Sets the description of an event
    /// </summary>
    void setDescription(const std::string& newDescription) { this->description = newDescription; }

    /// <summary>
    /// Sets the date of an event
    /// </summary>
    void setDate(const std::string& newDate) { this->date = newDate; }

    /// <summary>
    /// Sets the time of an event
    /// </summary>
    void setTime(const std::string& newTime) { this->time = newTime; }

    /// <summary>
    /// Sets the number of people attending an event
    /// </summary>
    void setNumberOfPeople(const int newNumber) { this->numberOfPeople = newNumber; }

    /// <summary>
    /// Sets the link to an event
    /// </summary>
    void setLink(const std::string& newLink) { this->link = newLink; }

    /// <summary>
    /// Returns the string representation of an event
    /// </summary>
    std::string toString();

    /// <summary>
    /// Overloads of the == operator between 2 events
    /// </summary>
    /// <param name="e1">first event</param>
    /// <param name="e2">second event</param>
    /// <returns> true if e1==e2
    ///           false otherwise</returns>
    friend bool operator==(const Event& e1, const Event& e2) {
        bool equal = e1.getTitle() == e2.getTitle();
        equal &= e1.getDescription() == e2.getDescription();
        equal &= e1.getDate() == e2.getDate();
        equal &= e1.getTime() == e2.getTime();
        equal &= e1.getNumberOfPeople() == e2.getNumberOfPeople();
        equal &= e1.getLink() == e2.getLink();

        return equal;
    }

    /// <summary>
    /// Overloads of the insertion >> operator 
    /// </summary>
    friend std::istream& operator>>(std::istream& is, Event& e);
    
    /// <summary>
    /// Overloads of the extraction << operator 
    /// </summary>
    friend std::ostream& operator<<(std::ostream& os, const Event& e);

private:

    /// <summary>
    /// Tokenizes a string given a separator
    /// </summary>
    std::vector<std::string> tokenize(const std::string& str, char separator);
};
