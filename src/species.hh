/*----------------------------------------------------------------------------
 *
 * $Id: species.hh,v 1.7 2006-05-02 21:53:58 grahn Exp $
 *
 * Species.hh
 *
 * Copyright (c) 1999 Jörgen Grahn
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *----------------------------------------------------------------------------
 *
 *----------------------------------------------------------------------------
 */

#ifndef SPECIES_HH
#define SPECIES_HH

#include <string>
#include <iosfwd>

/**
 * A species, which really just is a species name, as a string ...
 */
class Species {
public:
    Species(const std::string& name) : s(name) {}
    Species(const char * name) : s(name) {}
    Species(const char * a, const char * b) : s(a,b) {}

    int operator< (const Species& other) const { return s < other.s; }
    const char * c_str() const { return s.c_str(); }
    size_t size() const { return s.size(); }
private:
    Species();
    std::string s;
};

inline std::ostream& operator<< (std::ostream& os, const Species& s)
{
    return os << s.c_str();
}

#endif
