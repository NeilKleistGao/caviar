;; ---
;; GNU GENERAL PUBLIC LICENSE
;; Version 3, 29 June 2007
;;
;; Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
;; For more information on this, and how to apply and follow the GNU GPL, see
;; <https://www.gnu.org/licenses/>


;;; @file caviar.el

(defvar caviar-keywords
  '(("Account" . 'font-lock-type-face)
    ("Plan'" . 'font-lock-type-face)
    ("Plan" . 'font-lock-type-face)
    ("Balance" . 'font-lock-type-face)
    ("\\[.*\\]" . 'font-lock-keyword-face)
    ("^\\*\\* .*" . 'font-lock-string-face)
    ("[0-9]+" . 'font-lock-warning-face)
    ("\\." . 'font-lock-warning-face)
    ("---" . 'font-lock-string-face)
    ("[a-zA-Z]+\\:" . 'font-lock-keyword-face))
  "")

(define-derived-mode caviar-mode fundamental-mode
  "caviar" "A simple tool that helps you keep track of your personal expenses in Emacs."
  (setq-default font-lock-defaults '(caviar-keywords t)))

(add-to-list 'auto-mode-alist '("\\.fsd" . caviar-mode))

(global-set-key
    (kbd "C-c C-a")
    (lambda ()
      (interactive)
      (async-shell-command (concat "caviar -s " (buffer-file-name)))
    )
  )
