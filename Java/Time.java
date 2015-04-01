package frmi;

/**
 * Time class
 * I've chosen to leave all fields being public for simplicity
 * One might have made getters for each of them.
 */
public class Time {
    int year;
    int month;
    int day;
    int hour;
    int minute;

    public Time(int year, int month, int day, int hour, int minute) {
        this.year = year;
        this.month = month;
        this.day = day;
        this.hour = hour;
        this.minute = minute;
    }

    // Is this before t?
    public boolean before(Time t){
        if (year < t.year){
            return true;
        }
        else if (year == t.year){
            if (month < t.month){
                return true;
            }
            else if (month == t.month){
                if (day < t.day){
                    return true;
                }
                else if (day == t.day){
                    if (hour < t.hour){
                        return true;
                    }
                    else if (hour == t.hour){
                        return minute < t.minute;
                    }
                }
            }
        }
        return false;
    }

    // Use the before function but swap t and this
    public boolean after(Time t){
        return t.before(this);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Time time = (Time) o;
        return year == time.year && month == time.month &&
                day == time.day && hour == time.hour &&
                minute == time.minute;
    }

    @Override
    public String toString() {
        // Ensure we are always using atleast 2 digits for each field
        return String.format("%02d-%02d-%04d %02d:%02d", day, month, year, hour, minute);
    }
}
