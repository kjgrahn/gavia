/*----------------------------------------------------------------------------
 *
 * $Id: excursion.hh,v 1.5 2000-08-10 19:47:21 grahn Exp $
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

#include <string>
#include <hash_map>
#include "species.hh"
#include "speciesset.hh"

class SpeciesHash
{
    hash<const char *> cstrh;

public:
    size_t operator() (const Species & s) const
    {
	return cstrh(s.c_str());
    }
};


class Excursion
{
public:
    Excursion();			// constructor
    Excursion(const Excursion&);		// copy constructor

    virtual ~Excursion();		// destructor

    const Excursion& operator=(const Excursion&);

    // 'set' methods
    void setdate(long);
    void setplace(const string&);
    void settime(const string&);
    void setobservers(const string&);
    void setweather(const string&);
    void setcomments(const string&);

    // 'get' methods
    long getdate() const;
    const string& getplace() const;
    const string& gettime() const;
    const string& getobservers() const;
    const string& getweather() const;
    const string& getcomments() const;

    const SpeciesSet& speciesset() const;

    typedef struct
    {
	int count;
	string comment;
    } SpeciesData;

    int nofspecies() const;
    bool species(Species) const;
    int speciescount(Species) const;
    string speciescomment(Species) const;

    void speciescomment(Species, string);

    const SpeciesData& speciesdata(Species) const;

    void insert(Species, int=0, string="");
    void remove(Species);

protected:
private:
    long date;
    string place;
    string time;
    string observers;
    string weather;
    string comments;

    SpeciesSet sset;
    hash_map<Species, SpeciesData, SpeciesHash> smap;

};


inline
void Excursion::setdate(long dat) { date = dat;}
inline
void Excursion::setplace(const string& plac) { place = plac;}
inline
void Excursion::settime(const string& tim) { time = tim;}
inline
void Excursion::setobservers(const string& observer) { observers = observer;}
inline
void Excursion::setweather(const string& weathe) { weather = weathe;}
inline
void Excursion::setcomments(const string& comment) { comments = comment;}

inline
long Excursion::getdate() const { return date;}
inline
const string& Excursion::getplace() const { return place;}
inline
const string& Excursion::gettime() const { return time;}
inline
const string& Excursion::getobservers() const { return observers;}
inline
const string& Excursion::getweather() const { return weather;}
inline
const string& Excursion::getcomments() const { return comments;}

#endif
