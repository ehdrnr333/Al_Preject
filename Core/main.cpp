#include <chrono>
#include "./Stage.h"
#include "./Original.h"
#include "./Filtering.h"

using namespace std;
using namespace std::chrono;

using namespace project;

std::chrono::steady_clock::time_point tm_stamp() {
    return std::chrono::steady_clock::now();
}


// - Note :
//      박도령 알고리즘 테스트
int filtering_algorithm_test(const std::string _ipath,
	const std::string _opath){
    	for_each(Table.begin(), Table.end(), [&](Course c) {
		d.emplace_back(c);
	});

	cout << "NameFilter process completed" << endl;

	TimeFilter t{ n_filter_result };

	auto& t_filter_result = t.get_result();

	cout << "TimeFilter process completed" << endl;
	
	for (const auto& v : t_filter_result) {
		for (const auto& crs : v) {
			Table.append(crs);
		}
	}
}


int main(int argc, char* argv[]) 
{
    try {
        std::string ipath = argv[1];
        std::string opath = argv[2];

        // 0. Open the CSV file
        // ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
        std::ifstream fin{ ipath , std::ios_base::in };

        // 0. Interpret the file into Course vector
        //      >> 'EveryCourse'
        // ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
        // Course vector
        Vec<Course> EveryCourse;
        // Interpreter for Course
        Interpreter<Course> IL{ fin }; 

        // 0. Interpret file stream into Course vector
        // ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
        
        // Skip the first line (CSV headings)
        fin >> skip_line;
        // Until the stream is good, keep going
        while (fin) {
            try {
                // Generate the course and append it to table
                auto crs = IL.generate();
                EveryCourse.emplace_back(std::move(crs));
            }
            // If generate() throws,
            // ignore and go back to loop
            catch (std::invalid_argument& invalid) {
                std::cerr << invalid.what() << std::endl;
            }
        }
        std::cout << "All courses are on memory : " 
                  << EveryCourse.size() << std::endl;


        // ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
        // Original Algorithm
        // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
        
        // Algorithm 시작...
        auto org_start = tm_stamp();

        // Initiate TableResult Instance
        TableResult tr(EveryCourse);
        std::cout << "# Operating Instance Create Complete" << std::endl;
        // Calcuate Course's time and Create TimeTable
        tr.CreateTableList();

        //// Write text file
        //for (int i = 0; i < tr.table_list.size(); ++i)
        //{
        //    fout << "Rank " << i << " Table" << std::endl;
        //    fout << tr.table_list[i] << std::endl;
        //}
        //std::cout << "# Print Complete" << std::endl;

        // ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
        // Report : [Original]
        // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

        // Original Algorirthm이 소모한 시간
        auto org_time = duration_cast<milliseconds>(
            tm_stamp() - org_start);
        std::cout << org_time.count() << "ms" << std::endl;
        // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----



        // ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
        // Filtering Algorithm
        // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

        // Algorithm 시작...
        auto fil_start = tm_stamp();

        // ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
        // Report : [Filtering]
        // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

        // Filtering Algorirthm이 소모한 시간
        auto fil_time = duration_cast<milliseconds>(
                                tm_stamp() - fil_start);
        std::cout << fil_time.count() << "ms" << std::endl;

        // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----



        // ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
        // Stage Algorithm
        // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

        // 최소 Course 제한 : 7개 수업 이상
        auto min_course = 7;
        // 최대 Stage 진행은 12단계까지.
        auto max_stage = 12;

        // Stage Algorithm 시작...
        auto stg_start = tm_stamp();


        // 필터링 함수
        auto filter = [=](const Deq<int>& _list) -> bool {
            if (_list.size() > min_course){
                return true;
            }
            return false;
        };

        // DoneQue는
        //    max회만큼 staging한 결과를 filter함수로 걸러낸 것이다.
        auto DoneQue = stage_schedule(EveryCourse, max_stage, filter);

        // ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
        // Report : [Stage]
        // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

        // Stage Algorirthm이 소모한 시간
        auto stg_time = duration_cast<milliseconds>(
                                     tm_stamp() - stg_start);
        std::cout << stg_time.count() << "ms" << std::endl;

        //std::cout << "Staging Done : "
        //    << DoneQue.size() << " Table... " << std::endl;
        // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


    }
    catch (std::exception& ex) {
        std::cerr << "[ Exception Confirmed ]" << std::endl;
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
}
