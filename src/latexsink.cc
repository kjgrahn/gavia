/*----------------------------------------------------------------------------
 *
 * $Id: latexsink.cc,v 1.3 1999-10-24 20:52:24 grahn Exp $
 *
 * latexsink.cc
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
 *----------------------------------------------------------------------------
 */

static const char rcsid[] =
"$Id: latexsink.cc,v 1.3 1999-10-24 20:52:24 grahn Exp $";

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "dynamicorder.hh"

#include "latexsink.hh"


static int putpreamble(FILE *);
static int putpostamble(FILE *);
static int latexfputs(const char *, FILE *);


/*----------------------------------------------------------------------------
 *
 * constructor
 *
 *
 *----------------------------------------------------------------------------
 */
LaTeXSink::LaTeXSink(const SpeciesOrder * so, const char * path)
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
LaTeXSink::LaTeXSink(const SpeciesOrder * so, FILE * fp)
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
LaTeXSink::~LaTeXSink()
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
 * Print an Excursion as LaTeX2e text, using the
 * SpeciesOrder given at creation time.
 *----------------------------------------------------------------------------
 */
void LaTeXSink::put(const Excursion& ex)
{
    if(error())
    {
	return;		// no need to keep writing at I/O error
    }

    long date = ex.getdate();

    fprintf(mfp, "\\section*{%04ld--%02ld--%02ld ",
	    date/10000,
	    (date%10000)/100,
	    date%100);					// date
    latexfputs(ex.getplace().c_str(), mfp); 		// place
    fputs("}\n\n", mfp);

    fputs("\\begin{description}\n", mfp);

    fprintf(mfp, "  \\item[Time]      ");	    
    latexfputs(ex.gettime().c_str(), mfp);		// time
    fputs("\n", mfp);

    fprintf(mfp, "  \\item[Observers] ");
    latexfputs(ex.getobservers().c_str(), mfp);			// observers
    fputs("\n", mfp);

    fprintf(mfp, "  \\item[Weather]   ");
    latexfputs(ex.getweather().c_str(), mfp);			// weather
    fputs("\n", mfp);

    fprintf(mfp, "  \\item[Comments]   ");
    latexfputs(ex.getcomments().c_str(), mfp);			// comments
    fputs("\n", mfp);

    fprintf(mfp, "  \\item[Species]   %d\n",
	    ex.nofspecies());				// nof species

    fputs("\\end{description}\n", mfp);
    fputs("\n", mfp);

    const DynamicOrder order(morder, ex.speciesset());
    if(order.end()!=0)
    {
	fputs("\\begin{longtable}{|l|r|p{2.5in}|}\n", mfp);
	fputs("\\hline\n", mfp);

	for(int i = 0; i!=order.end(); i++)
	{
	    const Species species(order.species(i));
	    int count = ex.speciescount(species);

	    assert(count>=0);

	    if(count>0)
	    {
		fprintf(mfp, "  %s & %d & ",
			species.c_str(),
			count);
	    }
	    else
	    {
		fprintf(mfp, "  %s &    & ",
			species.c_str());
	    }
	    latexfputs(ex.speciescomment(species).c_str(), mfp);
	    fputs("\\\\\n", mfp);
	}

	fputs("\\hline\n", mfp);
	fputs("\\end{longtable}\n", mfp);
	fputs("\n", mfp);
    }

    fflush(mfp);
}


/*----------------------------------------------------------------------------
 *
 * error()
 *
 *
 *----------------------------------------------------------------------------
 */
bool LaTeXSink::error() const
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
    fputs("%%\n", fp);
    fputs("%% LaTeX2e source generated by Gavia\n", fp);
    fprintf(fp, "%%%% <dollar>%s\n", rcsid+1); // don't output full RCS keywords
    fputs("%%\n", fp);
    fputs("\\documentclass[a4paper]{article}\n", fp);
    fputs("\\usepackage[swedish]{babel}\n", fp);
#if 0
    fputs("\\usepackage{wasysym}\n", fp);
#endif
    fputs("\\usepackage{t1enc}\n", fp);
    fputs("\\usepackage{longtable}\n", fp);
    fputs("\\usepackage{parskip}\n", fp);
    fputs("\n", fp);
    fputs("\\pagestyle{empty}\n", fp);
    fputs("\n", fp);
    fputs("\\setlongtables\n", fp);
    fputs("\n", fp);
    fputs("\\begin{document}\n", fp);
    fputs("\n", fp);

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
    fputs("\n", fp);
    fputs("\\end{document}\n", fp);

    return 1;
}


/*----------------------------------------------------------------------------
 *
 * ::latexfputs()
 *
 *
 * As ANSI C fputs(), but escapes or changes "#%_ characters
 *----------------------------------------------------------------------------
 */
static int latexfputs(const char * str, FILE * fp)
{
    while(*str)
    {
	switch(*str)
	{
	case '"':
	    fputs("''", fp);
	    break;
	case '#':
	case '%':
	case '_':
	    putc('\\', fp);
	    /* FALLTHROUGH */
	default:
	    putc(*str, fp);
	    break;
	}

	str++;
    }

    return 1;
}
