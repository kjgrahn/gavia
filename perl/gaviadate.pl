#!/usr/bin/perl -w
#
# $Id: gaviadate.pl,v 1.4 2001-07-08 09:45:26 grahn Exp $
# $Name:  $
#
# gaviadate.pl - insert today's date in any empty
# date: header
#

($q, $q, $q,
 $mday, $mon, $year,
 $q, $q, $q) = localtime(time);

while(<>)
{
    if(/^\s*date\s*:\s+$/) {
	printf "date         : %04d%02d%02d\n", 1900+$year, 1+$mon, $mday;
    }
    else {
	print;
    }
}

exit 0;
