/*----------------------------------------------------------------------------
 *
 * $Id: motorola.h,v 1.1 1999-10-24 08:10:52 grahn Exp $
 *
 * motorola.h
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

#ifdef __cplusplus
extern "C" {
#endif

int motorolareadword(FILE *, unsigned int *);
int motorolareadulong(FILE *, unsigned long *);

int motorolawriteword(unsigned int, FILE *);
int motorolawriteulong(unsigned long, FILE *);

#ifdef __cplusplus
}
#endif
