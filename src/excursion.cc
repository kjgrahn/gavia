/*----------------------------------------------------------------------------
 *
 * $Id: excursion.cc,v 1.9 2004-08-05 09:52:51 grahn Exp $
 *
 * excursion.cc
 *
 * Copyright (c) 1999 Jörgen Grahn <jgrahn@algonet.se>
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

static const char* rcsid() { rcsid(); return
"$Id: excursion.cc,v 1.9 2004-08-05 09:52:51 grahn Exp $";
}

#include <cassert>

#include "excursion.hh"

using std::string;
#ifndef USE_HASHMAP
using std::map;
#endif

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


void Excursion::setdate(long dat)
{
    /* Dates are normalized to yyyymmdd before they arrive here.
     * XXX Do a sanity check here!
     */
    date = dat;
}


/*----------------------------------------------------------------------------
 *
 * has()
 *
 *
 *----------------------------------------------------------------------------
 */
bool Excursion::has(const Species& species) const
{
    return sset.count(species)>0;
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
bool Excursion::species(const Species& species) const
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
int Excursion::speciescount(const Species& species) const
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
string Excursion::speciescomment(const Species& species) const
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
void Excursion::speciescomment(const Species& species, const string& comment)
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
const Excursion::SpeciesData& Excursion::speciesdata(const Species& species) const
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
void Excursion::insert(const Species& species, int count, const string& comment)
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
void Excursion::remove(const Species& species)
{
    sset.erase(species);
    smap.erase(species);
}
