/*----------------------------------------------------------------------------
 *
 * $Id: motorola.c,v 1.1 1999-10-24 08:10:52 grahn Exp $
 *
 * motorola.c
 *
 * Copyright (C) 1999 Jörgen Grahn <jorgen.grahn@opensoftware.se>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *----------------------------------------------------------------------------
 *
 * Functions to read/write raw dumped 16-bit and
 * 32-bit words from a stream. The integers have big (Motorola) endianness.
 *
 * NOTE: these functions _might_ be little endian-specific.
 * Not tested on non-Intel machines.
 *----------------------------------------------------------------------------
 */

static const char rcsid[] =
"$Id: motorola.c,v 1.1 1999-10-24 08:10:52 grahn Exp $";

#include <stdio.h>

#include <assert.h>

#include "motorola.h"


/*----------------------------------------------------------------------------
 *
 * readword()
 *
 * Read a 16-bit word from a stream. The most significant octet comes
 * first in the file.
 * Returns false if EOF or error, in which case *n is undefined as well.
 *----------------------------------------------------------------------------
 */
int motorolareadword(FILE * fp, unsigned int *n)
{
    int acc;
    int acc2;

    acc = fgetc(fp);
    if(acc==EOF)
    {
	return(0);
    }

    acc = (1<<8) * (unsigned char)acc;

    acc2 = fgetc(fp);
    if(acc==EOF)
    {
	return(0);
    }

    *n = acc+acc2;

    return 1;
}


/*----------------------------------------------------------------------------
 *
 * readulong()
 *
 * Read a 32-bit unsigned from a stream. The most significant octet comes
 * first in the file, the least significant last.
 * Returns false if EOF or error, in which case *n is undefined as well.
 *----------------------------------------------------------------------------
 */
int motorolareadulong(FILE * fp, unsigned long *n)
{
    unsigned int acc;
    unsigned int acc2;

    if(motorolareadword(fp, &acc)
       && motorolareadword(fp, &acc2))
    {
	*n = acc*(1<<16)+acc2;
	return(1);
    }

    return(0);
}


/*----------------------------------------------------------------------------
 *
 * writeword()
 *
 * The opposite of readword().
 * If false, write failed.
 *----------------------------------------------------------------------------
 */
int motorolawriteword(unsigned int n, FILE * fp)
{
    int acc;

    acc = 1;
    acc = acc && (fputc(n>>8, fp)!=EOF);
    acc = acc && (fputc(n&0xff, fp)!=EOF);

    return(acc);
}


/*----------------------------------------------------------------------------
 *
 * writeulong()
 *
 * The opposite of readulong().
 * If false, write failed.
 *----------------------------------------------------------------------------
 */
int motorolawriteulong(unsigned long n, FILE * fp)
{
    int acc;

    acc = motorolawriteword((unsigned int)(n>>16), fp);
    acc = acc && motorolawriteword((unsigned int)(n & 0xffff), fp);

    return(acc);
}
