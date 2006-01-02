/* $Id: exception.cc,v 1.2 2006-01-02 22:15:25 grahn Exp $
 *
 * exception.cc
 *
 * Copyright (c) 2004 Jörgen Grahn
 * All rights reserved.
 *
 */

static const char* rcsid() { rcsid(); return
"$Id: exception.cc,v 1.2 2006-01-02 22:15:25 grahn Exp $";
}

#include <cstdio>
#include <string.h>
#include "exception.hh"


GaviaException::GaviaException(int err) : msg(strerror(err)) {}

GaviaException::GaviaException(const std::string& err, int line)
{
    char buf[10];
    std::sprintf(buf, "%d", line);

    msg = err + " (line " + buf + ")";
}
