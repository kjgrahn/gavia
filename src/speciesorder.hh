/*----------------------------------------------------------------------------
 *
 * $Id: speciesorder.hh,v 1.1 1999-10-24 08:10:52 grahn Exp $
 *
 * speciesorder.hh
 *
 * Copyright (C) 1999 Jörgen Grahn <jorgen.grahn@opensoftware.se>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *----------------------------------------------------------------------------
 *
 * Abstract ordering of a subset of all Species,
 * by mapping [0..end()[ onto them.
 *----------------------------------------------------------------------------
 */

#ifndef SPECIESORDER_HH
#define SPECIESORDER_HH

#include "species.hh"


class SpeciesOrder
{
public:
    virtual Species species(int) const = 0;
    virtual int end() const = 0;

    virtual ~SpeciesOrder() {}

protected:
private:

};

#endif
