/*----------------------------------------------------------------------------
 *
 * $Id: streamsink.cc,v 1.4 2000-08-10 19:47:21 grahn Exp $
 *
 * streamsink.cc
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
"$Id: streamsink.cc,v 1.4 2000-08-10 19:47:21 grahn Exp $";
}

#include <cstdio>
#include <cstring>
#include <ctime>
#include <cassert>

#include <string>

#include "streamsink.hh"

#include "canonorder.hh"
#include "speciesset.hh"
#include "bitmap.h"
#include "motorola.h"


static int putpreamble(FILE *);
static int putpostamble(FILE *);
static bool internalputstring(const string&, FILE *);
static unsigned long internaldatetoamigatime(long);


/*----------------------------------------------------------------------------
 *
 * constructor
 *
 *
 *----------------------------------------------------------------------------
 */
StreamSink::StreamSink(const char * path)
{
    assert(path);

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
StreamSink::StreamSink(FILE * fp)
{
    assert(fp);

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
StreamSink::~StreamSink()
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
 * Print an Excursion in ye old Lanius format.
 *----------------------------------------------------------------------------
 */
void StreamSink::put(const Excursion& ex)
{
    if(error())
    {
	return;			// no need to keep writing at I/O error
    }

    bool rc = true;

    rc = ::internalputstring(string(""), mfp);
    assert(rc);

    rc = ::internalputstring(ex.getplace(), mfp);
    assert(rc);

    rc = ::motorolawriteulong(
	::internaldatetoamigatime(ex.getdate()),
	mfp);
    assert(rc);

    rc = ::internalputstring(ex.gettime(), mfp);
    assert(rc);
    rc = ::internalputstring(ex.getobservers(), mfp);
    assert(rc);
    rc = ::internalputstring(ex.getweather(), mfp);
    assert(rc);
    rc = ::internalputstring(ex.getcomments(), mfp);
    assert(rc);

    // The extension field has never been used, but
    // should really have been recorded in Excursion ###
    rc = internalputstring(string(""), mfp);
    assert(rc);

    // write the bitmap, with the bits set that represent the
    // CanonOrder index of all species recorded in 'ex'.

    const CanonOrder co;
    Bitmap bmap;

    bitmapcreate(&bmap);

    for(int i=0; i!=co.end(); i++)
    {
	if(ex.species(co.species(i)))
	{
	    ::bitmapset(&bmap, i);
	}
    }

    rc = ::bitmapwrite(&bmap, mfp);
    assert(rc);

    bitmapdestroy(&bmap);

    // dump the number-of-individuals for all
    // species recorded in 'ex', also in CanonOrder.
    for(int i=0; i!=co.end(); i++)
    {
	if(ex.species(co.species(i)))
	{
	    rc = ::motorolawriteword(ex.speciescount(co.species(i)), mfp);
	    assert(rc);
	}
    }

    // ...and similarly,
    // dump the species comments
    for(int i=0; i!=co.end(); i++)
    {
	if(ex.species(co.species(i)))
	{
	    rc = ::internalputstring(ex.speciescomment(co.species(i)), mfp);
	    assert(rc);
	}
    }
}


/*----------------------------------------------------------------------------
 *
 * error()
 *
 *
 *----------------------------------------------------------------------------
 */
bool StreamSink::error() const
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
    static const char id[] = "Lanius Book v1.0";

    if(!::motorolawriteword(::strlen(id), fp))
    {
	return 0;
    }

    if(::fwrite(id, 1, ::strlen(id), fp) != ::strlen(id))
    {
	return 0;
    }

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
    static const char id[] = "NIL:";

    if(!::motorolawriteword(::strlen(id), fp))
    {
	return 0;
    }

    if(::fwrite(id, 1, ::strlen(id), fp) != ::strlen(id))
    {
	return 0;
    }

    return 1;
}


/*----------------------------------------------------------------------------
 *
 * ::internalputstring()
 *
 *
 *----------------------------------------------------------------------------
 */
static bool internalputstring(const string& str, FILE * fp)
{
    int n = str.length();

    if(::motorolawriteword(n, fp))
    {
	return(fwrite(str.c_str(), 1, n, fp)==(unsigned int)n);
    }
    else
    {
	return false;
    }
}


/*----------------------------------------------------------------------------
 *
 * internaldatetoamigatime()
 *
 *
 * The inverse (somewhat) of streamsource/internalamigatimetodate().
 * At least, transforming back and forth should give
 * the same date all the time.
 *
 * Or, rather, the seconds may change during the back-and-forth thing
 * but only in the first translations, and the date should always be
 * preserved!
 *
 * For reference, the comment for internalamigatimetodate():
 *
 * >Given the number of seconds from 1978-01-01 00:00:00
 * >local time, return a long integer which is defined as
 * >
 * >(year)*10000 + month*100 + mday
 * >
 * >e.g. 19990731
 * >
 * >Might be buggy right now, and the whole concept is a bit fucked up.
 * >###
 *----------------------------------------------------------------------------
 */
static unsigned long internaldatetoamigatime(long n)
{
    time_t punk;
    time_t utime;
    struct tm tm;


    // these asserts let through
    // a lot of illegal dates, of course
    assert(n<20380101);
    assert(n>=19780101);

    tm.tm_sec = 0;
    tm.tm_min = 0;
    tm.tm_hour = 0;
    tm.tm_mday = (n%100);
    tm.tm_mon = ((n/100)%100)-1;
    tm.tm_year= (n/10000) - 1900;
    tm.tm_isdst = 0;

    utime = mktime(&tm);
    assert(utime!=(time_t)(-1));

    tm.tm_sec = 0;
    tm.tm_min = 0;
    tm.tm_hour = 0;
    tm.tm_mday = 1;
    tm.tm_mon = 0;
    tm.tm_year = (1978 - 1900);
    tm.tm_isdst = 0;

    punk = mktime(&tm);
    assert(punk!=(time_t)(-1));

    return((unsigned long)(utime - punk));
}
