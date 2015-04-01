#ifndef CALENDAR_H
#define CALENDAR_H

#include <vector>
#include <algorithm>
#include <memory>
#include <iostream>
#include "Appointment.h"
#include "Predicate.h"

/* Aliases to simplify reading */
class Calendar_t;
using Calendar = std::shared_ptr < Calendar_t >;
using CalendarList = std::shared_ptr < std::vector<Calendar>>;

/* Class for representing a calendar
 * The constructor of the Calender is made private.
 * To create an instance of a calender once should use the function
 * createCalendar(std::string name). This will return a std::shared_ptr<Calendar_t>.
 * This ensures that than when working with Calendars we are always using shared pointers
 * and do not need to care about cleaning up.
 */
class Calendar_t {
private:
	/* Constructor */
	Calendar_t(std::string n) : name{ n }, appointments{ new std::vector<Appointment> }, calendars{ new std::vector<Calendar> } {}
public:
	/* Fields */
	std::string name;
	AppointmentList appointments;
	CalendarList calendars;

	/* Destructor */
	~Calendar_t(){
		std::cout << "Calendar killed: " << this << std::endl;
	}

	/* Functions for add and remove */
	void add(Appointment& app);
	void add(Calendar& cal);
	bool removeCalendar(std::string str);
	bool removeAppointment(std::string str);

	/* Functions for searching in a calendar */
	AppointmentList findInInterval(Time& t1, Time& t2);
	AppointmentList appsFulfillPred(Predicate& pred);
	Appointment findEarliest(Predicate& pred);
	Appointment findLatest(Predicate& pred);

	/* Converts a calendar to a flat calendar */
	Calendar flattenCalendar();
	std::ostream& print(std::ostream& os);

	/* Create a friend for the createCalendar function
	 * such that we can call the private construtor.
	 */ 
	friend Calendar createCalendar(std::string name);
};
// Function used to create a calendar - Calls private construtor
static Calendar createCalendar(std::string name){
	return Calendar{ new Calendar_t{ name } };
}
static std::ostream& operator<<(std::ostream& os, Calendar& c){
	return c->print(os);
}

#endif