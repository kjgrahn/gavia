/*
 * $Id: test_cont.cc,v 1.7 2007-07-02 11:21:29 grahn Exp $
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
}

namespace cont {

    void testA() {
	istringstream iss("");
	Continuation cs(iss);
	testicle::assert_eq("", line(cs));
	testicle::assert_(!cs);
    }
    void testB() {
	istringstream iss("\n");
	Continuation cs(iss);
	testicle::assert_eq("", line(cs));
	testicle::assert_eq(1, cs.line());
	testicle::assert_(!cs);
    }
    void testC() {
	istringstream iss("foo");
	Continuation cs(iss);
	testicle::assert_eq("foo", line(cs));
	testicle::assert_eq(1, cs.line());
	testicle::assert_(!cs);
    }
    void testD() {
	istringstream iss("foo\n");
	Continuation cs(iss);
	testicle::assert_eq("foo", line(cs));
	testicle::assert_eq(1, cs.line());
	testicle::assert_(!cs);
    }
    void testE() {
	istringstream iss("foo ");
	Continuation cs(iss);
	testicle::assert_eq("foo ", line(cs));
	testicle::assert_eq(1, cs.line());
	testicle::assert_(!cs);
    }
    void testF() {
	istringstream iss("foo\n"
			  "bar\n");
	Continuation cs(iss);
	testicle::assert_eq("foo", line(cs));
	testicle::assert_eq(1, cs.line());
	testicle::assert_eq("bar", line(cs));
	testicle::assert_eq(2, cs.line());
	testicle::assert_(!cs);
    }
    void testG() {
	istringstream iss("foo bar\t\n"
			  "  foo bar\n");
	Continuation cs(iss);
	testicle::assert_eq("foo bar foo bar", line(cs));
	testicle::assert_eq(2, cs.line());
	testicle::assert_(!cs);
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
	testicle::assert_(!cs);
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
	testicle::assert_(!cs);
    }
    void testJ() {
	istringstream iss("foo\n"
			  " foo\n"
			  " foo\n"
			  " foo\n");
	Continuation cs(iss);
	testicle::assert_eq("foo foo foo foo", line(cs));
	testicle::assert_eq(4, cs.line());
	testicle::assert_(!cs);
    }
    void testK() {
	istringstream iss("foo     \n"
			  "bar\n");
	Continuation cs(iss);
	testicle::assert_eq("foo     ", line(cs));
	testicle::assert_eq(1, cs.line());
	testicle::assert_eq("bar", line(cs));
	testicle::assert_eq(2, cs.line());
	testicle::assert_(!cs);
    }
}
