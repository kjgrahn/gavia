/*----------------------------------------------------------------------------
 *
 * $Id: version.hh,v 1.1 1999-10-24 09:00:45 grahn Exp $
 *
 * version.hh
 *
 * Copyright (C) 1999 Jörgen Grahn <jorgen.grahn@opensoftware.se>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *----------------------------------------------------------------------------
 *
 * A class that stores the version (revision) of the project it
 * is contained in. This might or might not be the revision of a
 * certain executable; if one project is under CVS (or possibly RCS)
 * control, all executables should share one release tag.
 * Dollar-Id tags should be used to identify the individual files that
 * contributed to a build.
 *----------------------------------------------------------------------------
 */

#ifndef VERSION_HH
#define VERSION_HH


class Version
{
public:
    const char * name() const {return tagname;}
protected:
private:
    static const char tagname[] = "$Name:  $";
};

#endif
