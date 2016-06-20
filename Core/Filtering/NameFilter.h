#ifndef NAME_FILTER_H 
#define NAME_FILTER_H

#include "../Base.h"
#include "../Model/Course.h"


namespace project
{
	class NameFilter {
	private:
        //원본 시간표
		Vec<Course> original_table; 
        //원본 시간표를 복사한 값
		Vec<Vec<Course>> tables_copied; 
        //동일한 이름 별로 묶은 정보들(string : 수업 이름, key : 분배 개수, value : 해당 수업 인덱스)
		std::map<std::string, Vec<std::pair<int, int>>> course_sets; 

        //벡터 내의 벡터 : 선택된 인덱스 번호들 
		Vec<Vec<int>> indexes_choosed; 
        //필터링 된 시간표들
		Vec<Vec<Course>> tables_filtered; 

		int start_index = 0;

		const int TABLES_COUNT = 130;
		const int VACANT = -1;

	public:
		NameFilter(const Vec<Course>& vec);
		Vec<Vec<Course>>& get_result();
	private:
		void sort_courses(Vec<std::pair<int, int>>& set);
		void priority_normalization(Vec<std::pair<int, int>>& set);
		void distribute_course_index(Vec<std::pair<int, int>>& set);
	};

}
#endif