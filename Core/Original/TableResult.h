// ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
//
//  File     : TableResult.h
//  Updated  : 16/06/17
//  Author
//      DongGuk Yang ( ehdrnr333@naver.com )
//  Note
//      class TableResult : Calcuate Course's time and Create TimeTable
//
//  Task
//      TableResult : Initialization TableResult based on the Course list
//      CreateTableList : All procedures that produce a timetable
//      CreateTable     : Produce one timetable
//      TimeCal         : Check course can put in timetable
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
#ifndef TABLERESULT_H
#define TABLERESULT_H

#include <bitset>

#include "SubTable.h"
#include "../Model/CrsTable.hpp"
static constexpr int PERIOD_MAX = 136;
// week index : 1~27 28~54 55~81 82~108 109~135
static constexpr int TABLE_MAX = 15;

namespace project
{
	// - Note
	//      class TableResult : 
	//            Calcuate Course's time and Create TimeTable
	class TableResult
	{
	public:  // ---- ---- member and functions ---- ----
		std::vector<int> execute;
		std::bitset<PERIOD_MAX> bmap;
		SubTable calList;
		std::vector<CrsTable<Course>> table_list;

		// Constructor
		TableResult(CrsTable<Course> _ctb);
		// Converting time information in the index
		int get_idx(const int& _i, const int& _w);

		// All procedures that produce a timetable
		void CreateTableList();

		void CreateTable();
		bool TimeCal(const Course& _course);

		// Function to check if the results do not exceed
		bool OverloadCheck(const CrsTable<Course>& _ctb);

		// Function for the next operation
		bool ExecuteMaxCheck();
		void NextExecute();
	};
} // namespace project
#endif 