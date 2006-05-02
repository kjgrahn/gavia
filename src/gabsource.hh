/*----------------------------------------------------------------------------
 *
 * $Id: gabsource.hh,v 1.8 2006-05-02 21:53:58 grahn Exp $
 *
 * gabsource.hh
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
 * A BookSource using a text file in "GAB" format
 * for data source.
 *
 * This "GAB" format is suitable for hand editing using any
 * text editor.
 *
 * (i) rows matching [ ]*#.* are discarded
 *
 * (ii) the remainder matches
 *      excursion*
 *
 *      excursion ::=
 *      {
 *      place:.+
 *      date:.+
 *      time:.+
 *      observers:.+
 *      weather:.+
 *      comments:.+
 *      }{
 *      speciesdata*
 *      }
 *
 *      speciesdata::=
 *      name:existancemarker?:nofindividuals?:comment?
 *
 *      but with whitespace (tabs and spaces) allowed
 *      where applicable and trimmed where it makes sense.
 *
 * Well, that's the general idea anyway...
 *----------------------------------------------------------------------------
 */

#ifndef GABSOURCE_HH
#define GABSOURCE_HH

#include "booksource.hh"
#include "contstream.hh"
#include <iosfwd>


class SpeciesRedro;
struct Parsing;


class GabSource: public BookSource
{
public:
    explicit GabSource(std::istream& is);
    virtual ~GabSource();

    virtual Excursion excursion();
    virtual void next();
    virtual bool eof() const;

private:
    GabSource();
    GabSource(const GabSource&);
    GabSource& operator= (const GabSource&);

    void eatexcursion();

    Excursion excursion_;
    Continuation cs_;
    SpeciesRedro * redro_;
    int line_;
    enum {SPACE,
	  HEAD,
	  BODY,
	  END} state_;
    Parsing * const parsing_;
};

#endif
