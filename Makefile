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

.PHONY: all
all: src/gavia_cat
all: src/gavia_grep
all: src/gavia_sort
all: src/gavia_score
all: src/gavia_stellata
all: perl/_gavia_focus
all: perl/gavia_stat.pl
all: perl/gavia_gab2html
all: perl/gavia_gab2roff
all: src/test/test

version.c: Makefile mkversion
	./mkversion gavia_{name=Gavia,version=4.5,prefix=$(INSTALLBASE)} $@

CFLAGS=-W -Wall -pedantic -ansi -g -Os
CXXFLAGS=-W -Wall -pedantic -std=c++11 -g -Os

src/gavia_cat: src/gavia_cat.o src/libgavia.a
	$(CXX) $(CXXFLAGS) -o $@ $< -Lsrc -lgavia

src/gavia_grep: src/gavia_grep.o src/libgavia.a
	$(CXX) $(CXXFLAGS) -o $@ $< -Lsrc -lgavia

src/gavia_sort: src/gavia_sort.o src/libgavia.a
	$(CXX) $(CXXFLAGS) -o $@ $< -Lsrc -lgavia

src/gavia_score: src/gavia_score.o src/libgavia.a
	$(CXX) $(CXXFLAGS) -o $@ $< -Lsrc -lgavia

src/gavia_stellata: src/gavia_stellata.o src/libgavia.a
	$(CXX) $(CXXFLAGS) -o $@ $< -Lsrc -lgavia

src/libgavia.a: src/contstream.o
src/libgavia.a: src/files...o
src/libgavia.a: src/taxon.o
src/libgavia.a: src/taxa.o
src/libgavia.a: src/date.o
src/libgavia.a: src/excursion.o
src/libgavia.a: src/excursion_put.o
src/libgavia.a: src/mbox.o
src/libgavia.a: src/indent.o
src/libgavia.a: src/regex.o
src/libgavia.a: src/filetest.o
src/libgavia.a: src/editor.o
src/libgavia.a: src/md5.o
src/libgavia.a: src/md5pp.o
src/libgavia.a: src/utf8.o
src/libgavia.a: version.o
	$(AR) -r $@ $^

# targets that need special help

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
src/test/libtest.a: src/test/test_indent.o
src/test/libtest.a: src/test/test_date.o
src/test/libtest.a: src/test/test_filetest.o
src/test/libtest.a: src/test/test_md5.o
src/test/libtest.a: src/test/test_utf8.o
src/test/libtest.a: src/test/test_lineparse.o
	$(AR) -r $@ $^

src/test/test_%.o: CPPFLAGS+=-Isrc

src/test/test: src/test/test.o src/test/libtest.a src/libgavia.a
	$(CXX) $(CXXFLAGS) -o $@ src/test/test.o -Lsrc/test/ -ltest -Lsrc -lgavia

src/test/test.cc: src/test/libtest.a
	orchis -o $@ $^

.PHONY: tags
tags: TAGS
TAGS:
	etags src/*.{c,h,cc,hh}

.PHONY: clean
clean:
	$(RM) src/test/test
	$(RM) src/test/test.cc
	$(RM) src/gavia_{cat,grep,sort,score,stellata}
	$(RM) version.[co]
	$(RM) src/*.[oa]
	$(RM) src/test/*.[oa]
	$(RM) Makefile.bak core TAGS
	$(RM) perl/_gavia_focus
	$(RM) -r dep

love:
	@echo "not war?"

# installation

.PHONY: install
install: gavia-mode.el
install: src/gavia_cat
install: src/gavia_grep
install: src/gavia_sort
install: src/gavia_score
install: src/gavia_stellata
install: doc/gavia.1
install: doc/gavia_cat.1
install: doc/gavia_focus.1
install: doc/gavia_gab2html.1
install: doc/gavia_gab2roff.1
install: doc/gavia_grep.1
install: doc/gavia_score.1
install: doc/gavia_sort.1
install: doc/gavia_stat.1
install: doc/gavia_stellata.1
install: doc/gavia.5
install: lib/default
install: lib/focus
install: lib/species
install: perl/_gavia_focus
install: perl/gavia_stat.pl
install: perl/gavia_gab2html
install: perl/gavia_gab2roff
	[ -d  $(ELISPDIR) ] && install -m644 gavia-mode.el $(ELISPDIR)
	install -s -m755 src/gavia_{cat,grep,sort,score,stellata} $(INSTALLBASE)/bin/
	install -m644 doc/gavia.1 doc/gavia_{cat,focus,gab2html,gab2roff,grep,score,sort,stat,stellata}.1 $(INSTALLBASE)/man/man1/
	install -m644 doc/gavia.5 $(INSTALLBASE)/man/man5/
	[ -d $(INSTALLBASE)/lib/gavia ] || mkdir -p $(INSTALLBASE)/lib/gavia
	install -m644 lib/{default,focus,species} $(INSTALLBASE)/lib/gavia/
	install -m555 perl/_gavia_focus $(INSTALLBASE)/bin/gavia_focus
	install -m555 perl/gavia_stat.pl $(INSTALLBASE)/bin/gavia_stat
	install -m555 perl/gavia_{gab2html,gab2roff} $(INSTALLBASE)/bin/
	$(RM) $(INSTALLBASE)/bin/gavia_{add,gab2text}
	$(RM) $(INSTALLBASE)/man/man1/gavia_{add,gab2text}.1

# DO NOT DELETE

$(shell mkdir -p dep/src{,/test})
DEPFLAGS=-MT $@ -MMD -MP -MF dep/$*.Td
COMPILE.cc=$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c

%.o: %.cc
	$(COMPILE.cc) $(OUTPUT_OPTION) $<
	mv dep/$*.{Td,d}

dep/%.d: ;
dep/src/%.d: ;
dep/src/test/%.d: ;
-include dep/src/*.d
-include dep/src/test/*.d
