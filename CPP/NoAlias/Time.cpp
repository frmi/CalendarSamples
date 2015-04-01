#include "Time.h"
#include <iostream>


Time::Time(int yy, int mm, int dd, int h, int m) : year{ yy }, month{ mm }, day{ dd }, hour{ h }, minute{ m }
{
}

Time::~Time()
{
	std::cout << "Time '" << this << "' killed" << std::endl;
}
// Function to ensure that we always write time as atleast two digits
std::ostream& ensureTwoDigits(std::ostream& os, const int& n){
	if (n > 9)
		os << n;
	else
		os << "0" << n;
	return os;
}
std::ostream& Time::print(std::ostream& os){
	ensureTwoDigits(os, day) << "-";
	ensureTwoDigits(os, day) << "-" << year << " ";
	ensureTwoDigits(os, hour) << ":";
	ensureTwoDigits(os, minute);
	return os;
}
bool Time::operator<(Time& time2){
	if (year < time2.year){
		return true;
	}
	else if (year == time2.year){
		if (month < time2.month){
			return true;
		}
		else if (month == time2.month){
			if (day < time2.day){
				return true;
			}
			else if (day == time2.day){
				if (hour < time2.hour){
					return true;
				}
				else if (hour == time2.hour){
					return minute < time2.minute;
				}
			}
		}
	}
	return false;
}
bool Time::operator==(Time& time2){
	if (year == time2.year &&
		month == time2.month &&
		day == time2.day &&
		hour == time2.hour &&
		minute == time2.minute){
		return true;
	}
	return false;
}
bool Time::operator>(Time& time2){
	if (year > time2.year){
		return true;
	}
	else if (year == time2.year){
		if (month > time2.month){
			return true;
		}
		else if (month == time2.month){
			if (day > time2.day){
				return true;
			}
			else if (day == time2.day){
				if (hour > time2.hour){
					return true;
				}
				else if (hour == time2.hour){
					return minute > time2.minute;
				}
			}
		}
	}
	return false;
}
