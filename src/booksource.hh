/*----------------------------------------------------------------------------
 *
 * $Id: booksource.hh,v 1.1 1999-10-24 08:10:52 grahn Exp $
 *
 * booksource.hh
 *
 * Copyright (C) 1999 Jörgen Grahn <jorgen.grahn@opensoftware.se>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *----------------------------------------------------------------------------
 *
 * Something you can pull a series of
 * Excursion objects from, e.g. a
 * Lanius book stream, or whatever.
 *
 * ###
 * Should use a fucking iterator...
 *----------------------------------------------------------------------------
 */

#ifndef BOOKSOURCE_HH
#define BOOKSOURCE_HH

#include "excursion.hh"


class BookSource
{
public:
    virtual Excursion excursion() = 0;
    virtual void next() = 0;
    virtual bool eof() const = 0;
    virtual bool error() const = 0;

    virtual ~BookSource() {}

protected:
private:
    BookSource& operator=(const BookSource&);

};

#endif
