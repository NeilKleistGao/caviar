(ns caviar.core)

(defn print-help []
  (println "see https://github.com/NeilKleistGao/caviar to get help."))

(defn run-rabit-run [cmd & args]
  (cond
    (= (compare cmd "account") 0) (apply println args)
    (= (compare cmd "plan") 0) (apply println args)
    (= (compare cmd "change") 0) (apply println args)
    (= (compare cmd "update") 0) (apply println args)
    :else (print-help)))

(defn -main [& args]
  (if (> (count args) 0)
        (run-rabit-run (first args) (rest args))
        (print-help)))

