/*----------------------------------------------------------------------------
 *
 * $Id: textsink.cc,v 1.2 1999-10-24 14:56:17 grahn Exp $
 *
 * textsink.cc
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
 *----------------------------------------------------------------------------
 */

static const char rcsid[] =
"$Id: textsink.cc,v 1.2 1999-10-24 14:56:17 grahn Exp $";

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
