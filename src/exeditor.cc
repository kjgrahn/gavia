/*----------------------------------------------------------------------------
 *
 * $Id: exeditor.cc,v 1.1 1999-10-24 08:10:52 grahn Exp $
 *
 * exeditor.cc
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
"$Id: exeditor.cc,v 1.1 1999-10-24 08:10:52 grahn Exp $";


#include <assert.h>


#include "exeditor.hh"


/*----------------------------------------------------------------------------
 *
 * constructor
 *
 *
 *----------------------------------------------------------------------------
 */
ExEditor::ExEditor(Excursion * ex, SpeciesOrder * order)
{
    assert(ex);
    assert(order);

    mexcursion = ex;
    morder = order;
}


/*----------------------------------------------------------------------------
 *
 * destructor
 *
 *
 *----------------------------------------------------------------------------
 */
ExEditor::~ExEditor()
{
}



/*----------------------------------------------------------------------------
 *
 * edit()
 *
 *
 *----------------------------------------------------------------------------
 */
int ExEditor::edit()
{
    return 0;
}
