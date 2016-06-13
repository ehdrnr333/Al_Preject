#include "./TimeTable.hpp"
using namespace project;

bool write_table(std::ofstream& _out, const ITimeTable& _table)
noexcept(false)
{
	std::string o_str = "";
	for (int i = 0; i < _table.courses.size(); ++i)
		o_str.append(_table.courses[i] + "\n");
	// _out<<o_str;
	return true;
}

bool write_tList(std::ofstream& _out, const ITableList& _tList)
noexcept(false)
{
	std::string o_str = "";
	for (int i = 0; i < _tList.max; ++i)
	{
		// _out<<"Table " << i << " : "<<_tList.tables[i].sum <<endl;
		write_table(_out, _tList.tables[i]);
	}

	return true;
}