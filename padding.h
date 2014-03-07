#ifndef PADDING_H_INCLUDED
#define PADDING_H_INCLUDED

#include<limits>

#include "scene.h"

#define debug false

//quelques fonctions utiles
int sign(double x);
int sign0(double x);
int nb_change_sign(double x1,double x2,double y1,double y2);
//calcul la distance entre le segment seg et le vecteur pt
double distance_pt_segment(segment seg, sommet pt);
double distance_pt_polygone(polygone p, sommet pt);

//les fonctions pour la création du padding
polygone padding_simple(const polygone&  P, double r=1);
/*polygone arc_cercle(double angle=PI/2, double r=1,unsigned int n=8);
polygone arc_cercle_ext(double angle=PI/2, double r=1,unsigned int n=8);*/
void padding_sommet(const polygone &P, segment seg1, segment seg2,vector<sommet> & tab, double r, unsigned int n=8);
void padding_sommet_rectangle(segment seg1, segment seg2, vector<sommet> & tab, vecteur el, vecteur eL);
polygone padding_cercle(const polygone&  P, double r, unsigned int n=8);
polygone  padding_rectangle(const polygone& P, vecteur el, vecteur eL);

#endif // PADDING_H_INCLUDED
