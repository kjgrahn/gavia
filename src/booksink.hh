/*----------------------------------------------------------------------------
 *
 * $Id: booksink.hh,v 1.1 1999-10-24 08:10:52 grahn Exp $
 *
 * booksink.hh
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
 * Excursion objects into, e.g. a
 * Lanius book stream, plain text, LaTeX source,
 * HTML, or whatever.
 *
 *----------------------------------------------------------------------------
 */

#ifndef BOOKSINK_HH
#define BOOKSINK_HH

#include "excursion.hh"


class BookSink
{
public:
    virtual void put(const Excursion&) = 0;
    virtual bool error() const = 0;

    virtual ~BookSink() {}

protected:
private:
    BookSink& operator=(const BookSink&);

};

#endif
