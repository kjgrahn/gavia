/*----------------------------------------------------------------------------
 *
 * $Id: gabsource.hh,v 1.1 1999-10-24 08:10:52 grahn Exp $
 *
 * gabsource.hh
 *
 * Copyright (C) 1999 Jörgen Grahn <jorgen.grahn@opensoftware.se>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *----------------------------------------------------------------------------
 *
 * A BookSource using a text file in "GAB" format
 * for data source.
 *
 * This "GAB" format is suitable for hand editing using any
 * text editor.
 *
 * (i) rows matching [ ]*#.* are discarded
 *
 * (ii) the remainder matches
 *      excursion*
 *
 *      excursion ::=
 *      {
 *      place:.+
 *      date:.+
 *      time:.+
 *      observers:.+
 *      weather:.+
 *      comments:.+
 *      }{
 *      speciesdata*
 *      }
 *
 *      speciesdata::=
 *      name:existancemarker?:nofindividuals?:comment?
 *
 *      but with whitespace (tabs and spaces) allowed
 *      where applicable and trimmed where it makes sense.
 *
 * Well, that's the general idea anyway...
 *----------------------------------------------------------------------------
 */

#ifndef GABSOURCE_HH
#define GABSOURCE_HH

#include "booksource.hh"
#include <stdio.h>


class SpeciesRedro;


class GabSource: public BookSource
{
public:
    GabSource(const char *);	// constructor
    GabSource(FILE *);		// constructor

    virtual ~GabSource();	// destructor

    virtual Excursion excursion();
    virtual void next();
    virtual bool eof() const;
    virtual bool error() const;

    // virtual string errstring() const;

protected:
private:
    Excursion mexcursion;
    int mstate;
    FILE * mfp;
    SpeciesRedro * redro;

};

#endif
