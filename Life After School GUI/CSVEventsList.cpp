#include "CSVEventsList.h"
#include <fstream>
#include <string>
#include <Windows.h>

CSVEventsList::CSVEventsList()
{
}

CSVEventsList::~CSVEventsList()
{
}

void CSVEventsList::writeToFile()
{
    std::ofstream file("events.csv");

    if (!file.is_open())
        throw FileException("File error : CSV file could not be opened!");

    for (auto& ev : this->userEventsList)
        file << ev;

    file.close();
}

void CSVEventsList::openInApp()
{
    ShellExecuteA(NULL, NULL, "C:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.EXE", "events.csv", NULL, SW_SHOWMAXIMIZED);
    // or system("notepad.exe events.csv");
}
