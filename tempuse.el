;;; tempuse.el --- temp use

;; Copyright 2012 Kun Wang
;;
;; Author: Kun Wang <ifreedom.cn@gmail.com>
;; Created: 2012-02-09 22:30:23
;; Version: $Id: temp.el,v 0.0 2012/02/09 14:30:23 ifreedom Exp $
;; Keywords:
;; X-URL: not distributed yet

;; Features that might be required by this library:

;;

;;; License:
;;
;; This program is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 2, or (at your option)
;; any later version.
;;
;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with this program; if not, write to the Free Software
;; Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

;;; Commentary:

;;

;;; Change log:
;;
;;; Code:

(defun nodejs-nge2-remove-block-comment ()
  (interactive)
  (let (beg end)
    (while (search-forward "/**" nil t)
      (setq beg (- (point) 3))
      (search-forward "*/")
      (setq end (point))
      (delete-region beg end))))

(defun nodejs-nge2-struct-quote-current-word ()
  (interactive)
  (search-backward-regexp "\\s-")
  (forward-char)
  (insert "\"")
  (search-forward-regexp "\\(\\s-\\|;\\)")
  (backward-char)
  (insert "\""))

(defun nodejs-nge2-conv-struct-prop ()
  (interactive)
  (search-forward-regexp "\\w")
  (backward-char 1)
  (insert "{ ")
  (forward-char 1)
  (nodejs-nge2-struct-quote-current-word)
  (insert ",")
  (search-forward-regexp "\\w")
  (nodejs-nge2-struct-quote-current-word)
  (insert " },")
  (search-forward ";")
  (delete-backward-char 1))

(defun nodejs-nge2-conv-struct ()
  (interactive)
  (let (cur r)
    (search-forward "{")

    (while (progn
	     (setq cur (point))
	     (search-forward "}")
	     (search-backward-regexp "\\w")
	     (setq r (< cur (point)))
	     (goto-char cur)
	     (message "%s" r)
	     r)
      (nodejs-nge2-conv-struct-prop))
    (delete-backward-char 1)))


;;; tempuse.el ends here
