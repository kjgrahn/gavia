/*----------------------------------------------------------------------------
 *
 * $Id: speciesredro.cc,v 1.5 2006-01-02 22:15:25 grahn Exp $
 *
 * speciesredro.cc
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
"$Id: speciesredro.cc,v 1.5 2006-01-02 22:15:25 grahn Exp $";
}

#include <cassert>

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
