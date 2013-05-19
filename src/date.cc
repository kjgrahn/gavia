/*
 * Copyright (c) 2013 Jörgen Grahn
 * All rights reserved.
 *
 */
#include "date.h"

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>


Date::Date(const char* a, const char* b)
    : val(0)
{
    while(a!=b && !std::isdigit(*a)) a++;

    /* (pretending to have guarantees that
     * *b is a readable non-digit)
     */
    char* end;
    unsigned long n = std::strtoul(a, &end, 10);
    if(end-a == 4+2+2) {
	val = n;
    }
    else if(end-a == 2+2+2) {
	if(n<780101) {
	    /* y2k */
	    n+=1000000;
	}
	n += 19000000;
	val = n;
    }
    else if(end-a == 4) {
	val = n*10000;
	a = end;
	if(a==b || *a!='-') return;

	a++;
	n = std::strtoul(a, &end, 10);
	if(end-a != 2 || n<1 || n>12) return;
	val += n*100;
	a = end;
	if(a==b || *a!='-') return;

	a++;
	n = std::strtoul(a, &end, 10);
	if(end-a != 2 || n<1 || n>31) return;
	val += n;
    }
}


std::ostream& Date::put(std::ostream& os) const
{
    char buf[4+3+3+1];
    const unsigned yyyy = val/10000;
    const unsigned mm   = (val/100) % 100;
    const unsigned dd   = val % 100;

    if(dd) {
	std::sprintf(buf, "%04u-%02u-%02u", yyyy, mm, dd);
    }
    else if(mm) {
	std::sprintf(buf, "%04u-%02u", yyyy, mm);
    }
    else if(yyyy) {
	std::sprintf(buf, "%04u", yyyy);
    }
    else {
	std::strcpy(buf, "nil");
    }

    return os << buf;
}
