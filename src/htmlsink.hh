/*----------------------------------------------------------------------------
 *
 * $Id: htmlsink.hh,v 1.1 1999-10-24 08:10:52 grahn Exp $
 *
 * htmlsink.hh
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
 * as HTML-formatted text. Renders species lists using a given SpeciesOrder.
 *----------------------------------------------------------------------------
 */

#ifndef HTMLSINK_HH
#define HTMLSINK_HH

#include "booksink.hh"
#include <stdio.h>


class SpeciesOrder;


class HtmlSink: public BookSink
{
public:
    HtmlSink(const SpeciesOrder *, const char *);	// constructor
    HtmlSink(const SpeciesOrder *, FILE *);		// constructor

    virtual ~HtmlSink();				// destructor

    virtual void put(const Excursion&);
    virtual bool error() const;

protected:
private:
    FILE * mfp;
    bool merror;
    const SpeciesOrder * morder;

};

#endif
