# $Id: Makefile,v 1.2 1999-10-24 09:00:45 grahn Exp $
#
# Makefile
#
# Copyright (C) 1999 Jörgen Grahn <jorgen.grahn@opensoftware.se>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#

SHELL = /bin/sh

CFLAGS = -Wall -pedantic -ansi -g
CPPFLAGS = -Wall -g
LDFLAGS =
LIBS = -lfl

SRCS = gavia_add.cc \
       gavia_cat.cc \
       gavia_grep.cc \
       excursion.cc \
       canonorder.cc sortedorder.cc dynamicorder.cc taxonomicorder.cc \
       speciesredro.cc \
       streamsource.cc gabsource.cc \
       streamsink.cc textsink.cc htmlsink.cc latexsink.cc \
       gablexer.cc \
       motorola.c bitmap.c
OBJS = gavia_add.o  \
       gavia_cat.o  \
       gavia_grep.o  \
       excursion.o  \
       canonorder.o  sortedorder.o  dynamicorder.o  taxonomicorder.o  \
       speciesredro.o  \
       streamsource.o  gabsource.o  \
       streamsink.o  textsink.o  htmlsink.o  latexsink.o  \
       gablexer.o  \
       motorola.o bitmap.o
OUTS = gavia_add gavia_cat gavia_grep gavia_sort gavia_stat

OBSOLETE = test.cc exeditor.cc exeditor.hh

all: $(OUTS)

objs: $(OBJS)

gavia_cat: gavia_cat.o excursion.o streamsource.o streamsink.o textsink.o htmlsink.o latexsink.o canonorder.o taxonomicorder.o sortedorder.o dynamicorder.o motorola.o bitmap.o
	g++ $(LDFLAGS) -o $@ $^ $(LIBS)

gavia_add: gavia_add.o excursion.o streamsource.o streamsink.o canonorder.o motorola.o bitmap.o dynamicorder.o gabsource.o gablexer.o speciesredro.o
	g++ $(LDFLAGS) -o $@ $^ $(LIBS)

gavia_grep: gavia_grep.o canonorder.o dynamicorder.o streamsink.o streamsource.o excursion.o motorola.o bitmap.o
	g++ $(LDFLAGS) -o $@ $^ $(LIBS)

gavia_sort:
	@echo "gavia_sort is not yet implemented"

gavia_stat:
	@echo "gavia_stat is not yet implemented"

gablexer.cc: gablexer.l
	flex -ist8 gablexer.l >gablexer.cc

install:
	false

TAGS: tags

tags: $(SRCS)
	etags *.c *.h *.cc *.hh

depend: $(SRCS)
	makedepend -- $(CFLAGS) -- -Y $(SRCS)

clean:
	rm -f $(OUTS) *.o gablexer.cc Makefile.bak core TAGS

love:
	@echo "not war?"

# DO NOT DELETE

gavia_add.o: version.hh streamsource.hh booksource.hh excursion.hh species.hh
gavia_add.o: speciesset.hh gabsource.hh streamsink.hh booksink.hh
gavia_add.o: canonorder.hh speciesorder.hh
gavia_cat.o: version.hh booksink.hh excursion.hh species.hh speciesset.hh
gavia_cat.o: streamsink.hh textsink.hh htmlsink.hh latexsink.hh
gavia_cat.o: speciesorder.hh canonorder.hh sortedorder.hh taxonomicorder.hh
gavia_cat.o: streamsource.hh booksource.hh
gavia_grep.o: version.hh excursion.hh species.hh speciesset.hh
gavia_grep.o: streamsource.hh booksource.hh streamsink.hh booksink.hh
gavia_grep.o: canonorder.hh speciesorder.hh dynamicorder.hh
excursion.o: excursion.hh species.hh speciesset.hh
canonorder.o: canonorder.hh speciesorder.hh species.hh
sortedorder.o: species.hh speciesorder.hh sortedorder.hh
dynamicorder.o: species.hh speciesset.hh speciesorder.hh dynamicorder.hh
taxonomicorder.o: taxonomicorder.hh speciesorder.hh species.hh
speciesredro.o: speciesredro.hh species.hh speciesorder.hh
streamsource.o: motorola.h bitmap.h speciesorder.hh species.hh canonorder.hh
streamsource.o: streamsource.hh booksource.hh excursion.hh speciesset.hh
gabsource.o: speciesorder.hh species.hh canonorder.hh speciesredro.hh
gabsource.o: gabsource.hh booksource.hh excursion.hh speciesset.hh
streamsink.o: streamsink.hh booksink.hh excursion.hh species.hh speciesset.hh
streamsink.o: canonorder.hh speciesorder.hh bitmap.h motorola.h
textsink.o: dynamicorder.hh speciesorder.hh species.hh speciesset.hh
textsink.o: textsink.hh booksink.hh excursion.hh
htmlsink.o: dynamicorder.hh speciesorder.hh species.hh speciesset.hh
htmlsink.o: htmlsink.hh booksink.hh excursion.hh
latexsink.o: dynamicorder.hh speciesorder.hh species.hh speciesset.hh
latexsink.o: latexsink.hh booksink.hh excursion.hh
gablexer.o: excursion.hh species.hh speciesset.hh speciesredro.hh
gablexer.o: speciesorder.hh
motorola.o: motorola.h
bitmap.o: bitmap.h
