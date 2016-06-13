#include "SubTable.h"
using namespace project;
SubTable::SubTable()
{
	crs_sum = 0;
}

void SubTable::addCrs(Course _c)
{
	Course copy = _c;
	++crs_sum;
	int i;
	for (i = 0; i < sub_list.size(); ++i)
	{
		if (sub_list[i].code==_c.code())
		{
			sub_list[i].crs_list.push_back(copy);
			return;
		}
	}
	Subject s(copy);
	sub_list.push_back(s);
}