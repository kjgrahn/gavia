/*----------------------------------------------------------------------------
 *
 * $Id: gavia_add.cc,v 1.7 2000-08-10 19:17:24 grahn Exp $
 *
 * gavia_add.cc
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
 * Interactively add an Excursion to
 * a Gavia book.
 *----------------------------------------------------------------------------
 */

static const char* rcsid() { rcsid(); return
"$Id: gavia_add.cc,v 1.7 2000-08-10 19:17:24 grahn Exp $";
}

#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <getopt.h>

#include <cassert>

#include <vector>

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
    const char optstring[] = "+v";
    int ch = EOF;

    Version version("$Name:  $");


    while((ch = getopt(argc, argv, optstring))!=EOF)
    {
	if(ch=='v')
	{
	    fprintf(stderr,
		    "gavia_add, part of %s\n"
		    "(c) 2000 Jörgen Grahn\n",
		    version.name());
	    return 0;
	}
    }

    if(argc==optind)
    {
	fprintf(stderr,	"usage: gavia_add book\n");

	return 1;
    }

    vector<Excursion> exlist;

    // Read the old book
    //
    {
	StreamSource src(argv[optind]);

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

    // Read the textual excursions,
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
