/*----------------------------------------------------------------------------
 *
 * $Id: exeditor.hh,v 1.1 1999-10-24 08:10:52 grahn Exp $
 *
 * exeditor.hh
 *
 * Copyright (C) 1999 Jörgen Grahn <jorgen.grahn@opensoftware.se>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *----------------------------------------------------------------------------
 *
 * Lets the user edit the given Excursion, using the SpeciesOrder
 * also given.
 * Takes control of stdin/out for rendering a curses UI.
 *----------------------------------------------------------------------------
 */

#ifndef EXEDITOR_HH
#define EXEDITOR_HH


class Excursion;
class SpeciesOrder;


class ExEditor
{
public:
    ExEditor(Excursion *, SpeciesOrder *); // constructor
    virtual ~ExEditor();		    // destructor
    virtual int edit();

protected:
private:
    Excursion * mexcursion;
    SpeciesOrder * morder;

    ExEditor::ExEditor(const ExEditor&);
    ExEditor& ExEditor::operator=(const ExEditor&);


};

#endif
