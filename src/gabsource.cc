/*----------------------------------------------------------------------------
 *
 * $Id: gabsource.cc,v 1.19 2008-01-03 09:38:19 grahn Exp $
 *
 * gabsource.cc
 *
 * Copyright (c) 1999, 2000, 2001, 2002, 2004, 2006, 2008 Jörgen Grahn
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *----------------------------------------------------------------------------
 *
 *----------------------------------------------------------------------------
 */
static const char* rcsid() { rcsid(); return
"$Id: gabsource.cc,v 1.19 2008-01-03 09:38:19 grahn Exp $";
}

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cctype>

#include <string>
#include <sstream>

#include "speciesorder.hh"
#include "canonorder.hh"
#include "speciesredro.hh"
#include "exception.hh"
#include "regex.hh"

#include "gabsource.hh"

using std::string;


/**
 * Parsing bits, gathered here for clarity.
 */
struct Parsing {
    Parsing()
	: blankline("^[ \t]*$"),
	  comment("^[ \t]*#"),
	  headstart("^\\{[ \t]*$"),
	  bodystart("^\\}\\{[ \t]*$"),
	  bodyend("^\\}[ \t]*$"),
	  header("^[^: \t]+[ \t]*:"),
	  //     "xxxx xxxx    : ### :    NNNN : ..."
	  spline("^[^: \t][^:]*:[^:]*:[0-9 \t]*:"),
	  //        yyyy-mm-dd
	  isodate("^[0-9]{4}-[01][0-9]-[0-3][0-9]$")
    {}

    bool isblank(const string& s) const { return blankline.matches(s); }
    bool iscomment(const string& s) const  { return comment.matches(s); }
    bool isheadstart(const string& s) const { return headstart.matches(s); }
    bool isbodystart(const string& s) const { return bodystart.matches(s); }
    bool isbodyend(const string& s) const { return bodyend.matches(s); }
    bool splitheader(const string& s, string * name, string * value) const;
    bool splitsp(const string& s,
		 string * name,
		 string * mark,
		 string * no,
		 string * comment) const;
    unsigned long date(const string& s) const;

    const Regex blankline;
    const Regex comment;
    const Regex headstart;
    const Regex bodystart;
    const Regex bodyend;
    const Regex header;
    const Regex spline;
    const Regex isodate;
};

namespace {

    enum strip_t {
	STRIP_BOTH,
	STRIP_LEFT
    };

    /**
     * If 's' is non-null, replace its content with the stuff in
     * [begin, end), with leading and (by default) trailing whitespace
     * stripped.
     */
    void stripped(string * s,
		  const char * begin, const char * end,
		  strip_t kind = STRIP_BOTH)
    {
	using std::isspace;

	if(!s) return;

	while(begin!=end && isspace(*begin)) begin++;
	if(kind==STRIP_BOTH) {
	    while(begin!=end && isspace(*(end-1))) end--;
	}
	*s = string(begin, end);
    }
}


bool Parsing::splitheader(const string& s, string * name, string * value) const
{
    if(!header.matches(s)) {
	return false;
    }

    const char * const begin = s.c_str();
    const char * p = begin;
    while(*p!=':') p++;
    const char * const colon = p;
    stripped(name, begin, colon);
    stripped(value, colon+1, begin + s.size(),
	     STRIP_LEFT);
    return true;
}


/**
 * Try to treat 's' as a species line, and pull at its parts.
 * Returns true iff it was a species line:
 * name : mark : no : comment
 */
bool Parsing::splitsp(const string& s,
		      string * name,
		      string * mark,
		      string * no,
		      string * comment) const
{
    if(!spline.matches(s)) {
	return false;
    }

    const char * const begin = s.c_str();
    const char * p = begin;
    while(*p!=':') p++;
    const char * const colon1 = p;
    stripped(name, begin, colon1);
    p++;
    while(*p!=':') p++;
    const char * const colon2 = p;
    stripped(mark, colon1+1, colon2);
    p++;
    while(*p!=':') p++;
    const char * const colon3 = p;
    stripped(no, colon2+1, colon3);
    stripped(comment, colon3+1, begin + s.size(),
	     STRIP_LEFT);

    return true;
}


