/*----------------------------------------------------------------------------
 *
 * $Id: exception.hh,v 1.1 2001-12-29 19:14:09 grahn Exp $
 *
 * exception.hh
 *
 * Copyright (c) 2001 Jörgen Grahn <jgrahn@algonet.se>
 * All rights reserved.
 * 
 *----------------------------------------------------------------------------
 *
 *----------------------------------------------------------------------------
 */
#ifndef EXCEPTION_HH
#define EXCEPTION_HH

#include <string>
#include <string.h>


struct GaviaException
{
    GaviaException(int err) {msg = std::string(strerror(err));}
    GaviaException(const std::string& err) : msg(err) {}
    virtual ~GaviaException() {}

    std::string msg;
};

#endif
