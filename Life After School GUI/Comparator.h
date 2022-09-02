#pragma once

#include "Domain.h"

template <class TElem>
class Comparator
{
public:
	virtual bool compare(TElem t1, TElem t2) = 0;
};


/// <summary>
/// Compares 2 events by title
/// </summary>
/// <param name="t1">first event</param>
/// <param name="t2">second event</param>
/// <returns> true if the two events are sorted ascending by title
///			  false, otherwise</returns>
class CompareAscendingByTitle : public Comparator<Event> {
	bool compare(Event t1, Event t2) override;
};

/// <summary>
/// Compares 2 events by number of people attending the event
/// </summary>
/// <param name="t1">first event</param>
/// <param name="t2">second event</param>
/// <returns> true if the two events are sorted descending by number of people
///			  false, otherwise</returns>
class CompareDescendingByNumberOfPeople : public Comparator<Event> {
	bool compare(Event t1, Event t2) override;
};

/// <summary>
/// Sorts a STL vector using the comparator
/// </summary>
template <typename TElem>
void genericSort(std::vector<TElem>& v, Comparator<Event>* compare)
{
	int i;
	bool sorted;
	do
	{
		sorted = true;
		for (i = 0; i < v.size() - 1; i++)
		{
			if (!compare->compare(v[i], v[i + 1]))
			{
				TElem aux;
				aux = v[i + 1];
				v[i + 1] = v[i];
				v[i] = aux;
				sorted = false;
			}
		}
	} while (sorted == false);
}
