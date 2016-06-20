#include "TableResult.h"
using namespace project;

// constructor : Initialization TableResult based on the Course list
TableResult::TableResult(Vec<Course> _ctb)
{
	for (auto crs : _ctb) {
		calList.addCrs(crs);
	}
	execute.resize(calList.sub_list.size());
}
// Converting time information in the index
int TableResult::get_idx(const int& _i, const int& _w)
{
	return (_i / 5 - 1) + ((_w - 1) * 27);
};

// CreateTableList : All procedures that produce a timetable
void TableResult::CreateTableList()
{
	std::cout << "# Operation Start" << std::endl;
	int i = 0;
	while (true)
	{
		CreateTable();
		if (ExecuteMaxCheck())
			break;
		NextExecute();
	}
	std::cout << "# Operation End" << std::endl;
}

// CreateTable  : Produce one timetable
void TableResult::CreateTable()
{
	bmap.reset();
	CrsTable<Course> ctb;

	for (int i = 0; i<calList.sub_list.size(); ++i)
	{
		Course crs = calList.sub_list[i].crs_list[execute[i]];
		if (execute[i]>0 && TimeCal(crs))
		{
			ctb.append(crs);
		}
	}
	if (OverloadCheck(ctb))
	{
		table_list.push_back(ctb);

		std::sort(table_list.begin(), table_list.end(), 
			[](const CrsTable<Course>& _lhs, const CrsTable<Course>& _rhs)->bool
		{
			return _rhs.total_point() < _lhs.total_point() ;
		});
	}
}

// TimeCal  : Check course can put in timetable
bool TableResult::TimeCal(const Course& _course)
{
	int s;
	for (int i = 0; i<_course.times.size(); ++i)
	{
		s = get_idx(_course.times[i].start().clock, _course.times[i].day());
		while (s < get_idx(_course.times[i].end().clock, _course.times[i].day()))
		{
			if (!bmap[s])
			{
				bmap.set(s);
				++s;
			}
			else
			{
				--s;
				while (s > get_idx(_course.times[i].start().clock, _course.times[i].day()) - 1)
				{
					bmap.reset(s);
					--s;
				}
				if (i != 0)
				{
					for (int j = i - 1; j >= 0; --j)
					{
						s = get_idx(_course.times[i].end().clock, _course.times[i].day()) - 1;
						while (s > (get_idx(_course.times[i].start().clock, _course.times[i].day()) - 1))
						{
							bmap.reset(s);
							--s;
						}
					}
				}return false;
			}
		}
	}return true;
}

// Function to check if the results do not exceed
bool TableResult::OverloadCheck(const CrsTable<Course>& _ctb)
{
	if (table_list.size() < TABLE_MAX)
		return true;
	if (table_list[table_list.size() - 1].total_point() < _ctb.total_point())
	{
		table_list.pop_back();
		return true;
	}
	return false;
}

// Check if all case have investigated
bool TableResult::ExecuteMaxCheck()
{
	for (int i = 0; i<execute.size(); ++i)
	{
		if (execute[i]<(calList.sub_list[i].crs_list.size()-1))
			return false;
	}
	return true;
}
// Function for the next operation
void TableResult::NextExecute()
{
	int count = calList.sub_list.size() - 1;
	while (count >= 0) {
		if (execute[count] + 1< calList.sub_list[count].crs_list.size())
		{
			++execute[count];
			return;
		}
		else
		{
			execute[count] = 0;
			--count;
		}
	}
}