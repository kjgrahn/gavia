/*----------------------------------------------------------------------------
 *
 * $Id: version.cc,v 1.1 2000-06-01 14:13:03 grahn Exp $
 *
 * version.cc
 *
 * Copyright (C) 2000 Jörgen Grahn <jorgen.grahn@opensoftware.se>
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

static const char* rcsid() { rcsid(); return
"$Id: version.cc,v 1.1 2000-06-01 14:13:03 grahn Exp $";
}

#include <cassert>

#include "version.hh"


/*----------------------------------------------------------------------------
 *
 * constructor
 *
 *
 *----------------------------------------------------------------------------
 */
Version::Version(const char *name)
{
    ;
}



/*----------------------------------------------------------------------------
 *
 * name()
 *
 *
 *----------------------------------------------------------------------------
 */
const char * Version::name() const
{
    return "foo";
}
