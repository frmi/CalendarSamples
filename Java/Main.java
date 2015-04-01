package frmi;

import java.util.ArrayList;
import java.lang.System;

import static java.lang.System.out;

public class Main {

    public static void main(String[] args) {
        Calendar mainCalendar = new Calendar("Main calendar");
        Time t1 = new Time(2015, 3, 30, 10, 45);
        Time t2 = new Time(2015, 3, 30, 10, 50);
        Appointment app = new Appointment("Test1", t1, t2);
        Time t3 = new Time(2015, 3, 30, 12, 45);
        Time t4 = new Time(2015, 3, 30, 15, 50);
        Appointment app1 = new Appointment("Test2", t3, t4);
        Time t5 = new Time(2015, 3, 30, 11, 45);
        Time t6 = new Time(2015, 3, 30, 13, 50);
        Appointment app2 = new Appointment("Test3", t5, t6);
        Time t7 = new Time(2015, 3, 30, 16, 0);
        Time t8 = new Time(2015, 3, 30, 17, 50);
        Appointment app4 = new Appointment("Test4", t8, t7);
        mainCalendar.add(app);
        mainCalendar.add(app4);
        mainCalendar.add(app2);
        Calendar nestedCal = new Calendar("Nested calendar");
        nestedCal.add(app1);
        mainCalendar.add(nestedCal);
        out.println(mainCalendar);
        out.println();

        Time start = new Time(2015, 03, 30, 9, 40);
        Time end = new Time(2015, 03, 30, 11, 50);
        Predicate pred = new Predicate(t3, t4);
        ArrayList<Appointment> result = mainCalendar.findInInterval(start, end);
        out.println("Results for given predicate: ");
        for (Appointment a : result)
            out.println(a);

        out.println();
        Appointment a = mainCalendar.findLatest(pred);
        out.println("Pred app: ");
        out.println(a);
        out.println();

        Calendar flatCal = mainCalendar.flattenCalendar();
        out.println(flatCal);
    }
}
