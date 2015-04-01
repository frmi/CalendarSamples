#include "Appointment.h"

std::ostream& Appointment::print(std::ostream& os){
	os << "Id : " << id << std::endl;
	os << "Title:\t" << title << std::endl;
	os << "From:\t"; from->print(os) << std::endl;
	os << "To:\t"; to->print(os) << std::endl;
	return os;
}
bool Appointment::operator<(Appointment* const app2){
	return from < app2->from;
}
bool Appointment::withinInterval(Time start, Time end){
	Time thisStart = (*from.get());
	Time thisEnd = (*to.get());
	// Check whether 'from' is between start and end
	bool bFrom = (thisStart > start && thisStart < end);
	// Check whether 'to' is between start and end
	bool bTo = (thisEnd > start && thisEnd < end);
	return bFrom && bTo;
}
bool Appointment::equals(Appointment* const app){
	// if app contains a title it has to be equal to title. 
	// Title can only be empty if it was created as a predicate
	bool checkTitle = !app->title.empty();
	if (checkTitle)
		return from == app->from && to == app->to && title.compare(app->title) == 0;
	else
		return from == app->from && to == app->to;
}
