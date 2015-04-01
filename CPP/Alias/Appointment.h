#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "Time.h"

/* Aliases for readability */
class Appointment_t;
using Appointment = std::shared_ptr < Appointment_t >;
using AppointmentList = std::shared_ptr < std::vector<std::shared_ptr<Appointment_t>>>;

// integer used for assigning id's to appointments, only used to identify destructions of appointments
static int appointment_next_id = 1;

/* Appointment class, represents an appointment by a title, and two Time objects (from and to).
 */
class Appointment_t {
private:
	Appointment_t(std::string str, Time f, Time t) : title{ str }, from{ f }, to{ t }, id{ appointment_next_id++ }{ }
public:
	~Appointment_t(){
		std::cout << "Appointment " << id << " killed: " << this << std::endl;
	}
	/* Fields */
	int id;
	Time from;
	Time to;
	std::string title;


	std::ostream& print(std::ostream& os);
	bool operator<(Appointment_t* const app2);

	/* Determines whether an appointment is between two Times */
	bool withinInterval(Time start, Time end);
	bool equals(Appointment_t* const app);

	/* Friends */
	// Makes sure that the subclass Predicate can pass parameters to the constructor of Appointment
	friend class Predicate_t;
	// createAppointment can now call the private constructor such that we can create std::shared_ptr<Appointment> objects
	friend Appointment createAppointment(std::string, Time, Time);
};
// Construtor method
static Appointment createAppointment(std::string str, Time f, Time t){
	return Appointment{ new Appointment_t{ str, f, t } };
}

// Struct for sorting appointments sorts by less than
struct less_than_appointment {
	bool operator()(const Appointment& app1, const Appointment& app2){
		return app1.get() < app2.get();
	}
};

/* Alias for Predicate */
class Predicate_t;
using Predicate = std::shared_ptr < Predicate_t >;

/* A simple subclass of Appointment, for better readability.
 * Instead of passing an Appointment we pass a predicate for our appointment searching functions in Calendar
 * It is possiblet to create a predicate without a title. This indicates that the title is ignored when compared
 * to appointments.
 */
class Predicate_t :
	public Appointment_t
{
private:
	Predicate_t(Time f, Time t) : Appointment_t{ "", f, t }{}
	Predicate_t(std::string str, Time f, Time t) : Appointment_t{ str, f, t } {}
public:
	~Predicate_t(){
		std::cout << "Predicate destroyed >> ";
	}

	friend Predicate createPredicate(Time, Time);
	friend Predicate createPredicate(std::string, Time, Time);
};

static Predicate createPredicate(std::string str, Time f, Time t){
	return Predicate{ new Predicate_t{ str, f, t } };
}
static Predicate createPredicate(Time f, Time t){
	return Predicate{ new Predicate_t{ f, t } };
}

#endif