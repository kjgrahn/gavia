#!/usr/bin/perl -w
#
# $Id: gaviadate.pl,v 1.3 2001-06-17 20:49:18 grahn Exp $
# $Name:  $
#
# gaviadate.pl - insert today's date in any empty
# date: header
#
# Requires GNU date from gnu sh-utils.
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
