/*----------------------------------------------------------------------------
 *
 * $Id: canonorder.hh,v 1.1 1999-10-24 08:10:52 grahn Exp $
 *
 * canonorder.hh
 *
 * Copyright (C) 1999 Jörgen Grahn <jorgen.grahn@opensoftware.se>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *----------------------------------------------------------------------------
 *
 * The canonical ordering of all Species.
 *----------------------------------------------------------------------------
 */

#ifndef CANONORDER_HH
#define CANONORDER_HH

#include "speciesorder.hh"
#include "species.hh"


class CanonOrder: public SpeciesOrder
{
public:
    CanonOrder();				// constructor
    CanonOrder(const CanonOrder&);		// copy constructor

    virtual ~CanonOrder();			// destructor

    virtual const CanonOrder& operator=(const SpeciesOrder&);

    virtual Species species(int) const;
    virtual int end() const;

protected:
private:

};

#endif
