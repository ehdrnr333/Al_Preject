
#include "./Model/CourseInterpreter.h"
#include "./Model/CrsTable.hpp"

using namespace std;
using namespace project;


// - Note :
//      Parsing the exace colum...
int main(int argc, char *argv[])
{
    std::string in_path = argv[1];
    //std::string path = "./TestCase.txt";
    std::ifstream fin{in_path,
                      ios_base::in};


    // Skip the first line
    fin >> skip_line;

    CourseInterpreter IL{fin};
    CrsTable<Course>  large_table;

    try{    // Interpreter's I/O exception

        // Until the stream is good, keep going
        // while(true){
        while(fin){
            try{
                // Generate the course and append it to table
                auto crs = IL.generate();
                large_table.append(crs);
            }
            // If generate() throws,
            // ignore and go back to loop
            catch(std::invalid_argument& invalid){
                std::cerr << invalid.what() << std::endl;
            }
        }

    }
    // I/O Failure. The Input file stream is done.
    catch(std::ios_base::failure& iofail){
        std::cerr << iofail.code() << " : " << iofail.what() << std::endl;
    }


    std::string out_path{ argv[2] };
    std::ofstream fout{out_path,
                       ios_base::out | ios_base::trunc};

    fout << large_table << std::endl;

    std::cout << large_table.size() << std::endl;

    return 0;
}
