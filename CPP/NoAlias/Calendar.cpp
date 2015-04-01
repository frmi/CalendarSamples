#include "Calendar.h"

// Add an appointment to the appointment list of the calendar
void Calendar::add(std::shared_ptr<Appointment>& app){
	appointments->push_back(app);
}
// Add a calendar to the calendar list of the calendar
void Calendar::add(std::shared_ptr<Calendar>& cal){
	calendars->push_back(cal);
}

// return a bool, such that we can break the recursive chain.
bool Calendar::removeCalendar(std::string str){
	bool calendarFound = false;

	// Search calendars with a name matching str
	std::vector<std::shared_ptr<Calendar>>::iterator it;
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
bool Calendar::removeAppointment(std::string str){
	bool appointmentFound = false;

	// Search appointments with a name matching str
	std::vector<std::shared_ptr<Appointment>>::iterator it;
	for (it = appointments->begin(); it < appointments->end(); it++){
		if (it->get()->title.compare(str) == 0){
			std::cout << "Removed appointment: " << str << std::endl;
			appointments->erase(it);
			break;
		}
	}
	// if we did not find the calendar search in contained calenders
	if (!appointmentFound){
		std::vector<std::shared_ptr<Calendar>>::iterator cal_it;
		for (cal_it = calendars->begin(); cal_it < calendars->end(); cal_it++){
			if (cal_it->get()->removeAppointment(str))
				break;
		}
	}
	return appointmentFound;
}

// Find all appointments with given interval
std::shared_ptr<std::vector<std::shared_ptr<Appointment>>> Calendar::findInInterval(Time& t1, Time& t2){
	std::shared_ptr<std::vector<std::shared_ptr<Appointment>>> result{ new std::vector < std::shared_ptr<Appointment> > };
	// Check directly contained appointments, if they are within add them to result
	for (int i = 0; i < appointments->size(); i++){
		if ((*appointments)[i]->withinInterval(t1, t2))
			result->push_back((*appointments)[i]);
	}
	// Search recursively in contained calenders
	std::vector<std::shared_ptr<Calendar>>::iterator cals_it;
	for (cals_it = calendars->begin(); cals_it < calendars->end(); cals_it++){
		std::shared_ptr<std::vector<std::shared_ptr<Appointment>>> list = (*cals_it)->findInInterval(t1, t2);
		result->insert(result->end(), list->begin(), list->end());
	}
	return result;
}
// Find all appointments fulfilling predicate
std::shared_ptr<std::vector<std::shared_ptr<Appointment>>> Calendar::appsFulfillPred(Predicate& pred){
	std::shared_ptr<std::vector<std::shared_ptr<Appointment>>> result{ new std::vector < std::shared_ptr<Appointment> > };
	// Check directly contained appointments, if they are within add them to result
	for (int i = 0; i < appointments->size(); i++){
		if ((*appointments)[i]->equals(&pred))
			result->push_back((*appointments)[i]);
	}
	// Search recursively in contained calenders
	std::vector<std::shared_ptr<Calendar>>::iterator cals_it;
	for (cals_it = calendars->begin(); cals_it < calendars->end(); cals_it++){
		std::shared_ptr<std::vector<std::shared_ptr<Appointment>>> list = (*cals_it)->appsFulfillPred(pred);
		result->insert(result->end(), list->begin(), list->end());
	}
	return result;
}
std::shared_ptr<Appointment> Calendar::findEarliest(Predicate& pred){
	std::shared_ptr<std::vector<std::shared_ptr<Appointment>>> result = appsFulfillPred(pred);
	// Use the std::sort function from <algortihm> to sort the list of results ascending
	std::sort(result->begin(), result->end(), less_than_appointment());

	// The list of results are sorted ascending with respect to starting Time of the appointment.
	// Thus pick the last element of the vector.
	// We assume that result is nonempty
	return *result.get()->begin();
}
std::shared_ptr<Appointment> Calendar::findLatest(Predicate& pred){
	std::shared_ptr<std::vector<std::shared_ptr<Appointment>>> result = appsFulfillPred(pred);
	// Use the std::sort function from <algortihm> to sort the list of results ascending
	std::sort(result->begin(), result->end(), less_than_appointment());

	// The list of results are sorted ascending with respect to starting Time of the appointment.
	// Thus pick the last element of the vector.
	// We assume that result is nonempty
	return *(result.get()->end() - 1);
}
std::shared_ptr<Calendar> Calendar::flattenCalendar(){
	// Create a new calender to represent the flat calender to be returned
	std::shared_ptr<Calendar> cal{ new Calendar{ name } };
	// Add all appointments of the outer calendar
	cal->appointments->insert(cal->appointments->end(), appointments->begin(), appointments->end());

	// Flatten each contained calendar recursively and add the appointments to the flat calender
	std::vector<std::shared_ptr<Calendar>>::iterator cals_it;
	for (cals_it = calendars->begin(); cals_it < calendars->end(); cals_it++){
		std::shared_ptr<Calendar> c = (*cals_it)->flattenCalendar();
		cal->appointments->insert(cal->appointments->end(), c->appointments->begin(), c->appointments->end());
	}
	return cal;
}

// Print a calendar
std::ostream& Calendar::print(std::ostream& os){
	std::vector<std::shared_ptr<Appointment>>::iterator apps_it;

	os << "Calendar: " << name << std::endl;;

	for (apps_it = appointments->begin(); apps_it < appointments->end(); apps_it++){
		(*apps_it)->print(os) << std::endl;
	}

	os << std::endl;

	std::vector<std::shared_ptr<Calendar>>::iterator cals_it;
	for (cals_it = calendars->begin(); cals_it < calendars->end(); cals_it++){
		(*cals_it).get()->print(os);
	}

	return os;
}
