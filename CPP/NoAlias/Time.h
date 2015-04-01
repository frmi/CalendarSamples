#ifndef TIME_H
#define TIME_H

#include <ostream>
/* Class to represent time.
* Mainly created to simplify the use of time, when creating this small
* program. One might have used the standard C library - time.h
*/
class Time {
public:
	/* Fields */
	int year;
	int month;
	int day;
	int hour;
	int minute;
	/* Constructor and Deconstructor */
	Time(int yy, int mm, int dd, int h, int m);
	~Time();

	/* Overriden methods */
	std::ostream& print(std::ostream& os);
	bool operator<(Time& time2);
	bool operator==(Time& time2);
	bool operator>(Time& time2);
};

#endif
