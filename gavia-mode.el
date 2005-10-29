;;; gavia-mode-el -- Major mode for editing Gavia "GAB" files

;; Copyright (C) 2005 Jörgen Grahn <jgrahn@algonet.se>
;; All right reserved.

;; Based on Scott Andrew Borton's tutorial at
;; http://two-wugs.net/emacs/mode-tutorial.html
;; and http://www.emacswiki.org/cgi-bin/wiki?SampleMode
;; and http://www.emacswiki.org/cgi-bin/wiki/DerivedMode

(define-derived-mode gavia-mode text-mode "Gavia"
  "Major mode for editing Gavia 'GAB' files."


  (setq comment-start "#")
  (setq comment-start-skip "#\\W*")


  ;;register keywords
  (setq gavia-font-lock-keywords
	(list '("#.*"
		. font-lock-comment-face)
	      '("^[\t ]*:.*"
		. font-lock-type-face)
	      '("[A-Za-z_]+=.*"
		. font-lock-keyword-face)
	      '("^[\t ]*\\*.*"
		. font-lock-doc-string-face)
	      '("\$[A-Za-z0-9_]+"
		. font-lock-function-name-face)))


  (font-lock-mode))

(add-to-list 'auto-mode-alist '("\\.gavia\\'" . gavia-mode))
