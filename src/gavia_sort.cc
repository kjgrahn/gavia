/*----------------------------------------------------------------------------
 *
 * $Id: gavia_sort.cc,v 1.17 2008-01-03 09:38:19 grahn Exp $
 *
 * gavia_sort.cc
 *
 * Copyright (c) 1999--2001 Jörgen Grahn
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
"$Id: gavia_sort.cc,v 1.17 2008-01-03 09:38:19 grahn Exp $";
}

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <vector>
#include <algorithm>

#ifdef USE_GETOPT_H
#include <getopt.h>
#endif

#include "version.hh"

#include "excursion.hh"
#include "streamsource.hh"
#include "streamsink.hh"
#include "exception.hh"

#include "canonorder.hh"

#include "excursion.hh"

using std::vector;
using std::stable_sort;


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
    const char optstring[] = "+pdv";
    int ch = EOF;
    bool byplace = false;

    Version version("$Name:  $");


    while((ch = getopt(argc, argv, optstring))!=EOF)
    {
	switch(ch)
	{
	case 'p':		// dictionary sort by place, then date
	    byplace = true;
	    break;
	case 'd':		// sort by date, then place
	    byplace = false;
	case 'v':
	case '?':
	    fprintf(stderr,
		    "gavia_sort, part of %s\n"
		    "Copyright (c) 2000-2008 Jörgen Grahn "
		    "<grahn+src@snipabacken.se>\n",
		    version.name());
	    return 0;
	    break;
	default:
	    break;
	}
    }

    int i = optind;		// [i..argc[ are now the input files

    char dash[] = "-";
    char * dashp = dash;
    char **p;
    char **end;

    if(i==argc)
    {
	// no file arguments, use stdin
	p = &dashp;
	end = p+1;
    }
    else
    {
	p = &argv[i];
	end = &argv[argc];
    }

    vector<Excursion> exlist;

    // read in excursions from all input files/stdin
    // and push them onto exlist
    try
    {
	while(p!=end) {
	    StreamSource src(*p);

	    while(!src.eof())
	    {
		exlist.push_back(src.excursion());
		src.next();
	    }

	    p++;
	}
    }
    catch(const GaviaException& exception)
    {
	std::cerr << "gavia_sort: error: " << exception.msg << std::endl;
	return 1;
    }

    // sort the exlist vector
    stable_sort(exlist.begin(), exlist.end(),
		byplace?(::internalplace):(::internaldate));


    // Dump the result to stdout
    //
    try
    {
        CanonOrder co;
        StreamSink sink(stdout);

        unsigned int i;
        for(i=0; i<exlist.size(); i++)
        {
            sink.put(exlist[i]);
        }
    }
    catch(const GaviaException& exception)
    {
	std::cerr << "gavia_sort: error: " << exception.msg << std::endl;
	return 1;
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
