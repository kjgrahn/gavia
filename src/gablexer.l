%{
/*----------------------------------------------------------------------------
 *
 * $Id: gablexer.l,v 1.2 1999-10-24 12:04:47 grahn Exp $
 *
 * gablexer.l
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
"$Id: gablexer.l,v 1.2 1999-10-24 12:04:47 grahn Exp $";

#include <ctype.h>
#include <string.h>

#include "excursion.hh"
#include "speciesredro.hh"

#define YY_DECL int yylex(Excursion * excursion, int * inc, SpeciesRedro * redro)

%}

BLANK [[:blank:]]
SPECIESFLD [[:blank:]]*[^:\n]+[[:blank:]]*
DATEFLD [[:blank:]]*[0-9]{6}[[:blank:]]*
LDATEFLD [[:blank:]]*[0-9]{8}[[:blank:]]*
NUMFLD [[:blank:]]*[0-9]+[[:blank:]]*
FREEFLD [[:blank:]]*[^ \t\n].*
BLANKFLD [[:blank:]]*
CHECKFLD [[:blank:]]*[^ \t\n:]+[[:blank:]]*

%x HEAD
%x BODY

%%

<*>^{BLANK}*\#.*$ {
    /* comment lines (#) are ignored */

    ;
}

<INITIAL>^{BLANK}*\{{BLANK}*$ {
    /* { (excursion intro) */
    /* fprintf(stderr, "%s\n", "intro"); */

    BEGIN(HEAD);
}

<HEAD>^{BLANK}*place{BLANK}*\:{FREEFLD}$ {
    /* place: <name> */
    /* fprintf(stderr, "%s\n", "place"); */

    char * s = yytext;

    while(isspace(*s)) s++;
    s += strlen("place");
    while(isspace(*s)) s++;
    s += strlen(":");
    while(isspace(*s)) s++;

    excursion->setplace(string(s));
}

<HEAD>^{BLANK}*date{BLANK}*\:{LDATEFLD}$ {
    /* date: <yyyymmdd> */
    /* fprintf(stderr, "%s\n", "date"); */

    char * s = yytext;

    while(isspace(*s)) s++;
    s += strlen("date");
    while(isspace(*s)) s++;
    s += strlen(":");
    while(isspace(*s)) s++;

    excursion->setdate(atol(s));
}

<HEAD>^{BLANK}*date{BLANK}*\:{DATEFLD}$ {
    /* date: <yymmdd> */
    /* fprintf(stderr, "%s\n", "date"); */

    char * s = yytext;

    while(isspace(*s)) s++;
    s += strlen("date");
    while(isspace(*s)) s++;
    s += strlen(":");
    while(isspace(*s)) s++;

    long n = atol(s);

    if(n<780101)
    {
	/* y2k */
        n+=1000000;
    }
    n += 19000000;

    excursion->setdate(n);
}

<HEAD>^{BLANK}*date{BLANK}*\:{BLANKFLD}$ {
    /* date: */
    /* fprintf(stderr, "%s\n", "date, empty"); */

    fprintf(stderr, "***Defaulted dates not yet implemented ###\n");
    return -1;
}

<HEAD>^{BLANK}*time{BLANK}*\:({FREEFLD}|{BLANKFLD})$ {
    /* time: <time> */
    /* fprintf(stderr, "%s\n", "time"); */

    char * s = yytext;

    while(isspace(*s)) s++;
    s += strlen("time");
    while(isspace(*s)) s++;
    s += strlen(":");
    while(isspace(*s)) s++;

    excursion->settime(string(s));
}

<HEAD>^{BLANK}*observers{BLANK}*\:({FREEFLD}|{BLANKFLD})$ {
    /* observers: <observers> */
    /* fprintf(stderr, "%s\n", "observers"); */

    char * s = yytext;

    while(isspace(*s)) s++;
    s += strlen("observers");
    while(isspace(*s)) s++;
    s += strlen(":");
    while(isspace(*s)) s++;

    excursion->setobservers(string(s));
}

<HEAD>^{BLANK}*weather{BLANK}*\:({FREEFLD}|{BLANKFLD})$ {
    /* weather: <weather> */
    /* fprintf(stderr, "%s\n", "weather"); */

    char * s = yytext;

    while(isspace(*s)) s++;
    s += strlen("weather");
    while(isspace(*s)) s++;
    s += strlen(":");
    while(isspace(*s)) s++;

    excursion->setweather(string(s));
}

<HEAD>^{BLANK}*comments{BLANK}*\:({FREEFLD}|{BLANKFLD})$ {
    /* comments: <comments> */
    /* fprintf(stderr, "%s\n", "comments"); */

    char * s = yytext;

    while(isspace(*s)) s++;
    s += strlen("comments");
    while(isspace(*s)) s++;
    s += strlen(":");
    while(isspace(*s)) s++;

    excursion->setcomments(string(s));
}

<HEAD>^{BLANK}*\}{BLANK}*\{{BLANK}*$ {
    /* }{ (excursion data/species data border) */
    /* fprintf(stderr, "%s\n", "border"); */

    BEGIN(BODY);
}

<BODY>^{SPECIESFLD}\:{BLANKFLD}\:{BLANKFLD}\:{BLANKFLD}$ {
    /* <species>: : : (left out) */
    /* fprintf(stderr, "%s\n", "dead"); */
}

<BODY>^{SPECIESFLD}\:{CHECKFLD}\:{BLANKFLD}\:{BLANKFLD}$ {
    /* <species>:x: : (just checked) */
    /* fprintf(stderr, "%s\n", "checked"); */

    char * s = yytext;

    while(isspace(*s)) s++;
    char * t = s;
    while(*t!=':') t++;
    *t = 0;
    t--;
    while(isspace(*t))
    {
	*t = 0;
	t--;
    }

    const Species species(s);

    if(!redro->ismember(species))
    {
	fprintf(stderr, "Invalid species '%.30s'\n", s);
	return -1;
    }

    excursion->insert(species);
}

<BODY>^{SPECIESFLD}\:[^:\n]*\:{NUMFLD}\:{BLANKFLD}$  |
<BODY>^{SPECIESFLD}\:[^:\n]*\:{NUMFLD}\:{FREEFLD}$ {
    /* <species>: : <no>: (numbers but no comment) */
    /* <species>: :<no>:<comment> */
    /* fprintf(stderr, "%s\n", "at least number"); */

    char * s = yytext;

    while(isspace(*s)) s++;
    char * t = s;
    while(*t!=':') t++;
    char * u = t+1;
    *t = 0;
    t--;
    while(isspace(*t))
    {
	*t = 0;
	t--;
    }

    while(*u!=':') u++;
    while(!isdigit(*u)) u++;

    int num = atoi(u);

    while(*u!=':') u++;
    u++;
    while(isspace(*u)) u++;

    const Species species(s);

    if(!redro->ismember(species))
    {
	fprintf(stderr, "Invalid species '%.30s'\n", s);
	return -1;
    }

    excursion->insert(species, num, u);
}

<BODY>{SPECIESFLD}\:[^:\n]*\:{BLANK}*\:{FREEFLD}$ {
    /* <species>: : : <comment> (comment but no numbers) */
    /* fprintf(stderr, "%s\n", "just comment"); */

    char * s = yytext;

    while(isspace(*s)) s++;
    char * t = s;
    while(*t!=':') t++;
    char * u = t+1;
    *t = 0;
    t--;
    while(isspace(*t))
    {
	*t = 0;
	t--;
    }

    while(*u!=':') u++;
    u++;
    while(*u!=':') u++;
    u++;
    while(isspace(*u)) u++;

    const Species species(s);

    if(!redro->ismember(species))
    {
	fprintf(stderr, "Invalid species '%.30s'\n", s);
	return -1;
    }

    excursion->insert(species, 0, u);
}

<BODY>^{BLANK}*\}{BLANK}* {
    /* } excursion end */
    /* fprintf(stderr, "%s\n", "end"); */

    BEGIN(INITIAL);

    return 1;

}

<*>[ \t] ;

<*>\n {
    /* count lines */
    (*inc)++;
}

<*>. {
    /* something wrong */

    fprintf(stderr, "***Parse error near line %d\n", *inc);
    return -1;
}

%%
