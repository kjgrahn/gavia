;;; gavia-mode-el -- Major mode for editing Gavia "GAB" files

;; Copyright (C) 2005 Jörgen Grahn <jgrahn@algonet.se>
;; All right reserved.

;; Based on Scott Andrew Borton's tutorial at
;; http://two-wugs.net/emacs/mode-tutorial.html
;; and http://www.emacswiki.org/cgi-bin/wiki?SampleMode
;; and http://www.emacswiki.org/cgi-bin/wiki/DerivedMode
;; and ps-mode.

(defconst gavia-font-lock-keywords
  '(("^#.*" . font-lock-comment-face)
    ("^place *:" . font-lock-constant-face)
    ("^date *:" . font-lock-constant-face)
    ("^time *:" . font-lock-constant-face)
    ("^observers *:" . font-lock-constant-face)
    ("^weather *:" . font-lock-constant-face)
    ("^comments *:" . font-lock-constant-face)
    ("^.+?:.:" . font-lock-variable-name-face)
    ("XXX" . font-lock-warning-face))
  "Syntax highlighting for Gavia mode.")

(define-derived-mode gavia-mode text-mode "Gavia"
  "Major mode for editing Gavia 'GAB' files."

  (setq comment-start "#")
  (setq comment-start-skip "#+\\s-*")

  (set (make-local-variable 'font-lock-defaults)
       '((gavia-font-lock-keywords
 	  gavia-font-lock-keywords
 	  gavia-font-lock-keywords
 	  gavia-font-lock-keywords)
 	 t)))

(add-to-list 'auto-mode-alist '("\\.gavia\\'" . gavia-mode))

(provide 'gavia-mode)
