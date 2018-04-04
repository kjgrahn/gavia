/*
 * Copyright (C) 2013 Jörgen Grahn.
 * All rights reserved.
 */
#include <filetest.h>

#include <orchis.h>


namespace {

    void assert_readable(const char* f) {
	orchis::assert_eq(filetest::readable(f), true);
    }

    void assert_not_readable(const char* f) {
	orchis::assert_eq(filetest::readable(f), false);
    }

    void assert_writeable(const char* f) {
	orchis::assert_eq(filetest::writeable(f), true);
    }

    void assert_not_writeable(const char* f) {
	orchis::assert_eq(filetest::writeable(f), false);
    }
}


namespace ftest {

    using orchis::TC;

    void readable(TC)
    {
	assert_readable("/etc/passwd");
    }

    void not_readable(TC)
    {
	assert_not_readable("/etc/shadow");
	assert_not_readable(".");
	assert_not_readable("/");
	assert_not_readable("xyzzy");
	assert_not_readable("");
    }

    void not_writable(TC)
    {
	assert_not_writeable("/etc/passwd");
	assert_not_writeable("/");
	assert_not_writeable(".");
    }
}
