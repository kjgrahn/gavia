#!/usr/bin/perl -w
#
# $Id: gaviadate.pl,v 1.2 1999-10-24 20:51:38 grahn Exp $
# $Name:  $
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
