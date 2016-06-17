#include "DongGuk_Test.h"

int main(int argc, char* argv[]){

    try{
        return dongguk_test("Test1.txt", "TestResult.txt");
    }
    catch(...){
        return EXIT_FAILURE;
    }
}
