/*----------------------------------------------------------------------------
 *
 * $Id: filtersink.cc,v 1.1 2002-09-29 19:47:56 grahn Exp $
 *
 * filtersink.cc
 *
 * Copyright (c) 2002 Jörgen Grahn <jgrahn@algonet.se>
 * All rights reserved.
 *
 *----------------------------------------------------------------------------
 *
 *----------------------------------------------------------------------------
 */

static const char* rcsid() { rcsid(); return
"$Id: filtersink.cc,v 1.1 2002-09-29 19:47:56 grahn Exp $";
}

#include <cassert>
#include <cstdio>
#include <cstring>
#include <errno.h>

#include "speciesorder.hh"
#include "exception.hh"
#include "gabsink.hh"

#include "filtersink.hh"


/*----------------------------------------------------------------------------
 *
 * constructor
 *
 *
 *----------------------------------------------------------------------------
 */
FilterSink::FilterSink(const SpeciesOrder * so, const char * path)
{
    assert(so);
    assert(path);

    FILE * fp = popen(path, "w");
    if(!fp)
    {
	throw GaviaException(errno);
    }

    gsink = new GabSink(so, fp);
}


/*----------------------------------------------------------------------------
 *
 * destructor
 *
 *
 *----------------------------------------------------------------------------
 */
FilterSink::~FilterSink()
{
    delete gsink;
}


/*----------------------------------------------------------------------------
 *
 * put()
 *
 *
 * Print an Excursion, using the
 * SpeciesOrder given at creation time.
 *----------------------------------------------------------------------------
 */
void FilterSink::put(const Excursion& ex)
{
    gsink->put(ex);
}
