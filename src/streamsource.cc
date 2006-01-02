/*----------------------------------------------------------------------------
 *
 * $Id: streamsource.cc,v 1.8 2006-01-02 22:15:25 grahn Exp $
 *
 * streamsource.cc
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
 *----------------------------------------------------------------------------
 */

static const char* rcsid() { rcsid(); return
"$Id: streamsource.cc,v 1.8 2006-01-02 22:15:25 grahn Exp $";
}

#include <cstdio>
#include <cstring>
#include <ctime>
#include <cassert>

#include <errno.h>

#include "motorola.h"
#include "bitmap.h"

#include "speciesorder.hh"
#include "canonorder.hh"

#include "exception.hh"

#include "streamsource.hh"

using std::string;


static int eatpreamble(FILE *);
static int eatexcursion(FILE *, SpeciesOrder *, Excursion&);
static int eatstring(FILE *, string&);
static long internalamigatimetodate(unsigned long);


/*----------------------------------------------------------------------------
 *
 * constructor
 *
 * Takes a file (given as a path string) and uses it for a source.
 * As a special case, the string "-" denotes stdin.
 *
 * An empty file is an empty source. However a non-existing or
 * non-readable file is an error.
 *----------------------------------------------------------------------------
 */
StreamSource::StreamSource(const char* path)
{
    morder = new CanonOrder();
    assert(morder);

    if(::strcmp(path, "-")==0)
    {
	mfp = stdin;
    }
    else
    {
	mfp = fopen(path, "rb");
    }

    if(!mfp)
    {
	throw GaviaException(errno);
    }

    int i = ::eatpreamble(mfp);

    if(i<0)
    {
	throw GaviaException("malformed preamble");
    }
    else if(i==0)
    {
	mstate = 0;
    }
    else
    {
	mstate = ::eatexcursion(mfp, morder, mexcursion);
    }
}


/*----------------------------------------------------------------------------
 *
 * constructor
 *
 * Takes an ANSI C stream pointer and uses it for a source.
 *----------------------------------------------------------------------------
 */
StreamSource::StreamSource(FILE * fp)
{
    morder = new CanonOrder();
    assert(morder);
    assert(fp);

    mfp = fp;

    int i = ::eatpreamble(mfp);

    if(i<0)
    {
	throw GaviaException("malformed preamble");
    }
    else if(i==0)
    {
	mstate = 0;
    }
    else
    {
	mstate = ::eatexcursion(mfp, morder, mexcursion);
    }
}


/*----------------------------------------------------------------------------
 *
 * destructor
 *
 *
 *----------------------------------------------------------------------------
 */
StreamSource::~StreamSource()
{
    delete morder;

    if(mfp && (mfp!=stdin))
    {
	fclose(mfp);		// should check for error here (and do _what_?)
    }
}


/*----------------------------------------------------------------------------
 *
 * excursion()
 *
 *
 *----------------------------------------------------------------------------
 */
Excursion StreamSource::excursion()
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
void StreamSource::next()
{
    assert(!eof());

    mstate = ::eatexcursion(mfp, morder, mexcursion);
}


/*----------------------------------------------------------------------------
 *
 * eof()
 *
 *
 *----------------------------------------------------------------------------
 */
bool StreamSource::eof() const
{
    return mstate==0;
}


/*----------------------------------------------------------------------------
 *
 * ::eatpreamble()
 *
 *
 * Consumes the preamble of a Lanius book. Returns <0 for I/O error, 0 for
 * EOF condition and >0 for success.
 * ### It's unclear wether EOF is an I/O error in this context...
 *----------------------------------------------------------------------------
 */
static int eatpreamble(FILE * fp)
{
    string tmp;

    return ::eatstring(fp, tmp);
}


/*----------------------------------------------------------------------------
 *
 * ::eatexcursion()
 *
 *
 * Pulls an Excursion from 'fp'. Throws GaviaException for I/O error,
 * else returns 0 for EOF condition *without* trailing garbage, and >0
 * for success.  'ex' has an undefined value if not success.
 *
 *----------------------------------------------------------------------------
 */
