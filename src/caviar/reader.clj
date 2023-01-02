(ns caviar.reader
  (:require [clojure.java.io :as io]
            [clojure.string :as cs]))

(defn read-file [filename]
  (with-open [fp (io/reader filename)]
    (reduce conj [] (line-seq fp))))

(defn ^:private create-account [data line]
  (let [res (re-seq #"Account\[(.+)\]: (\d+(\.\d+)?)(.+)" line)]
    (if (= nil res)
      (data)
      (conj data {(nth res 1) {:balance (nth res 2)}})))) ; TODO: deal with unit

(defn ^:private create-plan [data line]
  (let [res (re-seq #"Plan: (\d+(\.\d+)?)(.+)" line)]
    (if (= nil res)
      (data)
      (conj data {:plan {:balance (nth res 1)}})))) ; TODO: deal with unit

(defn ^:private modify-account [data line]
  (let [res (re-seq #"(.+):(.+) ((\+|\-)?\d+(\.\d+)?)(.+)" line)]
    (if (= nil res)
      (data)
      (let [account (nth res 1) delta (nth res 3) origin (get (get data account {:balance 0}) :balance 0) plan (get (get data :plan {:balance 0}) :balance 0)]
        (conj data {account {:balance (+ origin delta)} :plan {:balance (+ plan delta)}}))))) ; TODO: deal with unit

(defn parse-file [lines {:keys [res] :or {res {}}}]
  (if (> (count lines) 0)
    (let [line (cs/trim (first lines))]
      (cond
        (cs/blank? line) (parse-file (rest lines) res)
        (cs/starts-with? line "**") (parse-file (rest lines) res) ; ignore date
        (cs/starts-with? line "Account") (parse-file (rest lines) (create-account res line))
        (cs/starts-with? line "Plan") (parse-file (rest lines) (create-plan res line))
        (cs/starts-with? line "---") (res)
        :else (parse-file (rest lines) (modify-account res line))))
    (res)))

