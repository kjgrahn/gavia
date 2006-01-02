/*----------------------------------------------------------------------------
 *
 * $Id: exception.hh,v 1.3 2006-01-02 22:15:25 grahn Exp $
 *
 * exception.hh
 *
 * Copyright (c) 2001 Jörgen Grahn
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
