/* Copyright (C) 2013 J�rgen Grahn.
 * All rights reserved.
 */
#include "../taxa.h"

#include <testicle.h>
#include <iostream>
#include <sstream>

using std::string;

namespace {

    Taxa parse(const char* s)
    {
	std::istringstream iss(s);
	std::ostringstream err;
	const Taxa spp(iss, err);
	testicle::assert_eq(err.str(), "");
	return spp;
    }
}

namespace taxa {

    Taxa test_lom(const char* const txt)
    {
	const Taxa spp = parse(txt);
	const TaxonId lom = spp.find("storlom");
	testicle::assert_(lom);
	testicle::assert_eq(lom, spp.find("Gavia arctica"));

	const Taxon& lom2 = spp[lom];
	testicle::assert_eq(lom2.name, "storlom");
	testicle::assert_eq(lom2.latin, "Gavia arctica");

	testicle::assert_(!spp.find("nil"));
	return spp;
    }

    void test_simple()
    {
	test_lom("# comment\n"
		 "\n"
		 "storlom (Gavia arctica)\n");
    }

    void test_spacing()
    {
	test_lom("\n"
		 "  # nil\n"
		 "# nil\n"
		 "= nil\n"
		 " storlom   (Gavia arctica)   # nil");
    }

    void test_more()
    {
	test_lom("sm�lom\n"
		 "storlom (Gavia arctica)\n"
		 "sm�dopping\n");
    }

    void test_alias()
    {
	const Taxa spp = test_lom("storlom (Gavia arctica)\n"
				  "bj�rktrast\n"
				  "= sn�skata\n");
	testicle::assert_eq(spp.find("bj�rktrast"),
			    spp.find("sn�skata"));
    }

    void test_alias2()
    {
	const Taxa spp = test_lom("storlom (Gavia arctica)\n"
				  " bj�rktrast # nil\n"
				  "   \n"
				  "#nil\n"
				  "= sn�skata");
	testicle::assert_eq(spp.find("bj�rktrast"),
			    spp.find("sn�skata"));
    }

    void test_order()
    {
	const Taxa spp = test_lom("storlom (Gavia arctica)\n"
				  "bj�rktrast\n");
	testicle::assert_lt(spp.find("storlom"), spp.find("bj�rktrast"));
	testicle::assert_lt(spp.find("Gavia arctica"), spp.find("bj�rktrast"));
	testicle::assert_(!(spp.find("bj�rktrast") < spp.find("storlom")));
    }
}