# $Id: Makefile,v 1.6 2008-01-03 07:24:43 grahn Exp $
#
# Makefile
#
# Copyright (c) 2000-2007 Jörgen Grahn
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
ELISPDIR=$(INSTALLBASE)/share/emacs/site-lisp

CPPFLAGS = -DUSE_GETOPT_H
CFLAGS = -W -Wall -pedantic -ansi -g -O2
CXXFLAGS = -W -Wall -pedantic -std=c++98 -g -O2
LDFLAGS = -Lsrc

OUTS=src/gavia_add src/gavia_cat src/gavia_grep src/gavia_sort

all: $(OUTS)

src/gavia_cat: src/gavia_cat.o src/libgavia.a
	$(CXX) $(LDFLAGS) -o $@ $< -lgavia

src/gavia_add: src/gavia_add.o src/libgavia.a
	$(CXX) $(LDFLAGS) -o $@ $< -lgavia -lfl

src/gavia_grep: src/gavia_grep.o src/libgavia.a
	$(CXX) $(LDFLAGS) -o $@ $< -lgavia

src/gavia_sort: src/gavia_sort.o src/libgavia.a
	$(CXX) $(LDFLAGS) -o $@ $< -lgavia

.PHONY: lib
lib: src/libgavia.a

src/libgavia.a: src/excursion.o
src/libgavia.a: src/canonorder.o src/sortedorder.o src/dynamicorder.o src/taxonomicorder.o
src/libgavia.a: src/speciesredro.o
src/libgavia.a: src/streamsource.o src/gabsource.o
src/libgavia.a: src/streamsink.o src/gabsink.o src/mboxsink.o src/filtersink.o
src/libgavia.a: src/contstream.o
src/libgavia.a: src/motorola.o src/bitmap.o
src/libgavia.a: src/version.o
src/libgavia.a: src/specieslist.o src/exception.o
	$(AR) -r $@ $^

# targets that need special help
src/specieslist.o: src/specieslist.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -DINSTALLBASE=\"$(INSTALLBASE)\" -c -o $@ $<

src/filtersink.o: src/filtersink.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -D_POSIX_C_SOURCE=2 -c -o $@ $<

perl/_gavia_stellata: perl/gavia_stellata.pl
	sed "s|INSTALLBASE|$(INSTALLBASE)|" <$< >$@

perl/_gavia_focus: perl/gavia_focus
	sed "s|INSTALLBASE|$(INSTALLBASE)|" <$< >$@

# misc

.PHONY: test
test: src/test/test
	./src/test/test

src/test/test: src/test/test.o src/test/test_cont.o src/libgavia.a
	$(CXX) $(LDFLAGS) -o $@ src/test/test.o src/test/test_cont.o -lgavia

src/test/test.cc: src/test/test_cont.o
	testicle -o $@ $^

