/*----------------------------------------------------------------------------
 *
 * $Id: gavia_cat.cc,v 1.1 1999-10-24 08:10:52 grahn Exp $
 *
 * gavia_cat.cc
 *
 * Copyright (C) 1999 Jörgen Grahn <jorgen.grahn@opensoftware.se>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *----------------------------------------------------------------------------
 *
 * Concatenate one or more Gavia books and dump them to
 * stdout as a Gavia book or some other specified format
 * (plain text, HTML, LaTeX).
 *----------------------------------------------------------------------------
 */

static const char rcsid[] =
"$Id: gavia_cat.cc,v 1.1 1999-10-24 08:10:52 grahn Exp $";

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>

#include <assert.h>

#include "booksink.hh"
#include "streamsink.hh"
#include "textsink.hh"
#include "htmlsink.hh"
#include "latexsink.hh"

#include "speciesorder.hh"
#include "canonorder.hh"
#include "sortedorder.hh"
#include "taxonomicorder.hh"

#include "streamsource.hh"
#include "excursion.hh"


/*----------------------------------------------------------------------------
 *
 * main()
 *
 *
 *----------------------------------------------------------------------------
 */
int main(int argc, char ** argv)
{
    const char optstring[] = "+bthlcxs";
    int ch = EOF;
    int fmtch = 'b';
    int ordch = 'c';


    while((ch = getopt(argc, argv, optstring))!=EOF)
    {
	switch(ch)
	{
	case 'b':		// Lanius book
	case 't':		// plain text
	case 'h':		// HTML
	case 'l':		// LaTeX2e
	    fmtch = ch;
	    break;
	case 'c':		// 'canonical' order
	case 'x':		// taxonomical order
	case 's':		// sorted by name
	    ordch = ch;
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
    case 't':
    case 'h':
    case 'l':
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
	case 't':
	    sink = new TextSink(order, stdout);
	    break;
	case 'h':
	    sink = new HtmlSink(order, stdout);
	    break;
	case 'l':
	    sink = new LaTeXSink(order, stdout);
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

    for(int i=optind; i<argc; i++)
    {
	StreamSource src(argv[i]);

	while(!(src.eof() || src.error()))
	{
	    sink->put(src.excursion());
	    src.next();
	}

	if(src.error())
	{
	    // read error in this book - abort
	    delete order;
	    delete sink;
	    return 1;
	}
    }

    if(optind==argc)
    {
	// no filenames given ->
	// the previous for loop wasn't executed ->
	// read from stdin instead

	StreamSource src(stdin);

	while(!(src.eof() || src.error()))
	{
	    sink->put(src.excursion());
	    src.next();
	}
    }

    delete order;
    delete sink;
    return 0;
}
