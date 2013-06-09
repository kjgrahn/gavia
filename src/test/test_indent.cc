/* Copyright (C) 2013 Jörgen Grahn.
 * All rights reserved.
 */
#include <indent.h>

#include <testicle.h>
#include <iostream>
#include <sstream>

using std::string;

namespace indent {

    string adjust(const std::string& s, const size_t n, const bool left)
    {
	std::ostringstream oss;
	indent::adjust(oss, s, n, left);
	return oss.str();
    }

    string ljust(const std::string& s, const size_t n)
    {
	std::ostringstream oss;
	indent::ljust(oss, s, n);
	return oss.str();
    }

    string rjust(const std::string& s, const size_t n)
    {
	std::ostringstream oss;
	indent::rjust(oss, s, n);
	return oss.str();
    }

    string andjust(const std::string& s, const size_t n)
    {
	std::ostringstream oss;
	indent::andjust(oss, s, n);
	return oss.str();
    }
}

namespace indent {

    void test_simple()
    {
	using testicle::assert_eq;

	assert_eq(ljust("foo", 5), "foo  ");
	assert_eq(rjust("foo", 5), "  foo");
	assert_eq(andjust("foo\nbar\nbaz", 1),
		  "foo\n"
		  " bar\n"
		  " baz");
    }
}
