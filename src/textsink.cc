/*----------------------------------------------------------------------------
 *
 * $Id: textsink.cc,v 1.1 1999-10-24 08:10:53 grahn Exp $
 *
 * textsink.cc
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
"$Id: textsink.cc,v 1.1 1999-10-24 08:10:53 grahn Exp $";

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "dynamicorder.hh"

#include "textsink.hh"


static int putpreamble(FILE *);
static int putpostamble(FILE *);


/*----------------------------------------------------------------------------
 *
 * constructor
 *
 *
 *----------------------------------------------------------------------------
 */
TextSink::TextSink(const SpeciesOrder * so, const char * path)
{
    assert(so);
    assert(path);

    morder = so;

    if(::strcmp(path, "-")==0)
    {
	mfp = stdout;
    }
    else
    {
	mfp = fopen(path, "w");
    }

    merror = !mfp || !::putpreamble(mfp);
}


/*----------------------------------------------------------------------------
 *
 * constructor
 *
 *
 *----------------------------------------------------------------------------
 */
TextSink::TextSink(const SpeciesOrder * so, FILE * fp)
{
    assert(so);
    assert(fp);

    morder = so;

    mfp = fp;

    merror = !mfp || !::putpreamble(mfp);
}


/*----------------------------------------------------------------------------
 *
 * destructor
 *
 *
 *----------------------------------------------------------------------------
 */
TextSink::~TextSink()
{
    if(!error())
    {
	::putpostamble(mfp);
    }

    if(mfp && mfp!=stdout)
    {
	fclose(mfp);		// should check for error here (and do _what_?)
    }
}


/*----------------------------------------------------------------------------
 *
 * put()
 *
 *
 * Print an Excursion as readable text, using the
 * SpeciesOrder given at creation time.
 *----------------------------------------------------------------------------
 */
void TextSink::put(const Excursion& ex)
{
    if(error())
    {
	return;			// no need to keep writing at I/O error
    }

    fprintf(mfp, "%s\n", "------------------------------");
    long date = ex.getdate();
    fprintf(mfp, "Date     : %04ld-%02ld-%02ld\n",
	    date/10000,
	    (date%10000)/100,
	    date%100);
    fprintf(mfp, "Place    : %s\n", ex.getplace().c_str());
    fprintf(mfp, "Time     : %s\n", ex.gettime().c_str());
    fprintf(mfp, "Observers: %s\n", ex.getobservers().c_str());
    fprintf(mfp, "Weather  : %s\n", ex.getweather().c_str());
    fprintf(mfp, "Comments : %s\n", ex.getcomments().c_str());

    fprintf(mfp, "Species  : %d\n", ex.nofspecies());
    fprintf(mfp, "%s\n", "------------------------------");

    const DynamicOrder order(morder, ex.speciesset());
    for(int i = 0; i!=order.end(); i++)
    {
	fprintf(mfp, "%s (%d) %s\n",
		order.species(i).c_str(),
		ex.speciescount(order.species(i)),
		ex.speciescomment(order.species(i)).c_str());
    }

    fflush(mfp);
}


/*----------------------------------------------------------------------------
 *
 * error()
 *
 *
 *----------------------------------------------------------------------------
 */
bool TextSink::error() const
{
    return merror;
}


/*----------------------------------------------------------------------------
 *
 * ::putpreamble()
 *
 *
 *----------------------------------------------------------------------------
 */
static int putpreamble(FILE * fp)
{
    return 1;
}


/*----------------------------------------------------------------------------
 *
 * ::putpostamble()
 *
 *
 *----------------------------------------------------------------------------
 */
static int putpostamble(FILE * fp)
{
    return 1;
}
