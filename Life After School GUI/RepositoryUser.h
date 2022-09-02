#pragma once

#include <vector>
#include <algorithm>
#include "Domain.h"
#include "Exceptions.h"

class RepositoryUser {

protected:
    std::vector<Event> userEventsList;

public:
    /// <summary>
    /// Default constructor for RepositoryUser class
    /// </summary>
    RepositoryUser() = default;

    /// <summary>
    /// Destructor for Repository class
    /// </summary>
    virtual ~RepositoryUser() = default;

    /// <summary>
    /// Returns the number of events from the repo
    /// </summary>
    int getRepoSize() const { return (int)this->userEventsList.size(); }

    /// <summary>
    /// Returns the vector of events from the repo
    /// </summary>
    std::vector<Event>& getUserEvents() { return this->userEventsList; }

    /// <summary>
    /// Finds position of an event based on title and date
    /// </summary>
    /// <param name="title">title of the event</param>
    /// <param name="date">date of the event</param>
    /// <returns> position of the searched event
    ///           -1 in case of nonexistent event </returns>
    int searchByTitleDate(const std::string& title, const std::string& date);

    /// <summary>
    /// Adds an event to the repository
    /// </summary>
    /// <param name="elem">new event</param>
    void addUserEvent(const Event& elem);

    /// <summary>
    /// Deletes an event from the repository
    /// </summary>
    /// <param name="title">title of the event</param>
    /// <param name="date">date of the event</param>
    void deleteUserEvent(const std::string& title, const std::string& date);

    /// <summary>
    /// Updates an event from the repository
    /// </summary>
    /// <param name="oldElem">old event</param>
    /// <param name="newElem">new event</param>
    void updateUserEvent(const Event& oldElem, const Event& newElem);

    /// <summary>
    /// Overloads the [] operator: returns the event from position index fromt heSTL vector of events
    /// </summary>
    Event& operator[](int index) { return this->userEventsList[index]; }
    
    /// <summary>
    /// Abstract function for writing to file
    /// </summary>
    virtual void writeToFile() = 0;

    /// <summary>
    /// Abstract function for opening the list of events in app
    /// </summary>
    virtual void openInApp() = 0;
};
