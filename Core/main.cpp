#include <chrono>
#include "./Stage.h"

using namespace std;
using namespace std::chrono;

using namespace project;

std::chrono::steady_clock::time_point tm_stamp() {
    return std::chrono::steady_clock::now();
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







        // ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
        // Stage Algorithm section
        // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
        auto min_course = 7;
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

        std::cout << "Staging Done : "
            << DoneQue.size() << " Table... " << std::endl;

        // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


    }
    catch (...) {
        return EXIT_FAILURE;
    }
}
