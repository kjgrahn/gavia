/*----------------------------------------------------------------------------
 *
 * $Id: speciesredro.hh,v 1.1 1999-10-24 08:10:53 grahn Exp $
 *
 * speciesredro.hh
 *
 * Copyright (C) 1999 Jörgen Grahn <jorgen.grahn@opensoftware.se>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *----------------------------------------------------------------------------
 *
 * Given a SpeciesOrder (mapping [0..n[ -> Species),
 * generate the inverse mapping Species->[0..n[.
 *
 * Since the original mapping is one-to-one, this one
 * covers the range [0..n[ completely.
 *----------------------------------------------------------------------------
 */

#ifndef SPECIESREDRO_HH
#define SPECIESREDRO_HH

#include <map>
#include "species.hh"
#include "speciesorder.hh"


class SpeciesRedro
{
public:
    SpeciesRedro(const SpeciesOrder *);		// constructor
    SpeciesRedro(const SpeciesRedro&);		// copy constructor

    virtual ~SpeciesRedro();			// destructor

    const SpeciesRedro& operator=(const SpeciesRedro&);

    bool empty() const;
    bool ismember(const Species&) const;
    int index(const Species&);

protected:
private:
    SpeciesRedro();				// constructor

    map<Species, int> species;

};

#endif
