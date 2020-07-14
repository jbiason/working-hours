(ns working-hours.period
  (:require [working-hours.hours :as hours])
  )

(def working-hours-per-day (hours/new "08:48"))

(defn worked-so-far [start lunch-break lunch-return now]
  "Return the hours worked so far."
  (if (hours/preceeds? now lunch-return)
    (hours/sub start now)
    (hours/add (hours/sub start lunch-break)
               (hours/sub lunch-return now))
    )
  )

(defn extra? [worked]
  "Checks if the worked time is now on extra time."
  (> worked working-hours-per-day)
  )

(defn extra-work [worked]
  "Return the hours of extra work done."
  (if (extra? worked)
    (hours/sub working-hours-per-day worked)
    nil)
  )

(defn work-remaining [worked]
  "Return the hours remaing to complete the working day hours."
  (if (extra? worked)
    nil
    (hours/sub worked working-hours-per-day))
  )
