/* $Id: test.cc,v 1.1 1999-10-24 08:10:53 grahn Exp $ */

#include <iostream.h>
#include <string.h>
#include <stdio.h>

#include "species.hh"
#include "speciesset.hh"

#include "speciesorder.hh"
#include "canonorder.hh"
#include "sortedorder.hh"
#include "dynamicorder.hh"

#include "excursion.hh"
#include "streamsource.hh"

#include "exeditor.hh"

#include "textsink.hh"
#include "htmlsink.hh"
#include "latexsink.hh"


void testspeciesorders();
void testexcursionsource();
void testtextsink();
void testhtmlsink();
void testlatexsink();
void testexeditor();


int main(int argc, char ** argv)
{
    if(argc<2 || ::strlen(argv[1])<1)
    {
	return 1;
    }

    switch(argv[1][0])
    {
    case '0':
	::testspeciesorders();
	break;
    case '1':
	::testexcursionsource();
	break;
    case '2':
	::testtextsink();
	break;
    case '3':
	::testhtmlsink();
	break;
    case '4':
	::testlatexsink();
	break;
    case '5':
	::testexeditor();
	break;
    default:
	break;
    }

    return 0;
}


void testspeciesorders()
{
    CanonOrder co;
    SpeciesSet set;

    set.insert("sandsnäppa");
    set.insert("enkelbeckasin");
    set.insert("dammsnäppa");
    set.insert("turkduva");

    SpeciesOrder * sorder =
	new SortedOrder(&co, "e", "z");

    SpeciesOrder * dorder =
	new DynamicOrder(sorder, set);

    for(int i=0; i!=dorder->end(); i++)
    {
	cout << dorder->species(i) << endl;
    }
}


void testexcursionsource()
{
    BookSource * src = new StreamSource("/tmp/foo.book");

    int i = 0;

    while(!(src->eof() || src->error()))
    {
	Excursion ex(src->excursion());
	i++;

	src->next();
    }

    cout << "got " << i << " excursions" << endl;

    if(src->error())
    {
	cout << "error" << endl;
    }

    if(src->eof())
    {
        cout << "eof" << endl;
    }

    delete src;
}


void testtextsink()
{
    SpeciesOrder * so = new SortedOrder(&CanonOrder());
    TextSink sink(so, stdout);
    StreamSource src("/tmp/foo.book");

    while(!(sink.error() || src.eof() || src.error()))
    {
	sink.put(src.excursion());
	src.next();
    }
}


void testhtmlsink()
{
    SpeciesOrder * so = new SortedOrder(&CanonOrder());
    HtmlSink sink(so, stdout);
    StreamSource src("/tmp/foo.book");

    while(!(sink.error() || src.eof() || src.error()))
    {
	sink.put(src.excursion());
	src.next();
    }
}


void testlatexsink()
{
    SpeciesOrder * so = new SortedOrder(&CanonOrder());
    LaTeXSink sink(so, stdout);
    StreamSource src("/tmp/foo.book");

    while(!(sink.error() || src.eof() || src.error()))
    {
	sink.put(src.excursion());
	src.next();
    }
}


void testexeditor()
{
    SpeciesOrder * so = new SortedOrder(&CanonOrder());
    StreamSource src("/tmp/foo.book");

    if(!(src.eof() || src.error()))
    {
	Excursion ex = src.excursion();

	ExEditor edit(&ex, so);

	edit.edit();
    }
}
