/*
 * Copyright (C) 2014 Jörgen Grahn.
 * All rights reserved.
 */
#include <taxa.h>
#include <sstream>

#include <orchis.h>

namespace {

    Taxa list(const char* src)
    {
	std::istringstream iss(src);
	std::ostringstream err;

	Taxa spp(iss, err);
	orchis::assert_eq(err.str(), "");
	return spp;
    }

    void assert_sp(Taxa::const_iterator i, const char* name, const char* latin)
    {
	orchis::assert_eq(i->name, name);
	orchis::assert_eq(i->latin, latin);
    }

    void assert_same(const Taxa& spp, const char* a, const char* b, const char* c = 0)
    {
	orchis::assert_(spp.find(a));
	orchis::assert_eq(spp.find(a), spp.find(b));
	if(c) orchis::assert_eq(spp.find(a), spp.find(c));
    }
}


namespace taxa {
    using orchis::TC;

    void empty(TC)
    {
	const Taxa spp = list("");
	orchis::assert_(spp.begin() == spp.end());
    }

    void two(TC)
    {
	const Taxa spp = list("bergek  (Quercus petraea)\n"
			      "skogsek (Quercus robur)");
	Taxa::const_iterator i = spp.begin();
	assert_sp(i++, "Quercus sp", "Quercus");
	assert_sp(i++, "bergek", "Quercus petraea");
	assert_sp(i++, "skogsek", "Quercus robur");
	orchis::assert_(i == spp.end());
    }

    void common_only(TC)
    {
	const Taxa spp = list("skogsek");
	Taxa::const_iterator i = spp.begin();
	assert_sp(i++, "skogsek", "");
	orchis::assert_(i == spp.end());
    }

    void scientific_only(TC)
    {
	const Taxa spp = list("- (Taraxacum hamosiforme)");
	Taxa::const_iterator i = spp.begin();
	assert_sp(i++, "Taraxacum sp", "Taraxacum");
	assert_sp(i++, "Taraxacum hamosiforme", "Taraxacum hamosiforme");
	orchis::assert_(i == spp.end());
    }

    void alias(TC)
    {
	const Taxa spp = list("skogsek (Quercus robur)\n"
			      "= ek");
	Taxa::const_iterator i = spp.begin();
	assert_sp(i++, "Quercus sp", "Quercus");
	assert_sp(i++, "skogsek", "Quercus robur");
	orchis::assert_(i == spp.end());

	assert_same(spp, "skogsek", "ek", "Quercus robur");
    }

    void explicit_genus(TC)
    {
	const Taxa spp = list("-             (Cotoneaster)\n"
			      "starr         (Carex)\n"
			      "finnstarr     (Carex atherodes)\n"
			      "fetblad       (Phedimus)\n"
			      "= Sedum\n"
			      "gyllenfetblad (Phedimus aizoon)");
	Taxa::const_iterator i = spp.begin();
	assert_sp(i++, "Cotoneaster sp", "Cotoneaster");
	assert_sp(i++, "starr", "Carex");
	assert_sp(i++, "finnstarr", "Carex atherodes");
	assert_sp(i++, "fetblad", "Phedimus");
	assert_sp(i++, "gyllenfetblad", "Phedimus aizoon");
	orchis::assert_(i == spp.end());

	assert_same(spp, "Cotoneaster", "Cotoneaster sp");
	assert_same(spp, "starr", "Carex", "Carex sp");
	assert_same(spp, "fetblad", "Phedimus", "Phedimus sp");
	assert_same(spp, "fetblad", "Sedum");
    }

    namespace {

	Taxa parse(const char* s)
	{
	    return list(s);
	}
    }

    /* The older tests. Probably have a large overlap with the ones above,
     * taken from groblad.
     */
    namespace old {

	using orchis::TC;

	Taxa test_lom(const char* const txt)
	{
	    const Taxa spp = parse(txt);
	    const TaxonId lom = spp.find("storlom");
	    orchis::assert_(lom);
	    orchis::assert_eq(lom, spp.find("Gavia arctica"));

	    const Taxon& lom2 = spp[lom];
	    orchis::assert_eq(lom2.name, "storlom");
	    orchis::assert_eq(lom2.latin, "Gavia arctica");

	    orchis::assert_(!spp.find("nil"));
	    return spp;
	}

	void simple(TC)
	{
	    test_lom("# comment\n"
		     "\n"
		     "storlom (Gavia arctica)\n");
	}

	void spacing(TC)
	{
	    test_lom("\n"
		     "  # nil\n"
		     "# nil\n"
		     "= nil\n"
		     " storlom   (Gavia arctica)   # nil");
	}

	void more(TC)
	{
	    test_lom("smålom\n"
		     "storlom (Gavia arctica)\n"
		     "smådopping\n");
	}

	void alias(TC)
	{
	    const Taxa spp = test_lom("storlom (Gavia arctica)\n"
				      "björktrast\n"
				      "= snöskata\n");
	    orchis::assert_eq(spp.find("björktrast"),
			      spp.find("snöskata"));
	}

	void alias2(TC)
	{
	    const Taxa spp = test_lom("storlom (Gavia arctica)\n"
				      " björktrast # nil\n"
				      "   \n"
				      "#nil\n"
				      "= snöskata");
	    orchis::assert_eq(spp.find("björktrast"),
			      spp.find("snöskata"));
	}

	void order(TC)
	{
	    const Taxa spp = test_lom("storlom (Gavia arctica)\n"
				      "björktrast\n");
	    orchis::assert_lt(spp.find("storlom"), spp.find("björktrast"));
	    orchis::assert_lt(spp.find("Gavia arctica"), spp.find("björktrast"));
	    orchis::assert_true(!(spp.find("björktrast") < spp.find("storlom")));
	}
    }
}