unsigned long Parsing::date(const string& s) const
{
    const string::size_type size = s.size();
    const char * const ss = s.c_str();
    char * end;
    unsigned long n = strtoul(ss, &end, 10);
    if(*end) {
	if(isodate.matches(s)) {
	    n *= 10000;
	    n += strtoul(ss+5, 0, 10) * 100;
	    n += strtoul(ss+8, 0, 10);
	    return n;
	}
	else {
	    return 0;
	}
    }
    else if(size==6) {
	if(n<780101) {
	    /* y2k */
	    n+=1000000;
	}
	n += 19000000;
	return n;
    }
    else if(size==8) {
	return n;
    }
    else {
	return 0;
    }
}


GabSource::GabSource(std::istream& is)
    : cs_(is),
      line_(1),
      eof_(false),
      parsing_(new Parsing)
{
    CanonOrder order;
    redro_ = new SpeciesRedro(&order);
    eatexcursion();
}


GabSource::~GabSource()
{
    delete redro_;
    delete parsing_;
}


/**
 * Return the current Excursion. Undefined if eof().
 */
Excursion GabSource::excursion()
{
    assert(!eof());

    return excursion_;
}


/**
 * Advance to the next Excursion. Undefined if eof().
 */
void GabSource::next()
{
    assert(!eof());

    eatexcursion();
}


/**
 * True iff we're at EOF and the current Excursion is invalid.
 * Typically used as 'while(!s.eof()) { ... }'.
 */
bool GabSource::eof() const
{
    return eof_;
}


/**
 * Try to pull another Excursion from input, and set state.
 *
 * May also throw GaviaException.
 */
void GabSource::eatexcursion()
{
    if(eof_) return;

    excursion_ = Excursion();

    const Parsing& pa = *parsing_;
    string s;
    while(cs_) {
	getline(cs_, s);
	if(pa.isblank(s) || pa.iscomment(s)) continue;
	if(pa.isheadstart(s)) break;
	throw GaviaException("parse error", cs_.line());
    }
    // head
    while(cs_) {
	getline(cs_, s);
	if(pa.isblank(s) || pa.iscomment(s)) continue;
	string name;
	string value;
	if(pa.splitheader(s, &name, &value)) {
	    if(name=="place") {
		if(value=="") {
		    throw GaviaException("place name required", cs_.line());
		}
		excursion_.setplace(value);
	    }
	    else if(name=="date") {
		unsigned long n = pa.date(value);
		if(n==0) {
		    throw GaviaException("bad or absent date", cs_.line());
		}
		excursion_.setdate(n);
	    }
	    else if(name=="time") {
		excursion_.settime(value);
	    }
	    else if(name=="observers") {
		excursion_.setobservers(value);
	    }
	    else if(name=="weather") {
		excursion_.setweather(value);
	    }
	    else if(name=="comments") {
		excursion_.setcomments(value);
	    }
	    else {
		throw GaviaException("unknown field", cs_.line());
	    }
	    continue;
	}
	if(pa.isbodystart(s)) break;
	throw GaviaException("parse error", cs_.line());
    }
    // body
    while(cs_) {
	getline(cs_, s);
	if(pa.isblank(s) || pa.iscomment(s)) continue;
	string name;
	string mark;
	string no;
	string comment;
	if(pa.splitsp(s, &name, &mark, &no, &comment)) {
	    const Species species(name);
	    if(!redro_->ismember(species)) {
		std::ostringstream os;
		os << "invalid species '" << species << "'";
		throw GaviaException(os.str(), cs_.line());
	    }
	    if(excursion_.has(species)) {
		std::ostringstream os;
		os << "duplicate species '" << species << "'";
		throw GaviaException(os.str(), cs_.line());
	    }
	    if(mark=="" && no=="" && comment=="") continue;
	    excursion_.insert(species, atol(no.c_str()), comment);
	    continue;
	}
	if(pa.isbodyend(s)) break;
	throw GaviaException("parse error", cs_.line());
    }

    eof_ = !cs_;
}
