# $Id: Makefile,v 1.9 2002-09-29 19:43:41 grahn Exp $
#
# Makefile
#
# Copyright (c) 2000 Jörgen Grahn <jgrahn@algonet.se>
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. The name of the author may not be used to endorse or promote products
#    derived from this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

SHELL = /bin/sh

INSTALLBASE = /usr/local

all: gavia_cvs.txt gavia_cvs.ps

install:
	install -m644 gavia.1 $(INSTALLBASE)/man/man1/
	install -m644 gavia_add.1 $(INSTALLBASE)/man/man1/
	install -m644 gavia_cat.1 $(INSTALLBASE)/man/man1/
	install -m644 gavia_grep.1 $(INSTALLBASE)/man/man1/
	install -m644 gavia_sort.1 $(INSTALLBASE)/man/man1/
	install -m644 gavia_stat.1 $(INSTALLBASE)/man/man1/
	install -m644 gavia_stellata.1 $(INSTALLBASE)/man/man1/
	install -m644 gavia_focus.1 $(INSTALLBASE)/man/man1/
	install -m644 gavia_score.1 $(INSTALLBASE)/man/man1/
	install -m644 gavia.5 $(INSTALLBASE)/man/man5/
	install -m644 gavia_gab2roff.1 $(INSTALLBASE)/man/man1/
	install -m644 gavia_gab2latex.1 $(INSTALLBASE)/man/man1/
	install -m644 gavia_gab2text.1 $(INSTALLBASE)/man/man1/
	install -m644 gavia_gab2html.1 $(INSTALLBASE)/man/man1/

gavia_cvs.txt: gavia_cvs.mm
	nroff -mm $^ >$@

gavia_cvs.ps: gavia_cvs.mm
	groff -Tps -mm $^ >$@

depend:
	true

clean:
	$(RM) gavia_cvs.txt gavia_cvs.ps

love:
	@echo "not war?"