.PHONY: tags
tags: TAGS
TAGS:
	etags src/*.{c,h,cc,hh}

depend:
	makedepend -- $(CFLAGS) -- -Y -I. src/*.{c,cc} src/test/*.cc

clean:
	$(RM) src/test/test
	$(RM) src/test/test.cc
	$(RM) $(OUTS) src/libgavia.a
	$(RM) src/*.o
	$(RM) src/test/*.o
	$(RM) Makefile.bak core TAGS
	$(RM) perl/_gavia_focus
	$(RM) perl/_gavia_stellata

love:
	@echo "not war?"

# installation

.PHONY: install
install: gavia-mode.el
install: install_outs
install: install_man1
install: install_man5
install: install_lib
install: install_perl
	[ -d  $(ELISPDIR) ] && install -m444 gavia-mode.el $(ELISPDIR)

.PHONY: install_outs
install_outs: $(OUTS)
	install -s -m755 $(OUTS) $(INSTALLBASE)/bin/

.PHONY: install_man1
install_man1: doc/gavia.1
install_man1: doc/gavia_add.1 doc/gavia_cat.1
install_man1: doc/gavia_grep.1 doc/gavia_sort.1
install_man1: doc/gavia_stellata.1
install_man1: doc/gavia_stat.1 doc/gavia_focus.1 doc/gavia_score.1
install_man1: doc/gavia_gab2roff.1 doc/gavia_gab2text.1 doc/gavia_gab2html.1
	install -m644 $^ $(INSTALLBASE)/man/man1/

.PHONY: install_man5
install_man5: doc/gavia.5
	install -m644 $^ $(INSTALLBASE)/man/man5/

.PHONY: install_lib
install_lib: lib/species lib/default lib/focus
	[ -d $(INSTALLBASE)/lib ] || mkdir $(INSTALLBASE)/lib
	[ -d $(INSTALLBASE)/lib/gavia ] || mkdir $(INSTALLBASE)/lib/gavia
	install -m644 $^ $(INSTALLBASE)/lib/gavia

.PHONY: install_perl
install_perl: perl/gavia_stat.pl perl/_gavia_stellata perl/_gavia_focus
install_perl: perl/gavia_score
install_perl: perl/gavia_gab2text perl/gavia_gab2roff perl/gavia_gab2html
	install -m555 perl/gavia_stat.pl $(INSTALLBASE)/bin/gavia_stat
	install -m555 perl/_gavia_stellata $(INSTALLBASE)/bin/gavia_stellata
	install -m555 perl/_gavia_focus $(INSTALLBASE)/bin/gavia_focus
	install -m555 perl/gavia_score $(INSTALLBASE)/bin/
	install -m555 perl/gavia_gab2text $(INSTALLBASE)/bin/
	install -m555 perl/gavia_gab2roff $(INSTALLBASE)/bin/
	install -m555 perl/gavia_gab2html $(INSTALLBASE)/bin/

# DO NOT DELETE

src/motorola.o: src/motorola.h
src/bitmap.o: src/bitmap.h
src/canonorder.o: src/canonorder.hh src/speciesorder.hh src/species.hh
src/canonorder.o: src/specieslist.hh
src/contstream.o: src/contstream.hh
src/dynamicorder.o: src/species.hh src/speciesset.hh src/speciesorder.hh
src/dynamicorder.o: src/dynamicorder.hh
src/exception.o: src/exception.hh
src/excursion.o: src/excursion.hh src/species.hh src/speciesset.hh
src/excursion.o: src/exception.hh
src/filtersink.o: src/speciesorder.hh src/species.hh src/exception.hh
src/filtersink.o: src/gabsink.hh src/booksink.hh src/excursion.hh
src/filtersink.o: src/speciesset.hh src/filtersink.hh
src/gabsink.o: src/dynamicorder.hh src/speciesorder.hh src/species.hh
src/gabsink.o: src/speciesset.hh src/exception.hh src/gabsink.hh
src/gabsink.o: src/booksink.hh src/excursion.hh
src/gabsource.o: src/speciesorder.hh src/species.hh src/canonorder.hh
src/gabsource.o: src/speciesredro.hh src/exception.hh src/regex.hh
src/gabsource.o: src/gabsource.hh src/booksource.hh src/excursion.hh
src/gabsource.o: src/speciesset.hh src/contstream.hh
src/gavia_add.o: src/version.hh src/streamsource.hh src/booksource.hh
src/gavia_add.o: src/excursion.hh src/species.hh src/speciesset.hh
src/gavia_add.o: src/gabsource.hh src/contstream.hh src/streamsink.hh
src/gavia_add.o: src/booksink.hh src/canonorder.hh src/speciesorder.hh
src/gavia_add.o: src/exception.hh
src/gavia_cat.o: src/version.hh src/booksink.hh src/excursion.hh
src/gavia_cat.o: src/species.hh src/speciesset.hh src/gabsink.hh
src/gavia_cat.o: src/filtersink.hh src/streamsink.hh src/mboxsink.hh
src/gavia_cat.o: src/speciesorder.hh src/canonorder.hh src/sortedorder.hh
src/gavia_cat.o: src/taxonomicorder.hh src/streamsource.hh src/booksource.hh
src/gavia_cat.o: src/exception.hh
src/gavia_grep.o: src/version.hh src/streamsource.hh src/booksource.hh
src/gavia_grep.o: src/excursion.hh src/species.hh src/speciesset.hh
src/gavia_grep.o: src/streamsink.hh src/booksink.hh src/exception.hh
src/gavia_grep.o: src/canonorder.hh src/speciesorder.hh src/dynamicorder.hh
src/gavia_sort.o: src/version.hh src/excursion.hh src/species.hh
src/gavia_sort.o: src/speciesset.hh src/streamsource.hh src/booksource.hh
src/gavia_sort.o: src/streamsink.hh src/booksink.hh src/exception.hh
src/gavia_sort.o: src/canonorder.hh src/speciesorder.hh
src/mboxsink.o: src/dynamicorder.hh src/speciesorder.hh src/species.hh
src/mboxsink.o: src/speciesset.hh src/exception.hh src/mboxsink.hh
src/mboxsink.o: src/booksink.hh src/excursion.hh
src/sortedorder.o: src/species.hh src/speciesorder.hh src/sortedorder.hh
src/specieslist.o: src/specieslist.hh src/species.hh src/exception.hh
src/speciesredro.o: src/speciesredro.hh src/species.hh src/speciesorder.hh
src/streamsink.o: src/streamsink.hh src/booksink.hh src/excursion.hh
src/streamsink.o: src/species.hh src/speciesset.hh src/canonorder.hh
src/streamsink.o: src/speciesorder.hh src/exception.hh src/bitmap.h
src/streamsink.o: src/motorola.h
src/streamsource.o: src/motorola.h src/bitmap.h src/speciesorder.hh
src/streamsource.o: src/species.hh src/canonorder.hh src/exception.hh
src/streamsource.o: src/streamsource.hh src/booksource.hh src/excursion.hh
src/streamsource.o: src/speciesset.hh
src/taxonomicorder.o: src/taxonomicorder.hh src/speciesorder.hh
src/taxonomicorder.o: src/species.hh src/specieslist.hh
src/version.o: src/version.hh
src/test/test_cont.o: src/contstream.hh
