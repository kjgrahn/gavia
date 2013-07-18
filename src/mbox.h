/* -*- c++ -*-
 *
 * Copyright (C) 2013 Jörgen Grahn
 * All rights reserved.
 */
#ifndef GAVIA_MBOX_H
#define GAVIA_MBOX_H

#include <iostream>

class Excursion;


/**
 * Just a way of formatting parts of an Excursion as
 * an mbox header (that is, a "From_" line and some
 * Internet mail headers).
 *
 * See RFC 4145 (mbox) and RFC 2822 (mail headers).
 */
class MboxHeader {
public:
    explicit MboxHeader(const Excursion& ex) : ex(ex) {}
    std::ostream& put(std::ostream& os) const;

private:
    const Excursion& ex;
};


inline std::ostream& operator<< (std::ostream& os, const MboxHeader& val)
{
    return val.put(os);
}

#endif
