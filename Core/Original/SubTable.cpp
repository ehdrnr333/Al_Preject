#include "SubTable.h"
using namespace project;
// SubTable constructor
SubTable::SubTable()
{
	crs_sum = 0;
}

// addCrs : insert course into subjects such as same code
void SubTable::addCrs(Course& _c)
{
	Course copy = _c;
	++crs_sum;
	int i;
	int size = sub_list.size();

	// Touring all subjects
	for (i = 0; i < size; ++i)
	{
		// If code is same, insert course to this subject
		if (sub_list[i].code==_c.code())
		{
			sub_list[i].crs_list.push_back(copy);
			return;
		}
	}
	Subject s(copy);
	sub_list.push_back(s);
}