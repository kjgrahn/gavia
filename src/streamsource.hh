/*----------------------------------------------------------------------------
 *
 * $Id: streamsource.hh,v 1.1 1999-10-24 08:10:53 grahn Exp $
 *
 * streamsource.hh
 *
 * Copyright (C) 1999 Jörgen Grahn <jorgen.grahn@opensoftware.se>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *----------------------------------------------------------------------------
 *
 * A BookSource using an ANSI C stream
 * (in "Lanius" binary format) for data source.
 *----------------------------------------------------------------------------
 */

#ifndef STREAMSOURCE_HH
#define STREAMSOURCE_HH

#include "booksource.hh"
#include <stdio.h>


class SpeciesOrder;


class StreamSource: public BookSource
{
public:
    StreamSource(const char *);		// constructor
    StreamSource(FILE *);		// constructor

    virtual ~StreamSource();		// destructor

    virtual Excursion excursion();
    virtual void next();
    virtual bool eof() const;
    virtual bool error() const;

protected:
private:
    Excursion mexcursion;
    int mstate;
    FILE * mfp;

    SpeciesOrder * morder;

};

#endif
