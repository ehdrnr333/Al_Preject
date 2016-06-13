#include "Subject.h"
using namespace project;

Subject::Subject(Course _c) 
{
	Course copy = _c;
	Course c("", 0, 0);

	code = _c.code();
	crs_list.push_back(c);
	crs_list.push_back(copy);
}