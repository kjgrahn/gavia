/* Copyright (c) 2013 J�rgen Grahn
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
#include "excursion.h"
#include "indent.h"

#include <iostream>
#include <algorithm>
#include <sstream>


namespace {

    /**
     * The maximum width of iter->name.
     */
    template<class It>
    size_t max_name(Indent& indent, It a, It b)
    {
	size_t n = 0;
	while(a!=b) {
	    size_t m = indent.measure(a->name);
	    if(m>n) n=m;
	    a++;
	}
	return n;
    }

    template<class It>
    size_t max_number(Indent& indent, It a, It b)
    {
	size_t n = 0;
	while(a!=b) {
	    size_t m = indent.measure(a->number);
	    if(m>n) n=m;
	    a++;
	}
	return n;
    }
}


/**
 * Write in 'gab' format to 'os'. Little translation is done: may
 * optionally sort the sightings according to taxonomic order, but
 * species names are printed as they were entered, empty headers are
 * printed and so on ... more effort is spent on proper indentation.
 *
 * Indents the text after the taxon name to at least column 'indent';
 * more if needed to avoid jaggedness.
 */
std::ostream& Excursion::put(std::ostream& os,
			     const bool sort) const
{
    Indent indent;
    const size_t indentation = 16;

    os << "{\n";
    {
	const size_t n = max_name(indent, begin(headers), end(headers)) + 1;
	const Date& d = this->date;
	/* Printing a Header with the colon in
	 * column 'n', as
	 *
	 * name     : text text text
	 *            text text ...
	 */
	auto print = [&os, &indent, n, &d](const Header& h) {
			 indent.ljust(os, h.name, n) << ": ";
			 if(h.name != "date") {
			     indent.andjust(os, h.value, n+2) << '\n';
			 }
			 else {
			     os << d << '\n';
			 }
		     };

	std::for_each(begin(headers), end(headers), print);
    }

    Sightings sorted;
    if(sort) {
	sorted = sightings;
	std::stable_sort(begin(sorted), end(sorted));
    }
    const Sightings& ss = sort ? sorted : sightings;

    os << "}{\n";
    {
	size_t m = std::max(indentation,
			    max_name(indent, begin(ss), end(ss)) + 1);
	size_t n = max_number(indent, begin(ss), end(ss)) + 1;
	/* Printing a Sighting as
	 *
	 * <    m    >   < n >
	 * taxon      :#:  nnn: text text text
	 *                      text text ...
	 */
	auto print = [&os, &indent, m, n](const Sighting& s) {
			 indent.ljust(os, s.name, m) << ":#:";
			 indent.rjust(os, s.number, n) << ": ";
			 indent.andjust(os, s.comment, m+3+n+2) << '\n';
		     };

	std::for_each(begin(ss), end(ss), print);
    }
    return os << "}\n";
}


/**
 * Like put(ostream&, ...) but using stdio so it can be used with
 * popen(3).  Returns true if the writing worked.
 */
bool Excursion::put(FILE* f,
		    const bool sort) const
{
    std::ostringstream oss;
    put(oss, sort);
    const std::string s = oss.str();
    size_t n = std::fwrite(s.data(), s.size(), 1, f);
    return n==1;
}
