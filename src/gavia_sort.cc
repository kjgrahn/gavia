/*----------------------------------------------------------------------------
 *
 * $Id: gavia_sort.cc,v 1.4 2000-01-16 21:07:22 grahn Exp $
 *
 * gavia_sort.cc
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
 * From one or more Gavia books, output (on stdout) the excursions
 * sorted by (place,date) or (date,place).
 *----------------------------------------------------------------------------
 */

static const char* rcsid() { rcsid(); return
"$Id: gavia_sort.cc,v 1.4 2000-01-16 21:07:22 grahn Exp $";
}

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <getopt.h>

#include <cassert>

#include <vector>
#include <algorithm>

#include "version.hh"

#include "excursion.hh"
#include "streamsource.hh"
#include "streamsink.hh"

#include "canonorder.hh"
#include "dynamicorder.hh"

#include "excursion.hh"


static bool internalplace(const Excursion& a, const Excursion& b);
static bool internaldate(const Excursion& a, const Excursion& b);


/*----------------------------------------------------------------------------
 *
 * main()
 *
 *
 *----------------------------------------------------------------------------
 */
int main(int argc, char ** argv)
{
    const char optstring[] = "+pd";
    int ch = EOF;
    bool byplace = false;

    Version version;


    while((ch = getopt(argc, argv, optstring))!=EOF)
    {
	switch(ch)
	{
	case 'p':		// dictionary sort by place, then date
	    byplace = true;
	    break;
	case 'd':		// sort by date, then place
	    byplace = false;
	    break;
	default:
	    break;
	}
    }

    int i = optind;		// [i..argc[ are now the input files

    char * stargv[] = {"-", 0};
    char **p;

    if(i==argc)
    {
	// no file arguments, use stdin
	p = stargv;
    }
    else
    {
	p = &argv[i];
    }

    vector<Excursion> exlist;

    // read in excursions from all input files/stdin
    // and push them onto exlist
    while(*p)
    {
	StreamSource src(*p);

	while(!(src.eof() || src.error()))
        {
            exlist.push_back(src.excursion());
            src.next();
        }

        if(src.error())
        {
            perror("gavia_sort");
            return 1;
        }

	p++;
    }


    // sort the exlist vector
    stable_sort(exlist.begin(), exlist.end(),
		byplace?(::internalplace):(::internaldate));


    // Dump the result to stdout
    //
    {
        CanonOrder co;
        StreamSink sink(stdout);

        unsigned int i;
        for(i=0; i<exlist.size(); i++)
        {
            sink.put(exlist[i]);
        }

        if(sink.error())
        {
            perror("gavia_sort");
            return 1;
        }
    }

    return 0;
}


/*----------------------------------------------------------------------------
 *
 * ::internalplace()
 *
 * Orders excursions primarily on place string (case-sensitive),
 * secondarily on date
 *----------------------------------------------------------------------------
 */
static bool internalplace(const Excursion& a, const Excursion& b)
{
    if(a.getplace() != b.getplace())
    {
	return a.getplace() < b.getplace();
    }
    else
    {
	return a.getdate() < b.getdate();
    }
}


/*----------------------------------------------------------------------------
 *
 * ::internaldate()
 *
 * Orders excursions primarily on date,
 * secondarily on place string (case-sensitive)
 *----------------------------------------------------------------------------
 */
static bool internaldate(const Excursion& a, const Excursion& b)
{
    if(a.getdate() != b.getdate())
    {
	return a.getdate() < b.getdate();
    }
    else
    {
	return a.getplace() < b.getplace();
    }
}
