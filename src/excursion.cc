/*----------------------------------------------------------------------------
 *
 * $Id: excursion.cc,v 1.1 1999-10-24 08:10:52 grahn Exp $
 *
 * excursion.cc
 *
 * Copyright (C) 1999 Jörgen Grahn <jorgen.grahn@opensoftware.se>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *----------------------------------------------------------------------------
 *
 *----------------------------------------------------------------------------
 */

static const char rcsid[] =
"$Id: excursion.cc,v 1.1 1999-10-24 08:10:52 grahn Exp $";

#include <assert.h>

#include "excursion.hh"


/*----------------------------------------------------------------------------
 *
 * constructor
 *
 *
 *----------------------------------------------------------------------------
 */
Excursion::Excursion()
{
    ;
}


/*----------------------------------------------------------------------------
 *
 * copy constructor
 *
 *
 *----------------------------------------------------------------------------
 */
Excursion::Excursion(const Excursion& obj)
{
    date = obj.date;
    place = obj.place;
    time = obj.time;
    observers = obj.observers;
    weather = obj.weather;
    comments = obj.comments;
    sset = obj.sset;
    smap = obj.smap;

}


/*----------------------------------------------------------------------------
 *
 * destructor
 *
 *
 *----------------------------------------------------------------------------
 */
Excursion::~Excursion()
{
    ;
}


/*----------------------------------------------------------------------------
 *
 * operator=()
 *
 *
 *----------------------------------------------------------------------------
 */
const Excursion& Excursion::operator=(const Excursion& obj)
{
    date = obj.date;
    place = obj.place;
    time = obj.time;
    observers = obj.observers;
    weather = obj.weather;
    comments = obj.comments;
    sset = obj.sset;
    smap = obj.smap;

    return *this;
}


/*----------------------------------------------------------------------------
 *
 * speciesset()
 *
 *
 *----------------------------------------------------------------------------
 */
const SpeciesSet& Excursion::speciesset() const
{
    return sset;
}


/*----------------------------------------------------------------------------
 *
 * nofspecies()
 *
 *
 *----------------------------------------------------------------------------
 */
int Excursion::nofspecies() const
{
    return sset.size();
}


/*----------------------------------------------------------------------------
 *
 * species()
 *
 *
 *----------------------------------------------------------------------------
 */
bool Excursion::species(Species species) const
{
    return sset.count(species)>0;
}


/*----------------------------------------------------------------------------
 *
 * speciesnumber()
 *
 *
 *----------------------------------------------------------------------------
 */
int Excursion::speciescount(Species species) const
{
    assert(smap.count(species)>0);

    return smap.find(species)->second.count;
}


/*----------------------------------------------------------------------------
 *
 * speciescomment()
 *
 *
 *----------------------------------------------------------------------------
 */
string Excursion::speciescomment(Species species) const
{
    assert(smap.count(species)>0);

    return smap.find(species)->second.comment;
}


/*----------------------------------------------------------------------------
 *
 * speciescomment()
 *
 *
 *----------------------------------------------------------------------------
 */
void Excursion::speciescomment(Species species, string comment)
{
    assert(smap.count(species)>0);

    smap[species].comment = comment;
}


/*----------------------------------------------------------------------------
 *
 * speciesdata()
 *
 *
 *----------------------------------------------------------------------------
 */
const Excursion::SpeciesData& Excursion::speciesdata(Species species) const
{
    assert(smap.count(species)>0);

    return smap.find(species)->second;
}


/*----------------------------------------------------------------------------
 *
 * insert()
 *
 *
 *----------------------------------------------------------------------------
 */
void Excursion::insert(Species species, int count, string comment)
{
    SpeciesData sd;

    sd.count = count;
    sd.comment = comment;
    smap[species] = sd;

    sset.insert(species);
}


/*----------------------------------------------------------------------------
 *
 * delete()
 *
 *
 *----------------------------------------------------------------------------
 */
void Excursion::remove(Species species)
{
    sset.erase(species);
    smap.erase(species);
}
