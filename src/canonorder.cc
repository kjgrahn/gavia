/*----------------------------------------------------------------------------
 *
 * $Id: canonorder.cc,v 1.16 2004-08-04 11:50:50 grahn Exp $
 *
 * canonorder.cc
 *
 * Copyright (c) 1999--2002 Jörgen Grahn <jgrahn@algonet.se>
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
"$Id: canonorder.cc,v 1.16 2004-08-04 11:50:50 grahn Exp $";
}

#include "canonorder.hh"

#include "specieslist.hh"

#include <cassert>

using std::vector;


std::vector<const Species *> CanonOrder::internalcanon;


/*----------------------------------------------------------------------------
 *
 * constructor
 *
 *
 *----------------------------------------------------------------------------
 */
CanonOrder::CanonOrder()
{
    if(!internalcanon.size())
    {
	// fill the class-global list of canonical species names
	// from the likewise global SpeciesList

	const vector<SpeciesList::Item>& sl(SpeciesList().names());
	vector<SpeciesList::Item>::const_iterator i(sl.begin());

	assert(sl.size());

	internalcanon = vector<const Species *>(sl.size());

	while(i<sl.end())
	{
	    internalcanon[i->_no] = &i->_name;

	    ++i;
	}
    }
}


/*----------------------------------------------------------------------------
 *
 * destructor
 *
 *
 *----------------------------------------------------------------------------
 */
CanonOrder::~CanonOrder()
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
const Species& CanonOrder::species(int i) const
{
    assert(i>=0);
    assert(i<end());

    return *internalcanon[i];
}


/*----------------------------------------------------------------------------
 *
 * end()
 *
 *
 *----------------------------------------------------------------------------
 */
int CanonOrder::end() const
{
    return internalcanon.size();
}
