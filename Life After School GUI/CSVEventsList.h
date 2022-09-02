#pragma once

#include <string>
#include <vector>
#include "Domain.h"
#include "Exceptions.h"
#include "RepositoryUser.h"

class CSVEventsList : public RepositoryUser {

public:
	/// <summary>
	/// Constructor for CSVEventsList class
	/// </summary>
	CSVEventsList();

	/// <summary>
	/// Destructor for CSVEventsList class
	/// </summary>
	~CSVEventsList();

	/// <summary>
	/// Overrides the write to file function from the repository
	/// </summary>
	void writeToFile() override;
	
	/// <summary>
	/// Overrides the open in app function
	/// </summary>
	void openInApp() override;
};
