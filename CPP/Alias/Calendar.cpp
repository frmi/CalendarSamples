#include "Calendar.h"


// Add an appointment to the appointment list of the calendar
void Calendar_t::add(Appointment& app){
	appointments->push_back(app);
}
// Add a calendar to the calendar list of the calendar
void Calendar_t::add(Calendar& cal){
	calendars->push_back(cal);
}

// return a bool, such that we can break the recursive chain.
bool Calendar_t::removeCalendar(std::string str){
	bool calendarFound = false;

	// Search calendars with a name matching str
	std::vector<Calendar>::iterator it;
	for (it = calendars->begin(); it < calendars->end(); it++){
		if (it->get()->name.compare(str) == 0){
			std::cout << "Removed calendar: " << str << std::endl;
			calendars->erase(it);
			calendarFound = true;
			break;
		}
	}
	// if we did not find the calendar search in contained calenders
	if (!calendarFound){
		for (it = calendars->begin(); it < calendars->end(); it++){
			if (it->get()->removeCalendar(str))
				break;
		}
	}

	return calendarFound;
}
// return a bool, such that we can break the recursive chain.
bool Calendar_t::removeAppointment(std::string str){
	bool appointmentFound = false;

	// Search appointments with a name matching str
	std::vector<Appointment>::iterator it;
	for (it = appointments->begin(); it < appointments->end(); it++){
		if (it->get()->title.compare(str) == 0){
			std::cout << "Removed appointment: " << str << std::endl;
			appointments->erase(it);
			break;
		}
	}
	// if we did not find the calendar search in contained calenders
	if (!appointmentFound){
		std::vector<Calendar>::iterator cal_it;
		for (cal_it = calendars->begin(); cal_it < calendars->end(); cal_it++){
			if (cal_it->get()->removeAppointment(str))
				break;
		}
	}
	return appointmentFound;
}

// Find all appointments with given interval
AppointmentList Calendar_t::findInInterval(Time& t1, Time& t2){
	AppointmentList result{ new std::vector < Appointment > };
	// Check directly contained appointments, if they are within add them to result
	for (int i = 0; i < appointments->size(); i++){
		if ((*appointments)[i]->withinInterval(t1, t2))
			result->push_back((*appointments)[i]);
	}
	// Search recursively in contained calenders
	std::vector<Calendar>::iterator cals_it;
	for (cals_it = calendars->begin(); cals_it < calendars->end(); cals_it++){
		AppointmentList list = (*cals_it)->findInInterval(t1, t2);
		result->insert(result->end(), list->begin(), list->end());
	}
	return result;
}
// Find all appointments fulfilling predicate
AppointmentList Calendar_t::appsFulfillPred(Predicate& pred){
	AppointmentList result{ new std::vector < Appointment > };
	// Check directly contained appointments, if they are within add them to result
	for (int i = 0; i < appointments->size(); i++){
		if ((*appointments)[i]->equals(pred.get()))
			result->push_back((*appointments)[i]);
	}
	// Search recursively in contained calenders
	std::vector<Calendar>::iterator cals_it;
	for (cals_it = calendars->begin(); cals_it < calendars->end(); cals_it++){
		AppointmentList list = (*cals_it)->appsFulfillPred(pred);
		result->insert(result->end(), list->begin(), list->end());
	}
	return result;
}
Appointment Calendar_t::findEarliest(Predicate& pred){
	AppointmentList result = appsFulfillPred(pred);
	// Use the std::sort function from <algortihm> to sort the list of results ascending
	std::sort(result->begin(), result->end(), less_than_appointment());

	// The list of results are sorted ascending with respect to starting Time of the appointment.
	// Thus pick the last element of the vector.
	// We assume that result is nonempty
	return *result.get()->begin();
}
Appointment Calendar_t::findLatest(Predicate& pred){
	AppointmentList result = appsFulfillPred(pred);
	// Use the std::sort function from <algortihm> to sort the list of results ascending
	std::sort(result->begin(), result->end(), less_than_appointment());

	// The list of results are sorted ascending with respect to starting Time of the appointment.
	// Thus pick the last element of the vector.
	// We assume that result is nonempty
	return *(result.get()->end() - 1);
}
Calendar Calendar_t::flattenCalendar(){
	// Create a new calender to represent the flat calender to be returned
	Calendar cal = createCalendar(name);
	// Add all appointments of the outer calendar
	cal->appointments->insert(cal->appointments->begin(), appointments->begin(), appointments->end());
	
	// Flatten each contained calendar recursively and add the appointments to the flat calender
	std::vector<Calendar>::iterator cals_it;
	for (cals_it = calendars->begin(); cals_it < calendars->end(); cals_it++){
		Calendar c = (*cals_it)->flattenCalendar();
		cal->appointments->insert(cal->appointments->end(), c->appointments->begin(), c->appointments->end());
	}
	return cal;
}

// Print a calendar
std::ostream& Calendar_t::print(std::ostream& os){

	os << "Calendar: " << name << std::endl;;

	std::vector<Appointment>::iterator apps_it;
	for (apps_it = appointments->begin(); apps_it < appointments->end(); apps_it++){
		(*apps_it)->print(os) << std::endl;
	}

	os << std::endl;

	std::vector<Calendar>::iterator cals_it;
	for (cals_it = calendars->begin(); cals_it < calendars->end(); cals_it++){
		(*cals_it).get()->print(os);
	}

	return os;
}
