/*----------------------------------------------------------------------------
 *
 * $Id: taxonomicorder.hh,v 1.1 1999-10-24 08:10:53 grahn Exp $
 *
 * taxonomicorder.hh
 *
 * Copyright (C) 1999 Jörgen Grahn <jorgen.grahn@opensoftware.se>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *----------------------------------------------------------------------------
 *
 * The taxonomic ordering of all Species.
 *----------------------------------------------------------------------------
 */

#ifndef TAXONOMICORDER_HH
#define TAXONOMICORDER_HH

#include "speciesorder.hh"
#include "species.hh"


class TaxonomicOrder: public SpeciesOrder
{
public:
    TaxonomicOrder();				// constructor
    TaxonomicOrder(const TaxonomicOrder&);	// copy constructor

    virtual ~TaxonomicOrder();			// destructor

    virtual const TaxonomicOrder& operator=(const SpeciesOrder&);

    virtual Species species(int) const;
    virtual int end() const;

protected:
private:

};

#endif
