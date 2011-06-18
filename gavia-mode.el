;;; gavia-mode-el -- Major mode for editing Gavia "GAB" files

;; Copyright (C) 2005, 2007, 2010 Jörgen Grahn
;; All right reserved.

;; Based on Scott Andrew Borton's tutorial at
;; http://two-wugs.net/emacs/mode-tutorial.html
;; and http://www.emacswiki.org/cgi-bin/wiki?SampleMode
;; and http://www.emacswiki.org/cgi-bin/wiki/DerivedMode
;; and ps-mode.

(defconst gavia-font-lock-keywords
  '(("^#.*" . font-lock-comment-face)
    ("^place[ \t]*:" . font-lock-constant-face)
    ("^date[ \t]*:" . font-lock-constant-face)
    ("^time[ \t]*:" . font-lock-constant-face)
    ("^observers[ \t]*:" . font-lock-constant-face)
    ("^weather[ \t]*:" . font-lock-constant-face)
    ("^comments[ \t]*:" . font-lock-constant-face)
    ("^coordinate[ \t]*:" . font-lock-constant-face)
    ("^status[ \t]*:" . font-lock-constant-face)
    ("^.+?:.:" . font-lock-variable-name-face)
    ("XXX" . font-lock-warning-face))
  "Syntax highlighting for Gavia mode.")

(defun gavia-tick-species ()
  "Mark the species on the current line as seen
(with a '#' character) and advance."
  (interactive)
  (save-excursion
    (beginning-of-line)
    (if (looking-at "^[^:]+: :")
	(if (search-forward ": :" nil t)
	  (replace-match ":#:" nil t))
      )
    )
  (next-line 1)
  )

(define-derived-mode gavia-mode text-mode "Gavia"
  "Major mode for editing Gavia 'GAB' files.
This is merely text mode, plus some colorization, plus
a command to mark a species as seen (with a '#' character).
A file whose name ends in '.gavia' gets this mode."

  (define-key gavia-mode-map [f4] 'gavia-tick-species)
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
