%{
/*----------------------------------------------------------------------------
 *
 * $Id: gablexer.l,v 1.8 2001-12-29 19:14:09 grahn Exp $
 *
 * gablexer.l
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
"$Id: gablexer.l,v 1.8 2001-12-29 19:14:09 grahn Exp $";
}

#include <cctype>
#include <cstring>
#include <string>

#include "excursion.hh"
#include "exception.hh"
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

    excursion->setplace(std::string(s));
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

    throw GaviaException("defaulted dates not implemented");
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

    excursion->settime(std::string(s));
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

    excursion->setobservers(std::string(s));
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

    excursion->setweather(std::string(s));
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

    excursion->setcomments(std::string(s));
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
	throw GaviaException(std::string("invalid species '") + s + "'");
    }

    excursion->insert(species);
}

<BODY>^{SPECIESFLD}\:[^:\n]*\:{NUMFLD}\:.*$ {
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
	throw GaviaException(std::string("invalid species '") + s + "'");
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
	throw GaviaException(std::string("invalid species '") + s + "'");
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

    char buf[10];
    std::sprintf(buf, "%d", *inc);

    throw GaviaException(std::string("parse error near line ") + buf);
}

%%
