/*----------------------------------------------------------------------------
 *
 * $Id: excursion.hh,v 1.1 1999-10-24 08:10:52 grahn Exp $
 *
 * excursion.hh
 *
 * Copyright (C) 1999 Jörgen Grahn <jorgen.grahn@opensoftware.se>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
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
#include <map>
#include "species.hh"
#include "speciesset.hh"


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
    map<Species, SpeciesData> smap;

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
