#include "DongGuk_Test.h"

using namespace std;
using namespace project;

// - Note :
//      DongGuk's Algorithm Test Function
//
//      Open the file
//      Generate the course and append it to table
//      Initiate TableResult Instance
//      Calcuate Course's time and Create TimeTable
//      Write text file

int dongguk_test(const std::string _ipath, const std::string _opath)
{
	// Open the file
	std::ifstream fin{ _ipath, std::ios_base::in };

	// Skip the first line (CSV headings)
	fin >> skip_line;

	Interpreter<Course> IL{ fin };
	CrsTable<Course>    Table;

	// Until the stream is good, keep going
	while (fin) {
		try {
			// Generate the course and append it to table
			auto crs = IL.generate();
			Table.append(crs);
		}
		catch (std::invalid_argument& invalid) {
			std::cerr << invalid.what() << std::endl;
		}
	}
	std::ofstream fout{ _opath,
		ios_base::out | ios_base::trunc };
	std::cout << "# Instance Create Complete" << std::endl;

	// Initiate TableResult Instance
	TableResult tr(Table);
	std::cout << "# Operating Instance Create Complete" << std::endl;
	// Calcuate Course's time and Create TimeTable
	tr.CreateTableList();

	// Write text file
	for (int i = 0; i < tr.table_list.size(); ++i)
	{
		fout << "Rank " << i << " Table" << std::endl;
		fout << tr.table_list[i] << std::endl;
	}
	std::cout << "# Print Complete" << std::endl;
	system("pause");
	return EXIT_SUCCESS;
}