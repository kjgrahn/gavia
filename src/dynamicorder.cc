/*----------------------------------------------------------------------------
 *
 * $Id: dynamicorder.cc,v 1.3 1999-11-30 22:19:46 grahn Exp $
 *
 * dynamicorder.cc
 *
 * Copyright (c) 1999 Jörgen Grahn <jorgen.grahn@opensoftware.se>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *----------------------------------------------------------------------------
 *
 *----------------------------------------------------------------------------
 */

static const char* rcsid() { rcsid(); return
"$Id: dynamicorder.cc,v 1.3 1999-11-30 22:19:46 grahn Exp $";
}

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
