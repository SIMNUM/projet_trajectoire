//
//  geometrie.h
//  Projet Xcode : Planification de trajectoire
//
//  Created by Emmanuel JAY on 07/02/2014.
//  Copyright (c) 2014 Emmanuel JAY. All rights reserved.
//

#ifndef __Projet_Xcode___Planification_de_trajectoire__geometrie__
#define __Projet_Xcode___Planification_de_trajectoire__geometrie__

#include <iostream>
#include <cmath>


const double PI= 3.141592653589793238462643383279;
const double EPSILON = 1.e-12;

class vecteur;
typedef vecteur sommet;

class vecteur {
    public :
    int dim;
    double* pts;
// CONSTRUCTEURS
    vecteur(); // Point de dimension 2 par défaut nul
    vecteur(double x);
    vecteur(double x,double y);
    vecteur(double x,double y,double z);
    vecteur(const vecteur& s);
    vecteur(const sommet& v1,const sommet& v2);
    vecteur& operator= (const vecteur& s);
// AFFICHAGE
    friend std::ostream& operator <<(std::ostream &,const vecteur &);
    void print();
// ECRITURE
    void print_fichier(std::ostream&) const;
// COMBINAISONS LINEAIRES
    vecteur & operator +=(const vecteur & v);
    vecteur & operator +=(const double);
    vecteur & operator -=(const vecteur & v);
    vecteur & operator -=(const double);
    vecteur & operator *=(const double);
    vecteur & operator /=(const double);
// ACCES
    double& operator ()(int i) {return pts[i-1];}
    double& operator [](int i) {return pts[i];}
    double operator ()(int i) const{return pts[i-1];}
    double operator [](int i) const{return pts[i];}
};


// FONCTIONS DE COMBINAISONS DE VECTEURS
bool operator==(const vecteur & a,const vecteur & b);
bool operator!=(const vecteur & a,const vecteur & b);
vecteur operator +(const vecteur &,const vecteur &);
vecteur operator +(const vecteur &,const double & lambda);
vecteur operator +(const double & lambda,const vecteur &);
vecteur operator -(const vecteur &,const vecteur &);
vecteur operator -(const vecteur &,const double & lambda);
vecteur operator -(const double & lambda,const vecteur &);
vecteur operator *(const vecteur &,const double & lambda);
vecteur operator *(const double & lambda,const vecteur &);
vecteur operator /(const vecteur &,const double & lambda);

// FONCTIONS EUCLIDIENNES
double ps ( const vecteur & ,const vecteur &);
double norm (const vecteur & v);
double det_d2(const vecteur & v1, const vecteur & v2);
double maxim(double,double);
vecteur rotation_d2 (const vecteur& v, double theta);
sommet translation (const vecteur& v, const sommet& s);
sommet dillatation (const sommet& centre, const sommet& s,double dill);


class segment {
    public :
    sommet S1,S2;
    vecteur n;
    segment(const sommet& s1=sommet(),const sommet& s2=sommet());
// AFFICHAGE
    friend std::ostream& operator <<(std::ostream &,const segment &);
// ECRITURE
    void print_fichier(std::ostream&) const;
};

double round_to_0 (double d ,double eps=EPSILON);


#endif /* defined(__Projet_Xcode___Planification_de_trajectoire__geometrie__) */
