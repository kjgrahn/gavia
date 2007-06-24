#!/usr/bin/perl -w
#
# $Id: gavia_stat.pl,v 1.4 2007-06-24 20:10:24 grahn Exp $
# $Name:  $
#
# gavia_stat.pl - take a book in 'gab' format and output its content
#                 in 'species date place observers numbers comment' format.
# 
# Useful for generating reports based on species rather than excursion.
#
# Copyright (c) 2000, 2007 Jörgen Grahn
# All rights reserved.
use strict;

my ($place, $date, $observers) = ('', '', '');

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
    elsif(/\s*([a-zåäö ]+?)\s*:[^:]*:([^:]*:.*$)/i) {

	print "$1 : $date : $place : $2 : $observers\n";
    }
}

exit 0;
