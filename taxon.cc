/*
 * Copyright (c) 2013, 2014 Jörgen Grahn
 * All rights reserved.
 *
 */
#include "taxon.h"
#include "regex.h"

#include <iostream>


std::ostream& Taxon::put(std::ostream& os) const
{
    os << id.val << ' ' << name;

    if(!latin.empty()) {
	os << " (" << latin << ')';
    }

    if(!alias.empty()) {

	for(std::vector<std::string>::const_iterator i = alias.begin();
	    i!=alias.end();
	    i++) {
	    if(i==alias.begin()) {
		os << ' ';
	    }
	    else {
		os << ", ";
	    }
	    os << *i;
	}
    }
    return os;
}


bool Taxon::match(const Regex& re) const
{
    if(re.match(name)) return true;
    if(re.match(latin)) return true;
    for(const std::string& a : alias) {
	if(re.match(a)) return true;
    }
    return false;
}
