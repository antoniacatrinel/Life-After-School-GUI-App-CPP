#pragma once

#include "InmemoryRepository.h"
#include "RepositoryUser.h"
#include "FileRepository.h"
#include "Validation.h"
#include "Action.h"
#include <memory>
#include <vector>

class Service {

private:
    //Repository& repo;  -> when using inmemory repo
    RepositoryUser* repoUser;
    FileRepository& repo;
    Validator& validator;

    std::vector<std::unique_ptr<Action>> undoStack;
    std::vector<std::unique_ptr<Action>> redoStack;

public:
    /// <summary>
    /// Constructor for Service class
    /// </summary>
    /// <param name="r">file admin repo</param>
    /// <param name="ur">user repo</param>
    /// <param name="valid">validator</param>
    explicit Service(FileRepository& r, RepositoryUser* ur, Validator& valid);

    /// <summary>
    /// Returns the repository inside the service class
    /// </summary>
    FileRepository& getRepo() { return this->repo; }

    /// <summary>
    /// Finds an even based on title and date
    /// </summary>
    /// <param name="title">title of the event</param>
    /// <param name="date">date of the event</param>
    Event findByTitleDate(const std::string& title, const std::string& date);

    /// <summary>
    /// Adds a new event to the repository
    /// </summary>
    /// <param name="title">title of the event</param>
    /// <param name="description">description of the event</param>
    /// <param name="date">date of the event</param>
    /// <param name="time">time of the event</param>
    /// <param name="numberOfPeople">number of people of the event</param>
    /// <param name="link">link of the event</param>
    void addEventService(const std::string& title, const std::string& description, const std::string& date, const std::string& time, int numberOfPeople, const std::string& link);

    /// <summary>
    /// Deletes an event from the repository
    /// </summary>
    /// <param name="title">title of the event</param>
    /// <param name="date">date of the event</param>
    void deleteEventService(const std::string& title, const std::string& date);

    /// <summary>
    /// Updates an event from the repository
    /// </summary>
    /// <param name="oldElem">old event</param>
    /// <param name="newElem">new event</param>
    void updateEventService(const std::string& oldtitle, const std::string& olddate, const std::string& title, const std::string& description, const std::string& date, const std::string& time, int numberOfPeople, const std::string& link);

    /// <summary>
    /// Returns the user repository inside the service class
    /// </summary>
    RepositoryUser* getUserRepo() { return this->repoUser; }

    /// <summary>
    /// Filters repository by month of event
    /// </summary>
    /// <param name="month">month to filter</param>
    std::vector<Event> filterRepoByMonth(int month);

    /// <summary>
    /// Filters repository by title of event
    /// </summary>
    /// <param name="title">title to filter</param>
    std::vector<Event> filterRepoByTitle(const std::string& title);

    /// <summary>
    /// Sorts the repository chronologically by date 
    /// </summary>
    /// <param name="r">vector of events</param>
    static void sortRepoByDate(std::vector<Event>& r);

    /// <summary>
    /// Parse user's events list
    /// </summary>
    /// <param name="month">month to parse</param>
    std::vector<Event> parseUserEvents(std::string month);

    /// <summary>
    /// Adds a new event to the user repository
    /// </summary>
    /// <param name="e">event</param>
    void addEventToUserList(const Event& e);

    /// <summary>
    /// Deletes an event from the user repository
    /// </summary>
    /// <param name="title">title of the event</param>
    /// <param name="date">date of the event</param>
    void deleteEventUserService(const std::string& title, const std::string& date);

    /// <summary>
    /// Undoes the last performed operation
    /// </summary>
    void undo();

    /// <summary>
    /// Redoes the last performed operation
    /// </summary>
    void redo();

    /// <summary>
    /// Extracts the month from a date
    /// </summary>
    /// <param name="date">date</param>
    static int getMonth(const std::string& date);

    /// <summary>
    /// Compares the dates of 2 events
    /// </summary>
    /// <param name="event1">first event</param>
    /// <param name="event2">second event</param>
    static bool compareDates(const Event& event1, const Event& event2);
};
