# $Id: Makefile,v 1.13 2001-12-29 19:14:09 grahn Exp $
#
# Makefile
#
# Copyright (c) 1999--2001 Jörgen Grahn <jgrahn@algonet.se>
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

LDFLAGS =
LIBS = -lfl

SRCS = gavia_add.cc \
       gavia_cat.cc \
       gavia_grep.cc \
       gavia_sort.cc \
       excursion.cc \
       canonorder.cc sortedorder.cc dynamicorder.cc taxonomicorder.cc \
       speciesredro.cc \
       streamsource.cc gabsource.cc \
       streamsink.cc gabsink.cc textsink.cc htmlsink.cc latexsink.cc mboxsink.cc \
       gablexer.cc \
       motorola.c bitmap.c \
       version.cc
OBJS = gavia_add.o  \
       gavia_cat.o  \
       gavia_grep.o  \
       gavia_sort.o  \
       excursion.o  \
       canonorder.o  sortedorder.o  dynamicorder.o  taxonomicorder.o  \
       speciesredro.o  \
       streamsource.o  gabsource.o  \
       streamsink.o  gabsink.o  textsink.o  htmlsink.o  latexsink.o  mboxsink.o  \
       gablexer.o  \
       motorola.o bitmap.o \
       version.o
OUTS = gavia_add gavia_cat gavia_grep gavia_sort

all: $(OUTS)

objs: $(OBJS)

# executables
#

gavia_cat: gavia_cat.o excursion.o streamsource.o streamsink.o gabsink.o textsink.o htmlsink.o latexsink.o mboxsink.o canonorder.o taxonomicorder.o sortedorder.o dynamicorder.o motorola.o bitmap.o version.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)

gavia_add: gavia_add.o excursion.o streamsource.o streamsink.o canonorder.o motorola.o bitmap.o dynamicorder.o gabsource.o gablexer.o speciesredro.o version.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)

gavia_grep: gavia_grep.o canonorder.o dynamicorder.o streamsink.o streamsource.o excursion.o motorola.o bitmap.o version.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)

gavia_sort: gavia_sort.o canonorder.o dynamicorder.o streamsink.o streamsource.o excursion.o motorola.o bitmap.o version.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)

# targets that need special help
#

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

tags: $(SRCS)
	etags *.c *.h *.cc *.hh

depend: $(SRCS)
	makedepend -- $(CFLAGS) -- -Y -I. $(SRCS)

clean:
	rm -f $(OUTS) *.o gablexer.cc Makefile.bak core TAGS

love:
	@echo "not war?"

# DO NOT DELETE

gavia_add.o: version.hh streamsource.hh booksource.hh excursion.hh species.hh
gavia_add.o: speciesset.hh gabsource.hh streamsink.hh booksink.hh
gavia_add.o: canonorder.hh speciesorder.hh exception.hh
gavia_cat.o: version.hh booksink.hh excursion.hh species.hh speciesset.hh
gavia_cat.o: gabsink.hh streamsink.hh textsink.hh htmlsink.hh latexsink.hh
gavia_cat.o: mboxsink.hh speciesorder.hh canonorder.hh sortedorder.hh
gavia_cat.o: taxonomicorder.hh streamsource.hh booksource.hh exception.hh
gavia_grep.o: version.hh streamsource.hh booksource.hh excursion.hh
gavia_grep.o: species.hh speciesset.hh streamsink.hh booksink.hh exception.hh
gavia_grep.o: canonorder.hh speciesorder.hh dynamicorder.hh
gavia_sort.o: version.hh excursion.hh species.hh speciesset.hh
gavia_sort.o: streamsource.hh booksource.hh streamsink.hh booksink.hh
gavia_sort.o: exception.hh canonorder.hh speciesorder.hh
excursion.o: excursion.hh species.hh speciesset.hh
canonorder.o: canonorder.hh speciesorder.hh species.hh
sortedorder.o: species.hh speciesorder.hh sortedorder.hh
dynamicorder.o: species.hh speciesset.hh speciesorder.hh dynamicorder.hh
taxonomicorder.o: taxonomicorder.hh speciesorder.hh species.hh
speciesredro.o: speciesredro.hh species.hh speciesorder.hh
streamsource.o: motorola.h bitmap.h speciesorder.hh species.hh canonorder.hh
streamsource.o: exception.hh streamsource.hh booksource.hh excursion.hh
streamsource.o: speciesset.hh
gabsource.o: speciesorder.hh species.hh canonorder.hh speciesredro.hh
gabsource.o: exception.hh gabsource.hh booksource.hh excursion.hh
gabsource.o: speciesset.hh
streamsink.o: streamsink.hh booksink.hh excursion.hh species.hh speciesset.hh
streamsink.o: canonorder.hh speciesorder.hh exception.hh bitmap.h motorola.h
gabsink.o: dynamicorder.hh speciesorder.hh species.hh speciesset.hh
gabsink.o: exception.hh gabsink.hh booksink.hh excursion.hh
textsink.o: dynamicorder.hh speciesorder.hh species.hh speciesset.hh
textsink.o: exception.hh textsink.hh booksink.hh excursion.hh
htmlsink.o: dynamicorder.hh speciesorder.hh species.hh speciesset.hh
htmlsink.o: exception.hh htmlsink.hh booksink.hh excursion.hh
latexsink.o: dynamicorder.hh speciesorder.hh species.hh speciesset.hh
latexsink.o: exception.hh latexsink.hh booksink.hh excursion.hh
mboxsink.o: dynamicorder.hh speciesorder.hh species.hh speciesset.hh
mboxsink.o: exception.hh mboxsink.hh booksink.hh excursion.hh
gablexer.o: excursion.hh species.hh speciesset.hh exception.hh
gablexer.o: speciesredro.hh speciesorder.hh
motorola.o: motorola.h
bitmap.o: bitmap.h
version.o: version.hh
