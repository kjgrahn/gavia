/*----------------------------------------------------------------------------
 *
 * $Id: speciesredro.cc,v 1.1 1999-10-24 08:10:53 grahn Exp $
 *
 * speciesredro.cc
 *
 * Copyright (C) 1999 Jörgen Grahn <jorgen.grahn@opensoftware.se>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *----------------------------------------------------------------------------
 *
 *----------------------------------------------------------------------------
 */

static const char rcsid[] =
"$Id: speciesredro.cc,v 1.1 1999-10-24 08:10:53 grahn Exp $";

#include <assert.h>

#include "speciesredro.hh"


/*----------------------------------------------------------------------------
 *
 * constructor
 *
 *
 *----------------------------------------------------------------------------
 */
SpeciesRedro::SpeciesRedro(const SpeciesOrder * speciesorder)
{
    assert(speciesorder);

    int end = speciesorder->end();

    for(int i=0; i!=end; i++)
    {
	species[speciesorder->species(i)] = i;
    }
}


/*----------------------------------------------------------------------------
 *
 * copy constructor
 *
 *
 *----------------------------------------------------------------------------
 */
SpeciesRedro::SpeciesRedro(const SpeciesRedro& obj)
{
    species = obj.species;
}


/*----------------------------------------------------------------------------
 *
 * destructor
 *
 *
 *----------------------------------------------------------------------------
 */
SpeciesRedro::~SpeciesRedro()
{
    ;
}


/*----------------------------------------------------------------------------
 *
 * operator=()
 *
 *
 *----------------------------------------------------------------------------
 */
const SpeciesRedro& SpeciesRedro::operator=(const SpeciesRedro& obj)
{
    species = obj.species;

    return *this;
}


/*----------------------------------------------------------------------------
 *
 * empty()
 *
 *
 *----------------------------------------------------------------------------
 */
bool SpeciesRedro::empty() const
{
    return species.size()==0;
}


/*----------------------------------------------------------------------------
 *
 * ismember()
 *
 *
 *----------------------------------------------------------------------------
 */
bool SpeciesRedro::ismember(const Species& spec) const
{
    return species.count(spec)>0;
}


/*----------------------------------------------------------------------------
 *
 * index()
 *
 *
 *----------------------------------------------------------------------------
 */
int SpeciesRedro::index(const Species& spec)
{
    assert(species.count(spec)>0);

    if(species.count(spec)==0)
    {
	return -1;
    }

    return species[spec];
}
