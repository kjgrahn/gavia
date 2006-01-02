/*----*- c++ -*---------------------------------------------------------------
 *
 * $Id: bitmap.h,v 1.4 2006-01-02 22:15:25 grahn Exp $
 *
 * bitmap.h
 *
 * Jörgen Grahn
 * 1998-09-26, 2004
 *----------------------------------------------------------------------------
 *
 *----------------------------------------------------------------------------
 */

#include <cstdio>


class Bitmap
{
private:
    static const int BMAPNR = 200;
    unsigned char map[BMAPNR];

public:
    Bitmap() {
	for(int i=0; i!=sizeof(map); i++) map[i] = 0x00;
    }

    void set(int n) {
	map[n/8] |= (1<< (7 - (n%8)));
    }
    void clear(int n) {
	map[n/8] &= ~(1<< (7 - (n%8)));
    }
    bool isset(int n) const {
	return (map[n/8] >> (7-(n%8))) & 1;
    }

    int count() const;

    int size() const { return BMAPNR * 8; }

    int read(std::FILE * fp);
    int write(std::FILE * fp) const;
};
