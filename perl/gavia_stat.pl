#!/usr/bin/perl -w
#
# $Id: gavia_stat.pl,v 1.2 2000-12-17 14:49:24 grahn Exp $
# $Name:  $
#
# gavia_stat.pl - take a book in 'gab' format and output its content
#                 in 'species date place observers numbers comment' format.
# 
# Useful for generating reports based on species rather than excursion.
#

while(<>)
{
    chomp;

    if(/^place\s*:\s*(.+)/i) {

	$place = $1;
	$date = "";
	$observers = "";
    }
    elsif(/^date\s*:\s*(\d+)/i) {

	$date = $1;
    }
    elsif(/^observers\s*:\s*(.+)/i) {

	$observers = $1;
    }
    elsif(/^(time|weather|comments)/i) {

	;
    }
    elsif(/^\s*\#/) {
	;
    }
    elsif(/\s*([a-zедц ]+)\s*:[^:]*:([^:]*:.*$)/i) {

	print "$1 : $date : $place : $observers : $2\n";
    }
}

exit 0;
