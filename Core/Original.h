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
#ifndef _PROJ_ORIGINAL_H_
#define _PROJ_ORIGINAL_H_

#include "./Model.h"
#include "./Original/TableResult.h"


namespace project
{
    //  - Function    
    //    dongguk_test : Input file name and Execute Program
    int dongguk_test(const std::string _ipath, const std::string _opath);
}

#endif
