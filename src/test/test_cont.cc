/*
 * $Id: test_cont.cc,v 1.1 2006-05-01 17:12:00 grahn Exp $
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
	CPPUNIT_ASSERT(!cs);
    }
    void testC() {
	istringstream iss("foo");
	Continuation cs(iss);
	CPPUNIT_ASSERT_EQUAL(string("foo"), line(cs));
	CPPUNIT_ASSERT(!cs);
    }
    void testD() {
	istringstream iss("foo\n");
	Continuation cs(iss);
	CPPUNIT_ASSERT_EQUAL(string("foo"), line(cs));
	CPPUNIT_ASSERT(!cs);
    }
    void testE() {
	istringstream iss("foo ");
	Continuation cs(iss);
	CPPUNIT_ASSERT_EQUAL(string("foo "), line(cs));
	CPPUNIT_ASSERT(!cs);
    }
    void testF() {
	istringstream iss("foo\n"
			  "bar\n");
	Continuation cs(iss);
	CPPUNIT_ASSERT_EQUAL(string("foo"), line(cs));
	CPPUNIT_ASSERT_EQUAL(string("bar"), line(cs));
	CPPUNIT_ASSERT(!cs);
    }
    void testG() {
	istringstream iss("foo bar\t\n"
			  "  foo bar\n");
	Continuation cs(iss);
	CPPUNIT_ASSERT_EQUAL(string("foo bar foo bar"), line(cs));
	CPPUNIT_ASSERT(!cs);
    }
};


int main()
{
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(Test::suite());
    return runner.run()? 0: 1;
}
