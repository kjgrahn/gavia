/*----------------------------------------------------------------------------
 *
 * $Id: bitmap.h,v 1.1 1999-10-24 08:10:52 grahn Exp $
 *
 * bitmap.h
 *
 * Jörgen Grahn <jorgen.grahn@opensoftware.se>
 * 1998-09-26
 *----------------------------------------------------------------------------
 *
 *----------------------------------------------------------------------------
 */

#ifdef __cplusplus
extern "C" {
#endif

#define BMAPNR (200)


typedef struct
{
    unsigned char map[BMAPNR];

} Bitmap;


void bitmapcreate(Bitmap *);
void bitmapdestroy(Bitmap *);

int bitmapread(Bitmap *, FILE *);
int bitmapwrite(Bitmap *, FILE *);

void bitmapset(Bitmap *, int);
void bitmapclear(Bitmap *, int);
int bitmapisset(Bitmap *, int);
int bitmapcount(Bitmap *);

#ifdef __cplusplus
}
#endif
