#!/usr/bin/perl -w
#
# $Id: gaviadeexpand.pl,v 1.1 1999-10-24 14:30:41 grahn Exp $
#
# gaviadeexpand.pl - remove fluff and unused species
# from a 'gab' file
#

while(<>)
{
    unless(/^[a-zедц \t]+:\s*:\s*:\s*$/ ||
	   /^\s*\#/ ||
	   /^\s*$/
	   )
    {
	print;

	print "\n" if /^\s*}\s*$/;
    }
}

exit 0;
