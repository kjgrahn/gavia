/*----------------------------------------------------------------------------
 *
 * $Id: excursion.hh,v 1.6 2001-01-18 23:25:20 grahn Exp $
 *
 * excursion.hh
 *
 * Copyright (c) 1999, 2000 Jörgen Grahn <jgrahn@algonet.se>
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
 * A couple of general comment fields
 * (place, date, time, weather, observers, comments)
 * and a set of Species, each with a number/count and a comment.
 *----------------------------------------------------------------------------
 */

#ifndef EXCURSION_HH
#define EXCURSION_HH

#include "species.hh"
#include "speciesset.hh"

#include <string>

#ifdef USE_HASHMAP
#include <hash_map>

class SpeciesHash
{
    hash<const char *> cstrh;
public:
    size_t operator() (const Species & s) const {return cstrh(s.c_str());}
};

#else
#include <map>
#endif



class Excursion
{
public:
    Excursion();			// constructor
    Excursion(const Excursion&);		// copy constructor

    virtual ~Excursion();		// destructor

    const Excursion& operator=(const Excursion&);

    // 'set' methods
    void setdate(long);
    void setplace(const std::string&);
    void settime(const std::string&);
    void setobservers(const std::string&);
    void setweather(const std::string&);
    void setcomments(const std::string&);

    // 'get' methods
    long getdate() const;
    const std::string& getplace() const;
    const std::string& gettime() const;
    const std::string& getobservers() const;
    const std::string& getweather() const;
    const std::string& getcomments() const;

    const SpeciesSet& speciesset() const;

    typedef struct
    {
	int count;
	std::string comment;
    } SpeciesData;

    int nofspecies() const;
    bool species(Species) const;
    int speciescount(Species) const;
    std::string speciescomment(Species) const;

    void speciescomment(Species, std::string);

    const SpeciesData& speciesdata(Species) const;

    void insert(Species, int=0, std::string="");
    void remove(Species);

protected:
private:
    long date;
    std::string place;
    std::string time;
    std::string observers;
    std::string weather;
    std::string comments;

    SpeciesSet sset;
#ifdef USE_HASHMAP
    hash_map<Species, SpeciesData, SpeciesHash> smap;
#else
    std::map<Species, SpeciesData> smap;
#endif
};


inline
void Excursion::setdate(long dat) { date = dat;}
inline
void Excursion::setplace(const std::string& plac) { place = plac;}
inline
void Excursion::settime(const std::string& tim) { time = tim;}
inline
void Excursion::setobservers(const std::string& observer) { observers = observer;}
inline
void Excursion::setweather(const std::string& weathe) { weather = weathe;}
inline
void Excursion::setcomments(const std::string& comment) { comments = comment;}

inline
long Excursion::getdate() const { return date;}
inline
const std::string& Excursion::getplace() const { return place;}
inline
const std::string& Excursion::gettime() const { return time;}
inline
const std::string& Excursion::getobservers() const { return observers;}
inline
const std::string& Excursion::getweather() const { return weather;}
inline
const std::string& Excursion::getcomments() const { return comments;}

#endif
