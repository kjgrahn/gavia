#!/usr/bin/perl -w
#
# $Id: gavia_stat.pl,v 1.1 2000-01-16 20:46:07 grahn Exp $
# $Name:  $
#
# gavia_stat.pl - 
# 
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
