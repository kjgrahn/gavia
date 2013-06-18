/*
 * Copyright (C) 2013 Jörgen Grahn.
 * All rights reserved.
 */
#include <lineparse.h>

#include <testicle.h>

namespace {

    using testicle::assert_eq;

    void assert_ws(const std::string& s,
		   size_t n)
    {
	const char* p = s.data();
	assert_eq(Parse::ws(p, p + s.size()) - p, n);
    }

    void assert_non_ws(const std::string& s,
		   size_t n)
    {
	const char* p = s.data();
	assert_eq(Parse::non_ws(p, p + s.size()) - p, n);
    }

    void assert_trimr(const std::string& s,
		      const std::string& t)
    {
	const char* p = s.data();
	const char* q = Parse::trimr(p, p + s.size());
	assert_eq(std::string(p, q-p), t);
    }
}


namespace lineparse {

    void test_ws()
    {
	assert_ws("", 0);
	assert_ws("a", 0);
	assert_ws(" ", 1);
	assert_ws(" \t", 2);
	assert_ws(" \n", 2);
	assert_ws(" \xff", 1);
    }

    void test_non()
    {
	assert_non_ws("", 0);
	assert_non_ws("a", 1);
	assert_non_ws("a\tb", 1);
	assert_non_ws("\xff" "a", 2);
    }

    void test_trimr()
    {
	assert_trimr("", "");
	assert_trimr("foo", "foo");
	assert_trimr("  \n\t", "");
	assert_trimr("f  \n\t", "f");
	assert_trimr("\xff  \n\t", "\xff");
    }
}
