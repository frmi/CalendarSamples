#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <iostream>
#include <memory>
#include <string>
#include "Time.h"


// integer used for assigning id's to appointments, only used to identify destructions of appointments
static int appointment_next_id = 1;

/* Appointment class, represents an appointment by a title, and two Time objects (from and to).
 */
class Appointment {
public:
	/* Fields */
	int id;
	std::shared_ptr<Time> from;
	std::shared_ptr<Time> to;
	std::string title;

	/* Constructor and Destructor*/
	Appointment(std::string str, std::shared_ptr<Time> f, std::shared_ptr<Time> t) : 
		title{ str }, from{ f }, to{ t }, id{ appointment_next_id++ }{ }
	~Appointment(){
		std::cout << "Appointment " << id << " killed: " << this << std::endl;
	}

	std::ostream& print(std::ostream& os);
	bool operator<(Appointment* const app2);

	/* Determines whether an appointment is between two Times */
	bool withinInterval(Time start, Time end);
	bool equals(Appointment* const app);
};

// Struct for sorting appointments sorts by less than
struct less_than_appointment {
	bool operator()(const std::shared_ptr<Appointment>& app1, const std::shared_ptr<Appointment>& app2){
		return app1.get() < app2.get();
	}
};

/* A simple subclass of Appointment, for better readability.
 * Instead of passing an Appointment we pass a predicate for our appointment searching functions in Calendar
 * It is possiblet to create a predicate without a title. This indicates that the title is ignored when compared
 * to appointments.
 */
class Predicate :
	public Appointment
{
public:
	Predicate(std::shared_ptr<Time> f, std::shared_ptr<Time> t) : Appointment{ "", f, t }{};
	Predicate(std::string str, std::shared_ptr<Time> f, std::shared_ptr<Time> t) : Appointment{ str, f, t } {};
	~Predicate(){
		std::cout << "Predicate destroyed >> ";
	}
};

#endif