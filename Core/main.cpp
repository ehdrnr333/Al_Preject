
#include "./Model/Interpreter.hpp"
#include "./Model/CrsTable.hpp"
#include "./Model/Course.h"
#include "./Original/TableResult.h"
#include "./Filtering/TimeFilter.h"
#include "./Filtering/NameFilter.h"

using namespace std;
using namespace project;


// - Note :
//      박도령 알고리즘 테스트
int filtering_algorithm_test(const std::string _ipath,
	const std::string _opath)
{
    // Open the file
    std::ifstream fin{_ipath,
					  std::ios_base::in};

    // Skip the first line (CSV headings)
    fin >> skip_line;

    Interpreter<Course> IL{fin};
    CrsTable<Course>    Table;

	CrsTable<Course> tbl;

	vector<Course> d;

	// Until the stream is good, keep going
	while (fin) {
		try {
			// Generate the course and append it to table
			auto crs = IL.generate();
			Table.append(crs);
		}
		// If generate() throws,
		// ignore and go back to loop
		catch (std::invalid_argument& invalid) {
			std::cerr << invalid.what() << std::endl;
		}
	}


	for_each(Table.begin(), Table.end(), [&](Course c) {
		d.emplace_back(c);
	});

	NameFilter f{ d };

	auto& n_filter_result = f.get_result();

	cout << "NameFilter process completed" << endl;

	TimeFilter t{ n_filter_result };

	auto& t_filter_result = t.get_result();

	cout << "TimeFilter process completed" << endl;
	
	for (const auto& v : t_filter_result) {
		for (const auto& crs : v) {
			Table.append(crs);
		}
	}

    std::ofstream fout{_opath,
                       ios_base::out | ios_base::trunc};

    fout << Table << std::endl;

    // Print the table size
    std::cout << Table.size() << std::endl;

    return EXIT_SUCCESS;
}

int main() {
	filtering_algorithm_test("TestCase_euckr.txt", "TestResult.txt");
}