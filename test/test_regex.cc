/* Copyright (c) 2019 Jörgen Grahn
 * All rights reserved.
 *
 */
#include <regex.h>

#include <orchis.h>

namespace regex {

    using orchis::TC;

    void assert_broken(const Regex& re)
    {
	orchis::assert_true(re.bad());
    }

    void broken(TC)
    {
	assert_broken(Regex("\\1"));
	assert_broken(Regex("["));
	assert_broken(Regex("\\"));
	assert_broken(Regex("+"));
    }

    void matches(TC)
    {
	const std::string s = "foo bar foobar";
	auto assert_matches = [&s] (const char* r) {
				  const Regex re(r);
				  orchis::assert_false(re.bad());
				  orchis::assert_true(re.match(s));
			      };
	assert_matches("");
	assert_matches("f");
	assert_matches("o");
	assert_matches("fo[o-p]");
	assert_matches("f.+bar$");

	assert_matches("fo{2} bar");
    }

    void mismatch(TC)
    {
	const std::string s = "foobar foo bar";
	auto assert_mismatch = [&s] (const char* r) {
				   const Regex re(r);
				   orchis::assert_false(re.bad());
				   orchis::assert_false(re.match(s));
			       };
	assert_mismatch("z");
	assert_mismatch("^o");
	assert_mismatch("foo$");
    }

    void icase(TC)
    {
	using orchis::assert_true;
	const Regex re("foo");
	assert_true(re.match("foo"));
	assert_true(re.match("FOO"));
	assert_true(re.match("Foo"));
    }
}
