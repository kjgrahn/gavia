/*----------------------------------------------------------------------------
 *
 * $Id: taxonomicorder.cc,v 1.8 2001-07-22 21:03:32 grahn Exp $
 *
 * taxonomicorder.cc
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
"$Id: taxonomicorder.cc,v 1.8 2001-07-22 21:03:32 grahn Exp $";
}

#include <cassert>

#include "taxonomicorder.hh"


#define INTERNALORDERLEN (485)
 
static char * internalorder[INTERNALORDERLEN] =
{
    "smålom",  	       	       /* 000 */
    "storlom",		       /* 001 */
    "vitnäbbad islom",	       /* 002 */
    "svartnäbbad islom",       /* 300 */

    "smådopping",	       /* 003 */
    "skäggdopping",	       /* 004 */
    "gråhakedopping",	       /* 005 */
    "svarthakedopping",	       /* 006 */
    "svarthalsad dopping",     /* 007 */

    "stormfågel",	       /* 008 */
    "grålira",		       /* 009 */
    "mindre lira",	       /* 010 */
    "gulnäbbad lira",	       /* 301 */
    "större lira",	       /* 302 */
    "medelhavslira",	       /* 303 */
    "klykstjärtad stormsvala", /* 011 */
    "stormsvala",	       /* 304 */

    "havssula",		       /* 012 */
    "storskarv",	       /* 013 */
    "toppskarv",	       /* 305 */
    "dvärgskarv",	       /* 306 */

    "rördrom",		       /* 014 */
    "dvärgrördrom",	       /* 307 */
    "natthäger",	       /* 308 */
    "rallhäger",	       /* 309 */
    "kohäger",		       /* 310 */
    "silkeshäger",	       /* 311 */
    "ägretthäger",	       /* 312 */
    "häger",		       /* 015 */
    "purpurhäger",	       /* 313 */

    "svart stork",	       /* 016 */
    "vit stork",	       /* 017 */

    "bronsibis",	       /* 314 */
    "skedstork",	       /* 315 */

    "flamingo",		       /* 018 */

    "knölsvan",		       /* 019 */
    "mindre sångsvan",	       /* 020 */
    "sångsvan",		       /* 021 */
    "svart svan",	       /* 457 */

    "sädgås",		       /* 022 */
    "spetsbergsgås",	       /* 023 */
    "bläsgås",		       /* 024 */
    "fjällgås",		       /* 025 */
    "grågås",		       /* 026 */
    "stripgås",		       /* 027 */
    "snögås",		       /* 028 */
    "kanadagås",	       /* 029 */
    "vitkindad gås",	       /* 030 */
    "prutgås",		       /* 031 */
    "rödhalsad gås",	       /* 316 */
    "tundrasädgås",	       /* 471 */
    "grönländsk bläsgås",      /* 472 */
    "dvärgkanadagås",	       /* 473 */
    "svartbukig prutgås",      /* 474 */
    "ljusbukig prutgås",       /* 475 */

    "rostand",		       /* 032 */
    "gravand",		       /* 033 */
    "bläsand",		       /* 034 */
    "snatterand",	       /* 035 */
    "kricka",		       /* 036 */
    "gräsand",		       /* 037 */
    "stjärtand",	       /* 038 */
    "årta",		       /* 039 */
    "skedand",		       /* 040 */
    "mandarinand",	       /* 041 */
    "brudand",		       /* 042 */
    "amerikansk bläsand",      /* 317 */
    "svartand",		       /* 318 */
    "blåvingad årta",	       /* 319 */
    "amerikansk kricka",       /* 476 */

    "brunand",		       /* 043 */
    "vigg",		       /* 044 */
    "bergand",		       /* 045 */
    "mindre bergand",	       /* 466 */
    "ejder",		       /* 046 */
    "praktejder",	       /* 047 */
    "alförrädare",	       /* 048 */
    "alfågel",		       /* 049 */
    "sjöorre",		       /* 050 */
    "amerikansk sjöorre",      /* 477 */
    "svärta",		       /* 051 */
    "knipa",		       /* 052 */
    "rödhuvad dykand",	       /* 320 */
    "ringand",		       /* 321 */
    "vitögd dykand",	       /* 322 */
    "strömand",		       /* 323 */
    "vitnackad svärta",	       /* 324 */
    "amerikansk kopparand",    /* 456 */

    "salskrake",	       /* 053 */
    "småskrake",	       /* 054 */
    "storskrake",	       /* 055 */
    "kamskrake",	       /* 325 */

    "bivråk",		       /* 056 */
    "brunglada",	       /* 057 */
    "glada",		       /* 058 */
    "havsörn",		       /* 059 */
    "brun kärrhök",	       /* 060 */
    "blå kärrhök",	       /* 061 */
    "stäpphök",		       /* 062 */
    "ängshök",		       /* 063 */
    "duvhök",		       /* 064 */
    "sparvhök",		       /* 065 */
    "ormvråk",		       /* 066 */
    "fjällvråk",	       /* 067 */
    "mindre skrikörn",	       /* 068 */
    "kungsörn",		       /* 069 */
    "smutsgam",		       /* 326 */
    "gåsgam",		       /* 327 */
    "ormörn",		       /* 328 */
    "örnvråk",		       /* 329 */
    "större skrikörn",	       /* 330 */
    "stäppörn",		       /* 331 */
    "kejsarörn",	       /* 332 */
    "dvärgörn",		       /* 333 */

    "fiskgjuse",	       /* 070 */

    "tornfalk",		       /* 071 */
    "aftonfalk",	       /* 072 */
    "stenfalk",		       /* 073 */
    "lärkfalk",		       /* 074 */
    "jaktfalk",		       /* 075 */
    "pilgrimsfalk",	       /* 076 */
    "rödfalk",		       /* 334 */
    "eleonorafalk",	       /* 335 */
    "tatarfalk",	       /* 336 */

    "järpe",		       /* 077 */
    "dalripa",		       /* 078 */
    "fjällripa",	       /* 079 */
    "orre",		       /* 080 */
    "tjäder",		       /* 081 */
    "rapphöna",		       /* 082 */
    "vaktel",		       /* 083 */
    "fasan",		       /* 084 */
    "berghöna",		       /* 337 */

    "trana",		       /* 091 */
    "jungfrutrana",	       /* 340 */

    "småtrapp",		       /* 341 */
    "kragtrapp",	       /* 342 */
    "stortrapp",	       /* 343 */

    "vattenrall",	       /* 085 */
    "småfläckig sumphöna",     /* 086 */
    "mindre sumphöna",	       /* 087 */
    "karolinasumphöna",	       /* 338 */
    "dvärgsumphöna",	       /* 339 */
    "kornknarr",	       /* 088 */
    "rörhöna",		       /* 089 */
    "sothöna",		       /* 090 */

    "strandskata",	       /* 092 */
    "skärfläcka",	       /* 093 */
    "styltlöpare",	       /* 344 */
    "tjockfot",		       /* 345 */
    "ökenlöpare",	       /* 346 */
    "vadarsvala",	       /* 347 */
    "svartvingad vadarsvala",  /* 348 */
    "orientvadarsvala",	       /* 484 */
    "mindre strandpipare",     /* 094 */
    "större strandpipare",     /* 095 */
    "svartbent strandpipare",  /* 096 */
    "fjällpipare",	       /* 097 */
    "ljungpipare",	       /* 098 */
    "kustpipare",	       /* 099 */
    "ökenpipare",	       /* 349 */
    "mongolpipare",	       /* 350 */
    "amerikansk tundrapipare", /* 351 */
    "sibirisk tundrapipare",   /* 352 */
    "tofsvipa",	               /* 100 */
    "sumpvipa",		       /* 353 */
    "stäppvipa",	       /* 354 */
    "kustsnäppa",	       /* 101 */
    "sandlöpare",	       /* 102 */
    "sandsnäppa",	       /* 103 */
    "småsnäppa",	       /* 104 */
    "mosnäppa",		       /* 105 */
    "tuvsnäppa",	       /* 106 */
    "spovsnäppa",	       /* 107 */
    "skärsnäppa",	       /* 108 */
    "kärrsnäppa",	       /* 109 */
    "myrsnäppa",	       /* 110 */
    "brushane",		       /* 111 */
    "prärielöpare",	       /* 362 */
    "dvärgbeckasin",	       /* 112 */
    "enkelbeckasin",	       /* 113 */
    "dubbelbeckasin",	       /* 114 */
    "morkulla",		       /* 115 */
    "rödspov",		       /* 116 */
    "myrspov",		       /* 117 */
    "småspov",		       /* 118 */
    "storspov",		       /* 119 */
    "svartsnäppa",	       /* 120 */
    "rödbena",		       /* 121 */
    "dammsnäppa",	       /* 122 */
    "gluttsnäppa",	       /* 123 */
    "skogssnäppa",	       /* 124 */
    "amerikansk skogssnäppa",  /* 366 */
    "grönbena",		       /* 125 */
    "större gulbena",	       /* 364 */
    "mindre gulbena",	       /* 365 */
    "tereksnäppa",	       /* 126 */
    "drillsnäppa",	       /* 127 */
    "fläckdrillsnäppa",	       /* 462 */
    "roskarl",		       /* 128 */
    "tundrasnäppa",	       /* 355 */
    "rödhalsad snäppa",	       /* 356 */
    "långtåsnäppa",	       /* 357 */
    "vitgumpsnäppa",	       /* 358 */
    "gulbröstad snäppa",       /* 359 */
    "spetsstjärtad snäppa",    /* 360 */
    "styltsnäppa",	       /* 361 */
    "större beckasinsnäppa",   /* 363 */
    "smalnäbbad simsnäppa",    /* 129 */
    "brednäbbad simsnäppa",    /* 368 */
    "wilsonsimsnäppa",	       /* 367 */

    "bredstjärtad labb",       /* 130 */
    "labb",		       /* 131 */
    "fjällabb",		       /* 132 */
    "storlabb",		       /* 133 */

    "svarthuvad mås",	       /* 134 */
    "dvärgmås",		       /* 135 */
    "tärnmås",		       /* 136 */
    "skrattmås",	       /* 137 */
    "fiskmås",		       /* 138 */
    "silltrut",		       /* 139 */
    "gråtrut",		       /* 140 */
    "vitvingad trut",	       /* 141 */
    "vittrut",		       /* 142 */
    "havstrut",		       /* 143 */
    "tretåig mås",	       /* 144 */
    "svarthuvad trut",	       /* 369 */
    "sotvingad mås",	       /* 370 */
    "präriemås",	       /* 371 */
    "trädmås",		       /* 372 */
    "ringnäbbad mås",	       /* 373 */
    "kaspisk trut",	       /* 374 */
    "rosenmås",		       /* 375 */
    "ismås",		       /* 376 */
    "medelhavstrut",	       /* 461 */
    "östersjötrut",	       /* 478 */
    "sibirisk trut",	       /* 483 */

    "sandtärna",	       /* 145 */
    "skräntärna",	       /* 146 */
    "kentsk tärna",	       /* 147 */
    "fisktärna",	       /* 148 */
    "silvertärna",	       /* 149 */
    "rosentärna",	       /* 377 */
    "småtärna",		       /* 150 */
    "svarttärna",	       /* 151 */
    "vitvingad tärna",	       /* 152 */
    "sottärna",		       /* 378 */
    "skäggtärna",	       /* 379 */
    "kärrtärna",	       /* 467 */

    "sillgrissla",	       /* 153 */
    "tordmule",		       /* 154 */
    "tobisgrissla",	       /* 155 */
    "alkekung",		       /* 156 */
    "lunnefågel",	       /* 157 */
    "spetsbergsgrissla",       /* 380 */
    "papegojalka",	       /* 381 */
    "tofslunnefågel",	       /* 463 */

    "stäpphöna",	       /* 382 */

    "tamduva",		       /* 158 */
    "skogsduva",	       /* 159 */
    "ringduva",		       /* 160 */
    "turkduva",		       /* 161 */
    "turturduva",	       /* 162 */
    "större turturduva",       /* 163 */

    "gök",		       /* 164 */
    "skatgök",		       /* 383 */

    "berguv",		       /* 165 */
    "fjälluggla",	       /* 166 */
    "hökuggla",		       /* 167 */
    "sparvuggla",	       /* 168 */
    "kattuggla",	       /* 169 */
    "slaguggla",	       /* 170 */
    "lappuggla",	       /* 171 */
    "hornuggla",	       /* 172 */
    "jorduggla",	       /* 173 */
    "pärluggla",	       /* 174 */
    "tornuggla",	       /* 384 */
    "dvärguv",		       /* 385 */
    "minervauggla",	       /* 386 */

    "nattskärra",	       /* 175 */
    "ökennattskärra",	       /* 387 */
    "tornseglare",	       /* 176 */
    "blek tornseglare",	       /* 388 */
    "alpseglare",	       /* 389 */
    "stubbstjärtseglare",      /* 390 */
    "taggstjärtseglare",       /* 460 */
    "klippsvala",	       /* 468 */

    "kungsfiskare",	       /* 177 */
    "biätare",		       /* 178 */
    "grön biätare",	       /* 391 */
    "härfågel",		       /* 179 */
    "blåkråka",		       /* 392 */

    "göktyta",		       /* 180 */
    "gråspett",		       /* 181 */
    "gröngöling",	       /* 182 */
    "spillkråka",	       /* 183 */
    "större hackspett",	       /* 184 */
    "vitryggig hackspett",     /* 185 */
    "mindre hackspett",	       /* 186 */
    "tretåig hackspett",       /* 187 */
    "mellanspett",	       /* 393 */

    "korttålärka",	       /* 188 */
    "tofslärka",	       /* 189 */
    "trädlärka",	       /* 190 */
    "sånglärka",	       /* 191 */
    "berglärka",	       /* 192 */
    "kalanderlärka",	       /* 394 */
    "asiatisk kalanderlärka",  /* 395 */
    "dvärglärka",	       /* 396 */
    "svartlärka",	       /* 397 */

    "backsvala",	       /* 193 */
    "ladusvala",	       /* 194 */
    "hussvala",		       /* 195 */
    "rostgumpsvala",	       /* 398 */

    "större piplärka",	       /* 196 */
    "fältpiplärka",	       /* 197 */
    "trädpiplärka",	       /* 198 */
    "ängspiplärka",	       /* 199 */
    "rödstrupig piplärka",     /* 200 */
    "skärpiplärka",	       /* 201 */
    "vattenpiplärka",	       /* 458 */
    "hedpiplärka",	       /* 459 */
    "sibirisk piplärka",       /* 399 */
    "tundrapiplärka",	       /* 400 */

    "gulärla",		       /* 202 */
    "forsärla",		       /* 203 */
    "sädesärla",	       /* 204 */
    "engelsk sädesärla",       /* 479 */
    "citronärla",	       /* 401 */

    "sidensvans",	       /* 205 */

    "strömstare",	       /* 206 */

    "gärdsmyg",		       /* 207 */

    "järnsparv",	       /* 208 */
    "sibirisk järnsparv",      /* 402 */
    "svartstrupig järnsparv",  /* 403 */
    "alpjärnsparv",	       /* 404 */

    "rödhake",		       /* 209 */
    "näktergal",	       /* 210 */
    "sydnäktergal",	       /* 405 */
    "vitstrupig näktergal",    /* 407 */
    "blåhake",		       /* 211 */
    "svart rödstjärt",	       /* 212 */
    "rödstjärt",	       /* 213 */
    "blåstjärt",	       /* 406 */

    "buskskvätta",	       /* 214 */
    "ö svarth buskskvätta",    /* 408 */
    "svarthakad buskskvätta",  /* 409 */
    "stenskvätta",	       /* 215 */
    "isabellastenskvätta",     /* 410 */
    "nunnestenskvätta",	       /* 411 */
    "medelhavsstenskvätta",    /* 412 */
    "ökenstenskvätta",	       /* 413 */

    "ringtrast",	       /* 216 */
    "koltrast",		       /* 217 */
    "björktrast",	       /* 218 */
    "taltrast",		       /* 219 */
    "rödvingetrast",	       /* 220 */
    "dubbeltrast",	       /* 221 */
    "stentrast",	       /* 414 */
    "blåtrast",		       /* 415 */
    "guldtrast",	       /* 416 */
    "sibirisk trast",	       /* 417 */
    "eremitskogstrast",	       /* 418 */
    "rostskogtrast",	       /* 419 */
    "taigatrast",	       /* 420 */
    "gråhalsad trast",	       /* 421 */
    "vandringstrast",	       /* 422 */
    "bruntrast",	       /* 465 */
    "beigekindad skogstrast",  /* 469 */

    "cettisångare",	       /* 423 */
    "träsksångare",	       /* 424 */
    "vattensångare",	       /* 425 */
    "fältsångare",	       /* 426 */
    "gråsångare",	       /* 427 */
    "polyglottsångare",	       /* 428 */
    "provencesångare",	       /* 429 */
    "rödstrupig sångare",      /* 430 */
    "sammetshätta",	       /* 431 */
    "ökensångare",	       /* 432 */
    "nordsångare",	       /* 433 */
    "bergtaigasångare",	       /* 434 */
    "videsångare",	       /* 435 */
    "brunsångare",	       /* 436 */
    "bergsångare",	       /* 437 */
    "starrsångare",	       /* 464 */

    "gräshoppssångare",	       /* 222 */
    "flodsångare",	       /* 223 */
    "vassångare",	       /* 224 */
    "sävsångare",	       /* 225 */
    "busksångare",	       /* 226 */
    "kärrsångare",	       /* 227 */
    "rörsångare",	       /* 228 */
    "trastsångare",	       /* 229 */
    "härmsångare",	       /* 230 */

    "höksångare",	       /* 231 */
    "ärtsångare",	       /* 232 */
    "törnsångare",	       /* 233 */
    "trädgårdssångare",	       /* 234 */
    "svarthätta",	       /* 235 */

    "lundsångare",	       /* 236 */
    "kungsfågelsångare",       /* 237 */
    "taigasångare",	       /* 238 */
    "grönsångare",	       /* 239 */
    "gransångare",	       /* 240 */
    "sibirisk gransångare",    /* 480 */
    "lövsångare",	       /* 241 */

    "kungsfågel",	       /* 242 */
    "brandkronad kungsfågel",  /* 243 */

    "grå flugsnappare",	       /* 244 */
    "mindre flugsnappare",     /* 245 */
    "halsbandsflugsnappare",   /* 246 */
    "svartvit flugsnappare",   /* 247 */
    "glasögonflugsnappare",    /* 438 */

    "skäggmes",		       /* 248 */

    "stjärtmes",	       /* 249 */

    "entita",		       /* 250 */
    "talltita",		       /* 251 */
    "lappmes",		       /* 252 */
    "tofsmes",		       /* 253 */
    "svartmes",		       /* 254 */
    "blåmes",		       /* 255 */
    "azurmes",		       /* 439 */
    "talgoxe",		       /* 256 */

    "nötväcka",		       /* 257 */

    "trädkrypare",	       /* 258 */
    "trädgårdsträdkrypare",    /* 440 */

    "pungmes",		       /* 259 */

    "törnskata",	       /* 261 */
    "svartpannad törnskata",   /* 262 */
    "isabellatörnskata",       /* 441 */
    "rödhuvad törnskata",      /* 442 */
    "masktörnskata",	       /* 443 */
    "stäppvarfågel",	       /* 470 */
    "varfågel",		       /* 263 */

    "nötskrika",	       /* 264 */
    "lavskrika",	       /* 265 */
    "skata",		       /* 266 */
    "nötkråka",		       /* 267 */
    "kaja",		       /* 268 */
    "råka",		       /* 269 */
    "kråka",		       /* 270 */
    "svartkråka",	       /* 481 */
    "korp",		       /* 271 */
    "klippkaja",	       /* 444 */

    "sommargylling",	       /* 260 */
    "stare",		       /* 272 */
    "rosenstare",	       /* 445 */

    "gråsparv",		       /* 273 */
    "pilfink",		       /* 274 */

    "bofink",		       /* 275 */
    "bergfink",		       /* 276 */
    "gulhämpling",	       /* 277 */
    "grönfink",		       /* 278 */
    "steglits",		       /* 279 */
    "grönsiska",	       /* 280 */
    "hämpling",		       /* 281 */
    "vinterhämpling",	       /* 282 */
    "gråsiska",		       /* 283 */
    "brunsiska",	       /* 482 */
    "snösiska",		       /* 284 */
    "domherre",		       /* 290 */
    "rosenfink",	       /* 288 */
    "ökentrumpetare",	       /* 446 */
    "stenknäck",	       /* 291 */
    "bändelkorsnäbb",	       /* 285 */
    "mindre korsnäbb",	       /* 286 */
    "större korsnäbb",	       /* 287 */
    "tallbit",		       /* 289 */

    "lappsparv",	       /* 292 */
    "snösparv",		       /* 293 */
    "gulsparv",		       /* 294 */
    "ortolansparv",	       /* 295 */
    "videsparv",	       /* 296 */
    "dvärgsparv",	       /* 297 */
    "sävsparv",		       /* 298 */
    "kornsparv",	       /* 299 */
    "vitstrupig sparv",	       /* 447 */
    "tallsparv",	       /* 448 */
    "klippsparv",	       /* 449 */
    "rostsparv",	       /* 450 */
    "gyllensparv",	       /* 451 */
    "svarthuvad sparv",	       /* 452 */
    "stäppsparv",	       /* 453 */

    "brokig kardinal",	       /* 454 */
    "indigosparv",	       /* 455 */
};



/*----------------------------------------------------------------------------
 *
 * constructor
 *
 *
 *----------------------------------------------------------------------------
 */
TaxonomicOrder::TaxonomicOrder()
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
TaxonomicOrder::TaxonomicOrder(const TaxonomicOrder& obj)
{
    ;
}


/*----------------------------------------------------------------------------
 *
 * destructor
 *
 *
 *----------------------------------------------------------------------------
 */
TaxonomicOrder::~TaxonomicOrder()
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
const TaxonomicOrder& TaxonomicOrder::operator=(const SpeciesOrder& obj)
{
    return *this;
}


/*----------------------------------------------------------------------------
 *
 * species()
 *
 *
 *----------------------------------------------------------------------------
 */
Species TaxonomicOrder::species(int i) const
{
    assert(i>=0);
    assert(i<INTERNALORDERLEN);

    return Species(internalorder[i]);
}


/*----------------------------------------------------------------------------
 *
 * end()
 *
 *
 *----------------------------------------------------------------------------
 */
int TaxonomicOrder::end() const
{
    return INTERNALORDERLEN;
}
