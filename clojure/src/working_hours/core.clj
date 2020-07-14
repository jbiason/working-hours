(ns working-hours.core
  (:require [working-hours.hours :as hours]
            [working-hours.period :as period])
  (:import [java.time LocalDateTime])
  )

(declare usage get-value calc-time parse-values)

(defn usage []
  "Print the program usage."
  (println "Usage: working-hours START_TIME [LUNCH_BREAK] [LUNCH_RETURN]")
  )

(defn get-value
  ([args pos]
   "Return the argument in the position. Nil if there is no argument or the hour
   is invalid."
   (hours/new (nth args pos nil)))
  ([args pos default]
   "Return the argument in the position. Nil if the hours is invalid or use the
   default value."
   (hours/new (nth args pos default)))
  )

(defn parse-values [args]
  "Validate input values for each position."
  (let [entry  (get-value args 0)
        break  (get-value args 1 "12:00")
        return (get-value args 2 "13:00")]
    (cond
      (= entry  nil) (println "Invalid START")
      (= break  nil) (println "Invalid LUNCH_BREAK")
      (= return nil) (println "Invalid LUNCH_RETURN")
      :else          (calc-time entry break return)
      )
    )
  )

(defn now []
  (let [now (LocalDateTime/now)]
    (hours/new (format "%02d:%02d"
                       (.getHour now)
                       (.getMinute now)))
    )
  )

(defn calc-time [start lunch-break lunch-return]
  "Do the math around worked time."
  (let [now (now)
        so-far (period/worked-so-far start lunch-break lunch-return now)]
    (println (format "So far, you've worked %s" (hours/to-string so-far)))
    (let [remaining (period/work-remaining so-far)]
      (if (= remaining nil)
        (println (format "You did %s of extra work" (hours/to-string (period/extra-work so-far))))
        (println (format "You still need to work %s" (hours/to-string remaining)))
        )
      )
    )
  )

(defn -main [& args]
  (if (= (nth args 0 nil) nil)
    (usage)
    (parse-values args)
    )
  )
