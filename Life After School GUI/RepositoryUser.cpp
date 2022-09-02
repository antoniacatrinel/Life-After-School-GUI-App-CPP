#include <algorithm>
#include "RepositoryUser.h"

int RepositoryUser::searchByTitleDate(const std::string& title, const std::string& date)
{
    std::vector<Event>::iterator it;
    it = std::find_if(this->userEventsList.begin(), this->userEventsList.end(), [&](const Event& x) { return x.getTitle() == title && x.getDate() == date; });

    if (it != this->userEventsList.end())
        return (int)(it - this->userEventsList.begin());  
    return -1;
}

void RepositoryUser::addUserEvent(const Event& elem)
{
    int position = searchByTitleDate(elem.getTitle(), elem.getDate());
    if (position != -1) 
        throw RepositoryException("Repository error: this event already exists!");

    this->userEventsList.push_back(elem);
}

void RepositoryUser::deleteUserEvent(const std::string& title, const std::string& date)
{
    int position = searchByTitleDate(title, date);
    if (position == -1)  
        throw RepositoryException("Repository error: nonexistent event!");

    if (position == 0)
        this->userEventsList.pop_back();
    else
    {
        std::vector<Event>::iterator it = this->userEventsList.begin() + position;
        this->userEventsList.erase(it);
    }
}

void RepositoryUser::updateUserEvent(const Event& oldElem, const Event& newElem)
{
    int position = searchByTitleDate(oldElem.getTitle(), oldElem.getDate());
    if (position == -1)  
        throw RepositoryException("Repository error: nonexistent event!");

    this->userEventsList[position].setTitle(newElem.getTitle());
    this->userEventsList[position].setDescription(newElem.getDescription());
    this->userEventsList[position].setDate(newElem.getDate());
    this->userEventsList[position].setTime(newElem.getTime());
    this->userEventsList[position].setNumberOfPeople(newElem.getNumberOfPeople());
    this->userEventsList[position].setLink(newElem.getLink());
}