/*
 * $Id: test_cont.cc,v 1.9 2008-01-03 12:51:39 grahn Exp $
 *
 * Copyright (C) 2006, 2007 Jörgen Grahn.
 * All rights reserved.
 */
#include <iostream>
#include <sstream>

#include <testicle.h>

#include "../contstream.hh"

using std::istringstream;
using std::string;

namespace {
    std::string line(Continuation& c) {
	testicle::assert_(c);
	string s("deadbeef");
	getline(c, s);
	return s;
    }

    void assert_line(Continuation& c,
		     const int lineno,
		     const char * const s) {
	std::string ss;
	testicle::assert_(getline(c, ss));
	testicle::assert_eq(ss, s);
	testicle::assert_eq(c.line(), lineno);
    }

    void assert_eof(Continuation& c) {
	std::string s;
	testicle::assert_(!getline(c, s));
    }
}

namespace cont {

    void testA() {
	istringstream iss("");
	Continuation cs(iss);
	testicle::assert_eq("deadbeef", line(cs));
	testicle::assert_(!cs);
    }
    void testB() {
	istringstream iss("\n");
	Continuation cs(iss);
	testicle::assert_eq("", line(cs));
	testicle::assert_eq(1, cs.line());
	assert_eof(cs);
    }
    void testC() {
	istringstream iss("foo");
	Continuation cs(iss);
	testicle::assert_eq("foo", line(cs));
	testicle::assert_eq(1, cs.line());
	assert_eof(cs);
    }
    void testD() {
	istringstream iss("foo\n");
	Continuation cs(iss);
	testicle::assert_eq("foo", line(cs));
	testicle::assert_eq(1, cs.line());
	assert_eof(cs);
    }
    void testE() {
	istringstream iss("foo ");
	Continuation cs(iss);
	testicle::assert_eq("foo ", line(cs));
	testicle::assert_eq(1, cs.line());
	assert_eof(cs);
    }
    void testF() {
	istringstream iss("foo\n"
			  "bar\n");
	Continuation cs(iss);
	testicle::assert_eq("foo", line(cs));
	testicle::assert_eq(1, cs.line());
	testicle::assert_eq("bar", line(cs));
	testicle::assert_eq(2, cs.line());
	assert_eof(cs);
    }
    void testG() {
	istringstream iss("foo bar\t\n"
			  "  foo bar\n");
	Continuation cs(iss);
	testicle::assert_eq("foo bar foo bar", line(cs));
	testicle::assert_eq(2, cs.line());
	assert_eof(cs);
    }
    void testH() {
	istringstream iss("foobar\t\n"
			  "  foobar \n"
			  "  foobar \n"
			  "foobar\n");
	Continuation cs(iss);
	testicle::assert_eq("foobar foobar foobar ", line(cs));
	testicle::assert_eq(3, cs.line());
	testicle::assert_eq("foobar", line(cs));
	testicle::assert_eq(4, cs.line());
	assert_eof(cs);
    }
    void testI() {
	istringstream iss("foobar\t\n"
			  "  foobar \n"
			  "\t\t\n"
			  "foobar\n");
	Continuation cs(iss);
	testicle::assert_eq("foobar foobar ", line(cs));
	testicle::assert_eq(2, cs.line());
	testicle::assert_eq("\t\t", line(cs));
	testicle::assert_eq(3, cs.line());
	testicle::assert_eq("foobar", line(cs));
	testicle::assert_eq(4, cs.line());
	assert_eof(cs);
    }
    void testJ() {
	istringstream iss("foo\n"
			  " foo\n"
			  " foo\n"
			  " foo\n");
	Continuation cs(iss);
	testicle::assert_eq("foo foo foo foo", line(cs));
	testicle::assert_eq(4, cs.line());
	assert_eof(cs);
    }
    void testK() {
	istringstream iss("foo     \n"
			  "bar\n");
	Continuation cs(iss);
	testicle::assert_eq("foo     ", line(cs));
	testicle::assert_eq(1, cs.line());
	testicle::assert_eq("bar", line(cs));
	testicle::assert_eq(2, cs.line());
	assert_eof(cs);
    }
}


namespace continuation {

