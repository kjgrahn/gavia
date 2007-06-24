#!/usr/bin/perl -w
#
# $Id: gavia_stat.pl,v 1.5 2007-06-24 20:26:37 grahn Exp $
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

my @acc = ();

while(<>)
{
    my @aline = ();
    my $bline = '';

    if(/^\s+\S/) { # SPX
	push @acc, $_;
	next unless eof();
	@aline = @acc; @acc = ();
    }
    elsif(/^\s+/) { # SP
	@aline = @acc; @acc = ();
	$bline = $_;
    }
    else { # X
	@aline = @acc;
	if(eof()) {
	    $bline = $_;
	}
	else {
	    @acc = ($_);
	}
    }
    my @llines = ();
    if(@aline) {
	my $aline = join('', @aline);
	$aline =~ s/\s*?\n\s+/ /g;
	push @llines, $aline;
    }
    push @llines, $bline if $bline;
    # end line unfolding stuff

    foreach (@llines) {
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
}

exit 0;
