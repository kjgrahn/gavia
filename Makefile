# $Id: Makefile,v 1.7 2011-06-08 21:27:25 grahn Exp $
#
# Makefile
#
# Copyright (c) 2000-2007, 2013 Jörgen Grahn
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

SHELL=/bin/bash

INSTALLBASE=/usr/local
ELISPDIR=$(INSTALLBASE)/share/emacs/site-lisp

CFLAGS=-W -Wall -pedantic -ansi -g -Os
CXXFLAGS=-W -Wall -pedantic -std=c++98 -g -Os

all: src/gavia_cat
all: src/gavia_grep
all: src/gavia_sort
all: src/gavia_stellata

src/gavia_cat: src/gavia_cat.o src/libgavia.a
	$(CXX) $(CXXFLAGS) -o $@ $< -Lsrc -lgavia

src/gavia_grep: src/gavia_grep.o src/libgavia.a
	$(CXX) $(CXXFLAGS) -o $@ $< -Lsrc -lgavia

src/gavia_sort: src/gavia_sort.o src/libgavia.a
	$(CXX) $(CXXFLAGS) -o $@ $< -Lsrc -lgavia

src/gavia_stellata: src/gavia_stellata.o src/libgavia.a
	$(CXX) $(CXXFLAGS) -o $@ $< -Lsrc -lgavia

src/libgavia.a: src/contstream.o
src/libgavia.a: src/files...o
src/libgavia.a: src/motorola.o src/bitmap.o
src/libgavia.a: src/version.o
src/libgavia.a: src/exception.o
src/libgavia.a: src/taxon.o
src/libgavia.a: src/taxa.o
src/libgavia.a: src/date.o
src/libgavia.a: src/excursion.o
src/libgavia.a: src/excursion_put.o
src/libgavia.a: src/regex.o
src/libgavia.a: src/filetest.o
src/libgavia.a: src/editor.o
src/libgavia.a: src/md5.o
src/libgavia.a: src/md5pp.o
src/libgavia.a: version.o
	$(AR) -r $@ $^

# targets that need special help

version.c: Makefile mkversion
	./mkversion gavia_{name=Gavia,version=4.0,prefix=$(INSTALLBASE)} $@

src/specieslist.o: src/specieslist.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -DINSTALLBASE=\"$(INSTALLBASE)\" -c -o $@ $<

src/filtersink.o: src/filtersink.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -D_POSIX_C_SOURCE=2 -c -o $@ $<

perl/_gavia_stellata: perl/gavia_stellata.pl
	sed "s|INSTALLBASE|$(INSTALLBASE)|" <$< >$@

perl/_gavia_focus: perl/gavia_focus
	sed "s|INSTALLBASE|$(INSTALLBASE)|" <$< >$@

# misc

.PHONY: check checkv
check: src/test/test
	./src/test/test
checkv: src/test/test
	valgrind -q ./src/test/test -v

src/test/libtest.a: src/test/test_cont.o
src/test/libtest.a: src/test/test_taxon.o
src/test/libtest.a: src/test/test_files.o
src/test/libtest.a: src/test/test_date.o
src/test/libtest.a: src/test/test_filetest.o
src/test/libtest.a: src/test/test_md5.o
	$(AR) -r $@ $^

src/test/test_%.o: CPPFLAGS+=-Isrc

src/test/test: src/test/test.o src/test/libtest.a src/libgavia.a
	$(CXX) $(CXXFLAGS) -o $@ src/test/test.o -Lsrc/test/ -ltest -Lsrc -lgavia

