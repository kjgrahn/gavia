# $Id: gavia_cvs.mm,v 1.1 2001-05-13 20:30:41 grahn Exp $



.H 1 "CVS basics"

CVS is - for our purposes - much like RCS. CVS differs in three major ways:
it is intended to work on whole directories rather than individual files,
several people can modify a single file at the same time,
and
it is distributed; the main repository can live on a different machine.

The repository is the central place where all revisions of all files are
stored. Only CVS itself accesses it; you almost never need to touch
it directly.

A module is just a directory within the repository.
In our case, 'obsbok/' is a module within the repository,
containing gavia books from earlier years as well as
the current year's 'obsbok'.
Modules are used to separate different projects sharing
a single repository;
in our case the source code to 'gavia'
is another module within the same repository.

The working directory is a normal directory that you own;
usually you place it somewhere in your home directory.
You get a working directory when you check out a module from the repository
and CVS copies the latest version from the repository.

The working directory is just a normal directory and the files
in it are just normal files, until you use CVS on it.
CVS stores some extra information about it (in a subdirectory named 'CVS/');
in particular, the name of the repository it came from,
and the revision number each file had when it was checked out.



.H 1 "Remote CVS over ssh"

There are several ways for CVS to access the repository.

We use one of them - CVS over ssh - to access the repository on
the host islaya (also known as as3-1-3.ml.g.bonet.se).

As mentioned above, cvs remembers where the repository was when you
checked out the working directory, so that isn't usually a problem.
If you do a new, initial checkout, you point CVS to the right repository
by setting two environment variables:
$CVSROOT :ext:islaya:/home/cvs
$CVS_RSH ssh

CVS on your local machine (e.g. pinicola) will then use the ssh program
to communicate with CVS on islaya to do
the various operations; checkin, checkout et cetera.

You need to have a user account on islaya to do this, and
you need to authenticate to access islaya by ssh.
Ssh has several strategies for authentication, and CVS doesn't care which
one. We use 'RSAAuthentication'.
In practice, this means one of two things:

- each time you run CVS, ssh will ask you for the passphrase for
  your RSA key, or

- you unlock your RSA key by running ssh-add, and CVS/ssh will not
  prompt you for a passphrase, using the unlocked passphrase instead



.H 1 "Multiple editors and conflict resolution"

Right now, we have at least four working directories
for the 'obsbok' module:

- we have one each on frailea (Peppared)
- we have one each on pinicola (Falköping)

Thus, there are four working copies of the file 'obsbok'.
We can edit them as much as we want,
by running gavia_stellata (adding text to the end of the file)
or simply editing it in emacs.

When you check in obsbok, CVS can't just add your version of
it as the latest revision. Imagine, for example, that you checked
out revision 1.11 of obsbok to your work directory on pinicola,
and modified it.

% cvs co

  --1.10--1.11
             |
             +--*

At the same time, someone checked out the same revision on pinicola,
modified it and later checked it again,
at which time it became revision 1.12:

  --1.10--1.11--1.12
             |
             +--*

Clearly, when you check in again, the new revision must now become 1.13.
But CVS can't just store your version, since that would mean
discarding the changes that made it into 1.12.
1.13 must be a combination of

- revision 1.11
- the changes you made between 1.11 and what's in your working directory
- the changes someone else made between revisions 1.11 and 1.12

The solution is CVS' merge algorithm, which creates a version of 'obsbok'
which contains both your changes since 1.11,
and the changes to 1.11 made from the other working directory, which
now are revision 1.12.

% cvs update

  --1.10--1.11--1.12
             |     |
             +-----+--*

When you try to check in a file and CVS notices that the repository has
changed since your last checkin (you checked out 1.11, and there is
now a version 1.12), it aborts and suggests you do a
 'cvs update' first.

In the simple case, the merge that happens when you do 'cvs update'
is automatic - if one of the contributors contains a change to line N
and the other doesn't, the change is included in the result.

In our case, there are almost always problems which have to be resolved
manually. We always add text to the end of 'obsbok', and when CVS notices that
both files contains changes at the end of the file, it cannot know if
one or both of them should be included in the new version.
CVS inserts both changes, puts markers around them
('<<<<', '====' and '>>>>') and warns you that there is a merge
conflict and that you have to edit the file manually to resolve it.

When the file looks right and you have removed the conflict markers,
you can check in the changes, which will become revision 2.36:

cvs ci

  --1.10--1.11--1.12--1.13



.H 1 "References"

- the ssh(1) and ssh-add(1) manpages
- the cvs(1) manpage and the cvs info sheet
