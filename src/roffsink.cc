/*----------------------------------------------------------------------------
 *
 * $Id: roffsink.cc,v 1.1 2002-08-11 20:43:05 grahn Exp $
 *
 * roffsink.cc
 *
 * Copyright (c) 2002 Jörgen Grahn <jgrahn@algonet.se>
 * All rights reserved.
 *
 *----------------------------------------------------------------------------
 *
 *----------------------------------------------------------------------------
 */

static const char* rcsid() { rcsid(); return
"$Id: roffsink.cc,v 1.1 2002-08-11 20:43:05 grahn Exp $";
}

#include <cassert>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <errno.h>

#include "dynamicorder.hh"
#include "exception.hh"

#include "roffsink.hh"


using std::fprintf;


/*----------------------------------------------------------------------------
 *
 * constructor
 *
 *
 *----------------------------------------------------------------------------
 */
RoffSink::RoffSink(const SpeciesOrder * so, const char * path)
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
RoffSink::RoffSink(const SpeciesOrder * so, FILE * fp)
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
RoffSink::~RoffSink()
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
 * Print an Excursion, using the
 * SpeciesOrder given at creation time.
 *----------------------------------------------------------------------------
 */
void RoffSink::put(const Excursion& ex)
{
    fprintf(mfp, ".TS\n"
	"|lb |lw70 |.\n"
	"_\n");
    fprintf(mfp, "Place\tT{\n"
	    "%s\n"
	    "T}\n",
	    ex.getplace().c_str());

    static const char * wdays[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    long date = ex.getdate();
    struct tm tm =
    {
	0, 0, 0,
	date%100,
	(date%10000)/100 - 1,
	date/10000 - 1900,
	0, 0, -1
    };

    std::mktime(&tm);

    fprintf(mfp, "Date\t%04d\\(en%02d\\(en%02d (%s)\n",
	    tm.tm_year+1900,
	    tm.tm_mon+1,
	    tm.tm_mday,
	    wdays[tm.tm_wday]);

    fprintf(mfp, "Time\t%s\n", ex.gettime().c_str());
    fprintf(mfp, "Observers\t%s\n", ex.getobservers().c_str());
    fprintf(mfp, "Weather\t%s\n", ex.getweather().c_str());
    fprintf(mfp, "Comments\tT{\n"
	    "%s\n"
	    "T}\n"
	    "_\n",
	    ex.getcomments().c_str());

    char buf[10] = "No";
    if(ex.nofspecies())
    {
	std::sprintf(buf, "%d", ex.nofspecies());
    }

    fprintf(mfp, ".T&\n"
	    "|l s|.\n"
	    "%s species.\n"
	    "_\n"
	    ".TE\n",
	    buf);

    if(ex.nofspecies())
    {
	fprintf(mfp, ".TS\n"
		"|l |r |lw65 |.\n"
		"_\n");

	const DynamicOrder order(morder, ex.speciesset());
	for(int i = 0; i!=order.end(); i++)
	{
	    Species sp(order.species(i));

	    fprintf(mfp, "%s\t", sp.c_str());

	    const int n = ex.speciescount(sp);
	    const char * s = ex.speciescomment(sp).c_str();
	
	    if(n)
	    {
		fprintf(mfp, "%d", n);
	    }
	    fprintf(mfp, "\t");

	    if(std::strlen(s))
	    {
		fprintf(mfp, "T{\n"
			"%s\n"
			"T}",
			s);
	    }
	    fprintf(mfp, "\n");
	}

	fprintf(mfp, "_\n"
		".TE\n");
    }

    fflush(mfp);
}