src/test/test.cc: src/test/libtest.a
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
	$(RM) src/gavia_{cat,grep,sort,stellata}
	$(RM) src/*.[oa]
	$(RM) src/test/*.[oa]
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
install_outs: src/gavia_cat
install_outs: src/gavia_grep
install_outs: src/gavia_sort
install_outs: src/gavia_stellata
	install -s -m755 $^ $(INSTALLBASE)/bin/

.PHONY: install_man1
install_man1: doc/gavia.1
install_man1: doc/gavia_cat.1
install_man1: doc/gavia_grep.1 doc/gavia_sort.1
install_man1: doc/gavia_stellata.1
install_man1: doc/gavia_stat.1 doc/gavia_focus.1 doc/gavia_score.1
install_man1: doc/gavia_gab2roff.1 doc/gavia_gab2html.1
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
install_perl: perl/gavia_gab2roff perl/gavia_gab2html
	install -m555 perl/gavia_stat.pl $(INSTALLBASE)/bin/gavia_stat
	install -m555 perl/_gavia_stellata $(INSTALLBASE)/bin/gavia_stellata
	install -m555 perl/_gavia_focus $(INSTALLBASE)/bin/gavia_focus
	install -m555 perl/gavia_score $(INSTALLBASE)/bin/
	install -m555 perl/gavia_gab2roff $(INSTALLBASE)/bin/
	install -m555 perl/gavia_gab2html $(INSTALLBASE)/bin/

# DO NOT DELETE

src/md5.o: src/md5.h
src/motorola.o: src/motorola.h
src/bitmap.o: src/bitmap.h
src/canonorder.o: src/canonorder.hh src/speciesorder.hh src/specieslist.hh
src/contstream.o: src/contstream.hh
src/date.o: src/date.h
src/dynamicorder.o: src/speciesset.hh src/speciesorder.hh src/dynamicorder.hh
src/editor.o: src/editor.h
src/exception.o: src/exception.hh
src/excursion.o: src/excursion.hh src/taxon.h src/date.h src/taxa.h
src/excursion.o: src/lineparse.h src/files...h
src/excursion_put.o: src/excursion.hh src/taxon.h src/date.h
src/files...o: src/files...h
src/filetest.o: src/filetest.h
src/filtersink.o: src/speciesorder.hh src/exception.hh src/filtersink.hh
src/filtersink.o: src/booksink.hh src/excursion.hh src/taxon.h src/date.h
src/gabsink.o: src/dynamicorder.hh src/speciesorder.hh src/speciesset.hh
src/gabsink.o: src/exception.hh
src/gabsource.o: src/speciesorder.hh src/canonorder.hh src/speciesredro.hh
src/gabsource.o: src/exception.hh src/regex.hh src/gabsource.hh
src/gabsource.o: src/booksource.hh src/excursion.hh src/taxon.h src/date.h
src/gabsource.o: src/contstream.hh
src/gavia_cat.o: src/files...h src/taxa.h src/taxon.h src/excursion.hh
src/gavia_cat.o: src/date.h
src/gavia_grep.o: src/files...h src/taxa.h src/taxon.h src/excursion.hh
src/gavia_grep.o: src/date.h src/regex.hh
src/gavia_sort.o: src/files...h src/taxa.h src/taxon.h src/excursion.hh
src/gavia_sort.o: src/date.h
src/gavia_stellata.o: src/taxa.h src/taxon.h src/files...h src/excursion.hh
src/gavia_stellata.o: src/date.h src/lineparse.h src/editor.h src/filetest.h
src/gavia_stellata.o: src/md5pp.h src/md5.h
src/mboxsink.o: src/dynamicorder.hh src/speciesorder.hh src/speciesset.hh
src/mboxsink.o: src/exception.hh src/mboxsink.hh src/booksink.hh
src/mboxsink.o: src/excursion.hh src/taxon.h src/date.h
src/md5pp.o: src/md5pp.h src/md5.h
src/regex.o: src/regex.hh
src/sortedorder.o: src/speciesorder.hh src/sortedorder.hh
src/specieslist.o: src/specieslist.hh src/exception.hh
src/speciesredro.o: src/speciesredro.hh src/speciesorder.hh
src/streamsink.o: src/streamsink.hh src/booksink.hh src/excursion.hh
src/streamsink.o: src/taxon.h src/date.h src/canonorder.hh
src/streamsink.o: src/speciesorder.hh src/speciesset.hh src/exception.hh
src/streamsink.o: src/bitmap.h src/motorola.h
src/streamsource.o: src/motorola.h src/bitmap.h src/speciesorder.hh
src/streamsource.o: src/canonorder.hh src/exception.hh src/streamsource.hh
src/streamsource.o: src/booksource.hh src/excursion.hh src/taxon.h src/date.h
src/taxa.o: src/taxa.h src/taxon.h src/lineparse.h
src/taxon.o: src/taxon.h src/regex.hh
src/taxonomicorder.o: src/taxonomicorder.hh src/speciesorder.hh
src/taxonomicorder.o: src/specieslist.hh
src/version.o: src/version.hh
src/test/test_cont.o: src/contstream.hh
src/test/test_date.o: src/date.h
src/test/test_files.o: src/files...h
src/test/test_filetest.o: src/filetest.h
src/test/test_md5.o: src/md5.h src/md5pp.h
src/test/test_taxon.o: src/taxa.h src/taxon.h
