#!/usr/bin/perl -w
#
# $Id: gavia_stellata.pl,v 1.18 2006-01-03 23:18:08 grahn Exp $
# $Name:  $
#
# gavia_stellata.pl - interactively adding
# excursions to the default .gab file
#
# Copyright (c) 1999--2006 Jörgen Grahn
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. The name of the author may not be used to endorse or promote products
#    derived from this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' ...etc
#

use strict;
use vars qw($opt_f);
use Getopt::Std;

sub syntaxcheck;
sub pad;
sub mtime;


getopts('f:') and
    my $obsbok = shift
    or die "usage: $0 [-f template] file\n";

my $template = "INSTALLBASE/lib/gavia/default";
my $hometempl = glob "~/.gavia_template";
$template = $hometempl
    if -f $hometempl;
$template = $opt_f
    if defined $opt_f;

my $tmpname0 = "/tmp/gavia_stellata.tmp0.$$.gavia";
my $tmpname1 = "/tmp/gavia_stellata.tmp1.$$.gavia";

my $editor = "emacs";

if(defined $ENV{"GAVIAEDITOR"}) {
    $editor = $ENV{"GAVIAEDITOR"};
}
elsif(defined $ENV{"VISUAL"}) {
    $editor = $ENV{"VISUAL"};
}
elsif(defined $ENV{"EDITOR"}) {
    $editor = $ENV{"EDITOR"};
}

-w $obsbok and -f $obsbok
    or die "`$obsbok' is not a writeable file.\n";

my ($d0, $d1, $d2, $mday, $mon, $year, $d3, $d4, $d5) = localtime(time);
my $datestr = sprintf "%04d%02d%02d", 1900+$year, 1+$mon, $mday;

open TMPL, "<$template"
    or die "cannot open `$template' for reading: $!\n";
open TMP0, ">$tmpname0"
    or die "cannot open `$tmpname0': $!\n";

while(<TMPL>) {
    # fill in date fields with today's date
    if(/^(\s*date\s*):\s+$/) {
	print TMP0 "$1: $datestr\n";
    }
    else {
	print TMP0;
    }
}

close TMPL;
close TMP0;

my $mtime0 = mtime($tmpname0);

print STDERR "Invoking editor... ";

if(system("$editor $tmpname0")) {
    unlink $tmpname0;
    die "Couldn't execute '$editor'.\n";
}

my $mtime = mtime($tmpname0);
if($mtime == $mtime0) {
    unlink $tmpname0;
    print STDERR "\nAborted unmodified excursion.\n";
    exit 0;
}

open TMP0, "<$tmpname0"
    or die "cannot open `$tmpname0': $!\n";
open TMP1, ">$tmpname1"
    or die "cannot open `$tmpname1': $!\n";

while(<TMP0>) {
    # trim away species and comments, add line spacing
    next if /^[a-zåäö \t]+:\s*:\s*:\s*$/;
    next if /^\s*\#/;
    next if /^\s*$/;

    print TMP1;
    print TMP1 "\n" if /^\s*}\s*$/;
}

close TMP0;
unlink $tmpname0;
close TMP1;

print STDERR "again...\n";

if(system("$editor $tmpname1")) {
    die;
}

my ($smax, $nmax) = syntaxcheck($tmpname1);
# avoid too much jaggedness
$smax++;
$smax = 16 if $smax<16;

open TMP1, "<$tmpname1"
    or die "cannot open `$tmpname1': $!\n";
open BOOK, ">>$obsbok"
    or die "cannot append to $obsbok: $!\n";

while(<TMP1>) {
    if(/^(\s*[a-zåäö ]+?)\s*:(.*?):\s*(\d*)\s*:(.*)/i) {

	printf BOOK "%s:%s: %${nmax}s:%s\n", pad($1, $smax), $2, $3, $4;
	next;
    }

    print BOOK;
}

close TMP1;
unlink $tmpname1;
close BOOK;

exit 0;


# syntax check '$file', including validating species lists,
# but only _warn_ the user.
# Some things are not caught, e.g. duplicate lines and
# other line-spanning syntax errors.
#
# Also, return max widths for the species and number columns,
# to make it possible to align them later for readability.
#
sub syntaxcheck {
    my $file = shift;
    my %species;
    my ($smax, $nmax) = (0,0);

    open SPECIES, "INSTALLBASE/lib/gavia/species"
	or return ($smax, $nmax);

    while(<SPECIES>) {
	chomp;
	$species{$1} = 1 if /^\s*\d{3}\s+(.+)/;
    }
    close SPECIES;

    open FILE, $file;
    while(<FILE>) {
	chomp;

	next if /^\s*(time|observers|weather|comments)\s*:/i;
	next if /^\s*$/;
	next if /^\s*\#/;
	next if /^\s*[{}]\s*$/;
	next if /^\s*\}\s*\{\s*$/;
	if(/^\s*(place|date)\s*:\s*(.*)/i) {
	    if($2 eq "") {
		print STDERR "warning: field '$1' is empty\n";
	    }
	    next;
	}
	if(/(\s*([a-zåäö ]+?))\s*:.*?:\s*(\d*)\s*:/i) {
	    print STDERR "warning: species '$2' is unknown/misspelled\n"
		unless defined($species{$2});
	    my ($s, $n) = (length $1, length $3);
	    $smax = ($s > $smax)? $s: $smax;
	    $nmax = ($n > $nmax)? $n: $nmax;
	    next;
	}
	print STDERR "warning: malformed line\n   $_\n";
    }
    close FILE;
    return ($smax, $nmax);
}

# pad a string with whitespace to the right, until
# it's of a certain width. Use TABs to minimize the
# characters needed.
#
sub pad {
    my $s = shift;
    my $width = shift;

    my $slen = length $s;
    return $s if $slen >= $width;
    # last tab stop: 0, 8, 16, ...
    my $tabstop = $width - $width % 8;
    my ($ntab, $nsp);
    if($slen<$tabstop) {
	$ntab = 1 + ($tabstop-$slen-1)/8;
	$nsp = $width - $tabstop;
    }
    else {
	$ntab = 0;
	$nsp = $width - $slen;
    }
    return sprintf "%s%s%s", $s, "\t" x $ntab, " " x $nsp;
}

sub mtime {
    my $path = shift;
    my @stats = stat($path);
    return $stats[9];
}
