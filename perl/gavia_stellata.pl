#!/usr/bin/perl -w
#
# $Id: gavia_stellata.pl,v 1.3 2000-08-10 19:17:09 grahn Exp $
# $Name:  $
#
# gavia_stellata.pl - interactively adding
# excursions to the default .gab file
#
# Copyright (c) 1999, 2000 Jörgen Grahn <jgrahn@algonet.se>
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

$obsbok = glob "~gavia/obsbok";
$template = glob "~gavia/template/default";
$tmpname0 = "/tmp/gavia_stellata.tmp0.$$";
$tmpname1 = "/tmp/gavia_stellata.tmp1.$$";

-w $obsbok
    or die
    "You won't be able to write to $obsbok (maybe you should checkout?)\n";

if(system("gaviadate <$template >$tmpname0")) {
    unlink $tmpname0;
    die;
}

print "Invoking editor...\n";

if(system("emacs $tmpname0")) {
    unlink $tmpname0;
    die;
}

if(system("gaviadeexpand <$tmpname0 >$tmpname1")) {
    unlink $tmpname0;
    unlink $tmpname1;
    die;
}

unlink $tmpname0;

print "Invoking editor... again...\n";

if(system("emacs $tmpname1")) {
    unlink $tmpname1;
    die;
}

if(system("cat >>$obsbok $tmpname1")) {
    unlink $tmpname1;
    die;
}

unlink $tmpname1;

exit 0;
