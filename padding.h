#ifndef PADDING_H_INCLUDED
#define PADDING_H_INCLUDED

#include<limits>
#include<cmath>

#include "scene.h"

#define debug true

//quelques fonctions utiles
int sign(const double& x);
int sign0(const double& x);
int nb_change_sign(const double& x1,const double& x2, const double& y1, const double& y2);
//résolution de l'équation en x a*x^2+b*x+c=0
vector<double> trinome(const double& a, const double& b, const double& c);
//calcul la distance entre le segment seg et le point pt
double distance_pt_segment(const segment& seg, const sommet& pt);
//calcul la distance entre le segment et le point pt si pt est à la vertical du sommet
double distance_tronquee_pt_segment(const segment& seg, const sommet& pt);
double distance_pt_polygone(const polygone& p, const sommet& pt);
sommet inter_droites(const sommet& s0, const vecteur& v0, const sommet& s1,const vecteur& v1);
//intersection entre la doite passant par le point s0 de vecteur directeur
//v ( d'équation paramétrique t->s0+t*v) et le cercle de centre c et de rayon r.
// La fonction "inter_droite_cercle" renvoit les deux points d'intersection s'ils existent.
vector<sommet> inter_droite_cercle(const sommet& s0, const vecteur& v, const sommet& c, const double& r);
//intersection entre deux cercles, la fonction renvoit les deux points d'intersection s'ils existent
vector<sommet> inter_cercles(const sommet& c1, const double r1, const sommet& c2, const double r2);
//permet de savoir si le point S est dans le padding du polygone P
int in_padding(const polygone& p,const sommet pt, const vecteur el, const vecteur eL);

//les fonctions pour la création du padding
polygone padding_simple(const polygone&  P, const double& r=1);
/*polygone arc_cercle(double angle=PI/2, double r=1,unsigned int n=8);
polygone arc_cercle_ext(double angle=PI/2, double r=1,unsigned int n=8);*/
void padding_sommet(const polygone &P, const segment & seg1, const segment & seg2,vector<sommet> & tab, const double & r, const unsigned int n=8);
void padding_sommet_rectangle(const polygone& P, const segment& seg1, const segment& seg2, vector<sommet> & tab, const vecteur& el, const vecteur& eL);
polygone padding_cercle(const polygone&  P, const double& r, const unsigned int n=8);
polygone  padding_rectangle(const polygone& P, const vecteur& el, const vecteur& eL);

#endif // PADDING_H_INCLUDED