    void testA() {
	istringstream iss("");
	Continuation cs(iss);
	std::string s("deadbeef");
	testicle::assert_(!getline(cs, s));
	testicle::assert_eq(s, "deadbeef");
    }
    void testB() {
	istringstream iss("\n");
	Continuation cs(iss);
	assert_line(cs, 1, "");
	assert_eof(cs);
    }
    void testC() {
	istringstream iss("%foo");
	Continuation cs(iss);
	assert_line(cs, 1, "%foo");
	assert_eof(cs);
    }
    void testD() {
	istringstream iss("%foo\n");
	Continuation cs(iss);
	assert_line(cs, 1, "%foo");
	assert_eof(cs);
    }
    void testE() {
	istringstream iss("%foo ");
	Continuation cs(iss);
	assert_line(cs, 1, "%foo ");
	assert_eof(cs);
    }
    void testF() {
	istringstream iss("%foo\n"
			  "%bar\n");
	Continuation cs(iss);
	assert_line(cs, 1, "%foo");
	assert_line(cs, 2, "%bar");
	assert_eof(cs);
    }
    void testG() {
	istringstream iss("%foo bar\t\n"
			  "  foo bar\n");
	Continuation cs(iss);
	assert_line(cs, 2, "%foo bar foo bar");
	assert_eof(cs);
    }
    void testH() {
	istringstream iss("%foobar\t\n"
			  "  foobar \n"
			  "  foobar \n"
			  "%foobar\n");
	Continuation cs(iss);
	assert_line(cs, 3, "%foobar foobar foobar ");
	assert_line(cs, 4, "%foobar");
	assert_eof(cs);
    }
    void testI() {
	istringstream iss("%foobar\t\n"
			  "  foobar \n"
			  "\n"
			  "%foobar\n");
	Continuation cs(iss);
	assert_line(cs, 2, "%foobar foobar ");
	assert_line(cs, 3, "");
	assert_line(cs, 4, "%foobar");
	assert_eof(cs);
    }
    void testJ() {
	istringstream iss("%foo\n"
			  " foo\n"
			  " foo\n"
			  " foo\n");
	Continuation cs(iss);
	assert_line(cs, 4, "%foo foo foo foo");
	assert_eof(cs);
    }
    void testK() {
	istringstream iss("%foo     \n"
			  "%bar\n");
	Continuation cs(iss);
	assert_line(cs, 1, "%foo     ");
	assert_line(cs, 2, "%bar");
	assert_eof(cs);
    }
    void testL() {
	istringstream iss("%foo \n"
			  " bar\t\n"
			  " baz \n"
			  "%foo \n"
			  " bar\t\n"
			  " baz \n"
			  " \n"
			  "%foo \n"
			  " bar\t\n"
			  " baz \n");
	Continuation cs(iss);
	assert_line(cs, 3, "%foo bar baz ");
	assert_line(cs, 6, "%foo bar baz ");
	assert_line(cs, 7, " ");
	assert_line(cs, 10, "%foo bar baz ");
	assert_eof(cs);
    }
    void testM() {
	istringstream iss("  \n"
			  "\t\t");
	Continuation cs(iss);
	assert_line(cs, 1, "  ");
	assert_line(cs, 2, "\t\t");
	assert_eof(cs);
    }
    void testN() {
	istringstream iss("  \n"
			  "%foo\n"
			  " bar\n"
			  " baz\n"
			  "%bat");
	Continuation cs(iss);
	assert_line(cs, 1, "  ");
	assert_line(cs, 4, "%foo bar baz");
	assert_line(cs, 5, "%bat");
	assert_eof(cs);
    }
    void testO() {
	istringstream iss("%foo\n"
			  " bar\n"
			  " baz\n"
			  "%bat\n"
			  " ben");
	Continuation cs(iss);
	assert_line(cs, 3, "%foo bar baz");
	assert_line(cs, 5, "%bat ben");
	assert_eof(cs);
    }
    void testP() {
	istringstream iss("%foo\n"
			  " foo\n"
			  "%foo\n"
			  " foo\n");
	Continuation cs(iss);
	assert_line(cs, 2, "%foo foo");
	assert_line(cs, 4, "%foo foo");
	assert_eof(cs);
    }
    void testR() {
	istringstream iss("%foo\n"
			  "\n"
			  "%bar");
	Continuation cs(iss);
	assert_line(cs, 1, "%foo");
	assert_line(cs, 2, "");
	assert_line(cs, 3, "%bar");
	assert_eof(cs);
	assert_eof(cs);
	assert_eof(cs);
    }
}
