# $Id: Makefile,v 1.17 2004-01-04 14:10:41 grahn Exp $
#
# Makefile
#
# Copyright (c) 1999--2004 Jörgen Grahn <jgrahn@algonet.se>
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

# Sun's compilers:
#CFLAGS = -g
#CPPFLAGS = -g -features=no%conststrings

# GCC:
CPPFLAGS = -DUSE_GETOPT_H -DUSE_HASHMAP
CFLAGS = -Wall -pedantic -ansi -g -O2
CXXFLAGS = -Wall -pedantic -ansi -g -O2

LDFLAGS = -L.

OBJS = excursion.o \
       canonorder.o sortedorder.o dynamicorder.o taxonomicorder.o \
       speciesredro.o \
       streamsource.o gabsource.o \
       streamsink.o gabsink.o mboxsink.o filtersink.o \
       gablexer.o \
       motorola.o bitmap.o \
       version.o specieslist.o exception.o
OUTS = gavia_add gavia_cat gavia_grep gavia_sort

all: $(OUTS)

objs: $(OBJS) \
       gavia_add.o \
       gavia_cat.o \
       gavia_grep.o \
       gavia_sort.o

libgavia.a: $(OBJS)
	$(AR) -r $@ $^

# executables
#

gavia_cat: gavia_cat.o libgavia.a
	$(CXX) $(LDFLAGS) -o $@ $< -lgavia

gavia_add: gavia_add.o libgavia.a
	$(CXX) $(LDFLAGS) -o $@ $< -lgavia -lfl

gavia_grep: gavia_grep.o libgavia.a
	$(CXX) $(LDFLAGS) -o $@ $< -lgavia

gavia_sort: gavia_sort.o libgavia.a
	$(CXX) $(LDFLAGS) -o $@ $< -lgavia

# targets that need special help
#

specieslist.o: specieslist.cc
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) -DINSTALLBASE=\"$(INSTALLBASE)\" $<

filtersink.o: filtersink.cc
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) -D_POSIX_C_SOURCE=2 $<

gablexer.cc: gablexer.l
	flex -ist8 gablexer.l >$@

gablexer.o: gablexer.cc
	$(CXX) -c -g $<

# utility targets
#

install: $(OUTS)
	strip $(OUTS)
	install -m755 $(OUTS) $(INSTALLBASE)/bin/

TAGS: tags

tags:
	etags *.c *.h *.cc *.hh

depend:
	makedepend -- $(CFLAGS) -- -Y -I. *.c *.cc

clean:
	rm -f $(OUTS) *.o *.a gablexer.cc Makefile.bak core TAGS

love:
	@echo "not war?"

# DO NOT DELETE

bitmap.o: bitmap.h
motorola.o: motorola.h
canonorder.o: canonorder.hh speciesorder.hh species.hh specieslist.hh
dynamicorder.o: species.hh speciesset.hh speciesorder.hh dynamicorder.hh
exception.o: exception.hh
excursion.o: excursion.hh species.hh speciesset.hh
filtersink.o: speciesorder.hh species.hh exception.hh gabsink.hh booksink.hh
filtersink.o: excursion.hh speciesset.hh filtersink.hh
gablexer.o: excursion.hh species.hh speciesset.hh exception.hh
gablexer.o: speciesredro.hh speciesorder.hh
gabsink.o: dynamicorder.hh speciesorder.hh species.hh speciesset.hh
gabsink.o: exception.hh gabsink.hh booksink.hh excursion.hh
gabsource.o: speciesorder.hh species.hh canonorder.hh speciesredro.hh
gabsource.o: exception.hh gabsource.hh booksource.hh excursion.hh
gabsource.o: speciesset.hh
gavia_add.o: version.hh streamsource.hh booksource.hh excursion.hh species.hh
gavia_add.o: speciesset.hh gabsource.hh streamsink.hh booksink.hh
gavia_add.o: canonorder.hh speciesorder.hh exception.hh
gavia_cat.o: version.hh booksink.hh excursion.hh species.hh speciesset.hh
gavia_cat.o: gabsink.hh filtersink.hh streamsink.hh mboxsink.hh
gavia_cat.o: speciesorder.hh canonorder.hh sortedorder.hh taxonomicorder.hh
gavia_cat.o: streamsource.hh booksource.hh exception.hh
gavia_grep.o: version.hh streamsource.hh booksource.hh excursion.hh
gavia_grep.o: species.hh speciesset.hh streamsink.hh booksink.hh exception.hh
gavia_grep.o: canonorder.hh speciesorder.hh dynamicorder.hh
gavia_sort.o: version.hh excursion.hh species.hh speciesset.hh
gavia_sort.o: streamsource.hh booksource.hh streamsink.hh booksink.hh
gavia_sort.o: exception.hh canonorder.hh speciesorder.hh
mboxsink.o: dynamicorder.hh speciesorder.hh species.hh speciesset.hh
mboxsink.o: exception.hh mboxsink.hh booksink.hh excursion.hh
sortedorder.o: species.hh speciesorder.hh sortedorder.hh
specieslist.o: specieslist.hh species.hh exception.hh
speciesredro.o: speciesredro.hh species.hh speciesorder.hh
streamsink.o: streamsink.hh booksink.hh excursion.hh species.hh speciesset.hh
streamsink.o: canonorder.hh speciesorder.hh exception.hh bitmap.h motorola.h
streamsource.o: motorola.h bitmap.h speciesorder.hh species.hh canonorder.hh
streamsource.o: exception.hh streamsource.hh booksource.hh excursion.hh
streamsource.o: speciesset.hh
taxonomicorder.o: taxonomicorder.hh speciesorder.hh species.hh specieslist.hh
version.o: version.hh
