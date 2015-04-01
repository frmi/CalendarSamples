package frmi;

import java.util.Comparator;

/**
 * Comparator for appointments.
 */
public class AppointmentComparator implements Comparator<Appointment> {

    boolean ascending = true;
    public AppointmentComparator(boolean ascending){
        this.ascending = ascending;
    }

    @Override
    public int compare(Appointment a1, Appointment a2) {
        Appointment temp1;
        Appointment temp2;
        // Based on ascending we need to make a choice of order to sort
        if (!ascending){
            temp1 = a1;
            temp2 = a2;
        } else {
            temp1 = a2;
            temp2 = a1;
        }

        if (temp1.before(temp2))
            return 1;
        else if (temp1.after(temp2))
            return -1;
        else
            return 0;
    }
}
