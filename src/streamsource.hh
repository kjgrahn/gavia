/*----------------------------------------------------------------------------
 *
 * $Id: streamsource.hh,v 1.3 1999-11-30 22:19:46 grahn Exp $
 *
 * streamsource.hh
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
 * A BookSource using an ANSI C stream
 * (in "Lanius" binary format) for data source.
 *----------------------------------------------------------------------------
 */

#ifndef STREAMSOURCE_HH
#define STREAMSOURCE_HH

#include "booksource.hh"
#include <cstdio>


class SpeciesOrder;


class StreamSource: public BookSource
{
public:
    StreamSource(const char *);		// constructor
    StreamSource(FILE *);		// constructor

    virtual ~StreamSource();		// destructor

    virtual Excursion excursion();
    virtual void next();
    virtual bool eof() const;
    virtual bool error() const;

protected:
private:
    Excursion mexcursion;
    int mstate;
    FILE * mfp;

    SpeciesOrder * morder;

};

#endif
