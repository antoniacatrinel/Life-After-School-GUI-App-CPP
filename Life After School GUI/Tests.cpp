#include "Service.h"
#include "Tests.h"
#include "Validation.h"
#include <cassert>
#include <stdexcept>
#include <iostream>
#include "Comparator.h"
#include <crtdbg.h>

void Tests::test_genericSort()
{
    Event e{ "festival", "cluj-napoca", "13/09/2022", "18:00", 234, "https" };
    Event e1{ "marathon", "timisoara", "16/10/2023", "10:00", 5000, "url" };
    Event e2{ "concert", "iasi", "19/11/2023", "10:00", 3400, "url" };
    Repository repo{};
    repo.addEvent(e);
    repo.addEvent(e1);
    repo.addEvent(e2);
    Comparator<Event>* compare1 = new CompareAscendingByTitle;
    Comparator<Event>* compare2 = new CompareDescendingByNumberOfPeople;

    assert(repo.getEvents()[0].getTitle() == "festival");
    assert(repo.getEvents()[1].getTitle() == "marathon");
    assert(repo.getEvents()[2].getTitle() == "concert");
    genericSort(repo.getEvents(), compare1);
    assert(repo.getEvents()[0].getTitle() == "concert");
    assert(repo.getEvents()[1].getTitle() == "festival");
    assert(repo.getEvents()[2].getTitle() == "marathon");

    assert(repo.getEvents()[0].getNumberOfPeople() == 3400);
    assert(repo.getEvents()[1].getNumberOfPeople() == 234);
    assert(repo.getEvents()[2].getNumberOfPeople() == 5000);
    genericSort(repo.getEvents(), compare2);
    assert(repo.getEvents()[0].getNumberOfPeople() == 5000);
    assert(repo.getEvents()[1].getNumberOfPeople() == 3400);
    assert(repo.getEvents()[2].getNumberOfPeople() == 234);

    delete compare1;
    delete compare2;
}

void Tests::test_domain()
{
    Event e{ "festival", "cluj-napoca", "13/09/2022", "18:00", 15000, "https" };

    assert(e.getTitle() == "festival");
    assert(e.getDescription() == "cluj-napoca");
    assert(e.getTime() == "18:00");
    assert(e.getLink() == "https");
    assert(e.getNumberOfPeople() == 15000);
    assert(e.getDate() == "13/09/2022");

    e.setTitle("marathon");
    e.setDescription("timisoara");
    e.setDate("16/10/2023");
    e.setTime("10:00");
    e.setNumberOfPeople(5000);
    e.setLink("url");

    assert(e.getTitle() == "marathon");
    assert(e.getDescription() == "timisoara");
    assert(e.getTime() == "10:00");
    assert(e.getLink() == "url");
    assert(e.getNumberOfPeople() == 5000);
    assert(e.getDate() == "16/10/2023");

    std::string str = e.toString();
    assert(str.length() != 0);

    Event e1{};
}

void Tests::test_repository()
{
    Repository r;
    assert(r.getRepoSize() == 0);
    Event e{ "festival", "cluj-napoca", "13/09/2022", "18:00", 15000, "https" };
    r.addEvent(e);
    assert(r.getRepoSize() == 1);
    try {
        r.addEvent(e);
    }
    catch (RepositoryException& rerr)
    {
        assert(rerr.what() == "Repository error: this event already exists!");
    }

    assert(r.searchByTitleDate("aaa", "12/12/2012") == -1);
    assert(r.searchByTitleDate("festival", "13/09/2022") == 0);

    try {
        r.deleteEvent("aaa", "12/12/2012");
    }
    catch (RepositoryException& rerr)
    {
        assert(rerr.what() == "Repository error: nonexistent event!");
    }
    r.deleteEvent("festival", "13/09/2022");
    assert(r.getRepoSize() == 0);

    Event e1{ "marathon", "timisoara", "16/10/2023", "10:00", 5000, "url" };
    Event e2{};
    r.addEvent(e);
    assert(r.getRepoSize() == 1);
    assert(r.getEvents()[0].getTitle() == "festival");
    assert(r.getEvents()[0].getDescription() == "cluj-napoca");
    assert(r.getEvents()[0].getTime() == "18:00");
    assert(r.getEvents()[0].getLink() == "https");
    assert(r.getEvents()[0].getNumberOfPeople() == 15000);
    assert(r.getEvents()[0].getDate() == "13/09/2022");

    assert(r.searchByTitleDate(e1.getTitle(), e1.getDate()) == -1);
    r.updateEvent(e, e1);
    try {
        r.updateEvent(e2, e1);
    }
    catch (RepositoryException& rerr)
    {
        assert(rerr.what() == "Repository error: nonexistent event!");
    }

    assert(r.getEvents()[0].getTitle() == "marathon");
    assert(r.getEvents()[0].getDescription() == "timisoara");
    assert(r.getEvents()[0].getTime() == "10:00");
    assert(r.getEvents()[0].getLink() == "url");
    assert(r.getEvents()[0].getNumberOfPeople() == 5000);
    assert(r.getEvents()[0].getDate() == "16/10/2023");
}

