#include "NameFilter.h"	

using namespace std;
using namespace project;


NameFilter::NameFilter(const Vec<Course>& vec)
{
	original_table = vec;

	indexes_choosed.resize(TABLES_COUNT);

	//시간표 정보 삽입(first : index, second : priority)
	for (int i = 0; i < vec.size(); ++i) {
		string K = vec[i].code();
		auto Pri = static_cast<int>(vec[i].point);
		course_sets[K].push_back(
			pair<int, int>(i, Pri));
	}

	int prime_candidate = 3;

	while (prime_table.size() != course_sets.size()){
		if (isPrime(prime_candidate))
			prime_table.emplace_back(prime_candidate);
		
		prime_candidate++;
	}

	for (auto& set : course_sets) {
		sort_courses(set.second);
	}
	
	for (auto& set : course_sets) {
		if (set.second.size() >= TABLES_COUNT ||
			set.second.at(0).second == 0)
			continue;
		priority_normalization(set.second);
	}

	for (auto& set : course_sets) {
		distribute_course_index(set.second);
	}
}

Vec<Vec<Course>>& NameFilter::get_result()
{
	
	auto& chosed = indexes_choosed;
	
	//중복성 제거
	for (int i = 0; i < chosed.size(); ++i) {
		try {
			auto iter = chosed.begin();
			std::advance(iter, i + 1);

			for (; iter != chosed.end(); ++iter)
			{
				if (chosed[i] == (*iter)) {
					chosed.erase(iter);

					iter = chosed.begin();
					advance(iter, i + 1);
				}
			}
		}
		catch (std::exception& ex) {
			std::cerr << ex.what() << std::endl;
		}

	}
	
	tables_filtered.resize(indexes_choosed.size());

	for (int i = 0; i < indexes_choosed.size(); ++i) {

		for (auto a : indexes_choosed[i]) {
			if (a < 0)
				continue;
			auto&& current_crs = original_table[a];
			tables_filtered[i].emplace_back(current_crs);
		}

	}

	return tables_filtered;
}

// Insertion sort for priority(Insertion sort)
void NameFilter::sort_courses(
	Vec<pair<int, int>>& set)
{
	auto j = 0;

	for (int i = 1; i < set.size(); i++) {
		auto in = set[i];
		for (j = i - 1; (j >= 0) && 
			(in.second >= set[j].second); j--) {
			set[j + 1] = set[j];
		}
		set[j + 1] = in;
	}
}

// Normalization priority is changed to count
void NameFilter::priority_normalization(
	Vec<pair<int, int>>& set)
{
	int total = 0;
	int check = 0;

	for (auto& p : set) 
		total += p.second;

	for (auto& r : set) {
		r.second = round(static_cast<double>
			(TABLES_COUNT) * (static_cast<double>
				(r.second) / total));

		check += r.second;
	}

	//정규화 과정에서 딱 떨어지게 분배가 되지 않았을 경우
	while (check != TABLES_COUNT) {

		if (check < TABLES_COUNT) {
			++set[0].second;
			++check;
		}
		else {
			--set[0].second;
			--check;
		}
	}
	
}

//골라야하는 한 시간표 영역에 대하여 
//고르게 시간표 case를 가중치에 맞게 분배해준다.
void NameFilter::distribute_course_index(
	Vec<pair<int, int>>& set)
{
	
	for (int i = 0; i < TABLES_COUNT; ++i)
		indexes_choosed[i].emplace_back(VACANT);

	for (auto p : set) {

		auto count = abs(p.second);
		auto interval = prime_table[start_index];
		auto input_index = 0;

		while(count != 0){
			
			input_index += interval;
			input_index %= TABLES_COUNT;

			if (indexes_choosed[input_index].at
								(start_index) == VACANT) {
				indexes_choosed[input_index].at
								(start_index) = p.first;
				--count;
			}
			else {

				//빈 공간을 찾을 때 까지 한 칸씩 이동 
				while (!(indexes_choosed[input_index].at(start_index) 
					== VACANT)) {

					input_index += 1;
					input_index %= TABLES_COUNT;

				}

				indexes_choosed[input_index].at
								(start_index) = p.first;

				--count;
			}
		}
	}

	++start_index;
}

bool NameFilter::isPrime(const int& num) {
	
	if (num == 0)
		return true;

	for (int i = 2; i <= sqrt(num); i++)
		if (num % i == 0)
			return false;
	
	return true;

}