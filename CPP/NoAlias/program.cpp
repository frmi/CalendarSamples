#include "Calendar.h"

// Just print a list of appointments
void printList(std::shared_ptr<std::vector<std::shared_ptr<Appointment>>>& list){
	std::vector<std::shared_ptr<Appointment>>::iterator it;
	for (it = list->begin(); it < list->end(); it++){
		(*it)->print(std::cout);
	}
}

int main(){
	using namespace std;
	shared_ptr<Calendar> mainCalendar{ new Calendar{ "Main calendar" } };
	shared_ptr<Time> t1{ new Time{ 2015, 3, 30, 10, 45 } };
	shared_ptr<Time> t2{ new Time{ 2015, 3, 30, 10, 50 } };
	shared_ptr<Appointment> app{ new Appointment{ "Test1", t1, t2 } };
	shared_ptr<Time> t3{ new Time{ 2015, 3, 30, 12, 45 } };
	shared_ptr<Time> t4{ new Time{ 2015, 3, 30, 15, 50 } };
	shared_ptr<Appointment> app1{ new Appointment{ "Test2", t3, t4 } };
	shared_ptr<Time> t5{ new Time{ 2015, 3, 30, 11, 45 } };
	shared_ptr<Time> t6{ new Time{ 2015, 3, 30, 13, 50 } };
	shared_ptr<Appointment> app2{ new Appointment{ "Test3", t1, t2 } };
	shared_ptr<Time> t7{ new Time{ 2015, 3, 30, 16, 0 } };
	shared_ptr<Time> t8{ new Time{ 2015, 3, 30, 17, 50 } };
	shared_ptr<Appointment> app4{ new Appointment{ "Test4", t3, t4 } };
	mainCalendar->add(app);
	mainCalendar->add(app2);
	mainCalendar->add(app4);
	shared_ptr<Calendar> nestedCal{ new Calendar{ "Nested calendar" } };
	nestedCal->add(app1);
	mainCalendar->add(nestedCal);
	cout << mainCalendar << endl;

	Time start{ 2015, 03, 30, 9, 40 };
	Time end{ 2015, 03, 30, 11, 50 };
	Predicate pred{ t3, t4 };
	shared_ptr<std::vector<std::shared_ptr<Appointment>>> result = mainCalendar->findInInterval(start, end);
	cout << "Results for given predicate: " << endl;
	printList(result);
	
	shared_ptr<Appointment> earliest = mainCalendar->findLatest(pred);
	cout << "Earliest app: " << endl;
	earliest->print(cout);

	shared_ptr<Calendar> flatCal = mainCalendar->flattenCalendar();

	cout << flatCal;

	cout << endl << endl << "Press any key to exit...";
	getchar();
	return 0;
}