void Tests::test_user_repository()
{
    RepositoryUser* r;
    assert(r->getUserEvents().size() == 0);
    Event e{ "festival", "cluj-napoca", "13/09/2022", "18:00", 22, "https" };
    r->addUserEvent(e);
    assert(r->getRepoSize() == 1);

    try {
        r->addUserEvent(e);
    }
    catch (RepositoryException& rerr)
    {
        assert(rerr.what() == "Repository error: this event already exists!");
    }

    assert(r->getUserEvents().size() == 1);
    assert(r->searchByTitleDate("festival", "13/09/2022") == 0);
    assert(r->searchByTitleDate("aaa", "12/12/2012") == -1);

    try {
        r->deleteUserEvent("aaa", "12/12/2012");
    }
    catch (RepositoryException& rerr)
    {
        assert(rerr.what() == "Repository error: nonexistent event!");
    }
    r->deleteUserEvent("festival", "13/09/2022");
    assert(r->getUserEvents().size() == 0);

    Event e1{ "marathon", "timisoara", "16/10/2023", "10:00", 5000, "url" };
    Event e2{};
    r->addUserEvent(e);
    assert(r->getUserEvents().size() == 1);

    assert(r->getUserEvents()[0].getTitle() == "festival");
    assert(r->getUserEvents()[0].getDescription() == "cluj-napoca");
    assert(r->getUserEvents()[0].getTime() == "18:00");
    assert(r->getUserEvents()[0].getLink() == "https");
    assert(r->getUserEvents()[0].getDate() == "13/09/2022");

    assert(r->searchByTitleDate(e1.getTitle(), e1.getDate()) == -1);
    r->updateUserEvent(e, e1);
    try {
        r->updateUserEvent(e2, e1);
    }
    catch (RepositoryException& rerr)
    {
        assert(rerr.what() == "Repository error: nonexistent event!");
    }

    assert(r->getUserEvents()[0].getTitle() == "marathon");
    assert(r->getUserEvents()[0].getDescription() == "timisoara");
    assert(r->getUserEvents()[0].getTime() == "10:00");
    assert(r->getUserEvents()[0].getLink() == "url");
    assert(r->getUserEvents()[0].getNumberOfPeople() == 5000);
    assert(r->getUserEvents()[0].getDate() == "16/10/2023");
}

void Tests::test_validation()
{
    Validator v;
    assert(v.isInteger("aaa") == -1);
    assert(v.isInteger("12") == 12);

    Validator::validateEventDay("12");
    Validator::validateEventNrOfPeople(1000);
    Validator::validateEventMonth("8");
    Validator::validateEventYear("2025");
    Validator::validateEventMinutes("18");
    Validator::validateEventHour("7");
    Validator::validateEventTitle("aaaa");
    Validator::validateEventLink("aaaa");
    Validator::validateEventDescription("aaaa");
    std::string input;
    try
    {
        Validator::validateUserCommand(input);
    }
    catch (ValidatorException& e)
    {
    }
    try
    {
        Validator::validateEventMinutes("90000");
    }
    catch (ValidatorException& e)
    {
    }
    try
    {
        Validator::validateEventYear("3000");
    }
    catch (ValidatorException& e)
    {
    }
    try
    {
        Validator::validateEventHour("9999");
    }
    catch (ValidatorException& e)
    {
    }
    try
    {
        Validator::validateEventDay("9000");
    }
    catch (ValidatorException& e)
    {
    }
    try
    {
        Validator::validateEventNrOfPeople(-89000);
    }
    catch (ValidatorException& e)
    {
    }
    try
    {
        Validator::validateEventMonth("390");
    }
    catch (ValidatorException& e)
    {
    }
    try
    {
        Validator::validateEventTitle("");
    }
    catch (ValidatorException& e)
    {
    }
    try
    {
        Validator::validateEventDescription("");
    }
    catch (ValidatorException& e)
    {
    }
    try
    {
        Validator::validateEventLink("");
    }
    catch (ValidatorException& e)
    {
    }
    try
    {
        Validator::validateEventHour("");
    }
    catch (ValidatorException& e)
    {
    }
    try
    {
        Validator::validateEventDay("");
    }
    catch (ValidatorException& e)
    {
    }
    try
    {
        Validator::validateEventMinutes("");
    }
    catch (ValidatorException& e)
    {
    }
    try
    {
        Validator::validateEventYear("");
    }
    catch (ValidatorException& e)
    {
    }
    try
    {
        Validator::validateEventMonth("");
    }
    catch (ValidatorException& e)
    {
    }
    try
    {
        Validator::validateEventHour("aaa");
    }
    catch (ValidatorException& e)
    {
    }
    try
    {
        Validator::validateEventDay("aaa");
    }
    catch (ValidatorException& e)
    {
    }
    try
    {
        Validator::validateEventMinutes("aaa");
    }
    catch (ValidatorException& e)
    {
    }
    try
    {
        Validator::validateEventYear("aaa");
    }
    catch (ValidatorException& e)
    {
    }
    try
    {
        Validator::validateEventMonth("aaa");
    }
    catch (ValidatorException& e)
    {
    }
    try
    {
        Validator::validateEventDay("89");
    }
    catch (ValidatorException& e)
    {
    }
    try
    {
        Validator::validateEventMinutes("90");
    }
    catch (ValidatorException& e)
    {
    }
    try
    {
        Validator::validateEventYear("2900");
    }
    catch (ValidatorException& e)
    {
    }
    try
    {
        Validator::validateEventMonth("13");
    }
    catch (ValidatorException& e)
    {
    }
    try
    {
        Validator::validateEventNrOfPeople(-5);
    }
    catch (ValidatorException& e)
    {
    }
}

void Tests::run_all_tests()
{
    Tests::test_domain();
    Tests::test_repository();
    Tests::test_user_repository();
    Tests::test_validation();

    std::cout << "All tests passed successfully!" << std::endl;
}