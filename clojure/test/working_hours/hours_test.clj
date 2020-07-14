(ns working-hours.hours-test
  (:require [working-hours.hours :as hours]
            [clojure.test :as t]))

(t/deftest new
  (t/is (= (hours/new nil) nil))
  (t/is (not (= (hours/new "12:00") nil)))
  (t/is (= (hours/new "1200") nil))
  (t/is (= (hours/new "25:00") nil))
  (t/is (= (hours/new "12:61") nil))
  )

(t/deftest to-string
  (t/is (= (hours/to-string (hours/new "12:00")) "12:00"))
  )

(t/deftest add
  (t/is (= (hours/to-string (hours/add (hours/new "03:00")
                                       (hours/new "01:45")))
           "04:45"))
  )

(t/deftest sub
  (t/is (= (hours/to-string (hours/sub (hours/new "08:00")
                                       (hours/new "14:00")))
           "06:00"))
  (t/is (= (hours/to-string (hours/sub (hours/new "08:00")
                                       (hours/new "20:31")))
           "12:31"))
  )

(t/deftest preceeds
  (t/is (hours/preceeds? (hours/new "08:00")
                         (hours/new "14:00")))
  (t/is (not (hours/preceeds? (hours/new "14:00")
                              (hours/new "08:00"))))
  )
