
#include "./Model/Interpreter.hpp"
#include "./Model/CrsTable.hpp"
#include "TableResult.h"

using namespace std;
using namespace project;

// - Note :
//      Parsing the exace colum...
int io_test(const std::string _ipath,
            const std::string _opath)
{
    // Open the file
    std::ifstream fin{_ipath,
					  std::ios_base::in};

    // Skip the first line (CSV headings)
    fin >> skip_line;



    Interpreter<Course> IL{fin};
    CrsTable<Course>    Table;

    // Until the stream is good, keep going
    while(fin){
        try{
            // Generate the course and append it to table
            auto crs = IL.generate();
            Table.append(crs);
        }
        // If generate() throws,
        // ignore and go back to loop
        catch(std::invalid_argument& invalid){
            std::cerr << invalid.what() << std::endl;
        }
    }
    std::ofstream fout{_opath,
                       ios_base::out | ios_base::trunc};

    fout << Table << std::endl;

    // Print the table size
    std::cout << Table.size() << std::endl;

    return EXIT_SUCCESS;
}

// - Note :
//      양동국 기본 알고리즘 테스트...
int D_Algol_test(const std::string _ipath,
	const std::string _opath)
{
	// Open the file
	std::ifstream fin{ _ipath,
		std::ios_base::in };

	// Skip the first line (CSV headings)
	fin >> skip_line;



	Interpreter<Course> IL{ fin };
	CrsTable<Course>    Table;			// 모든 수업을 저장


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


	std::ofstream fout{ _opath,
		ios_base::out | ios_base::trunc };


	TableResult tr(Table);
	tr.CreateTableList();
	
	// 최종 테이블 리스트 출력
	for (int i = 0; i < tr.table_list.size(); ++i)
	{
		fout << "Rank "<< i <<" Table"<< std::endl;
		cout << "Rank " << i << " Table" << std::endl;
		fout << tr.table_list[i] << std::endl;
		cout << tr.table_list[i] << std::endl;
	}
	system("pause");
	return EXIT_SUCCESS;
}

int main(int argc, char* argv[]){
    try{
        return D_Algol_test("Test1.txt", "TestResult.txt");
    }
    catch(...){
        return EXIT_FAILURE;
    }
}
