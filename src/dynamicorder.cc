/*----------------------------------------------------------------------------
 *
 * $Id: dynamicorder.cc,v 1.1 1999-10-24 08:10:52 grahn Exp $
 *
 * dynamicorder.cc
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
"$Id: dynamicorder.cc,v 1.1 1999-10-24 08:10:52 grahn Exp $";

#include "species.hh"
#include "speciesset.hh"
#include "speciesorder.hh"

#include "dynamicorder.hh"


/*----------------------------------------------------------------------------
 *
 * constructor
 *
 *
 * Species are taken from the gived SpeciesOrder, and only
 * species in given SpeciesSet are chosen.
 *----------------------------------------------------------------------------
 */
DynamicOrder::DynamicOrder(const SpeciesOrder * obj, const SpeciesSet& set)
{
    assert(obj);
    assert(obj->end() <= MAXEND);

    int j=0;

    for(int i=0; i!=obj->end(); i++)
    {
	if(set.count(obj->species(i)) > 0)
	{
	    internalspecies[j] = obj->species(i);
	    j++;
	}
    }

    internalend = j;
}


/*----------------------------------------------------------------------------
 *
 * copy constructor
 *
 *
 *----------------------------------------------------------------------------
 */
DynamicOrder::DynamicOrder(const DynamicOrder& obj)
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
DynamicOrder::~DynamicOrder()
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
const DynamicOrder& DynamicOrder::operator=(const DynamicOrder& obj)
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
Species DynamicOrder::species(int i) const
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
int DynamicOrder::end() const
{
    return internalend;
}
