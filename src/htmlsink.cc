/*----------------------------------------------------------------------------
 *
 * $Id: htmlsink.cc,v 1.1 1999-10-24 08:10:52 grahn Exp $
 *
 * htmlsink.cc
 *
 * Copyright (C) 1999 Jörgen Grahn <jorgen.grahn@opensoftware.se>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *----------------------------------------------------------------------------
 *
 *----------------------------------------------------------------------------
 */

static const char rcsid[] =
"$Id: htmlsink.cc,v 1.1 1999-10-24 08:10:52 grahn Exp $";

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "dynamicorder.hh"

#include "htmlsink.hh"


static int putpreamble(FILE *);
static int putpostamble(FILE *);
static int htmlfputs(const char *, FILE *);


/*----------------------------------------------------------------------------
 *
 * constructor
 *
 *
 *----------------------------------------------------------------------------
 */
HtmlSink::HtmlSink(const SpeciesOrder * so, const char * path)
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

    merror = !mfp || !::putpreamble(mfp);
}


/*----------------------------------------------------------------------------
 *
 * constructor
 *
 *
 *----------------------------------------------------------------------------
 */
HtmlSink::HtmlSink(const SpeciesOrder * so, FILE * fp)
{
    assert(so);
    assert(fp);

    morder = so;

    mfp = fp;

    merror = !mfp || !::putpreamble(mfp);
}


/*----------------------------------------------------------------------------
 *
 * destructor
 *
 *
 *----------------------------------------------------------------------------
 */
HtmlSink::~HtmlSink()
{
    if(!error())
    {
	::putpostamble(mfp);
    }

    if(mfp && mfp!=stdout)
    {
	fclose(mfp);		// should check for error here (and do _what_?)
    }
}


/*----------------------------------------------------------------------------
 *
 * put()
 *
 *
 * Print an Excursion as readable text, using the
 * SpeciesOrder given at creation time.
 *----------------------------------------------------------------------------
 */
void HtmlSink::put(const Excursion& ex)
{
    if(error())
    {
	return;			// no need to keep writing at I/O error
    }

    fputs("<hr>\n", mfp);

    fputs("<h1>\n", mfp);

    long date = ex.getdate();

    fprintf(mfp, "%04ld-%02ld-%02ld ",
	    date/10000,
	    (date%10000)/100,
	    date%100);						// date

    ::htmlfputs(ex.getplace().c_str(), mfp);			// place
    fputs("</h1>\n\n", mfp);

    fputs("<dl>", mfp);
    fputs("\n<dt>Time\n<dd>", mfp);
    ::htmlfputs(ex.gettime().c_str(), mfp);			// time
    fputs("\n<dt>Observers\n<dd>", mfp);
    ::htmlfputs(ex.getobservers().c_str(), mfp);		// observers
    fputs("\n<dt>Weather\n<dd>", mfp);
    ::htmlfputs(ex.getweather().c_str(), mfp);			// weather
    fputs("\n<dt>Comments\n<dd>", mfp);
    ::htmlfputs(ex.getcomments().c_str(), mfp);			// comments
    fprintf(mfp, "\n<dt>Species\n<dd>%d\n", ex.nofspecies());	// nof species
    fputs("</dl>\n", mfp);

    fputs("<p>\n\n", mfp);

    fputs("<dl>\n", mfp);

    const DynamicOrder order(morder, ex.speciesset());
    for(int i = 0; i!=order.end(); i++)
    {
	fprintf(mfp, "<dt><em>%s</em>\n<dd>(%d) ",
		order.species(i).c_str(),
		ex.speciescount(order.species(i))
		);
	::htmlfputs(ex.speciescomment(order.species(i)).c_str(), // comments
		    mfp);
	fputs("\n", mfp);
    }

    fputs("</dl>\n\n", mfp);

    fflush(mfp);
}


/*----------------------------------------------------------------------------
 *
 * error()
 *
 *
 *----------------------------------------------------------------------------
 */
bool HtmlSink::error() const
{
    return merror;
}


/*----------------------------------------------------------------------------
 *
 * ::putpreamble()
 *
 *
 *----------------------------------------------------------------------------
 */
static int putpreamble(FILE * fp)
{
    fprintf(fp,
	    "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 3.2 Final//EN\">\n"
	    "<HTML>\n"
	    "<HEAD>\n"
	    "<META HTTP-EQUIV=\"Content-Type\" "
	    "CONTENT=\"text/html; charset=iso-8859-1\">\n"
	    "<TITLE>Gavia contents</TITLE>\n"
	    "</HEAD>\n"
	    "<BODY>\n\n");

    return 1;
}


/*----------------------------------------------------------------------------
 *
 * ::putpostamble()
 *
 *
 *----------------------------------------------------------------------------
 */
static int putpostamble(FILE * fp)
{
    fprintf(fp,
	    "\n"
	    "<hr>\n\n"
	    "</BODY>\n"
	    "</HTML>\n");

    return 1;
}


/*----------------------------------------------------------------------------
 *
 * ::htmlfputs()
 *
 *
 * As ANSI C fputs(), but escapes &<> characters
 *----------------------------------------------------------------------------
 */
static int htmlfputs(const char * str, FILE * fp)
{
    while(*str)
    {
        switch(*str)
        {
        case '&':
            fputs("&amp;", fp);
            break;
        case '<':
            fputs("&lt;", fp);
            break;
        case '>':
            fputs("&gt;", fp);
            break;
        default:
            putc(*str, fp);
            break;
        }

        str++;
    }

    return 1;
}
