#ifndef PADDING_H_INCLUDED
#define PADDING_H_INCLUDED

#include<limits>
#include "scene.h"

//macro definition
#define debug false





//***********************************************************************************
//-----------------------------------------------------------------------------------
//-------------------------Quelques fonctions utiles---------------------------------
//-----------------------------------------------------------------------------------
//***********************************************************************************






//----------------------deux types de fonctions "signes"--------------------------------
//Renvoit 0 si |x|<EPSILON^2, 1 si x>EPSILON^2 et -1 sinon
int sign(const double &x);
//Renvoit -1 si x<0 et 0 sinon
int sign0(const double &x);


//compter le nombre total de changement de signes (strict) entre d'une part x1 et x2
// et d'autre part y1 et y2
int nb_change_sign(const double &x1,const double &x2, const double &y1, const double &y2);


//renvoit les solutions de l'équation en x : a*x^2+b*x+c=0
vector<double> trinome(const double &a, const double &b, const double &c);


//Renvoit la distance entre le polygone p et le point pt
//le polygone p étant considéré comme l'ensemble des points de ses arêtes
//Si le polygone est vide : la fonction renvoit "l'infini"
double distance_pt_polygone(const polygone &p, const sommet &pt);


//Renvoit la distance entre le segment "seg" et le point "pt"
double distance_pt_segment( const segment &seg, const sommet &pt);


//Renvoit la distance entre le segment "seg" et le point "pt" si la projection
//du point "pt" sur la droite support du segment appartient au segment
//Sinon la fonction renvoit "l'infini"
double distance_tronquee_pt_segment(const segment &seg, const sommet &pt);


//Passage par référence : "res"n reçoit le point d'intersection entre la
//droite (so,v0) [passant par le point s0 dirigée par le vecteur v0] et la droite(s1, v1)
//Renvoit true si les deux droites s'intersectent et false sinon.
bool inter_droites(const sommet &s0, const vecteur &v0, const sommet &s1,const vecteur &v1, sommet &res);


//Passage par référence : "res" reçoit le point d'intersection entre la
//droite (s,v) [passant par le point s dirigée par le vecteur v] et
//le cercle de centre c et de rayon r
//Renvoit true si les deux droites s'intersectent et false sinon.
bool inter_droite_cercle(const sommet &s, const vecteur &v, const sommet &c, const double &r, vector<sommet> &res);


//Passage par référence : "res" reçoit le point d'intersection entre les
//deux cercles de centre respectif c0 et c1 et de rayon respectif r1
//Renvoit true si les deux cercles s'intersectent et false sinon.
bool inter_cercles(const sommet &c0, const double &r0, const sommet &c1, const double &r1, vector<sommet> &res);


//Renvoit true si le point S est à l'intérieur du padding du polygone P
//pour l'objet rectangulaire décrit par (el,eL)
bool in_padding(const polygone &p,const sommet &pt, const vecteur &el, const vecteur &eL);









//***********************************************************************************
//-----------------------------------------------------------------------------------
//----------------------------------PADDING------------------------------------------
//--------------------les fonctions pour la création du padding----------------------
//***********************************************************************************



//padding_simple prend en argument un polygone P et un double r.
//Elle renvoit le nouveau polygone "pad" avec une couche de padding construit selon le principe suivant:
//a chaque sommet on fait correspondre le point a la distance r du sommet dans la direction "somme des
// deux normales extérieurs des côtés adjacents"
polygone padding_simple(const polygone &P, const double &r=1);


//----------------Padding : fonctions pour les objets circulaires------------------

//La fonction padding_ sommet prend en argument :
//      - un polygone P
//      - les deux sommets seg1 et seg2 (adjacents au sommet autour duquel on va tracer la padding)
//      - un vctor<sommet> pour mettre les points du padding en construction
//      - le rayon "r" de l'objet épaisseur du padding) et
//      - éventuellement un entier n qui correspond au nombre de points pour approximer un arc de cercle à chaque sommet sortant du polygone
// La fonction complete le vecteur de sommet "tab" en y mettant les nouveaux points du padding associés au commet adjacent à seg1 et seg2
// Elle retourne true si le padding a bien été construit
bool padding_sommet(const polygone &P, const segment &seg1, const segment &seg2,vector<sommet> &tab, const double &r, const unsigned int n=8);


//PADDING pour un objet circulaire  de rayon r
//La fonction padding_cercle prend en argument un polygone "P", le rayon "r" de l'objet
//(épaisseur du padding) et éventuellement un entier n qui correspond au nombre de points
//utilisés pour approximer un arc de cercle à chaque sommet sortant du polygone.
//Elle renvoit le nouveau polygone "pad" avec une couche de padding
polygone padding_cercle(const polygone &P, const double &r, const unsigned int n=8);


//----------------Padding : fonctions pour les objets rectangulaires-----------------

//La fonction padding_ sommet_rectangle prend en argument :
//      - un polygone P
//      - les deux sommets seg1 et seg2 (adjacents au sommet autour duquel on va tracer la padding)
//      - un vctor<sommet> pour mettre les points du padding en construction
//      - les deux vecteur el et eL décrivant l'objet rectangulaire
// La fonction complete le vecteur de sommet "tab" en y mettant les nouveaux points du padding associés au commet adjacent à seg1 et seg2
// Elle retourne true si le padding a bien été construit
bool padding_sommet_rectangle(const polygone &P, const segment &seg1, const segment &seg2, vector<sommet> &tab, const vecteur &el, const vecteur &eL);

//PADDING pour un objet rectangulaire décrit par les deux vecteur el et eL
//La fonction padding_recatngle prend en argument un polygone "P" et les
//deux vecteur el et eL décrivant l'objet.
//Elle renvoit le nouveau polygone "pad" avec une couche de padding
// Attention : pour les polygones non convexes, l'objet ne doit pas être trop grand
polygone  padding_rectangle(const polygone &P, const vecteur &el, const vecteur &eL);

#endif // PADDING_H_INCLUDED
