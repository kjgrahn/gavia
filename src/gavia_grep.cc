/*----------------------------------------------------------------------------
 *
 * $Id: gavia_grep.cc,v 1.2 1999-10-24 09:00:45 grahn Exp $
 *
 * gavia_grep.cc
 *
 * Copyright (C) 1999 Jörgen Grahn <jorgen.grahn@opensoftware.se>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *----------------------------------------------------------------------------
 *
 * From one or more Gavia books, output (on stdout) all excursions
 * that contain text (e.g. place, species, species comments) matching
 * the pattern given on the command line.
 *----------------------------------------------------------------------------
 */

static const char rcsid[] =
"$Id: gavia_grep.cc,v 1.2 1999-10-24 09:00:45 grahn Exp $";

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <assert.h>

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
    const char optstring[] = "+v";
    int ch = EOF;
    bool invert = false;

    Version version;


    while((ch = getopt(argc, argv, optstring))!=EOF)
    {
	switch(ch)
	{
	case 'v':		// inverse grep
	    invert = true;
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
