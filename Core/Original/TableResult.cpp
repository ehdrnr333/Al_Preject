#include "TableResult.h"
using namespace project;

// TableResult 객체 초기화
TableResult::TableResult(CrsTable<Course> _ctb)
{
	map.resize(PERIOD_MAX);
	for (auto crs : _ctb) {
		calList.addCrs(crs);
	}
	execute.resize(calList.sub_list.size());
}

// 해당 시간에 위치한 맵의 인덱스 구하기
int TableResult::get_idx(const int& _i, const int& _w)
{
	return (_i / 5 - 1) + ((_w-1) * 27);
}

// 시간표 결과목록을 만드는 절차
void TableResult::CreateTableList()
{
	while (true)
	{
		CreateTable();
		if (ExecuteMaxCheck())
			break;
		NextExecute();
	}
}

// 하나의 시간표를 생성
void TableResult::CreateTable()
{
	ArrInit();
	CrsTable<Course> ctb;

	for (int i = 0; i<calList.sub_list.size(); ++i)
	{
		Course crs = calList.sub_list[i].crs_list[execute[i]];
		if (execute[i]>0 && TimeCal(crs))
		{
			ctb.crs_list.push_back(crs);
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

// 배열 초기화 작업
void TableResult::ArrInit()
{
	for (int i = 0; i < PERIOD_MAX; ++i)
		map[i] = false;
}

// 시간이 맵에 적절히 위치하는 지 확인하는 함수
bool TableResult::TimeCal(const Course& _course)
{
	int s;
	for (int i = 0; i<_course.lectures().size(); ++i)
	{
		s = get_idx(_course.lectures().at(i).start(), _course.lectures().at(i).day());
		while (s < get_idx(_course.lectures().at(i).end(), _course.lectures().at(i).day()))
		{
			if (map[s] == false)
			{
				map[s] = true; 
				++s;
			}
			else
			{
				--s;
				while (s > get_idx(_course.lectures().at(i).start(), _course.lectures().at(i).day()) - 1)
				{
					map[s] = false;
					--s;
				}
				if (i != 0)
				{
					for (int j = i - 1; j >= 0; --j)
					{
						s = get_idx(_course.lectures().at(i).end(), _course.lectures().at(i).day()) - 1;
						while (s > (get_idx(_course.lectures().at(i).start(), _course.lectures().at(i).day()) - 1))
						{
							map[s] = false;
							--s;
						}
					}
				}return false;
			}
		}
	}return true;
}

// 시간표 개수가 초과하지 않도록 제어하는 함수
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

// 모든 경우의 수를 조사했는지 확인하는 함수
bool TableResult::ExecuteMaxCheck()
{
	for (int i = 0; i<execute.size(); ++i)
	{
		if (execute[i]<(calList.sub_list[i].crs_list.size()-1))
			return false;
	}
	return true;
}
// 다음 진행 경우의 수로 이동
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