/*----------------------------------------------------------------------------
 *
 * $Id: gavia_grep.cc,v 1.9 2001-01-18 23:25:20 grahn Exp $
 *
 * gavia_grep.cc
 *
 * Copyright (c) 1999, 2000 Jörgen Grahn <jgrahn@algonet.se>
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
 * From one or more Gavia books, output (on stdout) all excursions
 * that contain text (e.g. place, species, species comments) matching
 * the pattern given on the command line.
 *----------------------------------------------------------------------------
 */

static const char* rcsid() { rcsid(); return
"$Id: gavia_grep.cc,v 1.9 2001-01-18 23:25:20 grahn Exp $";
}

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

#ifdef USE_GETOPT_H
#include <getopt.h>
#endif

#include <regex.h>

#include "version.hh"

#include "excursion.hh"
#include "streamsource.hh"
#include "streamsink.hh"

#include "canonorder.hh"
#include "dynamicorder.hh"

#include "excursion.hh"


static bool internalmatchex(const Excursion&, regex_t *);


/*----------------------------------------------------------------------------
 *
 * main()
 *
 *
 *----------------------------------------------------------------------------
 */
int main(int argc, char ** argv)
{
    const char optstring[] = "+vV";
    int ch = EOF;
    bool invert = false;

    Version version("$Name:  $");


    while((ch = getopt(argc, argv, optstring))!=EOF)
    {
	switch(ch)
	{
	case 'v':		// inverse grep
	    invert = true;
	    break;
	case 'V':
	    fprintf(stderr,
		    "gavia_grep, part of %s\n"
		    "Copyright (c) 2000 Jörgen Grahn "
		    "<jgrahn@algonet.se>\n",
		    version.name());
	    return 0;
	    break;
	default:
	    break;
	}
    }

    int i = optind;

    if((argc - i) < 1)
    {
	fprintf(stderr, "gavia_grep: %s\n", "too few arguments");
	return 1;
    }

    regex_t preg;
    int rc = regcomp(&preg, argv[i], REG_EXTENDED|REG_ICASE|REG_NOSUB);
    if(rc)
    {
	const size_t ERRBUF_SIZE = 80;
	char errbuf[ERRBUF_SIZE];

	regerror(rc, &preg, errbuf, ERRBUF_SIZE);
	regfree(&preg);

	fprintf(stderr, "gavia_grep: %s\n", errbuf);
	return 1;
    }

    i++;			// [i..argc[ are now the input files

    StreamSink sink(stdout);
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

    while(*p)
    {
	StreamSource src(*p);

	while(!(src.eof() || src.error()))
	{
	    Excursion ex = src.excursion();
	    
	    if(invert ^ internalmatchex(ex, &preg))
	    {
		sink.put(ex);
	    }
	    src.next();
	}

	if(src.error())
	{
	    // read error in this book - abort
	    fprintf(stderr,
		    "gavia_grep: something wrong in '%s'; aborting\n",
		    *p);
	    return 1;
	}

	p++;
    }

    return 0;
}


/*----------------------------------------------------------------------------
 *
 * ::internalmatchex()
 *
 *
 * Applies 'preg' to the excursion, and returns true if it matches.
 * The pattern is defined to match if it matches one or more of the
 * following strings:
 * - place
 * - date, formatted as yyyymmdd
 * - time
 * - observers
 * - weather
 * - comments
 * - the name of any species
 * - the comment to any species
 *----------------------------------------------------------------------------
 */
static bool internalmatchex(const Excursion& ex, regex_t * preg)
{
    // place
    if(regexec(preg,
	       ex.getplace().c_str(),
	       0, 0, 0)
       ==0)
    {
	return true;
    }

    // date
    char tmp2[9];
    sprintf(tmp2, "%8ld", ex.getdate());
    if(regexec(preg, tmp2, 0, 0, 0)==0)
    {
	return true;
    }

    // time
    if(regexec(preg,
	       ex.gettime().c_str(),
	       0, 0, 0)
       ==0)
    {
	return true;
    }

    // observers
    if(regexec(preg,
	       ex.getobservers().c_str(),
	       0, 0, 0)
       ==0)
    {
	return true;
    }

    // weather
    if(regexec(preg,
	       ex.getweather().c_str(),
	       0, 0, 0)
       ==0)
    {
	return true;
    }

    // comments
    if(regexec(preg,
	       ex.getcomments().c_str(),
	       0, 0, 0)
       ==0)
    {
	return true;
    }

    // species names and comments
    const CanonOrder canon;
    const DynamicOrder order(&canon, ex.speciesset());

    for(int i = 0; i!=order.end(); i++)
    {
	if(regexec(preg,
		   order.species(i).c_str(),
		   0, 0, 0)
	   ==0)
	{
	    return true;
	}

	if(regexec(preg,
		   ex.speciescomment(order.species(i)).c_str(),
		   0, 0, 0)
	   ==0)
	{
	    return true;
	}
    }

    return false;
}