static int eatexcursion(FILE * fp, SpeciesOrder * order, Excursion& ex)
{
    string tmp;
    int i;
    unsigned int n;


    ex = Excursion();			// hack needed to clear ex

    i = motorolareadword(fp, &n); 	// must start with a motorolaword of 0
    if(i<0)
    {
	throw GaviaException("garbage in excursion");
    }
    else if(i==0 || n!=0)
    {
	return 0;
    }

    i = ::eatstring(fp, tmp);		// place
    if(i<=0)
    {
	throw GaviaException("garbage in excursion");
    }
    ex.setplace(tmp);

    unsigned long m;			// date
    i = ::motorolareadulong(fp, &m);
    if(i<=0)
    {
	throw GaviaException("garbage in excursion");
    }
    ex.setdate(::internalamigatimetodate(m));

    i = ::eatstring(fp, tmp);		// time
    if(i<=0)
    {
	throw GaviaException("garbage in excursion");
    }
    ex.settime(tmp);

    i = ::eatstring(fp, tmp);		// observers
    if(i<=0)
    {
	throw GaviaException("garbage in excursion");
    }
    ex.setobservers(tmp);

    i = ::eatstring(fp, tmp);		// weather
    if(i<=0)
    {
	throw GaviaException("garbage in excursion");
    }
    ex.setweather(tmp);

    i = ::eatstring(fp, tmp);		// comments
    if(i<=0)
    {
	throw GaviaException("garbage in excursion");
    }
    ex.setcomments(tmp);

    i = ::eatstring(fp, tmp);		// extension ### don't discard
    if(i<=0)
    {
	throw GaviaException("garbage in excursion");
    }

    Bitmap bitmap;			// set of species
    i = bitmap.read(fp);
    if(!i)
    {
	throw GaviaException("garbage in excursion");
    }

    for(i=0; i<bitmap.size(); i++)	// speciescounts
    {
	if(bitmap.isset(i))
	{
	    unsigned int n;
	    if(::motorolareadword(fp, &n) <= 0)
	    {
		throw GaviaException("garbage in excursion");
	    }
	    ex.insert(order->species(i), n);
	}
    }

    for(i=0; i<bitmap.size(); i++)	// speciescomments
    {
	if(bitmap.isset(i))
	{
	    int n = ::eatstring(fp, tmp);
	    if(n<=0)
	    {
		throw GaviaException("garbage in excursion");
	    }

	    ex.speciescomment(order->species(i), tmp);
	}
    }

    return 1;
}


/*----------------------------------------------------------------------------
 *
 * ::eatstring()
 *
 *
 * Pulls a string from 'fp'. Returns <0 for I/O error, 0 for
 * EOF condition and >0 for success.
 * 'str' has an undefined value if not success.
 *----------------------------------------------------------------------------
 */
static int eatstring(FILE * fp, string& str)
{
    const int BUFLEN = 300;
    unsigned int len;
    char buf[BUFLEN];
    char * bufp;

    if(!::motorolareadword(fp, &len))
    {
	// EOF or error; we are positive and assume EOF

	return 0;
    }

    if(len==0)
    {
	str = "";

	return 1;
    }
    else if(len<BUFLEN-1)
    {
	// avoid temp allocation for reasonably short strings
	unsigned int n = ::fread(buf, 1, len, fp);
	if(n!=len)
	{
	    return -1;
	}

	buf[len] = '\0';
	str = buf;

	return 1;
    }
    else
    {
	bufp = new char[len+1];

	unsigned int n = ::fread(bufp, 1, len, fp);
	if(n!=len)
	{
	    return -1;
	}

	bufp[len] = '\0';
	str = bufp;

	delete[] bufp;

	return 1;
    }
}


/*----------------------------------------------------------------------------
 *
 * ::internalamigatimetodate()
 *
 *
 * Given the number of seconds from 1978-01-01 00:00:00
 * local time, return a long integer which is defined as
 *
 * (year)*10000 + month*100 + mday
 *
 * e.g. 19990731
 *
 * Might be buggy right now, and the whole concept is a bit fucked up.
 * ###
 *----------------------------------------------------------------------------
 */
static long internalamigatimetodate(unsigned long n)
{
    time_t punk;
    long acc;
    struct tm tm;
    struct tm * tmp;


    tm.tm_sec = 0;
    tm.tm_min = 0;
    tm.tm_hour = 0;
    tm.tm_mday = 1;
    tm.tm_mon = 0;
    tm.tm_year = (1978 - 1900);
    tm.tm_isdst = 0;

    punk = mktime(&tm);
    assert(punk!=(time_t)(-1));

    n += punk;
    n += 12*60*60;			// avoid truncating errors due to DST

    tmp = localtime((time_t *)&n);	// not thread-safe

    acc = tmp->tm_year + 1900;
    acc = acc * 100 + tmp->tm_mon+1;
    acc = acc * 100 + tmp->tm_mday;

    // these asserts let through
    // a lot of illegal dates, of course
    assert(acc<20380101);
    assert(acc>=19780101);

    return acc;
}
