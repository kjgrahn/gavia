/*----------------------------------------------------------------------------
 *
 * $Id: speciesredro.hh,v 1.3 1999-11-30 22:19:46 grahn Exp $
 *
 * speciesredro.hh
 *
 * Copyright (c) 1999 J�rgen Grahn <jorgen.grahn@opensoftware.se>
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

    std::map<Species, int> species;

};

#endif
