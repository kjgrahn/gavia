/*----------------------------------------------------------------------------
 *
 * $Id: gabsource.cc,v 1.13 2006-05-16 21:05:28 grahn Exp $
 *
 * gabsource.cc
 *
 * Copyright (c) 1999 Jörgen Grahn
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
"$Id: gabsource.cc,v 1.13 2006-05-16 21:05:28 grahn Exp $";
}

#include <cstdio>
#include <cstdlib>
#include <cassert>

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
	  spline("^[^: \t][^:]*:[^:]*:[0-9 \t]*:")
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

    const Regex blankline;
    const Regex comment;
    const Regex headstart;
    const Regex bodystart;
    const Regex bodyend;
    const Regex header;
    const Regex spline;
};

namespace {
    /**
     * If 's' is non-null, replace its content with the stuff
     * in [begin, end), with leading and trailing whitespace trimmed.
     */
    void stripped(string * s, const char * begin, const char * end)
    {
	if(!s) return;

	while(begin!=end && std::isspace(*begin)) begin++;
	while(begin!=end && std::isspace(*(end-1))) end--;
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
    stripped(value, colon+1, begin + s.size());
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
    stripped(comment, colon3+1, begin + s.size());

    return true;
}

GabSource::GabSource(std::istream& is)
    : cs_(is),
      line_(1),
      state_(SPACE),
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
    return state_==END;
}


/**
 * Try to pull another Excursion from input, and set state.
 *
 * May also throw GaviaException.
 */
void GabSource::eatexcursion()
{
    const Parsing& pa = *parsing_;
    string s;
    if(state_==SPACE) while(cs_) {
	getline(cs_, s);
	if(pa.isblank(s) || pa.iscomment(s)) continue;
	if(pa.isheadstart(s)) break;
	throw GaviaException("parse error", cs_.line());
    }
    while(cs_) {
	state_ = HEAD;
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
		char * end;
		unsigned long n = strtoul(value.c_str(), &end, 10);
		string::size_type size = value.size();
		if(!(size==6 || size==8) || *end) {
		    throw GaviaException("bad or absent date", cs_.line());
		}
		if(n<780101)
		{
		    /* y2k */
		    n+=1000000;
		}
		n += 19000000;
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
	}
	if(pa.isbodystart(s)) break;
	throw GaviaException("parse error", cs_.line());
    }
    while(cs_) {
	state_ = BODY;
	getline(cs_, s);
	if(pa.isblank(s) || pa.iscomment(s)) continue;
	string name;
	string mark;
	string no;
	string comment;
	if(pa.splitsp(s, &name, &mark, &no, &comment)) {
	    const Species species(name);
	    if(!redro_->ismember(s)) {
		std::ostringstream os;
		os << "invalid species '" << s << "'";
		throw GaviaException(os.str(), cs_.line());
	    }
	    if(excursion_.has(s)) {
		throw GaviaException("duplicate species", cs_.line());
	    }
	    if(mark=="" && no=="" && comment=="") continue;
	    excursion_.insert(species, atol(no.c_str()), comment);
	}
	if(pa.isbodyend(s)) break;
	throw GaviaException("parse error", cs_.line());
    }
}
