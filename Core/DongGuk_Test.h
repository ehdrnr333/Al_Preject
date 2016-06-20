// ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
//
//  File     : DongGuk_Test.h
//  Updated  : 16/06/17
//  Author
//      DongGuk Yang ( ehdrnr333@naver.com )
//  Note
//      Include Test Function dongguk_test
//
//  Task
//      dongguk_test : Input file name and Execute Program
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
#ifndef DONGGUT_TEST_H
#define DONGGUT_TEST_H

#include "Model\Course.h"
#include "Model/Interpreter.hpp"
#include "Model/CrsTable.hpp"
#include "Original/TableResult.h"
#include "Filtering/NameFilter.h"
#include "Filtering/TimeFilter.h"

//  - Function    
//    dongguk_test : Input file name and Execute Program
int dongguk_test(const std::string _ipath,const std::string _opath);

#endif