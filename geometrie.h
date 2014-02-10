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
#include <math.h>

const double PI= 3.1415926;

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
vecteur rotation_d2 (const vecteur& v, double theta);


class segment {
    public :
    sommet S1,S2;
    vecteur n;
    segment(const sommet& s1,const sommet& s2);
// AFFICHAGE
    friend std::ostream& operator <<(std::ostream &,const segment &);
};


#endif /* defined(__Projet_Xcode___Planification_de_trajectoire__geometrie__) */
