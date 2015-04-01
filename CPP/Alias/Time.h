#ifndef TIME_H
#define TIME_H

#include <ostream>
#include <memory>

/* Alias for more readability */
class Time_t;
using Time = std::shared_ptr < Time_t >;

/* Class to represent time.
 * Mainly created to simplify the use of time, when creating this small
 * program. One might have used the standard C library - time.h
 * Private constructor - one should use createTime() to create a Time instance
 */
class Time_t {
private:
	Time_t(int yy, int mm, int dd, int h, int m);
public:
	/* Fields */
	int year;
	int month;
	int day;
	int hour;
	int minute;

	/* Desturctor */
	~Time_t();

	/* Overriden operators */
	std::ostream& print(std::ostream& os);
	bool operator<(Time_t& time2);
	bool operator==(Time_t& time2);
	bool operator>(Time_t& time2);

	friend Time createTime(int yy, int mm, int dd, int h, int m);
};
// Overriden operators such that we can compare two std::shared_ptr<Time>
static bool operator<(const Time& t1, const Time& t2){
	return (*t1) < (*t2);
}
static bool operator>(const Time& t1, const Time& t2){
	return (*t1) > (*t2);
}
static Time createTime(int yy, int mm, int dd, int h, int m){
	return Time{ new Time_t{ yy, mm, dd, h, m } };
}

#endif
