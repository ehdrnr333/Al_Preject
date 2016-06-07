#include "NameFilter.h"
#include "Course.h"


using namespace std;

int main(int argc, char* argv[]) 
{

	vector<Course> d;

	d.emplace_back(Course{ "Algorithm", 3, 10 });
	d.emplace_back(Course{ "Algorithm", 3, 20 });
	d.emplace_back(Course{ "Algorithm", 3, 30 });

	d.emplace_back(Course{ "Pattern", 3, 40 });
	d.emplace_back(Course{ "Pattern", 3, 20 });
	d.emplace_back(Course{ "Pattern", 3, 30 });

	d.emplace_back(Course{ "OS", 3, 20 });
	d.emplace_back(Course{ "OS", 3, 30 });
	d.emplace_back(Course{ "OS", 3, 60 });

	d.emplace_back(Course{ "DIP", 3, 1 });
	d.emplace_back(Course{ "DIP", 3, 2 });

	d.emplace_back(Course{ "DS", 3, 10 });
	d.emplace_back(Course{ "DS", 3, 50 });
	d.emplace_back(Course{ "DS", 3, 20 });

	NameFilter f{ d };

	auto& n_filter_result = f.get_result();

	cout << "충 수업 수 : " << n_filter_result.size() << endl << endl;

	for (auto& a : n_filter_result) {
		for (auto& n : a) {
			cout << n.to_string() << endl;
		}

		cout << endl;
	}

	system("pause");
}