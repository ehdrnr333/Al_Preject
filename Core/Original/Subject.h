// ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
//
//  File     : Subject.h
//  Updated  : 16/06/17
//  Author
//      DongGuk Yang ( ehdrnr333@naver.com )
//  Note
//      class Subject : contain same code Courses
//
//  Task
//      Subject constructor
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
#ifndef SUBJECT_H
#define SUBJECT_H

#include "../Model/Course.h"

namespace project
{
	// - Note
	//      class Subject : contain same code Courses
	class Subject
	{
	public:  // ---- ---- all member ---- ----
		std::vector<Course> crs_list;
		string          code;

		Subject(Course& _c);
	};
} // namespace project
#endif 