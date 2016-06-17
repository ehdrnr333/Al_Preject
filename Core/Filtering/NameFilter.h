#ifndef NAME_FILTER_H 
#define NAME_FILTER_H

#include "../Base.h"
#include "../Model/Course.h"

/*
	NameFilter

	Author/SN		:	Doryeong Park/2010112406
	
	Description		:	Classify all courses with course name(key) and 
						distribute courses to create several cases 
						with different course names.


	*	Member variables

	original_table		:	Combinations of all courses as input

	course_sets			:	Map with components with string(course name)
							as key and index number of original table 
							and its priority as value

	indexes_choosed		:	Set of vectors of each cases containing 
							index numbers of courses
	
	tables_filtered		:	Result(Set of all courses' combination)

	start_index			:	Index to insert each courses index number
							of same key


	*	Constants

	TABLES_COUNT	:	Limitation constant of all cases as output

	VACANT			:	Constant value of index which of component 
							doesn't determined

	*	Member Functions
	
	sort_courses			:	Sorts set of courses priority with 
								same name(key) with ascending order 

	priority_normalization	:	Normalizes priorities with TABLES_COUNT
								to distribute index number of courses 

	distribute_course_index	:	Distributes index number of courses in 
								indexes_choosed

	
	Constructor				:	Initializes all components and excutes 
								3 procedures above

	get_result				:	Creates result of all combination with 
								no name duplication with indexes_choosed
								Converts index number with matching courses

*/
namespace project
{
	class NameFilter {
	private:
		Vec<Course> original_table; 
		std::map<std::string, Vec<std::pair<int, int>>> course_sets; 
		Vec<Vec<int>> indexes_choosed; 
		Vec<Vec<Course>> tables_filtered; 

		int start_index = 0;

		const int TABLES_COUNT = 200;
		const int VACANT = -1; 

		Vec<int> prime_table;

	public:
		NameFilter(const Vec<Course>& vec);
		Vec<Vec<Course>>& get_result();
	private:
		void sort_courses(Vec<std::pair<int, int>>& set);
		void priority_normalization(Vec<std::pair<int, int>>& set);
		void distribute_course_index(Vec<std::pair<int, int>>& set);
		bool isPrime(const int& num);
	};

}
#endif