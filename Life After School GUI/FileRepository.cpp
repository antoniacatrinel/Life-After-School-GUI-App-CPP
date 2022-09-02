#include "FileRepository.h"
#include <string>
#include <fstream>

FileRepository::FileRepository(std::string filename) : Repository{}
{
    this->filename = filename;
    this->readFromFile();
}

FileRepository::~FileRepository() {
}

void FileRepository::readFromFile()
{
    std::ifstream file{ this->filename };

    if (!file.is_open())
        throw FileException("File error : file could not be opened!");

    Event e;
    while (file >> e)
    {
        this->events.push_back(e);
    }

    file.close();
}

void FileRepository::writeToFile()
{
    std::ofstream file(this->filename);

    if (!file.is_open())
        throw FileException("File error : file could not be opened!");

    for (const auto& ev : this->events)
        file << ev;

    file.close();
}


int FileRepository::searchByTitleDate(const std::string& title, const std::string& date)
{
    return Repository::searchByTitleDate(title, date);
}

void FileRepository::addEvent(const Event& elem)
{
    Repository::addEvent(elem);
    this->writeToFile();
}

void FileRepository::deleteEvent(const std::string& title, const std::string& date)
{
    Repository::deleteEvent(title, date);
    this->writeToFile();
}

void FileRepository::updateEvent(const Event& oldElem, const Event& newElem)
{
    Repository::updateEvent(oldElem, newElem);
    this->writeToFile();
}