/*----------------------------------------------------------------------------
 *
 * $Id: textsink.hh,v 1.1 1999-10-24 08:10:53 grahn Exp $
 *
 * textsink.hh
 *
 * Copyright (C) 1999 Jörgen Grahn <jorgen.grahn@opensoftware.se>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *----------------------------------------------------------------------------
 *
 * Pushes a series of Excursion objects onto an ANSI C stream
 * as readable text. Renders species lists using a given SpeciesOrder.
 *----------------------------------------------------------------------------
 */

#ifndef TEXTSINK_HH
#define TEXTSINK_HH

#include "booksink.hh"
#include <stdio.h>


class SpeciesOrder;


class TextSink: public BookSink
{
public:
    TextSink(const SpeciesOrder *, const char *);	// constructor
    TextSink(const SpeciesOrder *, FILE *);		// constructor

    virtual ~TextSink();				// destructor

    virtual void put(const Excursion&);
    virtual bool error() const;

protected:
private:
    FILE * mfp;
    bool merror;
    const SpeciesOrder * morder;

};

#endif
