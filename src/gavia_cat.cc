/*----------------------------------------------------------------------------
 *
 * $Id: gavia_cat.cc,v 1.12 2001-12-29 19:14:09 grahn Exp $
 *
 * gavia_cat.cc
 *
 * Copyright (c) 1999--2001 Jörgen Grahn <jgrahn@algonet.se>
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
 * Concatenate one or more Gavia books and dump them to
 * stdout as a Gavia book or some other specified format
 * (plain text, HTML, LaTeX).
 *----------------------------------------------------------------------------
 */

static const char* rcsid() { rcsid(); return
"$Id: gavia_cat.cc,v 1.12 2001-12-29 19:14:09 grahn Exp $";
}

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cassert>

#ifdef USE_GETOPT_H
#include <getopt.h>
#endif

#include "version.hh"

#include "booksink.hh"
#include "gabsink.hh"
#include "streamsink.hh"
#include "textsink.hh"
#include "htmlsink.hh"
#include "latexsink.hh"
#include "mboxsink.hh"

#include "speciesorder.hh"
#include "canonorder.hh"
#include "sortedorder.hh"
#include "taxonomicorder.hh"

#include "streamsource.hh"
#include "excursion.hh"
#include "exception.hh"


/*----------------------------------------------------------------------------
 *
 * main()
 *
 *
 *----------------------------------------------------------------------------
 */
int main(int argc, char ** argv)
{
    const char optstring[] = "+bgthlmcxsv";
    int ch = EOF;
    int fmtch = 'b';
    int ordch = 'c';

    Version version("$Name:  $");


    while((ch = getopt(argc, argv, optstring))!=EOF)
    {
	switch(ch)
	{
	case 'b':		// Lanius book
	case 'g':		// 'Gab'-formatted text
	case 't':		// plain text
	case 'h':		// HTML
	case 'l':		// LaTeX2e
	case 'm':		// mbox
	    fmtch = ch;
	    break;
	case 'c':		// 'canonical' order
	case 'x':		// taxonomical order
	case 's':		// sorted by name
	    ordch = ch;
	    break;
	case 'v':
	    std::cerr << 
		"gavia_cat, part of " << version.name() << std::endl <<
		"Copyright (c) 1999--2001 Jörgen Grahn "
		"<jgrahn@algonet.se>" << std::endl;
	    return 0;
	    break;
	default:
	    break;
	}
    }

    CanonOrder canon;
    SpeciesOrder * order = 0;
    BookSink * sink = 0;

    switch(fmtch)
    {
    case 'b':
	sink = new StreamSink(stdout);
	break;
    case 'g':
    case 't':
    case 'h':
    case 'l':
    case 'm':
	switch(ordch)
	{
	case 'c':
	    order = new CanonOrder();
	    break;
	case 'x':
	    order = new TaxonomicOrder();
	    break;
	case 's':
	    order = new SortedOrder(&canon);
	    break;
	default:
	    assert(!"impossible");
	    break;
	}
	switch(fmtch)
	{
	case 'g':
	    sink = new GabSink(order, stdout);
	    break;
	case 't':
	    sink = new TextSink(order, stdout);
	    break;
	case 'h':
	    sink = new HtmlSink(order, stdout);
	    break;
	case 'l':
	    sink = new LaTeXSink(order, stdout);
	    break;
	case 'm':
	    sink = new MboxSink(order, stdout);
	    break;
	default:
	    assert(!"extremely impossible");
	    break;
	}
	break;
    default:
	assert(!"impossible");
	break;
    }

    try
    {
	for(int i=optind; i<argc; i++)
	{
	    StreamSource src(argv[i]);

	    while(!src.eof())
	    {
		sink->put(src.excursion());
		src.next();
	    }
	}

	if(optind==argc)
	{
	    // no filenames given ->
	    // the previous for loop wasn't executed ->
	    // read from stdin instead

	    StreamSource src(stdin);

	    while(!src.eof())
	    {
		sink->put(src.excursion());
		src.next();
	    }
	}
    }
    catch(const GaviaException& exception)
    {
	std::cerr << "gavia_cat: " << exception.msg << std::endl;
	return 1;
    }

    delete order;
    delete sink;
    return 0;
}
