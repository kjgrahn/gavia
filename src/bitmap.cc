/*----------------------------------------------------------------------------
 *
 * $Id: bitmap.cc,v 1.1 2004-01-07 22:23:00 grahn Exp $
 *
 * bitmap.cc
 *
 * Copyright (c) 1998--2004 Jörgen Grahn <jgrahn@algonet.se>
 * All rights reserved.
 *----------------------------------------------------------------------------
 *
 * A fixed-size bitmap.
 * Operations on it.
 * Also functions to read/write it to a stream in a safe way.
 *----------------------------------------------------------------------------
 */

static const char* rcsid(void) { rcsid(); return
"$Id: bitmap.cc,v 1.1 2004-01-07 22:23:00 grahn Exp $";
}

#include "bitmap.h"


int Bitmap::count() const
{
    int acc = 0;

    for(int i=0; i!=BMAPNR; ++i)
    {
	const int nybbleset[16] = {
	    0, 1, 1, 2,
	    1, 2, 2, 3,
	    1, 2, 2, 3,
	    2, 3, 3, 4
	};
	const unsigned char ch = map[i];

	if(!ch) continue;

	acc += nybbleset[(unsigned int)(ch&0x0f)];
	acc += nybbleset[(unsigned int)(ch>>4)];
    }

    return acc;
}


int Bitmap::read(std::FILE * fp)
{
    return std::fread(map, 1, BMAPNR, fp)==size_t(BMAPNR);
}


int Bitmap::write(std::FILE * fp) const
{
    return std::fwrite(map, 1, BMAPNR, fp)==size_t(BMAPNR);
}
