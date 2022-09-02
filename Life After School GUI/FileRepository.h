#pragma once

#include <string>
#include <vector>
#include "InmemoryRepository.h"
#include "Exceptions.h"

class FileRepository : public Repository {

protected:
    std::string filename;

public:
    /// <summary>
    /// Constructor for FileRepository class
    /// </summary>
    /// <param name="filename">path to file</param>
    FileRepository(std::string filename);

    /// <summary>
    /// Destructor for FileRepository class
    /// </summary>
    ~FileRepository() override;

    /// <summary>
    /// Reads everything from file and populates the repo
    /// </summary>
    void readFromFile();

    /// <summary>
    /// Writes everything to file
    /// </summary>
    void writeToFile();

    /// <summary>
    /// Finds position of an event based on title and date
    /// </summary>
    /// <param name="title">title of the event</param>
    /// <param name="date">date of the event</param>
    /// <returns> position of the searched event
    ///           -1 in case of nonexistent event </returns>
    int searchByTitleDate(const std::string& title, const std::string& date) override;

    /// <summary>
    /// Adds an event to the repository
    /// </summary>
    /// <param name="elem">new event</param>
    void addEvent(const Event& elem) override;

    /// <summary>
    /// Deletes an event from the repository
    /// </summary>
    /// <param name="title">title of the event</param>
    /// <param name="date">date of the event</param>
    void deleteEvent(const std::string& title, const std::string& date) override;

    /// <summary>
    /// Updates an event from the repository
    /// </summary>
    /// <param name="oldElem">old event</param>
    /// <param name="newElem">new event</param>
    void updateEvent(const Event& oldElem, const Event& newElem) override;
};

