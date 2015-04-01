#lang racket

; Name: Frederik Bruhn Mikkelsen
; Email: fmikke11@student.aau.dk

; List helper functions
(define (first l)
  (car l))
(define (second l)
  (first (cdr l)))
(define (third l)
  (second (cdr l)))
(define (fourth l)
  (third (cdr l)))
(define (fifth l)
  (fourth (cdr l)))
(define (sixth l)
  (fifth (cdr l)))

; Generel helper functions
(define (fulfill? element element2)
  (cond ((null? element) #f)
        ((eq? element element2) #t)
        (else #f)))
(define (between? n min max)
  (if (and (>= n min) (<= n max)) #t #f))
(define (ensure-two-numbers n)
  (if (number? n)
      (if (< n 10)
          (string-append "0" (number->string n))
          (number->string n))
      (error "Input is not a number")))

; Compare functions
(define (make-compare-fn lt)
  (lambda (x y)
    (cond ((lt x y) -1)
          ((lt y x) 1)
          (else 0))))
(define cmp (make-compare-fn <))
(define strcmp (make-compare-fn string<?))

; Time functions
(define (time-create-empty)
  (list 'time 0 0 0 0 0))
(define (time-create year month day hour minute)
  (if (time-valid? month day hour minute)
      (list 'time year month day hour minute)
      (error "One or more of the parameters for time is invalid")))
(define (time-year time)
  (second time))
(define (time-month time)
  (third time))
(define (time-day time)
  (fourth time))
(define (time-hour time)
  (fifth time))
(define (time-minute time)
  (sixth time))
(define (time-get time)
  (cdr time))
(define (time? element)
  (if (pair? element)
      (fulfill? (car element) 'time)
      #f))
(define (time-valid? month day hour minute)
  (if (and (between? month 1 12) (and (between? day 1 31) (and (between? hour 0 23) (between? minute 0 59))))
      #t
      #f))
(define (time-month->string time)
  (cond ((not (time? time)) (error "input is not a time element"))
        ((eq? (time-month time) 1) "January")
        ((eq? (time-month time) 2) "February")
        ((eq? (time-month time) 3) "March")
        ((eq? (time-month time) 4) "April")
        ((eq? (time-month time) 5) "May")
        ((eq? (time-month time) 6) "June")
        ((eq? (time-month time) 7) "Juli")
        ((eq? (time-month time) 8) "August")
        ((eq? (time-month time) 9) "September")
        ((eq? (time-month time) 10) "October")
        ((eq? (time-month time) 11) "November")
        ((eq? (time-month time) 12) "December")))
(define (time-empty? time)
  (if (= (time-cmp time (time-create-empty)) 0) #t #f))
(define (time->string time)
  (string-append (ensure-two-numbers (time-day time)) "-" 
                 (ensure-two-numbers (time-month time)) "-" 
                 (ensure-two-numbers (time-year time)) " " 
                 (ensure-two-numbers (time-hour time)) ":"
                 (ensure-two-numbers (time-minute time))))

;; compare two time
(define (time-cmp time1 time2)
  (time-cmp-helper (time-get time1) (time-get time2)))
(define (time-cmp-helper time1 time2)
  (cond ((null? time1) 0)
        ((eq? (car time1) (car time2)) (time-cmp-helper (cdr time1) (cdr time2)))
        (else (cmp (car time1) (car time2)))))

; Appointment Title
(define (title-create title)
  (list 'title title))
(define (title->string title)
  (second title))
(define (title-empty? title)
  (if (string=? (title->string title) "") #t #f))
(define (title? element)
  (if (pair? element)
      (fulfill? (car element) 'title)
      #f))

; Predicate functions
; We want to be able to create our predicate with empty times - therefore we cannot use app-create
(define (pred-create title start end)
  (list 'predicate (title-create title) start end))
(define (predicate? pred)
  (if (eq? (first pred) 'predicate) #t #f))

;; Appointement functions
; Appointment constructor
(define (apppointment-create title start end)
  (if (eq? (time-cmp start end) 1) (error "Error: Start time cannot be ealier than end time")
       (list 'appointment (title-create title) start end)))
; Appointment getters
(define (appointment-title app)
  (second app))
(define (appointment-from app)
  (third app))
(define (appointment-to app)
  (fourth app))
(define (appointment? element)
  (if (pair? element)
      (fulfill? (car element) 'appointment)
      #f))
; Appointment comparison functions
(define (appointment<? app1 app2)
  (if (= (time-cmp (appointment-from app1) (appointment-from app2)) -1) #t #f))
(define (appointment>? app1 app2)
  (appointment<? app2 app1))
(define (app-cmp app1 app2)
  (if (and (appointment? app1) (appointment? app2))
      (if (eq? (strcmp (appointment-title app1) (appointment-title app2)) 0)
          (if (time-cmp (appointment-from app1) (appointment-from app2))
              #t
              #f)
          #f)
      #f))
; Determines whether an appointment fulfills a predicate
(define (app-fulfill-pred? app pred)
  (if (and (appointment? app) (predicate? pred))
      (app-fulfill-pred-helper (cdr app) (cdr pred))
      (error (~a "Appointment or predicate given is not valid\n" "Appointment: " app "\nPredicate: " pred))))
; If the title or time elements are empty that part of the predicate is seens as fulfilled.
; that way all parameters in the predicate is made optional.
(define (app-fulfill-pred-helper app pred)
  (cond ((null? pred) #t)
        ((title? (car pred)) (if (or (title-empty? (car pred))
                                     (string=? (title->string (car app)) (title->string (car pred))))
                                 (app-fulfill-pred-helper (cdr app) (cdr pred))
                                 #f))
        ((time? (car pred)) (if (or (time-empty? (car pred))
                                    (= (time-cmp (car app) (car pred)) 0)) 
                                (app-fulfill-pred-helper (cdr app) (cdr pred))
                                #f))
        (else #f)))
; Is appointment within a certain predicate
(define (app-within-pred? app pred)
  (let ((appfrom (appointment-from app)) (appto (appointment-to app)))
    (cond ((and (time-empty? (appointment-from pred)) (time-empty? (appointment-to pred))) #t)
          ((and (>= (time-cmp appfrom (appointment-from pred)) 0) (time-empty? (appointment-to pred))) #t)
          ((and (time-empty? (appointment-from pred)) (<= (time-cmp appto (appointment-to pred)) 0)) #t)
          ((and (>= (time-cmp appfrom (appointment-from pred)) 0) (<= (time-cmp appto (appointment-to pred)) 0)) #t)
          (else #f))))
(define (appointment->html app pred)
  (if (app-within-pred? app pred)
      (string-append "\t\t<td>\n" (appointment->html-helper app) "\n\t\t</td>\n")
      ""))
(define (appointment->html-helper app)
  (string-append "\t\t\t<table>\n\t\t\t\t"
                 "<tr><td>Title:</td><td>" (title->string(appointment-title app))  "</td></tr>"
                 "\n\t\t\t\t<tr><td>From:</td><td>" (time->string (appointment-from app))  "</td></tr>"
                 "\n\t\t\t\t<tr><td>To:</td><td>" (time->string (appointment-to app)) "</td></tr>"
                 "\n\t\t\t</table>"))

; Calendar functions
;; Calendar constructor
(define (cal-create applist)
  (cons 'calendar (cal-create-helper applist '())))
(define (cal-create-helper applist res)
  (cond ((null? applist) (reverse res))
        (else (cal-create-helper (cdr applist) (cons (car applist) res)))))
; Calendar getter functions
(define (calendar-appointments cal)
  (cdr cal))
; Is element a calendar
(define (calendar? element)
  (if (pair? element)
      (fulfill? (car element) 'calendar)
      #f))
; Sort appointments in calendar
(define (calendar-sort cal fn)
  (cal-create (sort (calendar-appointments cal) fn)))
; Structure the appointments of a calendar in such a way that there is a row
; for each month. An appointment is added to the month of which it starts
(define (cal-html-month cal pred)
  (cal-html-month-helper (calendar-appointments cal) pred -1 ""))
(define (cal-html-month-helper apps pred month res)
  (cond ((null? apps) (string-append res "\t\t</tr>"))
        ((eq? month (time-month (appointment-from (car apps)))) 
         (cal-html-month-helper 
          (cdr apps) 
          pred
          (time-month (appointment-from (car apps)))
          (string-append res (appointment->html (car apps) pred))))
        ((eq? month -1) (let ((appstr (appointment->html (car apps) pred)))
                (if (eq? appstr "")
                    (cal-html-month-helper 
                     (cdr apps) 
                     pred 
                     -1
                     res)
                    (cal-html-month-helper
                     (cdr apps)
                     pred
                     (time-month (appointment-from (car apps)))
                     (string-append res 
                                    "<tr>\n\t\t<td align=\"center\">" 
                                    (time-month->string (appointment-from (car apps))) 
                                    "</td>\n" 
                                    appstr)))))
        (else (let ((appstr (appointment->html (car apps) pred)))
                (if (eq? appstr "")
                    (cal-html-month-helper 
                     (cdr apps) 
                     pred 
                     (time-month (appointment-from (car apps)))
                     res)
                    (cal-html-month-helper 
                     (cdr apps) 
                     pred 
                     (time-month (appointment-from (car apps)))
                     (string-append res 
                                    "\t\t</tr><tr>\n\t\t<td align=\"center\">" 
                                    (time-month->string (appointment-from (car apps))) 
                                    "</td>\n" 
                                    appstr)))))))
; Convert a calendar to html
(define (calendar->html cal from-time to-time)
  (string-append "<table border=\"1\">\n\t\t"
                 "<tr><th>Month</th><th colspan=\"100\">Appointments</th>\n\t\t"
                 (cal-html-month 
                  (calendar-sort cal appointment<?)
                  (pred-create "" from-time to-time))
                 "\n\t\t</table>"))

; Asked functionality for the miniproject
; 1. bullet point. Add and delete appointemnets/calendars to and from the calendar
; Add a calendar or appointment(s) to a calendar
(define (calendar-add cal item)
  (cond ((null? item) cal)
        ((not (pair? item)) (error (~a "'" item "' is not a valid item for adding to a calendar")))
        ((appointment? item) (cal-create (cons item (calendar-appointments cal))))
        ((calendar? item) (cal-create (append (calendar-appointments item) (calendar-appointments cal))))
        (else (calendar-add cal (cdr item)))))

; Delete an calendar or appointment from calendar 'cal'
(define (calendar-delete cal item)
  (cond ((null? item) cal)
        ((appointment? item) (cal-except-app (calendar-appointments cal) item))
        ((appointment? (car item)) (cal-except-app (calendar-appointments cal) item))
        ((calendar? item) (cal-except-cal cal item))
        (else (calendar-delete cal (cdr item)))))
; Remove all appointments from cal1 which are in cal2
(define (cal-except-cal cal1 cal2)
  (cal-create (cal-except-apps (calendar-appointments cal1) (calendar-appointments cal2))))
; Remove all appointments that are in items which also are in apps
(define (cal-except-apps apps items)
  (if (null? items)
      apps
      (cal-except-apps (cal-except-app apps (car items)) (cdr items))))
; Remove an appointment from calendar
(define (cal-except-app apps item)
  (cal-create (cal-except-app-helper apps item '())))
(define (cal-except-app-helper apps item res)
  (cond ((null? apps) res)
        ((app-cmp (car apps) item) (cal-except-app-helper (cdr apps) item res))
        (else (cal-except-app-helper (cdr apps) item (cons (car apps) res)))))

; 2. bullet point. Present the appointments of a calendar within a given time interval
; Present calendar
(define (present-calendar-html cal from-time to-time)
  (write-html (html-create (html-head (html-title "Calendar")) (html-body (calendar->html cal from-time to-time)))))

; Find all appointments that fulfills pred
; 3. bullet point. Find and return the list of all appointments in the calendar
(define (find-appointments cal pred)
      (find-appointments-helper (calendar-appointments cal) pred '()))
(define (find-appointments-helper apps pred res)
  (cond ((null? apps) (reverse res))
        ((app-fulfill-pred? (car apps) pred) (find-appointments-helper (cdr apps) pred (cons (car apps) res)))
        (else (find-appointments-helper (cdr apps) pred res))))
; 4. bullet point. Find the earliest appointment
; Find erliest appointment which fulfills pred
(define (find-first-appointment cal pred)
  (find-one-appointment cal pred appointment<?))

; Find last appointment which fulfills pred
; 4. bullet point. Find the latest appointment
(define (find-last-appointment cal pred)
  (find-one-appointment cal pred appointment>?))
; Uniform method to get the first element of the result of find-appointments.
; The result depends on the parameter fn - fn desicdes if the calendar is sorted descening or ascending
(define (find-one-appointment cal pred fn)
  (if (predicate? pred)
      (let ((appointments (find-appointments (calendar-sort cal fn) pred)))
        (if (null? appointments)
            #f
            (car appointments)))
      #f))

; Flatten calendar - The structure of calendar is always flattened so we just return the input calendar
; 5. bullet point. A function that eliminates nested calendars
(define (flatten-calendar cal)
  cal)

; Appointments overlap
; 6. bullet point. A predicate that returns if the two appointments ap1 and ap2 overlap in time
(define (appointments-overlap? app1 app2)
  (cond ((>= (time-cmp (appointment-from app1) (appointment-to app2)) 0) #f)
        ((>= (time-cmp (appointment-from app2) (appointment-to app1)) 0) #f)
        (else #t)))

; Calendars overlap
; 7. bullet point. A predicate that returns if two calendars have one or more overlapping appointments.
(define (calendars-overlap? cal1 cal2)
  (calendars-overlap-helper cal2 (calendar-appointments cal1) (calendar-appointments cal2)))
(define (calendars-overlap-helper cal2 apps1 apps2)
  (cond ((null? apps1) #f)
        ((null? apps2) (calendars-overlap-helper cal2 (cdr apps1) (calendar-appointments cal2)))
        ((appointments-overlap? (car apps1) (car apps2)) #t)
        (else (calendars-overlap-helper cal2 apps1 (cdr apps2)))))

; Html functions
(define (html-create head body)
  (string-append "<html>\n\t" head body "\n</html>"))
(define (html-head content)
  (string-append "<head>\n\t\t" content "\n\t</head>"))
(define (html-title title)
  (string-append "<title>" title "</title>"))
(define (html-body content)
  (string-append "\n\t<body>\n\t\t" content "\n\t</body>"))

; Write html to a file and print it to the console
(define output "calendar.html")
(define (write-html content)
  (begin 
    (let ((out (open-output-file output #:mode 'text #:exists 'replace)))
      (begin
        (display content out)
        (display (string-append "Following content was written to '" output "':\n\n"))
        (display content)
        (close-output-port out)))))

; test data
(define time1 (time-create 2014 5 14 08 15))
(define time2 (time-create 2014 6 15 10 15))
(define time3 (time-create 2014 7 16 11 15))
(define time4 (time-create 2014 8 17 12 15))
(define time5 (time-create 2014 9 18 13 15))
(define time6 (time-create 2014 10 18 14 15))
(define time7 (time-create 2014 10 19 14 15))
(define starttime1 (time-create 2014 5 9 13 1))
(define starttime2 (time-create 2014 6 11 13 5))
(define starttime3 (time-create 2014 7 12 15 1))
(define starttime4 (time-create 2014 8 13 16 1))
(define starttime5 (time-create 2014 9 14 17 1))
(define endtime1 (time-create 2014 5 16 14 1))
(define endtime2 (time-create 2014 6 16 13 30))
(define endtime3 (time-create 2014 7 16 16 1))
(define endtime4 (time-create 2014 8 16 17 1))
(define endtime5 (time-create 2014 9 16 18 1))
(define appoverlap1 (apppointment-create "Aftale1" starttime1 endtime1))
(define appoverlap2 (apppointment-create "Aftale2" starttime2 endtime2))
(define appoverlap3 (apppointment-create "Aftale3" starttime3 endtime3))
(define appoverlap4 (apppointment-create "Aftale4" starttime4 endtime4))
(define appoverlap5 (apppointment-create "Aftale5" starttime5 endtime5))
(define overlaplist1 (list appoverlap1 appoverlap3))
(define overlaplist2 (list appoverlap2 appoverlap4 appoverlap5))
(define caloverlap1 (cal-create overlaplist1))
(define caloverlap2 (cal-create overlaplist2))
(define applist1 (list (apppointment-create "PP" time1 time2) (apppointment-create "PP miniproject" time2 time3)))
(define applist2 (list (apppointment-create "WI" time3 time4) (apppointment-create "WI miniproject" time4 time5)))
(define applist3 (list (apppointment-create "WE" time5 time6) (apppointment-create "WE miniproject" time6 time7)))
(define cal1 (cal-create applist1))
(define cal2 (cal-create applist2))
(define cal3 (cal-create applist3))
(define multical (calendar-add cal1 (calendar-add cal2 (calendar-add cal3 (calendar-add caloverlap1 caloverlap2)))))