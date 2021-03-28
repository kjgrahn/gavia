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
all: gavia_cat
all: gavia_grep
all: gavia_sort
all: gavia_score
all: gavia_stat
all: gavia_stellata
all: perl/_gavia_focus
all: perl/gavia_gab2html
all: perl/gavia_gab2roff
all: test/test

version.c: Makefile mkversion
	./mkversion gavia_{name=Gavia,version=4.12,prefix=$(INSTALLBASE)} $@

CFLAGS=-W -Wall -pedantic -ansi -g -Os
CXXFLAGS=-W -Wall -pedantic -std=c++14 -g -Os
CPPFLAGS=
ARFLAGS=rTP

gavia_cat: gavia_cat.o libgavia.a
	$(CXX) $(CXXFLAGS) -o $@ $< -L. -lgavia

gavia_grep: gavia_grep.o libgavia.a
	$(CXX) $(CXXFLAGS) -o $@ $< -L. -lgavia

gavia_sort: gavia_sort.o libgavia.a
	$(CXX) $(CXXFLAGS) -o $@ $< -L. -lgavia

gavia_score: gavia_score.o libgavia.a
	$(CXX) $(CXXFLAGS) -o $@ $< -L. -lgavia

gavia_stat: gavia_stat.o libgavia.a
	$(CXX) $(CXXFLAGS) -o $@ $< -L. -lgavia

gavia_stellata: gavia_stellata.o libgavia.a
	$(CXX) $(CXXFLAGS) -o $@ $< -L. -lgavia

libgavia.a: contstream.o
libgavia.a: files...o
libgavia.a: taxon.o
libgavia.a: taxa.o
libgavia.a: date.o
libgavia.a: excursion.o
libgavia.a: excursion_put.o
libgavia.a: mbox.o
libgavia.a: indent.o
libgavia.a: regex.o
libgavia.a: filetest.o
libgavia.a: editor.o
libgavia.a: md5.o
libgavia.a: md5pp.o
libgavia.a: utf8.o
libgavia.a: version.o
	$(AR) $(ARFLAGS) $@ $^

# targets that need special help

perl/_gavia_focus: perl/gavia_focus
	sed "s|INSTALLBASE|$(INSTALLBASE)|" <$< >$@

# misc

.PHONY: check checkv
check: test/test
	./test/test
checkv: test/test
	valgrind -q ./test/test -v

test/libtest.a: test/test_cont.o
test/libtest.a: test/test_files.o
test/libtest.a: test/test_indent.o
test/libtest.a: test/test_date.o
test/libtest.a: test/test_filetest.o
test/libtest.a: test/test_md5.o
test/libtest.a: test/test_regex.o
test/libtest.a: test/test_utf8.o
test/libtest.a: test/test_lineparse.o
test/libtest.a: test/test_taxa.o
test/libtest.a: test/test_excursion.o
	$(AR) $(ARFLAGS) $@ $^

test/test_%.o: CPPFLAGS+=-I.

test/test: test/test.o test/libtest.a libgavia.a
	$(CXX) $(CXXFLAGS) -o $@ test/test.o -Ltest/ -ltest -L. -lgavia

test/test.cc: test/libtest.a
	orchis -o $@ $^

.PHONY: tags
tags: TAGS
TAGS:
	etags *.{c,h,cc}

.PHONY: clean
clean:
	$(RM) test/test
	$(RM) test/test.cc
	$(RM) gavia_{cat,grep,sort,score,stat,stellata}
	$(RM) version.[co]
	$(RM) *.[oa]
	$(RM) test/*.[oa]
	$(RM) Makefile.bak core TAGS
	$(RM) perl/_gavia_focus
	$(RM) -r dep

love:
	@echo "not war?"

# installation

.PHONY: install
install: gavia-mode.el
install: gavia_cat
install: gavia_grep
install: gavia_sort
install: gavia_score
install: gavia_stat
install: gavia_stellata
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
install: perl/gavia_gab2html
install: perl/gavia_gab2roff
	[ -d  $(ELISPDIR) ] && install -m644 gavia-mode.el $(ELISPDIR)
	install -s -m755 gavia_{cat,grep,sort,score,stat,stellata} $(INSTALLBASE)/bin/
	install -m644 doc/gavia.1 doc/gavia_{cat,focus,gab2html,gab2roff,grep,score,sort,stat,stellata}.1 $(INSTALLBASE)/man/man1/
	install -m644 doc/gavia.5 $(INSTALLBASE)/man/man5/
	[ -d $(INSTALLBASE)/lib/gavia ] || mkdir -p $(INSTALLBASE)/lib/gavia
	install -m644 lib/{default,focus,species} $(INSTALLBASE)/lib/gavia/
	install -m555 perl/_gavia_focus $(INSTALLBASE)/bin/gavia_focus
	install -m555 perl/gavia_{gab2html,gab2roff} $(INSTALLBASE)/bin/
	$(RM) $(INSTALLBASE)/bin/gavia_{add,gab2text}
	$(RM) $(INSTALLBASE)/man/man1/gavia_{add,gab2text}.1

# DO NOT DELETE

$(shell mkdir -p dep{,/test})
DEPFLAGS=-MT $@ -MMD -MP -MF dep/$*.Td
COMPILE.cc=$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c

%.o: %.cc
	$(COMPILE.cc) $(OUTPUT_OPTION) $<
	@mv dep/$*.{Td,d}

dep/%.d: ;
dep/test/%.d: ;
-include dep/*.d
-include dep/test/*.d
