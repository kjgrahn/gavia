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
#include <string>
#include <iostream>
#include <cstdlib>
#include <getopt.h>
#include <unistd.h>

#include "files...h"
#include "taxa.h"
#include "excursion.hh"


namespace {

    std::string getenv(const char* name)
    {
	const char* p = std::getenv(name);
	return p? p: "";
    }

    /**
     * foo -> $HOME/foo
     */
    std::string tilde(const std::string& tail)
    {
	return getenv("HOME") + "/" + tail;
    }

    /**
     * "/tmp/gavia_stellata.tmp.$$.gavia"
     */
    std::string tmpname()
    {
	char buf[50];
	std::snprintf(buf, sizeof buf,
		      "/tmp/gavia_stellata.tmp.%d.gavia",
		      getpid());
	return buf;
    }
}


int main(int argc, char ** argv)
{
    using std::string;

    const string prog = argv[0];
    const string usage = string("usage: ")
	+ prog + " [-f template] file\n"
	"       "
	+ prog + " --version";
    const char optstring[] = "f:";
    const struct option long_options[] = {
	{"version", 0, 0, 'V'},
	{"help", 0, 0, 'H'},
	{0, 0, 0, 0}
    };

    std::cin.sync_with_stdio(false);
    std::cout.sync_with_stdio(false);

    string extemplate;

    int ch;
    while((ch = getopt_long(argc, argv,
			    optstring,
			    &long_options[0], 0)) != -1) {
	switch(ch) {
	case 'f':
	    extemplate = optarg;
	    break;
	case 'V':
	    std::string version();
	    std::cout << prog << ", part of gavia " << "version()" << "\n"
		      << "Copyright (c) 1999 - 2013 Jörgen Grahn\n";
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

    if(extemplate.empty()) {
	extemplate = tilde(".gavia_template");
	;

    }

    return 0;
}
