# $Id: Makefile,v 1.7 2002-09-29 19:44:37 grahn Exp $
#
# Makefile
#
# Copyright (c) 2000--2002 Jörgen Grahn <jgrahn@algonet.se>
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

all: gavia_stat.pl _gavia_stellata gaviadate.pl gaviadeexpand.pl _gavia_focus gavia_score
all: gavia_gab2text gavia_gab2roff gavia_gab2latex gavia_gab2html

install: all
	install -m555 gavia_stat.pl $(INSTALLBASE)/bin/gavia_stat
	install -m555 _gavia_stellata $(INSTALLBASE)/bin/gavia_stellata
	install -m555 gaviadate.pl $(INSTALLBASE)/bin/gaviadate
	install -m555 gaviadeexpand.pl $(INSTALLBASE)/bin/gaviadeexpand
	install -m555 _gavia_focus $(INSTALLBASE)/bin/gavia_focus
	install -m555 gavia_score $(INSTALLBASE)/bin/
	install -m555 gavia_gab2text $(INSTALLBASE)/bin/
	install -m555 gavia_gab2roff $(INSTALLBASE)/bin/
	install -m555 gavia_gab2latex $(INSTALLBASE)/bin/
	install -m555 gavia_gab2html $(INSTALLBASE)/bin/

_gavia_stellata: gavia_stellata.pl
	sed "s|INSTALLBASE|$(INSTALLBASE)|" <$< >$@

_gavia_focus: gavia_focus
	sed "s|INSTALLBASE|$(INSTALLBASE)|" <$< >$@

depend:
	true

clean:
	$(RM) _gavia_stellata _gavia_focus

love:
	@echo "not war?"
