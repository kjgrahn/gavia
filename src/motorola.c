/*----------------------------------------------------------------------------
 *
 * $Id: motorola.c,v 1.4 2000-08-10 19:47:21 grahn Exp $
 *
 * motorola.c
 *
 * Copyright (c) 1999 Jörgen Grahn <jgrahn@algonet.se>
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
 * Functions to read/write raw dumped 16-bit and
 * 32-bit words from a stream. The integers have big (Motorola) endianness.
 *
 * NOTE: these functions _might_ be little endian-specific.
 * Not tested on non-Intel machines.
 *----------------------------------------------------------------------------
 */

static const char* rcsid(void) { rcsid(); return
"$Id: motorola.c,v 1.4 2000-08-10 19:47:21 grahn Exp $";
}

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
