package frmi;

import java.util.Comparator;

/**
 * Created by Frederik on 31-03-2015.
 */
public class Appointment {
    String title;
    Time from;
    Time to;

    public Appointment(String title, Time from, Time to) {
        this.title = title;
        this.from = from;
        this.to = to;
    }

    // Determine whether this appointment is within the two given Time objects
    public boolean withinInterval(Time start, Time end){
        return (start.before(from) && end.after(from)) &&
                (start.before(to) && end.after(to));
    }

    // determine whether this appointment fulfills given predicate
    public boolean fulfillPredicate(Predicate pred) {
        return from.equals(pred.from) && to.equals(pred.to) && (pred.title.isEmpty() || title.equals(pred.title));
    }

    // Is this appointment after app
    public boolean after(Appointment app){
        return from.after(app.from);
    }

    // Is this appointment before app
    public boolean before(Appointment app){
        return to.before(app.to);
    }


    // Is this this appointment and o equal?
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Appointment that = (Appointment) o;

        if (!title.equals(that.title)) return false;
        if (!from.equals(that.from)) return false;
        return to.equals(that.to);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Title: ").append(title).append("\n");
        sb.append("From: ").append(from).append("\n");
        sb.append("To: ").append(to).append("\n");
        return sb.toString();
    }
}
