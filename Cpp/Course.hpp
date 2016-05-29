#include <iostream>
#include <string>
#include <algorithm>
#include <array>
#include <vector>
namespace project
{
    // 날짜를 표현하는 클래스
    enum class Day : int {
        Sun = 0,
        Mon, Tue, Wed, Thu, Fri, Sat
    };

    static std::array<const std::string, 7> DayString = {
        "Sun",
        "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
    };

	std::ostream& operator<< (std::ostream& _out,
		const Day& _d)
		noexcept(false);
    // 하나의 강의 시간을 나타내는 클래스
    // Lecture Time Interface
    struct ILecTime
    {
        // 수업 요일
        // 일, 월, 화, 수, 목, 금, 토
        virtual Day day() const abstract;
        // 시작 시각:
        // ex) 9시 == 1교시
        virtual int start() const abstract;
        // 끝 시각 
        // ex) 10시 30분 == 2.5
        virtual int end() const abstract;

        // 수업시간 총 길이.
        // 30분 단위로 계산.
        // ex) 90분 수업의 반환값 == 3
        virtual int length() const abstract;
    };

	bool operator ==(const ILecTime& _lhs,
		const ILecTime& _rhs)
		noexcept;

	std::ostream& operator<<(std::ostream& _out,
		const ILecTime& _lec)
		noexcept(false);

	bool do_collide(const ILecTime& _lhs,
		const ILecTime& _rhs) noexcept;


    // 강의 인터페이스
    //   학수번호, 강의시간 목록, 학점, 가중치를 보유
    struct ICourse
    {
        // 학수번호
        virtual
            const std::string&  key()  const  abstract;

        // 강의시간 목록
        virtual 
        std::vector<ILecTime>&  times() const abstract;

        // 학점
        virtual int point() const  abstract;

    };

	std::ostream& operator << (std::ostream& _out,
		const ICourse& _crs)
		noexcept(false);

    // Test codes
    namespace test
    {
		template <class T>
		void print_to_cout(const T& _object) {
			std::cout << _object << std::endl;
		}
    }   // namespace test

} // namespace project