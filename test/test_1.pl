#!/usr/bin/perl -w
# $Id: test_1.pl,v 1.1 1999-10-24 08:10:53 grahn Exp $
#
#

(-x "../src/gavia_add"
 and -x "../src/gavia_cat")
    or die "gavia_{add,cat} aren't available for testing!\n";

-s "test_1.gab" or die "test_1.gab not found; cannot continue!\n";

`../src/gavia_add <test_1.gab /dev/null >result_1.book`;
die "gavia_add lost!\n" if $?;

-s "result_1.book" or die "gavia_add didn't do much; empty output!";

`../src/gavia_cat -t result_1.book /dev/null >result_1.txt`;
die "gavia_cat to text lost!\n" if $?;

`../src/gavia_cat -h result_1.book >result_1.html`;
die "gavia_cat to html lost!\n" if $?;

`../src/gavia_cat -l result_1.book >result_1.tex`;
die "gavia_cat to latex lost!\n" if $?;

print "no obvious errors; next check result_1.{book,txt,html,tex}\n";

exit 0
