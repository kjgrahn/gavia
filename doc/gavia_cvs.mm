.\" $Id: gavia_cvs.mm,v 1.11 2008-01-03 09:38:19 grahn Exp $
.hy
.nr LL 60n
.nr PI 3n
.
.ND "$Date: 2008-01-03 09:38:19 $"
.PF "\s-2$Id: gavia_cvs.mm,v 1.11 2008-01-03 09:38:19 grahn Exp $\s+2"
.
.TL
Using Gavia in combination with CVS
.AU
J\(:orgen Grahn <grahn+src@snipabacken.se>
.AB
Gavia is a set of tools to maintain an electronic bird notebook.
The present document gives a short introduction to
two pieces of software,
.B cvs
and
.B ssh ,
and how they are used in practice to give several people simultaneous
access to Gavia.
.PP
The instructions are of a local nature, and might not be
universally useful.
.AE
.
.
.
.NH
CVS basics
.LP
CVS is\(emfor our purposes\(emmuch like RCS. It differs in three major ways:
it is intended to work on whole directories rather than individual files,
several people can work independently on the same file,
and
it is distributed; the main repository can live on a different machine.
.PP
The
.I repository
is a special directory, either on the local machine or a server somewhere.
It is the central place where all revisions of all files are
stored. Only CVS itself accesses it; you almost never need to touch
it directly.
In our case, the repository is the directory
.B /home/cvs ' '
on
.I islaya ,
the old computer I keep in 'kyffet'.
.PP
A
.I module
is just a directory full of files within the repository.
In our case,
.B obsbok/ ' '
is a module within the repository,
containing gavia books from earlier years as well as
the current year's 'obsbok'.
Modules are used to separate different projects sharing
a single repository;
in our case the source code to 'gavia' itself
is another module within the same repository.
.PP
The
.I
working directory
.R
is a normal directory that you own;
usually you place it somewhere in your home directory.
You get a working directory when you check out a module from the repository
and CVS copies the latest version from the repository.
.PP
You can have as many working directories as you want, spread over
several computers (you can have several on
.I one
computer, for that matter).
All of them will, over time, keep in sync with
what's in the module in the repository, and thus they will
more or less be in sync with each other.
.PP
The working directory is just a normal directory and the files
in it are just normal files, in the eyes of everyone except CVS.
.IP
.nf
.CW
% ls ~/view/obsbok/
1995.book    1997.book    1999.book    Jonas94.book
1995_2.book  1997_2.book  1999_2.book  krysslistor.book
1996.book    1998.book    2000.obsbok  obsbok
1996_2.book  1998_2.book  CVS/
.LP
CVS stores some extra information about the working directory
(in a subdirectory named
.B CVS/ '); '
in particular, the name of the repository it came from,
and the revision number each file had when it was checked out.
Using this information, CVS can correlate the working directory and
the information in the repository.
.
.
.
.NH
The cvs command
.LP
RCS consists of many commands;
.B ci ,
.B ci ,
.B rcsdiff ,
.B rlog
and so on.
CVS is one single command,
.B cvs ,
with approximately 25 sub-commands and many more options.
The most important ones are:
.IP
.nf
.CW
% cvs co
% cvs ci
% cvs update
% cvs diff
% cvs log
.LP
You can give one or more filenames as arguments, but usually
you give none and let CVS work on the whole current directory
(which means you have to stand in a working directory.)
.
.
.
.NH
Remote CVS over ssh
.LP
.I SSH
is a program for logging in on machines over a network, much like
.I telnet .
Unlike telnet, ssh encrypts the connection and compresses the data
sent over it.
Ssh also has several other nifty features.
One is its ability (using
.I ssh-add/ssh-agent )
to save you from typing your password every time you login;
another is that it allows other programs use ssh to talk to each other
over a ssh connection, and thus getting the login procedure,
the encryption and compression for free.
CVS is one of many programs which can use this feature of ssh.
.PP
There are several ways for CVS to access the repository,
but we choose to use CVS over ssh to access the repository on
the host
.B islaya
(which is really just an alias for
.B as3-1-3.ml.g.bonet.se ).
.PP
As mentioned above, cvs remembers where the repository was when you
checked out the working directory, so that isn't usually a problem.
If you do a new, initial checkout, you may point CVS to the right repository
by setting two environment variables:
.IP
.nf
.CW
$CVSROOT :ext:islaya:/home/cvs
$CVS_RSH ssh
.LP
CVS on your local machine (e.g.\&
.B pinicola )
will then use the ssh program
to communicate with CVS on islaya to do
the various operations; checkin, checkout et cetera.
.PP
You need to have a user account on islaya to do this, and
you need to authenticate to access islaya by ssh.
Ssh has several strategies for authentication, and CVS doesn't care which
one. We use 'RSAAuthentication'.
In practice, this means one of three things:
.IP \-
each time you run CVS, ssh will ask you for the passphrase for
your RSA key, or
.IP \-
you created your RSA key with an empty password
(this is mildly unsafe),
or
.IP \-
you unlock your RSA key by running
.B ssh-add ,
and CVS/ssh will not
prompt you for a passphrase (using the unlocked passphrase instead)
until you log off your local computer.
.
.
.
.NH
Multiple editors and conflict resolution
.LP
Right now, we constantly have maybe half a dozen working directories
for the 'obsbok' module:
.IP \-
we have one each on
.B frailea
(Peppared),
.B pinicola
(Falk\(:oping) and
.B regulus
(Malm\(:o).
.IP \-
I have one on
.BR islaya ,
which I use from work
.IP \-
I keep one on my USB memory,
which I edit in Lund and sync with the
repository whenever I get to a computer
which has both USB and an Internet connection.
.LP
Thus, there are always many working copies of the file 'obsbok'.
We can edit them as much as we want,
by running
.I gavia_stellata
(which in practice just adds text to the end of the file)
or simply editing it in emacs.
.PP
Some of them are used more than others. Some are almost always
out-of-date.
.PP
When you check in obsbok, CVS can't just add your version of
it as the latest revision. Imagine, for example, that you checked
out revision 1.11 of obsbok to your work directory on pinicola,
and modified it
(the star in the figure denotes a changed working copy of obsbok).
.IP
.nf
.CW
% cvs co

  --1.10--1.11
             |
             +--*
.LP
At the same time, someone checked out the same revision
(on frailea, for example),
modified it and later checked it again,
at which time it became revision 1.12:
.IP
.nf
.CW
  --1.10--1.11--1.12
             |
             +--*
.LP
Clearly, when you check in again, the new revision must now become 1.13.
But CVS can't just store your version, since that would mean
discarding the changes that made it into 1.12.
1.13 must be a combination of
.IP \-
revision 1.11
.IP \-
the changes you made between 1.11 and what's in your working directory
.IP \-
the changes someone else made between revisions 1.11 and 1.12
.LP
The solution is CVS' merge algorithm (the
.I update
command), which creates a local version of 'obsbok'
which contains both your changes since 1.11,
and the changes to 1.11 made from the other working directory, which
now are revision 1.12.
.IP
.nf
.CW
% cvs update

  --1.10--1.11--1.12
             |     |
             +-----+--*
.LP
When you try to check in a file and CVS notices that the repository has
changed since your last checkin (you checked out 1.11, and there is
now a version 1.12), it aborts and suggests you do a
 'cvs update' first.
.PP
In the simple case, the merge that happens when you do 'cvs update'
is automatic\(em\
if one of the contributors contains a change to line N
and the other doesn't, the change is included in the result.
.PP
In our case, there are almost always problems which have to be resolved
manually. We always add text to the end of
.B obsbok ', '
and when CVS notices that
both files contains changes at the end of the file, it cannot know if
one or both of them should be included in the new version
(and, if both, in which order).
CVS inserts both changes, puts markers around them
('<<<<', '====' and '>>>>') and warns you that there is a
.I
merge conflict
.R
and that you have to edit the file manually to resolve it.
.PP
When the file looks right and you have removed the conflict markers,
you can check in the changes, which will become revision 1.13:
.IP
.nf
.CW
% cvs ci

  --1.10--1.11--1.12--1.13
.LP
This is in practice what tends to happen when we check
in new excursions.
There is only one way to avoid it, and it is to always keep
your working directory as up-to-date as possible, i.e. to do a
.I
cvs update
.R
before you add new excursions.
.PP
It usually doesn't make sense to do it this way, since it means
you would be connecting to the Internet first, to update your working copy,
then add your new excursions, check in, and disconnect.
We tend to prefer resolving simple conflicts to
tying up the phone line and paying the fee for maybe half an hour or more.
Still, there is a general lesson here:
checking in often and updating often makes life easier.
.PP
On rare occasions, we have had more serious conflicts which were hard to
resolve manually.
This has happened, for example, when one completed a previously checked-in
excursion (e.g. added comments) and the other changed the order of excursions
that were thrown around by earlier update-merge stuff.
.IP
.nf
.CW
  --1.10--1.11--1.12
             |     |
             +-----+--* ugly mix
.LP
If we're not sure that what CVS suggests makes sense, we try to back out
from the change.
.I "cvs update"
always leaves the original working copy in a backup file
(in this case it would have been named
.I .#obsbok.1.11 ).
You can thus safely remove the broken, merged file,
and do a new update. That would place a clean copy of 1.12 in your
working directory.
Then you can compare the hidden backup copy with 1.11 to see what
.I your
changes really were,
and introduce them one by one, by hand, into your copy of 1.12,
and then check it in as 1.13.
.
.
.
.NH
References
.IP \-
.B ssh (1),
.B ssh-keygen (1)
and
.B ssh-add (1)
manpages
.IP \-
the
.B cvs (1)
manpage and the cvs info sheet
.B "info cvs" \& (
or, from within emacs,
.B "C-h i" ).
