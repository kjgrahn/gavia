/*
 * Copyright (c) 1999--2001, 2013 Jörgen Grahn
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
#include <string>
#include <list>
#include <iostream>
#include <getopt.h>

#include "files...h"
#include "taxa.h"
#include "excursion.h"


extern "C" {
    const char* gavia_name();
    const char* gavia_version();
}


namespace {

    template<class BinOp>
    struct Reverse {
	explicit Reverse(const BinOp& op) : op(op) {}
	BinOp op;
	bool operator() (const Excursion& a, const Excursion& b) const {
	    return op(b, a);
	}
    };

    struct ByDate {
	bool operator() (const Excursion& a, const Excursion& b) const {
	    return a.date < b.date;
	}
    };

    struct ByPlace {
	bool operator() (const Excursion& a, const Excursion& b) const {
	    return a.place < b.place;
	}
    };
}


int main(int argc, char ** argv)
{
    using std::string;

    const string prog = argv[0];
    const string usage = string("usage: ")
	+ prog + " [-dpr] file ...\n"
	"       "
	+ prog + " --version";
    const char optstring[] = "dpr";
    struct option long_options[] = {
	{"version", 0, 0, 'V'},
	{"help", 0, 0, 'H'},
	{0, 0, 0, 0}
    };

    std::cin.sync_with_stdio(false);
    std::cout.sync_with_stdio(false);

    char sorting = 'd';
    bool reverse = false;

    int ch;
    while((ch = getopt_long(argc, argv,
			    optstring,
			    &long_options[0], 0)) != -1) {
	switch(ch) {
	case 'd':
	case 'p':
	    sorting = ch;
	    break;
	case 'r':
	    reverse = true;
	    break;
	case 'V':
	    std::cout << prog << ", part of "
		      << gavia_name() << ' ' << gavia_version() << "\n"
		      << "Copyright (c) 2000 - 2013 Jörgen Grahn\n";
	    return 0;
	    break;
	case 'H':
	    std::cout << usage << '\n';
	    return 0;
	    break;
	case ':':
	case '?':
	default:
	    std::cerr << usage << '\n';
	    return 1;
	    break;
	}
    }

    Files files(argv+optind, argv+argc);
    std::ifstream species(Taxa::species_file());
    Taxa taxa(species, std::cerr);

    std::list<Excursion> book;
    const Excursion nil;
    Excursion ex;
    while(get(files, std::cerr, taxa, ex)) {
	book.push_back(nil);
	book.back().swap(ex);
    }

    /* Note that reverse sort is not the same thing as sorting, then
     * reverse; the latter sort is not stable. So we do it the hard
     * way.
     */
    switch(sorting+reverse) {
    case 'd':
	book.sort(ByDate());
	break;
    case 'd'+true:
	book.sort(Reverse<ByDate>(ByDate()));
	break;
    case 'p':
	book.sort(ByPlace());
	break;
    case 'p'+true:
	book.sort(Reverse<ByPlace>(ByPlace()));
	break;
    }

    for(auto i = begin(book); i != end(book); i++) {
	if(i!=begin(book)) std::cout << '\n';
	std::cout << *i;
    }

    return 0;
}
