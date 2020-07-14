(ns working-hours.hours)

(defn not-nil? [x]
  "Just check if the value is not nil."
  (not (= x nil))
  )

(defn right-size? [x]
  "Check if the hour has the correct size."
  (= (count x) 5)
  )

(defn extract-hours [x]
  "Extract the hours in the hour string."
  (Integer. (.substring x 0 2))
  )

(defn extract-minutes [x]
  "Extract the minutes in the hour string."
  (Integer. (.substring x 3 5))
  )

(defn valid-hours? [x]
  "Check if the hours are valid."
  (let [hours (extract-hours x)]
    (and (>= hours 0)
         (<= hours 23)
         )
    )
  )

(defn valid-minutes? [x]
  "Check if the minutes are valid."
  (let [minutes (extract-minutes x)]
    (and (>= minutes 0)
         (<= minutes 59)
         )
    )
  )

(defn build-hour-struct [x]
  "Return the internal representation for the hour."
  (let [hours (extract-hours x)
        minutes (extract-minutes x)]
    (+ (* hours 60) minutes)
    )
  )

(defn new [x]
  "Create a new hour representation from the string."
  (if (and (and (and (not-nil? x)
                     (right-size? x)
                     (valid-hours? x)
                     (valid-minutes? x)
                     )))
    (build-hour-struct x)
    nil
    )
  )

(defn sub [x y]
  "Substract one hour from another."
  (- y x)
  )

(defn add [x y]
  "Add one hour to another."
  (+ x y)
  )

(defn preceeds? [x y]
  (< x y)
  )

(defn to-string [x]
  "Convert the hour structure to a string."
  (let [hour (int (Math/floor (/ x 60)))
        minute (- x (* hour 60))]
    (format "%02d:%02d" hour minute)
    )
  )
