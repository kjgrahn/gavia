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
#include <cstdio>
#include <ctime>
#include <getopt.h>
#include <sys/types.h>
#include <unistd.h>

#include "taxa.h"
#include "excursion.hh"
#include "editor.h"


extern "C" {
    const char* gavia_name();
    const char* gavia_version();
    const char* gavia_prefix();
}


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
     * Invent a temporary file name "/tmp/gavia_stellata.pid.gavia."
     * I'd rather not do this by hand, but the numerous library
     * functions are, as always, either deprecated or unsuitable.
     */
    std::string temp_name()
    {
	char buf[50];
	std::snprintf(buf, sizeof buf,
		      "/tmp/gavia_stellata.%x.gavia",
		      unsigned(getpid()));
	return buf;
    }


    std::string today()
    {
	char buf[4+3+3+1];
	const time_t t = time(0);
	struct tm tm;
	localtime_r(&t, &tm);
	std::strftime(buf, sizeof buf,
		      "%Y-%m-%d", &tm);
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
	    std::cout << prog << ", part of "
		      << gavia_name() << ' ' << gavia_version() << "\n"
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

    if(optind+1!=argc) {
	std::cerr << usage << '\n';
	return 1;
    }

    const std::string book = argv[optind];

    return editor(book)? 0: 1;

    return 0;
}
