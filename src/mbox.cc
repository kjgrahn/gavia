/*
 * Copyright (c) 2013 Jörgen Grahn
 * All rights reserved.
 *
 */
#include "mbox.h"

#include "excursion.hh"

#include <algorithm>
#include <time.h>

namespace {

    std::ostream& join(std::ostream& os, const std::string& s)
    {
	std::string ss = s;
	std::replace(ss.begin(), ss.end(), '\n', ' ');
	return os << ss;
    }

    /**
     * "Sun Jan  1 00:00:00 2012"
     */
    std::ostream& utc(std::ostream& os, const struct tm& tm)
    {
	char buf[40];
	if(asctime_r(&tm, buf)) {
	    std::replace(buf, buf + sizeof buf, '\n', '\0');
	    os << buf;
	}
	return os;
    }

    /**
     * "Sat, 13 Apr 2013 10:12:34 -0000", or simpler:
     * "13 Apr 2013 10:12 -0000"
     *
     * Note that -0000 means that "the date-time contains no
     * information about the local time zone".
     */
    std::ostream& rfc2822(std::ostream& os, const struct tm& tm)
    {
	static const char names[] =
	    "Jan\0Feb\0Mar\0Apr\0May\0Jun\0"
	    "Jul\0Aug\0Sep\0Oct\0Nov\0Dec";
	char buf[30];
	std::sprintf(buf, "%2d %s %d 00:00 -0000",
		     tm.tm_mday,
		     &names[tm.tm_mon],
		     1900+tm.tm_year);

	return os << buf;
    }
}


std::ostream& MboxHeader::put(std::ostream& os) const
{
    const struct tm tm = ex.date.tm();
    os << "From GAVIA@invalid ";
    utc(os, tm) << '\n';
    os << "MIME-Version: 1.0\n"
       << "Content-Type: text/plain; charset=\"iso-8859-1\"\n"
       << "Return-Path: <>\n"
       << "From: \"";
    join(os, ex.find_header("observers")) << "\" <>\n";
    os << "Subject: ";
    join(os, ex.place) << '\n';
    os << "Date: ";
    rfc2822(os, tm) << '\n';

    return os;
}
