#pragma once

#include <string>
#include <vector>
#include "Domain.h"
#include "Exceptions.h"
#include "RepositoryUser.h"

class HTMLEventsList : public RepositoryUser {

public:
	/// <summary>
	/// Constructor for HTMLEventsList class
	/// </summary>
	HTMLEventsList();

	/// <summary>
	/// Destructor for HTMLEventsList class
	/// </summary>
	~HTMLEventsList();

	/// <summary>
	/// Overrides the write to file function from the repository
	/// </summary>
	void writeToFile() override;
	
	/// <summary>
	/// Overrides the open in app function
	/// </summary>
	void openInApp() override;
};
