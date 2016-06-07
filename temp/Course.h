#ifndef COURSE_H 
#define COURSE_H

#include "Common.h"

class Course {
private:
	std::string m_key;
	int m_point;
	int m_priority;

public:
	Course(std::string key, int point, int priority) :
		m_key(key), m_point(point), m_priority(priority)
	{}

	std::string key() const {
		return this->m_key;
	}

	int point() const {
		return this->m_point;
	}

	int priority() const {
		return this->m_priority;
	}

	std::string to_string() const {
	
		std::string r_str;

		r_str = std::string{ 
			"수업 이름 : " + m_key + 
			" / 학점 : " + std::to_string(m_point) +
			" / 우선도 : " + std::to_string(m_priority) };

		return r_str;
	}
};

#endif