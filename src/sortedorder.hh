/*----------------------------------------------------------------------------
 *
 * $Id: sortedorder.hh,v 1.1 1999-10-24 08:10:52 grahn Exp $
 *
 * sortedorder.hh
 *
 * Copyright (C) 1999 Jörgen Grahn <jorgen.grahn@opensoftware.se>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *----------------------------------------------------------------------------
 *
 * A SpeciesOrder created from another SpeciesOrder,
 * but ordered lexicographically.
 * Optionally, only a lexicographical subset.
 *----------------------------------------------------------------------------
 */

#ifndef SORTEDORDER_HH
#define SORTEDORDER_HH

#include <string>
#include "speciesorder.hh"
#include "species.hh"


class SortedOrder: public SpeciesOrder
{
public:
    SortedOrder(const SpeciesOrder *, string="aaaaa", string="ýýýýý");
    SortedOrder(const SortedOrder&);		// copy constructor
    virtual ~SortedOrder();			// destructor

    virtual const SortedOrder& operator=(const SortedOrder&);

    virtual Species species(int) const;
    virtual int end() const;

protected:
private:
    SortedOrder();				// constructor

    const int MAXEND = 1000;

    Species internalspecies[MAXEND];
    int internalend;

};

#endif
