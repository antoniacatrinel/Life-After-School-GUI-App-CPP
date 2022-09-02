#include "HTMLEventsList.h"
#include <fstream>
#include <string>
#include <Windows.h>
#include <shellapi.h>

HTMLEventsList::HTMLEventsList()
{
}

HTMLEventsList::~HTMLEventsList()
{
}

void HTMLEventsList::writeToFile()
{
	std::ofstream outFile{ "events.html" };
	if (!outFile.is_open())
		throw FileException("File error : HTML file could not be opened!");

	outFile << "<!DOCTYPE html>" << std::endl;
	outFile << "<html>" << std::endl;
	outFile << "<head><title>Events list</title></head>" << std::endl;
	outFile << "<body style = \"background-color:green;\"><table border=\"1\">" << std::endl;

	outFile << "<tr>" << std::endl;
	outFile << "<td>Title</td>" << std::endl;
	outFile << "<td>Description</td>" << std::endl;
	outFile << "<td>Date</td>" << std::endl;
	outFile << "<td>Time</td>" << std::endl;
	outFile << "<td>Number of people</td>" << std::endl;
	outFile << "<td>Link" << std::endl;
	outFile << "</tr>" << std::endl;

	for (auto& event : this->userEventsList) {
		outFile << "<tr>" << std::endl;
		outFile << "<td>" << event.getTitle() << "</td>" << std::endl;
		outFile << "<td>" << event.getDescription() << "</td>" << std::endl;
		outFile << "<td>" << event.getDate() << "</td>" << std::endl;
		outFile << "<td>" << event.getTime() << "</td>" << std::endl;
		outFile << "<td>" << event.getNumberOfPeople() << "</td>" << std::endl;
		outFile << "<td>" << event.getLink() << "</td>" << std::endl;
		outFile << "</tr>" << std::endl;
	}
	outFile << "</table>" << std::endl;
	outFile << "</body>" << std::endl;
	outFile << "</html>" << std::endl;
	outFile.close();
}

void HTMLEventsList::openInApp()
{
	system("start events.html");
	// or ShellExecuteA(NULL, NULL, "C:\\Program Files(x86)\\Microsoft\\Edge\\Application\\msedge.exe", "events.html", NULL, SW_SHOWMAXIMIZED);
}
