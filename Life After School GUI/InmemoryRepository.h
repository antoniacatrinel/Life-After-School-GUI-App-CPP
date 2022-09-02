#pragma once

#include "Domain.h"
#include <vector>
#include <algorithm>
#include "Exceptions.h"

class Repository {

protected:
    std::vector<Event> events;

public:
    /// <summary>
    /// Default constructor for Repository class
    /// </summary>
    Repository() = default;

    /// <summary>
    /// Destructor for Repository class
    /// </summary>
    virtual ~Repository() = default;

    /// <summary>
    /// Returns the number of events from the repo
    /// </summary>
    virtual int getRepoSize() const { return (int)this->events.size(); }

    /// <summary>
    /// Returns the vector of events from the repo
    /// </summary>
    virtual std::vector<Event>& getEvents() { return this->events; }

    /// <summary>
    /// Finds position of an event based on title and date
    /// </summary>
    /// <param name="title">title of the event</param>
    /// <param name="date">date of the event</param>
    /// <returns> position of the searched event
    ///           -1 in case of nonexistent event </returns>
    virtual int searchByTitleDate(const std::string& title, const std::string& date);

    /// <summary>
    /// Adds an event to the repository
    /// </summary>
    /// <param name="elem">new event</param>
    virtual void addEvent(const Event& elem);

    /// <summary>
    /// Deletes an event from the repository
    /// </summary>
    /// <param name="title">title of the event</param>
    /// <param name="date">date of the event</param>
    virtual void deleteEvent(const std::string& title, const std::string& date);

    /// <summary>
    /// Updates an event from the repository
    /// </summary>
    /// <param name="oldElem">old event</param>
    /// <param name="newElem">new event</param>
    virtual void updateEvent(const Event& oldElem, const Event& newElem);

};

/// <summary>
/// Overloads the + operator: adds a new event to a STL vector of events
/// </summary>
inline std::vector<Event> operator+(std::vector<Event>& evs, const Event& e)
{
    evs.push_back(e);
    return evs;
}

/// <summary>
/// Overloads the + operator: adds a new event to a STL vector of events
/// </summary>
inline std::vector<Event> operator+(const Event& e, std::vector<Event>& evs)
{
    evs.push_back(e);
    return evs;
}

/// <summary>
/// Overloads the - operator: deletes an event from a STL vector of events
/// </summary>
inline std::vector<Event> operator-(std::vector<Event>& evs, const Event& e)
{
    evs.erase(remove(evs.begin(), evs.end(), e), evs.end());
    return evs;
}
