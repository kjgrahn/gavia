/*----------------------------------------------------------------------------
 *
 * $Id: streamsink.hh,v 1.1 1999-10-24 08:10:53 grahn Exp $
 *
 * streamsink.hh
 *
 * Copyright (C) 1999 Jörgen Grahn <jorgen.grahn@opensoftware.se>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *----------------------------------------------------------------------------
 *
 * Something you can push a series of
 * Excursion objects into, in this case a
 * Lanius book stream.
 *----------------------------------------------------------------------------
 */

#ifndef STREAMSINK_HH
#define STREAMSINK_HH

#include "booksink.hh"
#include <stdio.h>

class StreamSink: public BookSink
{
public:
    StreamSink(const char *);				// constructor
    StreamSink(FILE *);					// constructor

    virtual ~StreamSink();				// destructor

    virtual void put(const Excursion&);
    virtual bool error() const;

protected:
private:
    FILE * mfp;
    bool merror;

};

#endif
