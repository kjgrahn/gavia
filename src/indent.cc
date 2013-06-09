/*
 * Copyright (c) 2013 Jörgen Grahn
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
 */
#include "indent.h"

#include <iostream>
#include <algorithm>


namespace {

    static const std::string space(20, ' ');

    std::ostream& spacer(std::ostream& os, size_t n)
    {
	while(n >= space.size()) {
	    os << space;
	    n -= space.size();
	}
	if(n) {
	    os.write(space.c_str(), n);
	}
	return os;
    }
}

namespace indent {

    /**
     * A string printed with space padding to a total of 'n'.
     */
    std::ostream& adjust(std::ostream& os, const std::string& s,
			 const size_t n, const bool left)
    {
	size_t sn = s.size();
	if(left && sn) {
	    os << s;
	}
	while(sn < n) {
	    if(n - sn >= space.size()) {
		os << space;
		sn += space.size();
	    }
	    else {
		os.write(space.c_str(), n - sn);
		sn = n;
	    }
	}
	if(!left && sn) {
	    os << s;
	}
	return os;
    }

    std::ostream& ljust(std::ostream& os, const std::string& s,
			const size_t n) {
	return adjust(os, s, n, true);
    }

    std::ostream& rjust(std::ostream& os, const std::string& s,
			const size_t n) {
	return adjust(os, s, n, false);
    }


    /**
     * Print the string 's', replacing any newlines with
     * n spaces + newline.
     */
    std::ostream& andjust(std::ostream& os, const std::string& s,
			  const size_t n)
    {
	const char* a = s.c_str();
	const char* const b = a + s.size();

	while(a!=b) {
	    const char* p = std::find(a, b, '\n');
	    if(p==b) {
		os.write(a, p-a);
		a = p;
	    }
	    else {
		p++;
		os.write(a, p-a);
		spacer(os, n);
		a = p;
	    }
	}
	return os;
    }
}
