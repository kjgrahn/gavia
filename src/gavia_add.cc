/*----------------------------------------------------------------------------
 *
 * $Id: gavia_add.cc,v 1.2 1999-10-24 09:00:45 grahn Exp $
 *
 * gavia_add.cc
 *
 * Copyright (C) 1999 Jörgen Grahn <jorgen.grahn@opensoftware.se>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *----------------------------------------------------------------------------
 *
 * Interactively add an Excursion to
 * a Gavia book.
 *----------------------------------------------------------------------------
 */

static const char rcsid[] =
"$Id: gavia_add.cc,v 1.2 1999-10-24 09:00:45 grahn Exp $";

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <vector.h>

#include <assert.h>

#ifdef NON_FUCKED_UP_READLINE_H
#include <readline/readline.h>
#else
extern "C" char * readline(const char*);
#endif

#include "version.hh"

#include "streamsource.hh"
#include "gabsource.hh"
#include "streamsink.hh"
#include "canonorder.hh"


/*----------------------------------------------------------------------------
 *
 * main()
 *
 *
 *----------------------------------------------------------------------------
 */
int main(int argc, char ** argv)
{
    Version version;


    if(argc!=2)
    {
	fprintf(stderr, "usage: gavia_add book\n");
	return 1;
    }

    vector<Excursion> exlist;

    // Read in the old book
    //
    {
	StreamSource src(argv[1]);

	while(!(src.eof()||src.error()))
	{
	    exlist.push_back(src.excursion());
	    src.next();
	}

	if(src.error())
	{
	    perror("gavia_add");
	    return 1;
	}
    }

    // Read in the textual excursions,
    // add to the original
    {
	GabSource src(stdin);

	while(!(src.eof()||src.error()))
	{
	    exlist.push_back(src.excursion());
	    src.next();
	}

	if(src.error())
	{
	    perror("gavia_add");
	    return 1;
	}
    }

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
	    perror("gavia_add");
	    return 1;
	}
    }

    return 0;
}
