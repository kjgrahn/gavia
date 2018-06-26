/*
 * Copyright (C) 2013 Jörgen Grahn.
 * All rights reserved.
 */
#include <files...h>

#include <orchis.h>

namespace {

    std::vector<std::string> cat(const char* const* argv, size_t n)
    {
	std::vector<std::string> acc;
	Files f(argv, argv+n);
	std::string s;
	while(f.getline(s)) {
	    acc.push_back(s);
	}
	return acc;
    }

    std::vector<std::string> cat(const char* a, const char* b)
    {
	const char* const argv[] = {a, b};
	return cat(argv, 2);
    }

    std::vector<std::string> cat(const char* a,
				 const char* b,
				 const char* c)
    {
	const char* const argv[] = {a, b, c};
	return cat(argv, 3);
    }

    std::vector<std::string> cat(const char* a,
				 const char* b,
				 const char* c,
				 const char* d)
    {
	const char* const argv[] = {a, b, c, d};
	return cat(argv, 4);
    }
}


namespace files {

    using orchis::assert_eq;
    using orchis::assert_gt;
    using orchis::assert_;
    using orchis::TC;

    static const char pass[] = "/etc/passwd";
    static const char devnull[] = "/dev/null";
    static const char dir[] = "/";

    void construct(TC)
    {
	const char* const argv[] = {"foo", "bar", "baz"};
	Files f0(argv, argv);
	Files f3(argv, argv+3);
    }

    /* The rest of the tests are kind of Linux-specific; there's
     * /dev/null on every Unix, but what short text files are
     * guaranteed to exist everywhere? I'm assuming /etc/passwd
     * exists as a readable, non-empty text file.
     */

    void null(TC)
    {
	const char* const argv[] = {devnull};
	Files f(argv, argv+1);
	std::string s;
	assert_eq(f.getline(s), false);
    }

    void no_means_no(TC)
    {
	const char* const argv[] = {devnull};
	Files f(argv, argv+0, false);
	std::string s;
	assert_eq(f.getline(s), false);
    }

    void null2(TC)
    {
	const char* const argv[] = {devnull, devnull};
	Files f(argv, argv+2);
	std::string s;
	assert_eq(f.getline(s), false);
    }

    void many(TC)
    {
	const std::vector<std::string> p2 = cat(pass, pass);
	assert_gt(p2.size(), 0);
	assert_eq(p2.size() % 2, 0);

	const char* const null = devnull;
	assert_(cat(null, pass, pass) == p2);
	assert_(cat(pass, pass, null) == p2);
	assert_(cat(pass, null, pass) == p2);
	assert_(cat(pass, null, null, pass) == p2);
	assert_(cat(pass, pass, null, null) == p2);
	assert_(cat(null, null, pass, pass) == p2);
    }

    void err(TC)
    {
	const std::vector<std::string> p2 = cat(pass, pass);
	assert_(cat(devnull, dir, pass, pass) == p2);
    }
}
