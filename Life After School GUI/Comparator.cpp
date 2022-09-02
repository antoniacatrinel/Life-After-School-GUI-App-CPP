#include "Comparator.h"
#include "InmemoryRepository.h"
#include <vector>
#include <algorithm>
#include <assert.h>

bool CompareDescendingByNumberOfPeople::compare(Event t1, Event t2)
{
	return t1.getNumberOfPeople() > t2.getNumberOfPeople();
}

bool CompareAscendingByTitle::compare(Event t1, Event t2)
{
	return t1.getTitle().compare(t2.getTitle()) < 0;
}
