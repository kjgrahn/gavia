/*----------------------------------------------------------------------------
 *
 * $Id: gabsource.cc,v 1.8 2004-08-05 10:16:11 grahn Exp $
 *
 * gabsource.cc
 *
 * Copyright (c) 1999 Jörgen Grahn <jgrahn@algonet.se>
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
"$Id: gabsource.cc,v 1.8 2004-08-05 10:16:11 grahn Exp $";
}

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <errno.h>

#include <string>

#include "speciesorder.hh"
#include "canonorder.hh"
#include "speciesredro.hh"
#include "exception.hh"

#include "gabsource.hh"


static int eatexcursion(Excursion&, int *, SpeciesRedro *);


extern FILE * yyin;
extern int yylex(Excursion *, int *, const SpeciesRedro *);


/*----------------------------------------------------------------------------
 *
 * constructor
 *
 * Takes a file (given as a path string) and uses it for a source.
 * As a special case, the string "-" denotes stdin.
 *
 * ### Should empty files flag an error or act as an empty source?
 *----------------------------------------------------------------------------
 */
GabSource::GabSource(const char* path)
{
    CanonOrder order;

    redro = new SpeciesRedro(&order);

    line = 1;

    if(::strcmp(path, "-")==0)
    {
	mfp = stdin;
    }
    else
    {
	mfp = fopen(path, "r");
    }

    if(!mfp)
    {
	throw GaviaException(errno);
    }

    yyin = mfp;

    mstate = ::eatexcursion(mexcursion, &line, redro);
}


/*----------------------------------------------------------------------------
 *
 * constructor
 *
 * Takes an ANSI C stream pointer and uses it for a source.
 *----------------------------------------------------------------------------
 */
GabSource::GabSource(FILE * fp)
{
    assert(fp);

    CanonOrder order;

    redro = new SpeciesRedro(&order);

    line = 1;

    mfp = fp;

    yyin = mfp;

    mstate = ::eatexcursion(mexcursion, &line, redro);
}


/*----------------------------------------------------------------------------
 *
 * destructor
 *
 *
 *----------------------------------------------------------------------------
 */
GabSource::~GabSource()
{
    if(mfp && (mfp!=stdin))
    {
	fclose(mfp);		// should check for error here (and do _what_?)
    }

    delete redro;
}


/*----------------------------------------------------------------------------
 *
 * excursion()
 *
 *
 *----------------------------------------------------------------------------
 */
Excursion GabSource::excursion()
{
    assert(!eof());

    return mexcursion;
}


/*----------------------------------------------------------------------------
 *
 * next()
 *
 *
 *----------------------------------------------------------------------------
 */
void GabSource::next()
{
    assert(!eof());

    mstate = ::eatexcursion(mexcursion, &line, redro);
}


/*----------------------------------------------------------------------------
 *
 * eof()
 *
 *
 *----------------------------------------------------------------------------
 */
bool GabSource::eof() const
{
    return mstate==0;
}


/*----------------------------------------------------------------------------
 *
 * ::eatexcursion()
 *
 *
 * Pulls an Excursion from 'yyin' (set in constructor).  Returns 0 for
 * EOF condition *without* trailing garbage, and >0 for success.  'ex'
 * has an undefined value if not success.
 *----------------------------------------------------------------------------
 */
static int eatexcursion(Excursion& ex, int * line, SpeciesRedro * redro)
{
    ex = Excursion();			// hack needed to clear ex

    try {
	return yylex(&ex, line, redro);
    }
    catch(const GaviaException& ge)
    {
	/* re-throw with line info */
	throw GaviaException(ge.msg, *line);
    }
}
