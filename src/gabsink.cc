/*----------------------------------------------------------------------------
 *
 * $Id: gabsink.cc,v 1.5 2001-12-29 19:14:09 grahn Exp $
 *
 * gabsink.cc
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
 *----------------------------------------------------------------------------
 */

static const char rcsid[] =
"$Id: gabsink.cc,v 1.5 2001-12-29 19:14:09 grahn Exp $";

#include <assert.h>
#include <stdio.h>
#include <cstring>
#include <errno.h>

#include "dynamicorder.hh"
#include "exception.hh"

#include "gabsink.hh"


/*----------------------------------------------------------------------------
 *
 * constructor
 *
 *
 *----------------------------------------------------------------------------
 */
GabSink::GabSink(const SpeciesOrder * so, const char * path)
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

    if(!mfp)
    {
	throw GaviaException(errno);
    }
}


/*----------------------------------------------------------------------------
 *
 * constructor
 *
 *
 *----------------------------------------------------------------------------
 */
GabSink::GabSink(const SpeciesOrder * so, FILE * fp)
{
    assert(so);
    assert(fp);

    morder = so;

    mfp = fp;
}


/*----------------------------------------------------------------------------
 *
 * destructor
 *
 *
 *----------------------------------------------------------------------------
 */
GabSink::~GabSink()
{
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
void GabSink::put(const Excursion& ex)
{
    fprintf(mfp, "%s\n", "{");

    fprintf(mfp, "place        : %s\n", ex.getplace().c_str());
    fprintf(mfp, "date         : %08ld\n", ex.getdate());
    fprintf(mfp, "time         : %s\n", ex.gettime().c_str());
    fprintf(mfp, "observers    : %s\n", ex.getobservers().c_str());
    fprintf(mfp, "weather      : %s\n", ex.getweather().c_str());
    fprintf(mfp, "comments     : %s\n", ex.getcomments().c_str());

    fprintf(mfp, "%s\n", "}{");

    const DynamicOrder order(morder, ex.speciesset());
    for(int i = 0; i!=order.end(); i++)
    {
	Species sp(order.species(i));

	/*
	  Format the entries so that the part after the species name (":...")
	  begins at column 24 (three tabs off) if possible
	*/
	fputs(sp.c_str(), mfp);
	if(sp.size()<8)
	{
	    fputs("\t\t\t", mfp);
	}
	else if(sp.size()<16)
	{
	    fputs("\t\t", mfp);
	}
	else if(sp.size()<24)
	{
	    fputs("\t", mfp);
	}
	else
	{
	    fputs(" ", mfp);
	}

	const int n = ex.speciescount(sp);
	
	if(n)
	{
	    fprintf(mfp, ":#: %3d: %s\n",
		    n,
		    ex.speciescomment(sp).c_str());
	}
	else
	{
	    fprintf(mfp, ":#:    : %s\n",
		    ex.speciescomment(sp).c_str());
	}
    }

    fprintf(mfp, "%s\n\n", "}");

    fflush(mfp);
}
