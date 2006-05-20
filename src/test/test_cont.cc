/*
 * $Id: test_cont.cc,v 1.5 2006-05-20 08:07:44 grahn Exp $
 *
 * Copyright (C) 2006 Jörgen Grahn.
 * All rights reserved.
 */
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

#include <iostream>
#include <sstream>

#include "../contstream.hh"

using std::istringstream;
using std::string;


class Test: public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(Test);
    CPPUNIT_TEST(testA);
    CPPUNIT_TEST(testB);
    CPPUNIT_TEST(testC);
    CPPUNIT_TEST(testD);
    CPPUNIT_TEST(testE);
    CPPUNIT_TEST(testF);
    CPPUNIT_TEST(testG);
    CPPUNIT_TEST(testH);
    CPPUNIT_TEST(testI);
    CPPUNIT_TEST(testJ);
    CPPUNIT_TEST_SUITE_END();

    std::string line(Continuation& c) {
	CPPUNIT_ASSERT(c);
	string s("deadbeef");
	getline(c, s);
	return s;
    }

public:
    void testA() {
	istringstream iss("");
	Continuation cs(iss);
	CPPUNIT_ASSERT_EQUAL(string(""), line(cs));
	CPPUNIT_ASSERT(!cs);
    }
    void testB() {
	istringstream iss("\n");
	Continuation cs(iss);
	CPPUNIT_ASSERT_EQUAL(string(""), line(cs));
	CPPUNIT_ASSERT_EQUAL(1, cs.line());
	CPPUNIT_ASSERT(!cs);
    }
    void testC() {
	istringstream iss("foo");
	Continuation cs(iss);
	CPPUNIT_ASSERT_EQUAL(string("foo"), line(cs));
	CPPUNIT_ASSERT_EQUAL(1, cs.line());
	CPPUNIT_ASSERT(!cs);
    }
    void testD() {
	istringstream iss("foo\n");
	Continuation cs(iss);
	CPPUNIT_ASSERT_EQUAL(string("foo"), line(cs));
	CPPUNIT_ASSERT_EQUAL(1, cs.line());
	CPPUNIT_ASSERT(!cs);
    }
    void testE() {
	istringstream iss("foo ");
	Continuation cs(iss);
	CPPUNIT_ASSERT_EQUAL(string("foo "), line(cs));
	CPPUNIT_ASSERT_EQUAL(1, cs.line());
	CPPUNIT_ASSERT(!cs);
    }
    void testF() {
	istringstream iss("foo\n"
			  "bar\n");
	Continuation cs(iss);
	CPPUNIT_ASSERT_EQUAL(string("foo"), line(cs));
	CPPUNIT_ASSERT_EQUAL(1, cs.line());
	CPPUNIT_ASSERT_EQUAL(string("bar"), line(cs));
	CPPUNIT_ASSERT_EQUAL(2, cs.line());
	CPPUNIT_ASSERT(!cs);
    }
    void testG() {
	istringstream iss("foo bar\t\n"
			  "  foo bar\n");
	Continuation cs(iss);
	CPPUNIT_ASSERT_EQUAL(string("foo bar foo bar"), line(cs));
	CPPUNIT_ASSERT_EQUAL(2, cs.line());
	CPPUNIT_ASSERT(!cs);
    }
    void testH() {
	istringstream iss("foobar\t\n"
			  "  foobar \n"
			  "  foobar \n"
			  "foobar\n");
	Continuation cs(iss);
	CPPUNIT_ASSERT_EQUAL(string("foobar foobar foobar "), line(cs));
	CPPUNIT_ASSERT_EQUAL(3, cs.line());
	CPPUNIT_ASSERT_EQUAL(string("foobar"), line(cs));
	CPPUNIT_ASSERT_EQUAL(4, cs.line());
	CPPUNIT_ASSERT(!cs);
    }
    void testI() {
	istringstream iss("foobar\t\n"
			  "  foobar \n"
			  "\t\t\n"
			  "foobar\n");
	Continuation cs(iss);
	CPPUNIT_ASSERT_EQUAL(string("foobar foobar "), line(cs));
	CPPUNIT_ASSERT_EQUAL(2, cs.line());
	CPPUNIT_ASSERT_EQUAL(string("\t\t"), line(cs));
	CPPUNIT_ASSERT_EQUAL(3, cs.line());
	CPPUNIT_ASSERT_EQUAL(string("foobar"), line(cs));
	CPPUNIT_ASSERT_EQUAL(4, cs.line());
	CPPUNIT_ASSERT(!cs);
    }
    void testJ() {
	istringstream iss("foo\n"
			  " foo\n"
			  " foo\n"
			  " foo\n");
	Continuation cs(iss);
	CPPUNIT_ASSERT_EQUAL(string("foo foo foo foo"), line(cs));
	CPPUNIT_ASSERT_EQUAL(4, cs.line());
	CPPUNIT_ASSERT(!cs);
    }
};


int main()
{
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(Test::suite());
    return runner.run()? 0: 1;
}
