#!/usr/bin/perl -w
#
# $Id: gaviadate.pl,v 1.1 1999-10-24 14:30:41 grahn Exp $
#
# gaviadate.pl - insert today's date in any empty
# date: header
#

while(<>)
{
    if(/^\s*date\s*:\s+$/) {
	print `date "+date         : %Y%m%d"`;
    }
    else {
	print;
    }
}

exit 0;
