#include "Calendar.h"

using namespace std;

void printList(AppointmentList& list){
	vector<Appointment>::iterator it;
	for (it = list->begin(); it < list->end(); it++){
		(*it)->print(cout);
	}
}

int main(){
	Calendar mainCalendar = createCalendar("Main calendar");
	Time t1 = createTime(2015, 3, 30, 10, 45);
	Time t2 = createTime(2015, 3, 30, 10, 50);
	Appointment app = createAppointment("Test1", t1, t2);
	Time t3 = createTime(2015, 3, 30, 12, 45);
	Time t4 = createTime(2015, 3, 30, 15, 50);
	Appointment app1 = createAppointment("Test2", t3, t4);
	Time t5 = createTime(2015, 3, 30, 11, 45);
	Time t6 = createTime(2015, 3, 30, 13, 50);
	Appointment app2 = createAppointment("Test3", t5, t6);
	Time t7 = createTime(2015, 3, 30, 16, 0);
	Time t8 = createTime(2015, 3, 30, 17, 50);
	Appointment app4 = createAppointment("Test4", t8, t7);
	mainCalendar->add(app);
	mainCalendar->add(app2);
	mainCalendar->add(app4);
	Calendar nestedCal = createCalendar("Nested calendar");
	nestedCal->add(app1);
	mainCalendar->add(nestedCal);
	cout << mainCalendar << endl;

	Time start = createTime(2015, 03, 30, 9, 40);
	Time end = createTime(2015, 03, 30, 11, 50);
	Predicate pred = createPredicate(t3, t4);
	AppointmentList result = mainCalendar->findInInterval(start, end);
	cout << "Results for given predicate: " << endl;
	printList(result);
	
	Appointment earliest = mainCalendar->findLatest(pred);
	cout << "Earliest app: " << endl;
	earliest->print(cout);

	Calendar flatCal = mainCalendar->flattenCalendar();

	cout << flatCal;

	cout << endl << endl << "Press any key to exit...";
	getchar();
	return 0;
}