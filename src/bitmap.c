/*----------------------------------------------------------------------------
 *
 * $Id: bitmap.c,v 1.1 1999-10-24 08:10:52 grahn Exp $
 *
 * bitmap.c
 *
 * Jörgen Grahn <jorgen.grahn@opensoftware.se>
 * 1998-09-26
 *----------------------------------------------------------------------------
 *
 * A fixed-size bitmap.
 * Operations on it.
 * Also functions to read/write it to a stream in a safe way.
 *----------------------------------------------------------------------------
 */

static const char rcsid[] =
"$Id: bitmap.c,v 1.1 1999-10-24 08:10:52 grahn Exp $";

#include <stdio.h>

#include <assert.h>

#include "bitmap.h"


static int internalbitscount8(unsigned char);


/*----------------------------------------------------------------------------
 *
 * create()
 *
 *
 * Creates a Bitmap, zero-filled.
 *----------------------------------------------------------------------------
 */
void bitmapcreate(Bitmap * obj)
{
    int i;


    assert(obj);

    for(i=0; i<BMAPNR; i++)
    {
	obj->map[i] = 0x00;
    }
}


/*----------------------------------------------------------------------------
 *
 * destroy()
 *
 *
 * Destroys a Bitmap.
 *----------------------------------------------------------------------------
 */
void bitmapdestroy(Bitmap * obj)
{
    assert(obj);
}


/*----------------------------------------------------------------------------
 *
 * read()
 *
 *
 * Reads a Bitmap from a stream.
 *----------------------------------------------------------------------------
 */
int bitmapread(Bitmap * obj, FILE * fp)
{
    assert(obj);
    assert(fp);

    return(fread(obj->map, 1, BMAPNR, fp)==BMAPNR);
}


/*----------------------------------------------------------------------------
 *
 * write()
 *
 *
 * Writes a Bitmap to a stream.
 *----------------------------------------------------------------------------
 */
int bitmapwrite(Bitmap * obj, FILE * fp)
{
    assert(obj);
    assert(fp);

    return(fwrite(obj->map, 1, BMAPNR, fp)==BMAPNR);
}


/*----------------------------------------------------------------------------
 *
 * set()
 *
 *
 * Sets a bit.
 * n must be in [0..BMAPNR*8[.
 *----------------------------------------------------------------------------
 */
void bitmapset(Bitmap * obj, int n)
{
    assert(obj);
    assert(n>=0);
    assert(n<BMAPNR*8);

    obj->map[n/8] |= (1<< (7 - (n%8)));
}


/*----------------------------------------------------------------------------
 *
 * clear()
 *
 *
 * Clears a bit.
 * n must be in [0..BMAPNR*8[.
 *----------------------------------------------------------------------------
 */
void bitmapclear(Bitmap * obj, int n)
{
    assert(obj);
    assert(n>=0);
    assert(n<BMAPNR*8);

    obj->map[n/8] &= ~(1<< (7 - (n%8)));

}


/*----------------------------------------------------------------------------
 *
 * isset()
 *
 *
 * Returns 1 if bit 'n' is set, otherwise 0.
 * n must be in [0..BMAPNR*8[.
 * [0..1]
 *----------------------------------------------------------------------------
 */
int bitmapisset(Bitmap * obj, int n)
{
    assert(obj);
    assert(n>=0);
    assert(n<BMAPNR*8);

    return((obj->map[n/8] >> (7-(n%8))) & 1);
}


/*----------------------------------------------------------------------------
 *
 * count()
 *
 * returns number of bits set.
 * [0..BMAPNR*8]
 *----------------------------------------------------------------------------
 */
int bitmapcount(Bitmap * obj)
{
    int acc;
    int i;


    assert(obj);

    acc = 0;
    for(i=0; i<BMAPNR; i++)
    {
	acc+=internalbitscount8(obj->map[i]);
    }

    return(acc);
}


/*----------------------------------------------------------------------------
 *
 * internalbitscount8()
 *
 *
 * Returns the number of bits set in a byte.
 *----------------------------------------------------------------------------
 */
static int internalbitscount8(unsigned char ch)
{
    static int nybbleset[16] = {
	0, 1, 1, 2,
	1, 2, 2, 3,
	1, 2, 2, 3,
	2, 3, 3, 4
    };

    return(nybbleset[(unsigned int)(ch&0x0f)] +
	   nybbleset[(unsigned int)(ch>>4)]);
}
