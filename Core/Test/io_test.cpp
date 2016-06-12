
#include "../Model/Interpreter.hpp"
#include "../Model/CrsTable.hpp"

using namespace std;
using namespace project;


// - Note :
//      Parsing the exace colum...
int io_test(const std::string _ipath,
    const std::string _opath)
{
    // Open the file
    std::ifstream fin{ _ipath,
        ios_base::in };

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
        // If generate() throws,
        // ignore and go back to loop
        catch (std::invalid_argument& invalid) {
            std::cerr << invalid.what() << std::endl;
        }
    }


    std::ofstream fout{ _opath,
        ios_base::out | ios_base::trunc };

    fout << Table << std::endl;

    // Print the table size
    std::cout << Table.size() << std::endl;

    return EXIT_SUCCESS;
}
