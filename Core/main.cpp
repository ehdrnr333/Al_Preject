
#include "./Model/Interpreter.hpp"
#include "./Model/CrsTable.hpp"
#include "TableResult.h"
#include "./Filtering/NameFilter.h"
#include "./Filtering/TimeFilter.h"
#include "./Model/RBTree.h"

using namespace std;
using namespace project;


// - Note :
//      양동국 기본 알고리즘 테스트...
int D_Algol_test(const std::string _ipath,
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

	d.emplace_back(Course{ "Algorithm", 1, 3 });
	d.emplace_back(Course{ "Algorithm", 2, 3 });
	d.emplace_back(Course{ "Algorithm", 3, 3 });

	d.emplace_back(Course{ "Pattern", 1, 3 });
	d.emplace_back(Course{ "Pattern", 2, 3 });
	d.emplace_back(Course{ "Pattern", 3, 3 });

	d.emplace_back(Course{ "OS", 1, 3 });
	d.emplace_back(Course{ "OS", 2, 3 });
	
	d.emplace_back(Course{ "OS", 3, 3 });

	d.emplace_back(Course{ "DIP", 1, 3 });
	d.emplace_back(Course{ "DIP", 2, 3 });

	d.emplace_back(Course{ "DS", 1, 3 });
	d.emplace_back(Course{ "DS", 2, 3 });
	d.emplace_back(Course{ "DS", 3, 3 });

	d[0].addTime(LecTime{ WeekDay(0), 10, 20 });
	d[4].addTime(LecTime{ WeekDay(0), 15, 30 });
	d[7].addTime(LecTime{ WeekDay(1), 15, 25 });
	d[10].addTime(LecTime{ WeekDay(3), 10, 20 });

	NameFilter f{ d };

	auto& n_filter_result = f.get_result();

	TimeFilter t{ n_filter_result };

	auto& t_filter_result = t.get_result();
	
	for (const auto& v : n_filter_result) {
		for (const auto& crs : v) {
			Table.append(crs);
		}
	}

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
	rb_tree_init();
	//CrsTable<Course> Table;
	for (auto iter = Table.begin(); iter != Table.end(); iter++)
	{
		auto& item = *iter;
		//중복 체크
		rb_tree_insert(&item);
		
	}

	rb_tree_iter_inorder();

    std::ofstream fout{_opath,
                       ios_base::out | ios_base::trunc};

    fout << Table << std::endl;

    // Print the table size
    std::cout << Table.size() << std::endl;

    return EXIT_SUCCESS;
}

int main(int argc, char* argv[]){

    try{
        return io_test("TestCase_euckr.txt", "TestResult.txt");
    }
    catch(...){
        return EXIT_FAILURE;
    }
}
