// ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
//
//  File     : SubTable.h
//  Updated  : 16/06/17
//  Author
//      DongGuk Yang ( ehdrnr333@naver.com )
//  Note
//      class SubTable : contain Subject instance list
//
//  Task
//      SubTable constructor
//      addCrs : insert course into subjects such as same code
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
#ifndef SUBTABLE_H
#define SUBTABLE_H

#include "Subject.h"

namespace project
{

	// - Note
	//      Subject Table class
	class SubTable
	{
	public: // ---- ---- Default ---- ----
		int          crs_sum;
		std::vector<Subject> sub_list;

		SubTable();
		// addCrs : insert course into subjects such as same code
		void addCrs(Course& _c);
	};
} // namespace project
#endif 