/*----------------------------------------------------------------------------
 *
 * $Id: version.cc,v 1.4 2002-09-29 09:17:12 grahn Exp $
 *
 * version.cc
 *
 * Copyright (C) 2000--2002 Jörgen Grahn <jgrahn@algonet.se>
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
"$Id: version.cc,v 1.4 2002-09-29 09:17:12 grahn Exp $";
}

#include <cstring>
#include <cctype>
#include <cassert>
#include <cstdio>

#include "version.hh"

using std::isspace;
using std::isalnum;

/*----------------------------------------------------------------------------
 *
 * constructor
 *
 * When given a string on the form
 *   \$Name:  $
 * initialize the version name to
 *   <name> <num>.<num>...
 * otherwise to something apologetic...
 *
 *----------------------------------------------------------------------------
 */
Version::Version(const char *name)
{
  char * p;
  char * q = namebuf;


  assert(name);

  std::strcpy(q, "");
  
  if((p = (char *)std::strstr(name, "$" "Name:"))) {

    p += std::strlen("$" "Name:");

    while(isspace(*p)) {
      p++;
    }

    while(isalnum(*p)) {
      *q++ = *p++;
    }
    *q = '\0';

    if(*p=='-') {

	p++;
	*q++ = ' ';
	*q = '\0';

	int n = std::strspn(p, "0123456789-");
	std::strncat(q, p, n);

	while(*q) {
	    if(*q=='-') {
		*q = '.';
	    }
	    q++;
	}
    }
  }

  if(!std::strcmp(namebuf, "")){
      std::sprintf(namebuf, "Gavia (non-release build no older than %s)",
		   __DATE__);
  }
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
    return namebuf;
}
