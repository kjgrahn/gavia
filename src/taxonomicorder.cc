/*----------------------------------------------------------------------------
 *
 * $Id: taxonomicorder.cc,v 1.8 2001-07-22 21:03:32 grahn Exp $
 *
 * taxonomicorder.cc
 *
 * Copyright (c) 1999 J�rgen Grahn <jgrahn@algonet.se>
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
    "sm�lom",  	       	       /* 000 */
    "storlom",		       /* 001 */
    "vitn�bbad islom",	       /* 002 */
    "svartn�bbad islom",       /* 300 */

    "sm�dopping",	       /* 003 */
    "sk�ggdopping",	       /* 004 */
    "gr�hakedopping",	       /* 005 */
    "svarthakedopping",	       /* 006 */
    "svarthalsad dopping",     /* 007 */

    "stormf�gel",	       /* 008 */
    "gr�lira",		       /* 009 */
    "mindre lira",	       /* 010 */
    "guln�bbad lira",	       /* 301 */
    "st�rre lira",	       /* 302 */
    "medelhavslira",	       /* 303 */
    "klykstj�rtad stormsvala", /* 011 */
    "stormsvala",	       /* 304 */

    "havssula",		       /* 012 */
    "storskarv",	       /* 013 */
    "toppskarv",	       /* 305 */
    "dv�rgskarv",	       /* 306 */

    "r�rdrom",		       /* 014 */
    "dv�rgr�rdrom",	       /* 307 */
    "natth�ger",	       /* 308 */
    "rallh�ger",	       /* 309 */
    "koh�ger",		       /* 310 */
    "silkesh�ger",	       /* 311 */
    "�gretth�ger",	       /* 312 */
    "h�ger",		       /* 015 */
    "purpurh�ger",	       /* 313 */

    "svart stork",	       /* 016 */
    "vit stork",	       /* 017 */

    "bronsibis",	       /* 314 */
    "skedstork",	       /* 315 */

    "flamingo",		       /* 018 */

    "kn�lsvan",		       /* 019 */
    "mindre s�ngsvan",	       /* 020 */
    "s�ngsvan",		       /* 021 */
    "svart svan",	       /* 457 */

    "s�dg�s",		       /* 022 */
    "spetsbergsg�s",	       /* 023 */
    "bl�sg�s",		       /* 024 */
    "fj�llg�s",		       /* 025 */
    "gr�g�s",		       /* 026 */
    "stripg�s",		       /* 027 */
    "sn�g�s",		       /* 028 */
    "kanadag�s",	       /* 029 */
    "vitkindad g�s",	       /* 030 */
    "prutg�s",		       /* 031 */
    "r�dhalsad g�s",	       /* 316 */
    "tundras�dg�s",	       /* 471 */
    "gr�nl�ndsk bl�sg�s",      /* 472 */
    "dv�rgkanadag�s",	       /* 473 */
    "svartbukig prutg�s",      /* 474 */
    "ljusbukig prutg�s",       /* 475 */

    "rostand",		       /* 032 */
    "gravand",		       /* 033 */
    "bl�sand",		       /* 034 */
    "snatterand",	       /* 035 */
    "kricka",		       /* 036 */
    "gr�sand",		       /* 037 */
    "stj�rtand",	       /* 038 */
    "�rta",		       /* 039 */
    "skedand",		       /* 040 */
    "mandarinand",	       /* 041 */
    "brudand",		       /* 042 */
    "amerikansk bl�sand",      /* 317 */
    "svartand",		       /* 318 */
    "bl�vingad �rta",	       /* 319 */
    "amerikansk kricka",       /* 476 */

    "brunand",		       /* 043 */
    "vigg",		       /* 044 */
    "bergand",		       /* 045 */
    "mindre bergand",	       /* 466 */
    "ejder",		       /* 046 */
    "praktejder",	       /* 047 */
    "alf�rr�dare",	       /* 048 */
    "alf�gel",		       /* 049 */
    "sj�orre",		       /* 050 */
    "amerikansk sj�orre",      /* 477 */
    "sv�rta",		       /* 051 */
    "knipa",		       /* 052 */
    "r�dhuvad dykand",	       /* 320 */
    "ringand",		       /* 321 */
    "vit�gd dykand",	       /* 322 */
    "str�mand",		       /* 323 */
    "vitnackad sv�rta",	       /* 324 */
    "amerikansk kopparand",    /* 456 */

    "salskrake",	       /* 053 */
    "sm�skrake",	       /* 054 */
    "storskrake",	       /* 055 */
    "kamskrake",	       /* 325 */

    "bivr�k",		       /* 056 */
    "brunglada",	       /* 057 */
    "glada",		       /* 058 */
    "havs�rn",		       /* 059 */
    "brun k�rrh�k",	       /* 060 */
    "bl� k�rrh�k",	       /* 061 */
    "st�pph�k",		       /* 062 */
    "�ngsh�k",		       /* 063 */
    "duvh�k",		       /* 064 */
    "sparvh�k",		       /* 065 */
    "ormvr�k",		       /* 066 */
    "fj�llvr�k",	       /* 067 */
    "mindre skrik�rn",	       /* 068 */
    "kungs�rn",		       /* 069 */
    "smutsgam",		       /* 326 */
    "g�sgam",		       /* 327 */
    "orm�rn",		       /* 328 */
    "�rnvr�k",		       /* 329 */
    "st�rre skrik�rn",	       /* 330 */
    "st�pp�rn",		       /* 331 */
    "kejsar�rn",	       /* 332 */
    "dv�rg�rn",		       /* 333 */

    "fiskgjuse",	       /* 070 */

    "tornfalk",		       /* 071 */
    "aftonfalk",	       /* 072 */
    "stenfalk",		       /* 073 */
    "l�rkfalk",		       /* 074 */
    "jaktfalk",		       /* 075 */
    "pilgrimsfalk",	       /* 076 */
    "r�dfalk",		       /* 334 */
    "eleonorafalk",	       /* 335 */
    "tatarfalk",	       /* 336 */

    "j�rpe",		       /* 077 */
    "dalripa",		       /* 078 */
    "fj�llripa",	       /* 079 */
    "orre",		       /* 080 */
    "tj�der",		       /* 081 */
    "rapph�na",		       /* 082 */
    "vaktel",		       /* 083 */
    "fasan",		       /* 084 */
    "bergh�na",		       /* 337 */

    "trana",		       /* 091 */
    "jungfrutrana",	       /* 340 */

    "sm�trapp",		       /* 341 */
    "kragtrapp",	       /* 342 */
    "stortrapp",	       /* 343 */

    "vattenrall",	       /* 085 */
    "sm�fl�ckig sumph�na",     /* 086 */
    "mindre sumph�na",	       /* 087 */
    "karolinasumph�na",	       /* 338 */
    "dv�rgsumph�na",	       /* 339 */
    "kornknarr",	       /* 088 */
    "r�rh�na",		       /* 089 */
    "soth�na",		       /* 090 */

    "strandskata",	       /* 092 */
    "sk�rfl�cka",	       /* 093 */
    "styltl�pare",	       /* 344 */
    "tjockfot",		       /* 345 */
    "�kenl�pare",	       /* 346 */
    "vadarsvala",	       /* 347 */
    "svartvingad vadarsvala",  /* 348 */
    "orientvadarsvala",	       /* 484 */
    "mindre strandpipare",     /* 094 */
    "st�rre strandpipare",     /* 095 */
    "svartbent strandpipare",  /* 096 */
    "fj�llpipare",	       /* 097 */
    "ljungpipare",	       /* 098 */
    "kustpipare",	       /* 099 */
    "�kenpipare",	       /* 349 */
    "mongolpipare",	       /* 350 */
    "amerikansk tundrapipare", /* 351 */
    "sibirisk tundrapipare",   /* 352 */
    "tofsvipa",	               /* 100 */
    "sumpvipa",		       /* 353 */
    "st�ppvipa",	       /* 354 */
    "kustsn�ppa",	       /* 101 */
    "sandl�pare",	       /* 102 */
    "sandsn�ppa",	       /* 103 */
    "sm�sn�ppa",	       /* 104 */
    "mosn�ppa",		       /* 105 */
    "tuvsn�ppa",	       /* 106 */
    "spovsn�ppa",	       /* 107 */
    "sk�rsn�ppa",	       /* 108 */
    "k�rrsn�ppa",	       /* 109 */
    "myrsn�ppa",	       /* 110 */
    "brushane",		       /* 111 */
    "pr�riel�pare",	       /* 362 */
    "dv�rgbeckasin",	       /* 112 */
    "enkelbeckasin",	       /* 113 */
    "dubbelbeckasin",	       /* 114 */
    "morkulla",		       /* 115 */
    "r�dspov",		       /* 116 */
    "myrspov",		       /* 117 */
    "sm�spov",		       /* 118 */
    "storspov",		       /* 119 */
    "svartsn�ppa",	       /* 120 */
    "r�dbena",		       /* 121 */
    "dammsn�ppa",	       /* 122 */
    "gluttsn�ppa",	       /* 123 */
    "skogssn�ppa",	       /* 124 */
    "amerikansk skogssn�ppa",  /* 366 */
    "gr�nbena",		       /* 125 */
    "st�rre gulbena",	       /* 364 */
    "mindre gulbena",	       /* 365 */
    "tereksn�ppa",	       /* 126 */
    "drillsn�ppa",	       /* 127 */
    "fl�ckdrillsn�ppa",	       /* 462 */
    "roskarl",		       /* 128 */
    "tundrasn�ppa",	       /* 355 */
    "r�dhalsad sn�ppa",	       /* 356 */
    "l�ngt�sn�ppa",	       /* 357 */
    "vitgumpsn�ppa",	       /* 358 */
    "gulbr�stad sn�ppa",       /* 359 */
    "spetsstj�rtad sn�ppa",    /* 360 */
    "styltsn�ppa",	       /* 361 */
    "st�rre beckasinsn�ppa",   /* 363 */
    "smaln�bbad simsn�ppa",    /* 129 */
    "bredn�bbad simsn�ppa",    /* 368 */
    "wilsonsimsn�ppa",	       /* 367 */

    "bredstj�rtad labb",       /* 130 */
    "labb",		       /* 131 */
    "fj�llabb",		       /* 132 */
    "storlabb",		       /* 133 */

    "svarthuvad m�s",	       /* 134 */
    "dv�rgm�s",		       /* 135 */
    "t�rnm�s",		       /* 136 */
    "skrattm�s",	       /* 137 */
    "fiskm�s",		       /* 138 */
    "silltrut",		       /* 139 */
    "gr�trut",		       /* 140 */
    "vitvingad trut",	       /* 141 */
    "vittrut",		       /* 142 */
    "havstrut",		       /* 143 */
    "tret�ig m�s",	       /* 144 */
    "svarthuvad trut",	       /* 369 */
    "sotvingad m�s",	       /* 370 */
    "pr�riem�s",	       /* 371 */
    "tr�dm�s",		       /* 372 */
    "ringn�bbad m�s",	       /* 373 */
    "kaspisk trut",	       /* 374 */
    "rosenm�s",		       /* 375 */
    "ism�s",		       /* 376 */
    "medelhavstrut",	       /* 461 */
    "�stersj�trut",	       /* 478 */
    "sibirisk trut",	       /* 483 */

    "sandt�rna",	       /* 145 */
    "skr�nt�rna",	       /* 146 */
    "kentsk t�rna",	       /* 147 */
    "fiskt�rna",	       /* 148 */
    "silvert�rna",	       /* 149 */
    "rosent�rna",	       /* 377 */
    "sm�t�rna",		       /* 150 */
    "svartt�rna",	       /* 151 */
    "vitvingad t�rna",	       /* 152 */
    "sott�rna",		       /* 378 */
    "sk�ggt�rna",	       /* 379 */
    "k�rrt�rna",	       /* 467 */

    "sillgrissla",	       /* 153 */
    "tordmule",		       /* 154 */
    "tobisgrissla",	       /* 155 */
    "alkekung",		       /* 156 */
    "lunnef�gel",	       /* 157 */
    "spetsbergsgrissla",       /* 380 */
    "papegojalka",	       /* 381 */
    "tofslunnef�gel",	       /* 463 */

    "st�pph�na",	       /* 382 */

    "tamduva",		       /* 158 */
    "skogsduva",	       /* 159 */
    "ringduva",		       /* 160 */
    "turkduva",		       /* 161 */
    "turturduva",	       /* 162 */
    "st�rre turturduva",       /* 163 */

    "g�k",		       /* 164 */
    "skatg�k",		       /* 383 */

    "berguv",		       /* 165 */
    "fj�lluggla",	       /* 166 */
    "h�kuggla",		       /* 167 */
    "sparvuggla",	       /* 168 */
    "kattuggla",	       /* 169 */
    "slaguggla",	       /* 170 */
    "lappuggla",	       /* 171 */
    "hornuggla",	       /* 172 */
    "jorduggla",	       /* 173 */
    "p�rluggla",	       /* 174 */
    "tornuggla",	       /* 384 */
    "dv�rguv",		       /* 385 */
    "minervauggla",	       /* 386 */

    "nattsk�rra",	       /* 175 */
    "�kennattsk�rra",	       /* 387 */
    "tornseglare",	       /* 176 */
    "blek tornseglare",	       /* 388 */
    "alpseglare",	       /* 389 */
    "stubbstj�rtseglare",      /* 390 */
    "taggstj�rtseglare",       /* 460 */
    "klippsvala",	       /* 468 */

    "kungsfiskare",	       /* 177 */
    "bi�tare",		       /* 178 */
    "gr�n bi�tare",	       /* 391 */
    "h�rf�gel",		       /* 179 */
    "bl�kr�ka",		       /* 392 */

    "g�ktyta",		       /* 180 */
    "gr�spett",		       /* 181 */
    "gr�ng�ling",	       /* 182 */
    "spillkr�ka",	       /* 183 */
    "st�rre hackspett",	       /* 184 */
    "vitryggig hackspett",     /* 185 */
    "mindre hackspett",	       /* 186 */
    "tret�ig hackspett",       /* 187 */
    "mellanspett",	       /* 393 */

    "kortt�l�rka",	       /* 188 */
    "tofsl�rka",	       /* 189 */
    "tr�dl�rka",	       /* 190 */
    "s�ngl�rka",	       /* 191 */
    "bergl�rka",	       /* 192 */
    "kalanderl�rka",	       /* 394 */
    "asiatisk kalanderl�rka",  /* 395 */
    "dv�rgl�rka",	       /* 396 */
    "svartl�rka",	       /* 397 */

    "backsvala",	       /* 193 */
    "ladusvala",	       /* 194 */
    "hussvala",		       /* 195 */
    "rostgumpsvala",	       /* 398 */

    "st�rre pipl�rka",	       /* 196 */
    "f�ltpipl�rka",	       /* 197 */
    "tr�dpipl�rka",	       /* 198 */
    "�ngspipl�rka",	       /* 199 */
    "r�dstrupig pipl�rka",     /* 200 */
    "sk�rpipl�rka",	       /* 201 */
    "vattenpipl�rka",	       /* 458 */
    "hedpipl�rka",	       /* 459 */
    "sibirisk pipl�rka",       /* 399 */
    "tundrapipl�rka",	       /* 400 */

    "gul�rla",		       /* 202 */
    "fors�rla",		       /* 203 */
    "s�des�rla",	       /* 204 */
    "engelsk s�des�rla",       /* 479 */
    "citron�rla",	       /* 401 */

    "sidensvans",	       /* 205 */

    "str�mstare",	       /* 206 */

    "g�rdsmyg",		       /* 207 */

    "j�rnsparv",	       /* 208 */
    "sibirisk j�rnsparv",      /* 402 */
    "svartstrupig j�rnsparv",  /* 403 */
    "alpj�rnsparv",	       /* 404 */

    "r�dhake",		       /* 209 */
    "n�ktergal",	       /* 210 */
    "sydn�ktergal",	       /* 405 */
    "vitstrupig n�ktergal",    /* 407 */
    "bl�hake",		       /* 211 */
    "svart r�dstj�rt",	       /* 212 */
    "r�dstj�rt",	       /* 213 */
    "bl�stj�rt",	       /* 406 */

    "buskskv�tta",	       /* 214 */
    "� svarth buskskv�tta",    /* 408 */
    "svarthakad buskskv�tta",  /* 409 */
    "stenskv�tta",	       /* 215 */
    "isabellastenskv�tta",     /* 410 */
    "nunnestenskv�tta",	       /* 411 */
    "medelhavsstenskv�tta",    /* 412 */
    "�kenstenskv�tta",	       /* 413 */

    "ringtrast",	       /* 216 */
    "koltrast",		       /* 217 */
    "bj�rktrast",	       /* 218 */
    "taltrast",		       /* 219 */
    "r�dvingetrast",	       /* 220 */
    "dubbeltrast",	       /* 221 */
    "stentrast",	       /* 414 */
    "bl�trast",		       /* 415 */
    "guldtrast",	       /* 416 */
    "sibirisk trast",	       /* 417 */
    "eremitskogstrast",	       /* 418 */
    "rostskogtrast",	       /* 419 */
    "taigatrast",	       /* 420 */
    "gr�halsad trast",	       /* 421 */
    "vandringstrast",	       /* 422 */
    "bruntrast",	       /* 465 */
    "beigekindad skogstrast",  /* 469 */

    "cettis�ngare",	       /* 423 */
    "tr�sks�ngare",	       /* 424 */
    "vattens�ngare",	       /* 425 */
    "f�lts�ngare",	       /* 426 */
    "gr�s�ngare",	       /* 427 */
    "polyglotts�ngare",	       /* 428 */
    "provences�ngare",	       /* 429 */
    "r�dstrupig s�ngare",      /* 430 */
    "sammetsh�tta",	       /* 431 */
    "�kens�ngare",	       /* 432 */
    "nords�ngare",	       /* 433 */
    "bergtaigas�ngare",	       /* 434 */
    "vides�ngare",	       /* 435 */
    "bruns�ngare",	       /* 436 */
    "bergs�ngare",	       /* 437 */
    "starrs�ngare",	       /* 464 */

    "gr�shoppss�ngare",	       /* 222 */
    "flods�ngare",	       /* 223 */
    "vass�ngare",	       /* 224 */
    "s�vs�ngare",	       /* 225 */
    "busks�ngare",	       /* 226 */
    "k�rrs�ngare",	       /* 227 */
    "r�rs�ngare",	       /* 228 */
    "trasts�ngare",	       /* 229 */
    "h�rms�ngare",	       /* 230 */

    "h�ks�ngare",	       /* 231 */
    "�rts�ngare",	       /* 232 */
    "t�rns�ngare",	       /* 233 */
    "tr�dg�rdss�ngare",	       /* 234 */
    "svarth�tta",	       /* 235 */

    "lunds�ngare",	       /* 236 */
    "kungsf�gels�ngare",       /* 237 */
    "taigas�ngare",	       /* 238 */
    "gr�ns�ngare",	       /* 239 */
    "grans�ngare",	       /* 240 */
    "sibirisk grans�ngare",    /* 480 */
    "l�vs�ngare",	       /* 241 */

    "kungsf�gel",	       /* 242 */
    "brandkronad kungsf�gel",  /* 243 */

    "gr� flugsnappare",	       /* 244 */
    "mindre flugsnappare",     /* 245 */
    "halsbandsflugsnappare",   /* 246 */
    "svartvit flugsnappare",   /* 247 */
    "glas�gonflugsnappare",    /* 438 */

    "sk�ggmes",		       /* 248 */

    "stj�rtmes",	       /* 249 */

    "entita",		       /* 250 */
    "talltita",		       /* 251 */
    "lappmes",		       /* 252 */
    "tofsmes",		       /* 253 */
    "svartmes",		       /* 254 */
    "bl�mes",		       /* 255 */
    "azurmes",		       /* 439 */
    "talgoxe",		       /* 256 */

    "n�tv�cka",		       /* 257 */

    "tr�dkrypare",	       /* 258 */
    "tr�dg�rdstr�dkrypare",    /* 440 */

    "pungmes",		       /* 259 */

    "t�rnskata",	       /* 261 */
    "svartpannad t�rnskata",   /* 262 */
    "isabellat�rnskata",       /* 441 */
    "r�dhuvad t�rnskata",      /* 442 */
    "maskt�rnskata",	       /* 443 */
    "st�ppvarf�gel",	       /* 470 */
    "varf�gel",		       /* 263 */

    "n�tskrika",	       /* 264 */
    "lavskrika",	       /* 265 */
    "skata",		       /* 266 */
    "n�tkr�ka",		       /* 267 */
    "kaja",		       /* 268 */
    "r�ka",		       /* 269 */
    "kr�ka",		       /* 270 */
    "svartkr�ka",	       /* 481 */
    "korp",		       /* 271 */
    "klippkaja",	       /* 444 */

    "sommargylling",	       /* 260 */
    "stare",		       /* 272 */
    "rosenstare",	       /* 445 */

    "gr�sparv",		       /* 273 */
    "pilfink",		       /* 274 */

    "bofink",		       /* 275 */
    "bergfink",		       /* 276 */
    "gulh�mpling",	       /* 277 */
    "gr�nfink",		       /* 278 */
    "steglits",		       /* 279 */
    "gr�nsiska",	       /* 280 */
    "h�mpling",		       /* 281 */
    "vinterh�mpling",	       /* 282 */
    "gr�siska",		       /* 283 */
    "brunsiska",	       /* 482 */
    "sn�siska",		       /* 284 */
    "domherre",		       /* 290 */
    "rosenfink",	       /* 288 */
    "�kentrumpetare",	       /* 446 */
    "stenkn�ck",	       /* 291 */
    "b�ndelkorsn�bb",	       /* 285 */
    "mindre korsn�bb",	       /* 286 */
    "st�rre korsn�bb",	       /* 287 */
    "tallbit",		       /* 289 */

    "lappsparv",	       /* 292 */
    "sn�sparv",		       /* 293 */
    "gulsparv",		       /* 294 */
    "ortolansparv",	       /* 295 */
    "videsparv",	       /* 296 */
    "dv�rgsparv",	       /* 297 */
    "s�vsparv",		       /* 298 */
    "kornsparv",	       /* 299 */
    "vitstrupig sparv",	       /* 447 */
    "tallsparv",	       /* 448 */
    "klippsparv",	       /* 449 */
    "rostsparv",	       /* 450 */
    "gyllensparv",	       /* 451 */
    "svarthuvad sparv",	       /* 452 */
    "st�ppsparv",	       /* 453 */

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
