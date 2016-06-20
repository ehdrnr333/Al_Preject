#include "./NameFilter.h"	

using namespace std;
using namespace project;

std::string key(const Course& _crs) {
	//std::ostringstream sout;
	//sout << _crs.code() << "-" << _crs.id();
	//return sout.str();
	return _crs.code();
}

int priority(const Course& _crs) {
	return _crs.point;
}


NameFilter::NameFilter(const Vec<Course>& vec)
{
	original_table = vec;

	//TABLES_COUNT ��ŭ Copy
	for (int i = 0; i < TABLES_COUNT; ++i)
		tables_copied.emplace_back(vec);

	indexes_choosed.resize(TABLES_COUNT);

	//�ð�ǥ ���� ����(first : index, second : priority)
	for (int i = 0; i < vec.size(); ++i) {
		auto K = key(vec[i]);
		auto Pri = priority(vec[i]);
			course_sets[K].push_back(
				pair<int, int>(i, Pri));
	}

	//Priority�� TABLES_COUNT��ŭ ����ȭ
	for (auto& set : course_sets) {
		sort_courses(set.second);
		priority_normalization(set.second);
		distribute_course_index(set.second);
	}
	
}

Vec<Vec<Course>>& NameFilter::get_result()
{
	auto& chosed = indexes_choosed;
	//�ε��� ���¿�
	for (auto a : chosed) {
		for (auto b : a){
			cout << b << " ";
		}
		cout << endl;
	}
	
	
	//�ߺ��� ����
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

	//����ȭ �������� �� �������� �й谡 ���� �ʾ��� ����
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

//�������ϴ� �� �ð�ǥ ������ ���Ͽ� 
//������ �ð�ǥ case�� ����ġ�� �°� �й����ش�.
void NameFilter::distribute_course_index(
	Vec<pair<int, int>>& set)
{
	for (int i = 0; i < TABLES_COUNT; ++i)
		indexes_choosed[i].emplace_back(VACANT);

	for (auto p : set) {

		auto count = p.second;
		auto interval = TABLES_COUNT / 
						count + pow(count, start_index);
		auto input_index = start_index;

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
				//�� ������ ã�� �� ���� �� ĭ�� �̵�
				while (!(indexes_choosed[input_index].at
								(start_index) == VACANT)) {
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
