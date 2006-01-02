/*----------------------------------------------------------------------------
 *
 * $Id: mboxsink.cc,v 1.4 2006-01-02 22:15:25 grahn Exp $
 *
 * mboxsink.cc
 *
 * Copyright (c) 2001 Jörgen Grahn
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
"$Id: mboxsink.cc,v 1.4 2006-01-02 22:15:25 grahn Exp $";

#include <cassert>
#include <cstdio>
#include <cstring>
#include <time.h>
#include <errno.h>

#include "dynamicorder.hh"
#include "exception.hh"

#include "mboxsink.hh"


static time_t mkgaviatime(long date);
static void put822date(FILE * fp, time_t time);
static void putFromdate(FILE * fp, time_t time);


/*----------------------------------------------------------------------------
 *
 * constructor
 *
 *
 *----------------------------------------------------------------------------
 */
MboxSink::MboxSink(const SpeciesOrder * so, const char * path)
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
MboxSink::MboxSink(const SpeciesOrder * so, FILE * fp)
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
MboxSink::~MboxSink()
{
    if(mfp!=stdout)
    {
	fclose(mfp);		// should check for error here (and do _what_?)
    }
}


/*----------------------------------------------------------------------------
 *
 * put()
 *
 *
 * Print an Excursion as an item in a mailbox, using the
 * SpeciesOrder given at creation time.
 *----------------------------------------------------------------------------
 */
void MboxSink::put(const Excursion& ex)
{
    fprintf(mfp, "From GAVIA  ");
    putFromdate(mfp, time(0));
    fprintf(mfp, "\n");
    fprintf(mfp, "Return-Path: <>\n");
    fprintf(mfp, "From: \"%s\"\n", ex.getobservers().c_str());
    fprintf(mfp, "To: \n");
    fprintf(mfp, "Date: ");
    put822date(mfp, mkgaviatime(ex.getdate()));
    fprintf(mfp, "\n");
    fprintf(mfp, "Subject: %s\n", ex.getplace().c_str());

    fprintf(mfp, "\n{\n");

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

    fprintf(mfp, "}\n");

    fflush(mfp);
}


static time_t mkgaviatime(long n)
{
    struct tm tm;

    // these asserts let through
    // a lot of illegal dates, of course
    assert(n<20380101);
    assert(n>=19780101);

    tm.tm_sec = 0;
    tm.tm_min = 0;
    tm.tm_hour = 12;
    tm.tm_mday = (n%100);
    tm.tm_mon = ((n/100)%100)-1;
    tm.tm_year= (n/10000) - 1900;
    tm.tm_isdst = 0;

    return mktime(&tm);
}


static void put822date(FILE * fp, time_t time)
{
    const struct tm * const tm = ::localtime(&time);
    char buf[100];
    const char * weekdays = "Sun\0Mon\0Tue\0Wed\0Thu\0Fri\0Sat";
    const char * months = "Jan\0Feb\0Mar\0Apr\0May\0Jun"
	"\0Jul\0Aug\0Sep\0Oct\0Nov\0Dec";

    /*
     * transform the timezone info left by localtime() into
     * a sign and a four-digit integer encoding hhmm
     *
     * ### BUG: DST is ignored; __timezone expresses
     * the 'normal' delta against UTC.
     *
     */
    long tz = __timezone/60;
    char tzsign = (tz>0)? '-': '+';
    if(tz<0)
    {
	tz = -tz;
    }
    tz = 100*(tz/60) + tz%60;


    sprintf(buf, "%s, %2d %s %4d %02d:%02d:%02d %c%04ld",
	    weekdays+4*tm->tm_wday,
	    tm->tm_mday,
	    months+4*tm->tm_mon,
	    1900+tm->tm_year,
	    tm->tm_hour,
	    tm->tm_min,
	    tm->tm_sec,
	    tzsign, tz);

    fputs(buf, fp);
}


static void putFromdate(FILE * fp, time_t time)
{
    const struct tm * const tm = ::localtime(&time);
    char buf[100];
    const char * weekdays = "Sun\0Mon\0Tue\0Wed\0Thu\0Fri\0Sat";
    const char * months = "Jan\0Feb\0Mar\0Apr\0May\0Jun"
	"\0Jul\0Aug\0Sep\0Oct\0Nov\0Dec";

    sprintf(buf, "%s %s %2d %02d:%02d:%02d %4d",
	    weekdays+4*tm->tm_wday,
	    months+4*tm->tm_mon,
	    tm->tm_mday,
	    tm->tm_hour,
	    tm->tm_min,
	    tm->tm_sec,
	    1900+tm->tm_year);

    fputs(buf, fp);
}
