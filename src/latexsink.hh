/*----------------------------------------------------------------------------
 *
 * $Id: latexsink.hh,v 1.5 2001-12-29 19:14:09 grahn Exp $
 *
 * latexsink.hh
 *
 * Copyright (c) 1999, 2001 Jörgen Grahn <jgrahn@algonet.se>
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
 * Pushes a series of Excursion objects onto an ANSI C stream
 * as LaTeX2e-formatted text.
 * Renders species lists using a given SpeciesOrder.
 *----------------------------------------------------------------------------
 */

#ifndef LATEXSINK_HH
#define LATEXSINK_HH

#include "booksink.hh"
#include <cstdio>


class SpeciesOrder;


class LaTeXSink: public BookSink
{
public:
    LaTeXSink(const SpeciesOrder *, const char *);	// constructor
    LaTeXSink(const SpeciesOrder *, FILE *);		// constructor

    virtual ~LaTeXSink();				// destructor

    virtual void put(const Excursion&);

protected:
private:
    FILE * mfp;
    const SpeciesOrder * morder;

};

#endif
