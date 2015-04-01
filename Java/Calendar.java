package frmi;

import java.util.ArrayList;
import java.util.Collections;


/** Class for representing a calendar
 */
public class Calendar {
    /* Fields */
    String title;
    ArrayList<Appointment> appointments;
    ArrayList<Calendar> calendars;

    public Calendar(String title) {
        this.title = title;
        appointments = new ArrayList<>();
        calendars = new ArrayList<>();
    }

    /* Add and remove functions*/
    public void add(Appointment app){
        appointments.add(app);
    }
    public void add(Calendar cal){
        calendars.add(cal);
    }
    // return a bool, such that we can break the recursive chain.
    public boolean removeAppointment(String title){
        boolean appointmentFound = false;
        // Search calendars with a name matching title
        for(int i = 0; i < appointments.size(); i++){
            if (appointments.get(i).title.equals(title)){
                appointments.remove(i);
                appointmentFound = true;
                break;
            }
        }
        // if we did not find the calendar search in contained calenders
        if (!appointmentFound){
            for (Calendar cal : calendars){
                if (cal.removeAppointment(title))
                    break;
            }
        }
        return appointmentFound;
    }
    // return a bool, such that we can break the recursive chain.
    public boolean removeCalendar(String title){
        boolean calendarFound = false;
        // Search calendars with a name matching title
        for(int i = 0; i < calendars.size(); i++){
            if (calendars.get(i).title.equals(title)){
                calendars.remove(i);
                calendarFound = true;
                break;
            }
        }
        // if we did not find the calendar search in contained calenders
        if (!calendarFound){
            for (Calendar cal : calendars){
                if (cal.removeCalendar(title))
                    break;
            }
        }
        return calendarFound;
    }
    // Find all appointments fulfilling predicate
    public ArrayList<Appointment> appsFulfillPred(Predicate pred){
        ArrayList<Appointment> result = new ArrayList<>();
        // Check directly contained appointments, if they are within add them to result
        for (Appointment app : appointments){
            if (app.fulfillPredicate(pred)){
                result.add(app);
            }
        }
        // Search recursively in contained calenders
        for (Calendar cal : calendars)
            result.addAll(cal.appsFulfillPred(pred));

        return result;
    }
    // Find all appointments with given interval
    public ArrayList<Appointment> findInInterval(Time t1, Time t2){
        ArrayList<Appointment> result = new ArrayList<>();
        // Check directly contained appointments, if they are within add them to result
        for (Appointment app : appointments){
            if (app.withinInterval(t1, t2)){
                result.add(app);
            }
        }
        // Search recursively in contained calenders
        for (Calendar cal : calendars)
            result.addAll(cal.findInInterval(t1, t2));

        return result;
    }

    public Appointment findEarliest(Predicate pred){
        ArrayList<Appointment> result = appsFulfillPred(pred);
        Collections.sort(result, new AppointmentComparator(true));

        if (result.size() > 0)
            return result.get(0);
        return null;
    }

    public Appointment findLatest(Predicate pred){
        ArrayList<Appointment> result = appsFulfillPred(pred);
        Collections.sort(result, new AppointmentComparator(false));

        if (result.size() > 0)
            return result.get(0);
        return null;
    }

    // Create a flattened calendar
    public Calendar flattenCalendar(){
        Calendar cal = new Calendar(title);
        cal.appointments = this.appointments;
        // Flatten all contained calendars recursively
        for (Calendar c : calendars){
            cal.appointments.addAll(c.flattenCalendar().appointments);
        }
        return cal;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Calendar: ").append(title).append("\n");
        for (Appointment app : appointments){
            sb.append(app.toString()).append("\n");
        }
        for (Calendar cal : calendars){
            sb.append(cal.toString());
        }
        return sb.toString();
    }
}
