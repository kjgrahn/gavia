/*----------------------------------------------------------------------------
 *
 * $Id: exception.hh,v 1.2 2004-01-04 14:10:41 grahn Exp $
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


struct GaviaException
{
    GaviaException(int err);
    GaviaException(const std::string& err) : msg(err) {}
    GaviaException(const std::string& err, int line);
    virtual ~GaviaException() {}

    std::string msg;
};

#endif
