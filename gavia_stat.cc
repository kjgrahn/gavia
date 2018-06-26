/*
 * Copyright (c) 2018 Jörgen Grahn
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
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <getopt.h>

#include "files...h"
#include "taxa.h"
#include "excursion.h"
#include "regex.h"


extern "C" {
    const char* gavia_name();
    const char* gavia_version();
}


namespace {

    /**
     * 's' but with newlines replaced by spaces.
     */
    std::string join(std::string s)
    {
	std::replace(begin(s), end(s), '\n', ' ');
	return s;
    }

    class Columnar {
    public:
	Columnar(std::ostream& os, const std::string& delimiter);
	void add(const Excursion& ex);

    private:
	std::ostream& os;
	const std::string delimiter;
    };

    Columnar::Columnar(std::ostream& os, const std::string& delimiter)
	: os{os},
	  delimiter{delimiter}
    {}

    void Columnar::add(const Excursion& ex)
    {
	auto h = [&ex](const char* name) { return join(ex.find_header(name)); };

	for(auto it = ex.sbegin(); it != ex.send(); it++) {
	    const Excursion::Sighting& s = *it;
	    os << join(s.name)
	       << delimiter <<  ex.date
	       << delimiter <<  h("place")
	       << delimiter <<  join(s.number)
	       << delimiter <<  join(s.comment)
	       << delimiter <<  h("observers")
	       << '\n';
	}
    }
}


int main(int argc, char ** argv)
{
    using std::string;

    const string prog = argv[0];
    const string usage = string("usage: ")
	+ prog + " file ...\n"
	"       "
	+ prog + " --version";
    const struct option long_options[] = {
	{"version", 0, 0, 'V'},
	{"help", 0, 0, 'H'},
	{0, 0, 0, 0}
    };

    std::cin.sync_with_stdio(false);
    std::cout.sync_with_stdio(false);

    int ch;
    while((ch = getopt_long(argc, argv, "",
			    &long_options[0], 0)) != -1) {
	switch(ch) {
	case 'V':
	    std::cout << prog << ", part of "
		      << gavia_name() << ' ' << gavia_version() << "\n"
		      << "Copyright (c) 2018 Jörgen Grahn\n";
	    return 0;
	    break;
	case 'H':
	    std::cout << usage << '\n';
	    return 0;
	    break;
	case ':':
	case '?':
	    std::cerr << usage << '\n';
	    return 1;
	    break;
	default:
	    break;
	}
    }

    if(optind==argc) {
	std::cerr << usage << '\n';
	return 1;
    }

    Files files(argv+optind, argv+argc);
    std::ifstream species(Taxa::species_file());
    Taxa taxa(species, std::cerr);
    species.close();

    Columnar columnar{std::cout, " : "};

    Excursion ex;
    while(get(files, std::cerr, taxa, ex)) {
	columnar.add(ex);
    }

    return 0;
}
