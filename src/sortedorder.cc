/*----------------------------------------------------------------------------
 *
 * $Id: sortedorder.cc,v 1.1 1999-10-24 08:10:52 grahn Exp $
 *
 * sortedorder.cc
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
"$Id: sortedorder.cc,v 1.1 1999-10-24 08:10:52 grahn Exp $";

#include "species.hh"
#include "speciesorder.hh"

#include <algorithm>

#include "sortedorder.hh"


/*----------------------------------------------------------------------------
 *
 * constructor
 *
 *
 * Species are taken from the gived SpeciesOrder, and only
 * species in [begin..end[ (if given) are chosen.
 *----------------------------------------------------------------------------
 */
SortedOrder::SortedOrder(const SpeciesOrder * obj, string begin, string end)
{
    assert(obj);
    assert(obj->end() <= MAXEND);

    int j=0;

    for(int i=0; i!=obj->end(); i++)
    {
	if((obj->species(i) >= begin) && (obj->species(i) < end))
	{
	    internalspecies[j] = obj->species(i);
	    j++;
	}
    }

    internalend = j;

    sort(internalspecies, internalspecies+internalend);
}


/*----------------------------------------------------------------------------
 *
 * copy constructor
 *
 *
 *----------------------------------------------------------------------------
 */
SortedOrder::SortedOrder(const SortedOrder& obj)
{
    for(int i=0; i!=MAXEND; i++)
    {
	internalspecies[i] = obj.internalspecies[i];
    }

    internalend = obj.internalend;
}


/*----------------------------------------------------------------------------
 *
 * destructor
 *
 *
 *----------------------------------------------------------------------------
 */
SortedOrder::~SortedOrder()
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
const SortedOrder& SortedOrder::operator=(const SortedOrder& obj)
{
    for(int i=0; i!=MAXEND; i++)
    {
	internalspecies[i] = obj.internalspecies[i];
    }

    internalend = obj.internalend;

    return *this;
}


/*----------------------------------------------------------------------------
 *
 * species()
 *
 *
 *----------------------------------------------------------------------------
 */
Species SortedOrder::species(int i) const
{
    assert(i>=0);
    assert(i<end());

    return internalspecies[i];
}


/*----------------------------------------------------------------------------
 *
 * end()
 *
 *
 *----------------------------------------------------------------------------
 */
int SortedOrder::end() const
{
    return internalend;
}
