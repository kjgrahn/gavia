/*----------------------------------------------------------------------------
 *
 * $Id: sortedorder.hh,v 1.8 2004-08-04 11:50:50 grahn Exp $
 *
 * sortedorder.hh
 *
 * Copyright (c) 1999, 2000 Jörgen Grahn <jgrahn@algonet.se>
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
 * A SpeciesOrder created from another SpeciesOrder,
 * but ordered lexicographically.
 * Optionally, only a lexicographical subset.
 *----------------------------------------------------------------------------
 */

#ifndef SORTEDORDER_HH
#define SORTEDORDER_HH

#include <string>
#include "speciesorder.hh"
#include "species.hh"


class SortedOrder: public SpeciesOrder
{
public:
    SortedOrder(const SpeciesOrder *, std::string="aaaaa", std::string="ýýýýý");
    virtual ~SortedOrder();			// destructor

    virtual const Species& species(int) const;
    virtual int end() const;

protected:
private:
    SortedOrder();				// constructor
    SortedOrder(const SortedOrder&);
    const SortedOrder& operator=(const SortedOrder&);

    static const int MAXEND = 1000;

    const Species * internalspecies[MAXEND];
    int internalend;

};

#endif
