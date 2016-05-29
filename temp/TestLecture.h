#pragma once
#include "../Cpp/Course.hpp"

namespace project
{


	class TestLecture : public ILecTime
	{
		// 수업 요일
		// 일, 월, 화, 수, 목, 금, 토
		virtual Day day() const override;
		// 시작 시각:
		// ex) 9시 == 1교시
		virtual int start() const override;
		// 끝 시각 
		// ex) 10시 30분 == 2.5
		virtual int end() const override;

		// 수업시간 총 길이.
		// 30분 단위로 계산.
		// ex) 90분 수업의 반환값 == 3
		virtual int length() const override;
	};


}