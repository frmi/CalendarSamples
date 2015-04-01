#ifndef CALENDAR_H // Include guard to ensure we do not make multiple declarations of Calendar
#define CALENDAR_H // by multiple includes

#include <vector>
#include <algorithm>
#include <memory>
#include <iostream>
#include "Appointment.h"

/* Class for representing a calendar
 */
class Calendar {
public:
	/* Fields */
	std::string name;
	std::shared_ptr<std::vector<std::shared_ptr<Appointment>>> appointments;
	std::shared_ptr<std::vector<std::shared_ptr<Calendar>>> calendars;

	/* Constructor and Deconstructor */
	Calendar(std::string n) : name{ n }, appointments{ new std::vector<std::shared_ptr<Appointment>> }, calendars{ new std::vector<std::shared_ptr<Calendar>> } {}
	~Calendar(){
		std::cout << "Calendar destoryed: " << this << std::endl;
	}

	/* Add and remove functions*/
	void add(std::shared_ptr<Appointment>& app);
	void add(std::shared_ptr<Calendar>& cal);
	bool removeCalendar(std::string str);
	bool removeAppointment(std::string str);

	/* Functions for searching in a calendar */
	std::shared_ptr<std::vector<std::shared_ptr<Appointment>>> findInInterval(Time& t1, Time& t2);
	std::shared_ptr<std::vector<std::shared_ptr<Appointment>>> appsFulfillPred(Predicate& pred);
	std::shared_ptr<Appointment> findEarliest(Predicate& pred);
	std::shared_ptr<Appointment> findLatest(Predicate& pred);
	std::shared_ptr<Calendar> flattenCalendar();

	// Print function for calendar
	std::ostream& print(std::ostream& os);
};
static std::ostream& operator<<(std::ostream& os, std::shared_ptr<Calendar>& c){
	return c->print(os);
}

#endif