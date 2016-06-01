#ifndef NAME_FILTER_H 
#define NAME_FILTER_H

#include "../Cpp/Course.hpp"
#include <string>
#include <map>

using namespace std;
using namespace project;

class NameFilter {
private:
	
	vector<vector<ICourse>> tables_copied; //원본 시간표를 복사한 값
	map<string, vector<pair<int, int>>> course_sets; //동일한 이름 별로 묶은 정보들(string : 수업 이름, key : 분배 개수, value : 해당 수업 인덱스)

	vector<vector<int>> indexes_choosed; //벡터 내의 벡터 : 선택된 인덱스 번호들 
	vector<vector<ICourse>> tables_filtered; //필터링 된 시간표들

	int start_index = 0;

	const int TABLES_COUNT = 20;
	const int VACANT = -1;

public:
	NameFilter(const vector<ICourse>& vec);
	vector<vector<ICourse>>& get_result();
private:
	void sort_courses(vector<pair<int, int>>& set);
	void priority_normalization(vector<pair<int, int>>& set);
	void distribute_course_index(vector<pair<int, int>>& set);
};

#endif