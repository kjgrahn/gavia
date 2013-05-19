/* Copyright (c) 1999, 2008, 2011, 2013 Jörgen Grahn
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
#include "excursion.hh"
#include "exception.hh"

#include "lineparse.h"
#include "files...h"

#include <algorithm>

namespace {

    struct Errlog {
	Errlog(std::ostream& errstream,
	       const Files& files)
	    : errstream(errstream),
	      files(files)
	{}

	void general(const std::string& s);
	void header(const std::string& s);
	void sighting(const std::string& s);
	void trailer();

	void warn_header(const char* s, size_t len);
	void warn_sighting(const char* s, size_t len);

	std::ostream& errstream;
	const Files& files;
    };
}


/**
 * Read one excursion from 'is', using and possibly augmenting 'spp'
 * meanwhile.  Logs errors (warnings, really) to 'err'.
 * Returns false at eof with no complete excursion read.
 */
bool get(Files& is, std::ostream& errstream,
	 Taxa& spp, Excursion& ex)
{
    using Parse::ws;
    using Parse::trimr;

    Errlog err(errstream, is);

    enum State { BETWEEN, HEADERS, SIGHTINGS };
    State state = BETWEEN;
    std::string s;

    while(is.getline(s)) {

	const char* a = s.c_str();
	const char* const b = trimr(a, a + s.size());

	const char* c = ws(a, b);
	if(c==b || *c=='#') continue;

	if(state==BETWEEN) {

	    if(*a=='{' && a+1==b) {
		state = HEADERS;
	    }
	    else {
		err.general(s);
		continue;
	    }
	}
	else if(state==HEADERS && c==a) {

	    if(a+2==b && a[0]=='}' && a[1]=='{') {
		state = SIGHTINGS;
		continue;
	    }

	    c = std::find(a, b, ':');
	    if(c==b) {
		err.header(s);
		continue;
	    }

	    const char* d = trimr(a, c);
	    c = ws(c+1, b);

	    /* [a, d) : [c, b) */
	    if(!ex.add_header(a, d-a, c, b-c)) {
		err.warn_header(a, d-a);
	    }
	}
	else if(state==HEADERS) {

	    /* continuation ___ [c, b) */
	    if(!ex.add_header_cont(c, b-c)) {
		err.header(s);
	    }
	}
	else if(state==SIGHTINGS && c==a) {

	    if(a+1==b && *a=='}') {
		return true;
	    }

	    /* species : marker : n : comment
	     * a       c        d   e        b
	     */
	    c = std::find(a, b, ':');
	    if(c==b) {
		err.sighting(s);
		continue;
	    }
	    const char* d = std::find(c+1, b, ':');
	    if(d==b) {
		err.sighting(s);
		continue;
	    }
	    const char* e = std::find(d+1, b, ':');
	    if(e==b) {
		err.sighting(s);
		continue;
	    }

	    /* species : marker : n : comment
	     * a      .  c     .  d.  e      b
	     */
	    const char* ae = trimr(a, c);
	    c = ws(c+1, b);
	    const char* ce = trimr(c, d);
	    d = ws(d+1, b);
	    const char* de = trimr(d, e);
	    e = ws(e+1, b);
	    if(a==ae) {
		err.sighting(s);
		continue;
	    }
	    if(c==ce && d==de && e==b) {
		/* unfilled */
		continue;
	    }

	    /* [a, ae) : marker : [d, de) : [e, b) */
	    if(!ex.add_sighting(spp,
				a, ae-a,
				d, de-d,
				e, b-e)) {
		err.warn_sighting(a, ae-a);
	    }
	}
	else if(state==SIGHTINGS) {

	    /* continuation ___ [c, b) */
	    if(!ex.add_sighting_cont(c, b-c)) {
		err.sighting(s);
	    }
	}
    }

    if(state!=BETWEEN) {
	err.trailer();
    }
    return false;
}
