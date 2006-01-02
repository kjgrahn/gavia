/*----------------------------------------------------------------------------
 *
 * $Id: sortedorder.cc,v 1.9 2006-01-02 22:15:25 grahn Exp $
 *
 * sortedorder.cc
 *
 * Copyright (c) 1999 Jörgen Grahn
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
"$Id: sortedorder.cc,v 1.9 2006-01-02 22:15:25 grahn Exp $";
}

#include "species.hh"
#include "speciesorder.hh"

#include <cassert>
#include <algorithm>

#include "sortedorder.hh"

using std::string;

static bool less(const Species * a, const Species * b) { return *a<*b;}

/*----------------------------------------------------------------------------
 *
 * constructor
 *
 *
 * Species are taken from the gived SpeciesOrder, and only
 * species in [begin..end[ (if given) are chosen.
 *----------------------------------------------------------------------------
 */
SortedOrder::SortedOrder(const SpeciesOrder * obj)
{
    assert(obj);
    assert(obj->end() <= MAXEND);

    int j=0;

    for(int i=0; i!=obj->end(); i++)
    {
	internalspecies[j] = &obj->species(i);
    }

    internalend = j;

    std::sort(internalspecies, internalspecies+internalend, less);
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
 * species()
 *
 *
 *----------------------------------------------------------------------------
 */
const Species& SortedOrder::species(int i) const
{
    assert(i>=0);
    assert(i<end());

    return *internalspecies[i];
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
