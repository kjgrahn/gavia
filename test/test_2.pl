#!/usr/bin/perl -w
# $Id: test_2.pl,v 1.1 1999-10-24 08:10:53 grahn Exp $
#
#

(-x "../src/gavia_grep")
    or die "gavia_grep isn't available for testing!\n";

-s "test_2.book" or die "test_2.book not found; aborting";

print<<EOF;
Testing efficiency by greping a large book for
something unlikely... You _have_ compiled gavia_grep
with profiling enabled, right? (-pg everywhere)
EOF


`../src/gavia_grep aardvark test_2.book >/dev/null`;
die "gavia_grep lost!\n" if $?;


print "no obvious errors; next check result_1.{book,txt,html,tex}\n";

exit 0
