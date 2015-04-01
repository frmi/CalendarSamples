package frmi;

/**
 * Subclass of Appointment to make it more readable that we are passing a predicate.
 * Also a predicate can be created without a title such that it may be ignored
 * when compared with an appointment.
 */
public class Predicate extends Appointment {
    public Predicate(Time from, Time to) {
        super("", from, to);
    }
    public Predicate(String title, Time from, Time to) {
        super(title, from, to);
    }
}
