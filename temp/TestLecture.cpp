#include "TestLecture.h"
using namespace project;

Day project::TestLecture::day() const
{
	return Day::Sat;
}

int project::TestLecture::start() const
{
	return 11;
}

int project::TestLecture::end() const
{
	return 22;
}

int project::TestLecture::length() const
{
	return 10;
}
