/*----------------------------------------------------------------------------
 *
 * $Id: gabsource.cc,v 1.1 1999-10-24 08:10:52 grahn Exp $
 *
 * gabsource.cc
 *
 * Copyright (C) 1999 Jörgen Grahn <jorgen.grahn@opensoftware.se>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *----------------------------------------------------------------------------
 *
 *----------------------------------------------------------------------------
 */

static const char rcsid[] =
"$Id: gabsource.cc,v 1.1 1999-10-24 08:10:52 grahn Exp $";

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <string>

#include "speciesorder.hh"
#include "canonorder.hh"
#include "speciesredro.hh"

#include "gabsource.hh"


static int eatexcursion(Excursion&, SpeciesRedro *);


extern FILE * yyin;
extern int yylex(Excursion *, SpeciesRedro *);


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
	mstate = -1;
	return;
    }

    yyin = mfp;

    mstate = ::eatexcursion(mexcursion, redro);
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
    CanonOrder order;

    redro = new SpeciesRedro(&order);

    if(!fp)
    {
	mstate = -1;
	return;
    }

    mfp = fp;

    yyin = mfp;

    mstate = ::eatexcursion(mexcursion, redro);
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
    assert(!(eof() || error()));

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
    assert(!(eof() || error()));

    mstate = ::eatexcursion(mexcursion, redro);
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
 * error()
 *
 *
 *----------------------------------------------------------------------------
 */
bool GabSource::error() const
{
    return mstate<0;
}


/*----------------------------------------------------------------------------
 *
 * ::eatexcursion()
 *
 *
 * Pulls an Excursion from 'yyin' (set in constructor).
 * Returns <0 for I/O error, 0 for
 * EOF condition *without* trailing garbage, and >0 for success.
 * 'ex' has an undefined value if not success.
 *----------------------------------------------------------------------------
 */
static int eatexcursion(Excursion& ex, SpeciesRedro * redro)
{
    ex = Excursion();			// hack needed to clear ex

    return yylex(&ex, redro);
}
