/*
 * Copyright (c) 2013, 2014 Jörgen Grahn
 * All rights reserved.
 *
 */
#include "taxon.h"
#include "regex.hh"


bool Taxon::match(const Regex& re) const
{
    if(re.match(name)) return true;
    if(re.match(latin)) return true;
    for(const std::string& name : alias) {
	if(re.match(name)) return true;
    }
    return false;
}
