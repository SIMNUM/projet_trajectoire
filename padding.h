#ifndef PADDING_H_INCLUDED
#define PADDING_H_INCLUDED

#include "scene.h"

#define debug false

polygone padding_simple(const polygone&  P, double r=1);
/*polygone arc_cercle(double angle=PI/2, double r=1,unsigned int n=8);
polygone arc_cercle_ext(double angle=PI/2, double r=1,unsigned int n=8);*/
void padding_sommet(segment seg1, segment seg2, vector<sommet> & tab, double r, unsigned int n=8);
polygone padding_cercle(const polygone&  P, double r, unsigned int n=8);

#endif // PADDING_H_INCLUDED
