#!/usr/bin/perl -w
#
# $Id: gaviadeexpand.pl,v 1.2 1999-10-24 20:51:38 grahn Exp $
# $Name:  $
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
