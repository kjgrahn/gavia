/*----------------------------------------------------------------------------
 *
 * $Id: roffsink.hh,v 1.1 2002-08-11 20:43:05 grahn Exp $
 *
 * roffsink.hh
 *
 * Copyright (c) 2002 Jörgen Grahn <jgrahn@algonet.se>
 * All rights reserved.
 *
 *----------------------------------------------------------------------------
 *
 * Pushes a series of Excursion objects onto an ANSI C stream
 * in {,g,n,t}roff format.
 * Renders species lists using a given SpeciesOrder.
 *----------------------------------------------------------------------------
 */

#ifndef ROFFSINK_HH
#define ROFFSINK_HH

#include "booksink.hh"
#include <stdio.h>


class SpeciesOrder;


class RoffSink: public BookSink
{
public:
    RoffSink(const SpeciesOrder *, const char *);	// constructor
    RoffSink(const SpeciesOrder *, FILE *);		// constructor

    virtual ~RoffSink();				// destructor

    virtual void put(const Excursion&);

protected:
private:
    FILE * mfp;
    const SpeciesOrder * morder;

};

#endif
