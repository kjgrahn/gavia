#!/usr/bin/perl -w
#
# $Id: gavia_stellata.pl,v 1.12 2002-11-23 17:07:03 grahn Exp $
# $Name:  $
#
# gavia_stellata.pl - interactively adding
# excursions to the default .gab file
#
# Copyright (c) 1999--2002 Jörgen Grahn <jgrahn@algonet.se>
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

$obsbok = shift
    or die "usage: $0 filename\n";
$template = (glob "~/.gavia_template"
    or "INSTALLBASE/lib/gavia/default")
    or die "Cannot find an excursion template to use.\n";
$tmpname0 = "/tmp/gavia_stellata.tmp0.$$";
$tmpname1 = "/tmp/gavia_stellata.tmp1.$$";

if(defined $ENV{"GAVIAEDITOR"}) {
    $editor = $ENV{"GAVIAEDITOR"};
}
elsif(defined $ENV{"VISUAL"}) {
    $editor = $ENV{"VISUAL"};
}
elsif(defined $ENV{"EDITOR"}) {
    $editor = $ENV{"EDITOR"};
}
else {
    # rudely assume emacs is installed and in the path
    $editor = "emacs";
}

-w $obsbok
    or die
    "\'$obsbok\' is not writeable.\n";

if(system("gaviadate <$template >$tmpname0")) {
    unlink $tmpname0;
    die "\'gaviadate\' failed, exiting.\n";
}

($a,$a,$a,$a,$a,$a,$a,$a,$a,$mtime0,$a,$a,$a) = stat($tmpname0);

print STDERR "Invoking editor... ";

if(system("$editor $tmpname0")) {
    unlink $tmpname0;
    die "Couldn't execute '$editor'.\n";
}

($a,$a,$a,$a,$a,$a,$a,$a,$a,$mtime,$a,$a,$a) = stat($tmpname0);
if($mtime == $mtime0) {
    unlink $tmpname0;
    print STDERR "\nAborted unmodified excursion.\n";
    exit 0;
}

if(system("gaviadeexpand <$tmpname0 >$tmpname1")) {
    unlink $tmpname0;
    unlink $tmpname1;
    die "'gaviadeexpand' failed, exiting.\n";
}

unlink $tmpname0;

print STDERR "again...\n";

if(system("$editor $tmpname1")) {
    unlink $tmpname1;
    die;
}

syntaxcheck($tmpname1);

if(system("cat >>$obsbok $tmpname1")) {
    unlink $tmpname1;
    die "Failed to add the new data to $obsbok, exiting.\n";
}

unlink $tmpname1;

exit 0;


# syntax check '$file', including validating species lists,
# but only _warn_ the user.
# Some things are not caught, e.g. duplicate lines and
# other line-spanning syntax errors.
#
sub syntaxcheck {
    my $file = shift;
    my %species;

    open SPECIES, "INSTALLBASE/lib/gavia/species"
	or return;

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
	if(/\s*([a-zåäö ]+?)\s*:.*?:\s*\d*\s*:/i) {
	    print STDERR "warning: species '$1' is unknown/misspelled\n"
		unless defined($species{$1});
	    next;
	}
	print STDERR "warning: malformed line\n   $_\n";
    }
    close FILE;
}
