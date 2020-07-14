(ns working-hours.period-test
  (:require [working-hours.period :as period]
            [working-hours.hours :as hours]
            [clojure.test :as t]))

(t/deftest so-far
  (t/is (= (hours/to-string (period/worked-so-far (hours/new "08:00")
                                                  (hours/new "12:00")
                                                  (hours/new "13:00")
                                                  (hours/new "09:33")))
           "01:33"))
  (t/is (= (hours/to-string (period/worked-so-far (hours/new "08:10")
                                                  (hours/new "12:08")
                                                  (hours/new "13:00")
                                                  (hours/new "12:30")))
           "04:20"))
  (t/is (= (hours/to-string (period/worked-so-far (hours/new "08:20")
                                                  (hours/new "12:20")
                                                  (hours/new "13:40")
                                                  (hours/new "14:40")))
           "05:00"))
  )

(t/deftest extra
  (t/is (period/extra? (hours/new "09:00")))
  (t/is (not (period/extra? (hours/new "08:00"))))
  )

(t/deftest extra-hours
  (t/is (= (hours/to-string (period/extra-work (hours/new "09:00")))
           "00:12"))
  (t/is (= (period/extra-work (hours/new "08:00"))
           nil))
  )

(t/deftest remaining
  (t/is (= (hours/to-string (period/work-remaining (hours/new "08:00")))
           "00:48"))
  (t/is (= (period/work-remaining (hours/new "09:00"))
           nil))
  )
