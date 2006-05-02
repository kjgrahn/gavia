/* -*- c++ -*-
 *
 * $Id: regex.hh,v 1.1 2006-05-02 21:53:58 grahn Exp $
 *
 * regex.h
 *
 * Copyright (C) 2001 Jörgen Grahn <jgrahn@algonet.se>
 *----------------------------------------------------------------------------
 *
 *----------------------------------------------------------------------------
 */
#ifndef REGEX_H
#define REGEX_H

#include <sys/types.h>
#include <regex.h>

#include <string>
#include <cassert>

/**
 * A simple wrapper around the basic parts of
 * POSIX Extended Regular Expressions.
 *
 */
class Regex
{
public:
    explicit Regex(const std::string& regex) {
	int rc = regcomp(&_preg, regex.c_str(), REG_EXTENDED|REG_NOSUB|REG_ICASE);
	assert(!rc);
    }
    ~Regex() {regfree(&_preg);}

    bool matches(const std::string& s) const {
	return !regexec(&_preg, s.c_str(), 0, 0, 0);
    }

private:
    Regex();
    Regex(const Regex&);

    regex_t _preg;
};

#endif
