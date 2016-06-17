#include "Subject.h"
using namespace project;

// Subject constructor
Subject::Subject(Course& _c)
{
	Course c("", 0, 0); // 0 index course : this member expres
	Course copy = _c;   // 1 index course : this member expresses absenting in the operation

	code = _c.code();
	crs_list.push_back(c);
	crs_list.push_back(copy);
}