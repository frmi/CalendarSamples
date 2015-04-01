# CalendarSamples
Each folder in this repository represents an implementation of a very simple calendar in the language of which the folder specifies.

## Structure of a calendar
A calendar can contain a number of appointments. An appointment is characterized by an appointment text, a starting time and an ending time. Times have the usual constituents: Year, month, day, hour, and minute.

A calendar can also contain other calendars recursively (as in a Composite design pattern).

## Functionality
- Functions that add and delete appointments/calendars to and from the calendar. Feel free to the design the signatures of theses functions appropriately. Please be sure to program pure functions (which return a new calendar that represents the addition/deletion).
- Present calendar as HTML
 - A function that presents the appointments of a calendar within a given time interval: From a calendar start time from-time to a calendar end time to-time.
- Find appointments
 - Find and return the list of all appointments in the calendar that fulfills an appointment predicate.
- Find first appointment
 - Find the earliest appointment (if any) that satisfies an appointment predicate. Return false if no such appointment exists in the calendar.
- Find last appointment
 - As Find first appointment, but find the latest appointment instead of the earliest.
- Flatten calendar
 - A function that eliminates nested calendars. All appointments of nested calendards must be raised to appointments in the top-level calendar. The function should return the flattened calendar.
- Appointments overlap
 - A function that returns if two appointments overlap in time.
- Calendars overlap
 - A function that returns if two calendars have one or more overlapping appointments. If this functions returns false, all appointments in the two calendars are temporally disjoint.
