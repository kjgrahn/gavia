/*----------------------------------------------------------------------------
 *
 * $Id: speciesset.hh,v 1.1 1999-10-24 08:10:53 grahn Exp $
 *
 * speciesset.hh
 *
 * Copyright (C) 1999 Jörgen Grahn <jorgen.grahn@opensoftware.se>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *----------------------------------------------------------------------------
 *
 * A set of Species, implemented as an instance of the STL 'set'.
 *----------------------------------------------------------------------------
 */

#ifndef SPECIESSET_HH
#define SPECIESSET_HH


#include "species.hh"
#include <set>

typedef set<Species> SpeciesSet;

#endif
