/*
 * Copyright (C) 2018 Jörgen Grahn.
 * All rights reserved.
 */
#include <excursion.h>
#include <taxa.h>
#include <files...h>

#include <orchis.h>

namespace {
    Taxa taxa()
    {
	const char src[] =
	    "röd glada	(Milvus milvus)\n"
	    "= glada\n"
	    "gulsparv	(Emberiza citrinella)\n";
	std::istringstream iss(src);

	std::ostringstream err;
	auto spp = Taxa(iss, err);
	orchis::assert_eq(err.str(), "");
	return spp;
    }
}


namespace excursion {

    void simple(orchis::TC)
    {
	const char src[] =
	    "{\n"
	    "place        : the\n"
	    "               place\n"
	    "date         : 2018-11-16\n"
	    "time         : the time\n"
	    "observers    : the observers\n"
	    "weather      : the weather\n"
	    "comments     :\n"
	    "}{\n"
	    "gulsparv : :   : bar\n"
	    "# foo is not a species\n"
	    "foo      :-:  0: baz\n"
	    "glada    :#: 17:\n"
	    "}";
	const char ref[] =
	    "{\n"
	    "place	  : the\n"
	    "	    place\n"
	    "date	  : 2018-11-16\n"
	    "time	  : the time\n"
	    "observers : the observers\n"
	    "weather	  : the weather\n"
	    "comments  : \n"
	    "}{\n"
	    "glada		:#: 17: \n"
	    "gulsparv	:#:   : bar\n"
	    "foo		:#:  0: baz\n"
	    "}\n";

	std::stringstream srcs(src);
	Files srcf(srcs);

	Taxa spp = taxa();
	std::ostringstream err;
	Excursion ex;
	orchis::assert_true(get(srcf, err, spp, ex));

	orchis::assert_eq(err.str(),
			  "<string>:12: unfamiliar taxon \"foo\"\n");

	std::ostringstream oss;
	ex.put(oss, true);
	orchis::assert_eq(oss.str(), ref);

	orchis::assert_false(get(srcf, err, spp, ex));
    }

    void optional_headers(orchis::TC)
    {
	const char src[] =
	    "{\n"
	    "bar     : bar\n"
	    "comments: no comment\n"
	    "foo     : foo\n"
	    "}{\n"
	    "}";
	const char ref[] =
	    "{\n"
	    "bar	 : bar\n"
	    "comments : no comment\n"
	    "foo	 : foo\n"
	    "}{\n"
	    "}\n";

	std::stringstream srcs(src);
	Files srcf(srcs);

	Taxa spp = taxa();
	std::ostringstream err;
	Excursion ex;
	orchis::assert_true(get(srcf, err, spp, ex));

	orchis::assert_eq(err.str(), "");

	std::ostringstream oss;
	ex.put(oss, true);
	orchis::assert_eq(oss.str(), ref);

	orchis::assert_false(get(srcf, err, spp, ex));
    }

    void empty_headers(orchis::TC)
    {
	const char src[] =
	    "{\n"
	    "place     : \n"
	    "date      :   \n"
	    "time      : \n"
	    "observers :  \n"
	    "weather   : \n"
	    "comments  :\n"
	    "}{\n"
	    "}";
	const char ref[] =
	    "{\n"
	    "place	  : \n"
	    "date	  : \n"
	    "time	  : \n"
	    "observers : \n"
	    "weather	  : \n"
	    "comments  : \n"
	    "}{\n"
	    "}\n";

	std::stringstream srcs(src);
	Files srcf(srcs);

	Taxa spp = taxa();
	std::ostringstream err;
	Excursion ex;
	orchis::assert_true(get(srcf, err, spp, ex));

	orchis::assert_eq(err.str(),
			  "<string>:2: empty header field \"place\"\n"
			  "<string>:3: empty header field \"date\"\n"
			  "<string>:5: empty header field \"observers\"\n");

	std::ostringstream oss;
	ex.put(oss, true);
	orchis::assert_eq(oss.str(), ref);

	orchis::assert_false(get(srcf, err, spp, ex));
    }
}
