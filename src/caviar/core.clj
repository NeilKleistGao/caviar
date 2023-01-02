(ns caviar.core
  (:require [caviar.handler :as handler]))

(defn print-help []
  (println "see https://github.com/NeilKleistGao/caviar to get help."))

(defn create-account [& args]
  ()); TODO

(defn create-plan [& args]
  ()); TODO

(defn create-change [& args]
  ()); TODO

(defn update-data [& args]
  (if (= (count args) 1)
    (handler/update-balance (first args))
    (print-help)))

(defn run-rabit-run [cmd & args]
  (cond
    (= (compare cmd "account") 0) (apply create-account args)
    (= (compare cmd "plan") 0) (apply create-plan args)
    (= (compare cmd "change") 0) (apply create-change args)
    (= (compare cmd "update") 0) (apply update-data args)
    :else (print-help)))

(defn -main [& args]
  (if (> (count args) 0)
        (run-rabit-run (first args) (rest args))
        (print-help)))

