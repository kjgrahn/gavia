/*----------------------------------------------------------------------------
 *
 * $Id: dynamicorder.hh,v 1.1 1999-10-24 08:10:52 grahn Exp $
 *
 * dynamicorder.hh
 *
 * Copyright (C) 1999 Jörgen Grahn <jorgen.grahn@opensoftware.se>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *----------------------------------------------------------------------------
 *
 * A SpeciesOrder as the one given as an argument, but
 * containing only the Species in the Species set (also given)
 *
 * (SpeciesOrder, Species set) --> SpeciesOrder
 *----------------------------------------------------------------------------
 */

#ifndef DYNAMICORDER_HH
#define DYNAMICORDER_HH

#include "speciesorder.hh"
#include "species.hh"
#include "speciesset.hh"


class DynamicOrder: public SpeciesOrder
{
public:
    DynamicOrder(const SpeciesOrder *, const SpeciesSet&);
    DynamicOrder(const DynamicOrder&);		// copy constructor
    virtual ~DynamicOrder();			// destructor

    virtual const DynamicOrder& operator=(const DynamicOrder&);

    virtual Species species(int) const;
    virtual int end() const;

protected:
private:
    DynamicOrder();				// constructor

    const int MAXEND = 1000;

    Species internalspecies[MAXEND];
    int internalend;

};

#endif
